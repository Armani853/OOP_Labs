#include "../include/simulation.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>

using namespace std::chrono_literals;

Simulation::Simulation() : battle_logic_(cout_mutex_) {
    for (int i = 0; i < INITIAL_NPC_COUNT; ++i) {
        npcs_.push_back(factory_.create_random_npc(i + 1));
    }
    
    std::lock_guard<std::mutex> lock(cout_mutex_);
    std::cout << "Simulation initialized with " << npcs_.size() << " NPCs. Map size: " << MAP_SIZE << "x" << MAP_SIZE << std::endl;
}

Simulation::~Simulation() {
    stop();
}

void Simulation::start() {
    if (running_.exchange(true)) return;

    move_thread_ = std::thread([this] { move_and_detect_thread_func(); });

    battle_thread_ = std::thread([this] { battle_thread_func(); });

    main_thread_ = std::thread([this] { main_print_thread_func(); });
}

void Simulation::stop() {
    bool was_running = running_.exchange(false);
    if (!was_running) return;

    queue_cv_.notify_all();
    
    if (main_thread_.joinable()) {
        main_thread_.join();
    }
    if (move_thread_.joinable()) {
        move_thread_.join();
    }
    if (battle_thread_.joinable()) {
        battle_thread_.join();
    }
    
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        battle_queue_.clear();
    }
}
void Simulation::print_survivors() const {
    std::shared_lock<std::shared_mutex> lock(npcs_mutex_); 
    std::lock_guard<std::mutex> cout_lock(cout_mutex_);

    size_t count = 0;
    std::cout << "\n--- Final Survivors ---\n";
    for (const auto& npc : npcs_) {
        if (npc->is_alive()) {
            int x, y;
            npc->get_position(x, y);
            std::cout << "[" << npc->get_symbol() << "] " << npc->get_name() 
                      << " at (" << x << ", " << y << ")" << std::endl;
            count++;
        }
    }
    std::cout << "Total survivors: " << count << std::endl;
    std::cout << "-----------------------\n";
}

void Simulation::move_and_detect_thread_func() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-1, 1);

    while (running_.load()) {
        std::shared_lock<std::shared_mutex> read_lock(npcs_mutex_);
        
        for (const auto& npc : npcs_) {
            if (npc->is_alive()) {
                int move_dist = npc->get_stats().move_distance;
                int dx = dist(gen) * move_dist / 2;
                int dy = dist(gen) * move_dist / 2;
                npc->move(dx, dy);
            }
        }
        
        for (size_t i = 0; i < npcs_.size(); ++i) {
            for (size_t j = i + 1; j < npcs_.size(); ++j) {
                auto npc1 = npcs_[i];
                auto npc2 = npcs_[j];

                if (!npc1->is_alive() || !npc2->is_alive()) continue;

                int kill_dist_sq = std::max(npc1->get_stats().kill_distance, npc2->get_stats().kill_distance);
                kill_dist_sq *= kill_dist_sq;

                if (distance_sq(npc1, npc2) <= kill_dist_sq) {
                    {
                        std::lock_guard<std::mutex> queue_lock(queue_mutex_);
                        battle_queue_.push_back({npc1, npc2});
                    }
                    queue_cv_.notify_one();
                }
            }
        }
        
        read_lock.unlock();

        std::this_thread::sleep_for(100ms); 
    }
}

void Simulation::battle_thread_func() {
    while (running_.load()) {
        BattleTask task;
        {
            std::unique_lock<std::mutex> queue_lock(queue_mutex_);
            queue_cv_.wait(queue_lock, [this] { return !battle_queue_.empty() || !running_.load(); });
            
            if (!running_.load() && battle_queue_.empty()) break;

            task = battle_queue_.front();
            battle_queue_.erase(battle_queue_.begin());
        }

        battle_logic_.start_battle(task.npc1, task.npc2);
        
        {
            std::lock_guard<std::shared_mutex> write_lock(npcs_mutex_);
            npcs_.erase(std::remove_if(npcs_.begin(), npcs_.end(), 
                                       [](const auto& npc) { return !npc->is_alive(); }), 
                                       npcs_.end());
        }
    }
}

void Simulation::main_print_thread_func() {
    auto start_time = std::chrono::high_resolution_clock::now();
    auto end_time = start_time + SIMULATION_DURATION_SEC * 1s;

    while (running_.load() && std::chrono::high_resolution_clock::now() < end_time) {
        std::shared_lock<std::shared_mutex> read_lock(npcs_mutex_);
        
        std::lock_guard<std::mutex> cout_lock(cout_mutex_); 

        std::cout << "\033[2J\033[1;1H"; 

        std::cout << "--- Map Status (" << std::time(nullptr) << ") ---" << std::endl;
        std::cout << "Remaining time: " << SIMULATION_DURATION_SEC - (std::chrono::high_resolution_clock::now() - start_time) / 1s << "s" << std::endl;
        
        std::vector<std::vector<char>> map_grid(MAP_SIZE / 10 + 1, std::vector<char>(MAP_SIZE / 10 + 1, '.'));
        
        int alive_count = 0;
        for (const auto& npc : npcs_) {
            if (npc->is_alive()) {
                int x, y;
                npc->get_position(x, y);
                
                int grid_x = x / (MAP_SIZE / 10);
                int grid_y = y / (MAP_SIZE / 10);
                
                if (map_grid[grid_y][grid_x] == '.') {
                    map_grid[grid_y][grid_x] = npc->get_symbol();
                } else {
                    map_grid[grid_y][grid_x] = '*';
                }
                alive_count++;
            }
        }
        
        for (int y = 0; y < map_grid.size(); ++y) {
            for (int x = 0; x < map_grid[y].size(); ++x) {
                std::cout << map_grid[y][x] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "Alive NPCs: " << alive_count << std::endl;
        std::cout << "--------------------------------\n";
        
        read_lock.unlock();
        
        std::this_thread::sleep_for(1s);
    }
    
    {
        std::lock_guard<std::mutex> cout_lock(cout_mutex_);
        std::cout << "Simulation time expired. Stopping threads." << std::endl;
    }
}
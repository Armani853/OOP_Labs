#include "include/simulation.h"
#include <iostream>
#include <cstdlib>

int main() {
    std::ios_base::sync_with_stdio(false);
    Simulation sim;
    
    try {
        sim.start();
        
        std::this_thread::sleep_for(std::chrono::seconds(SIMULATION_DURATION_SEC + 2));
        
        sim.stop();
        
    } catch (const std::exception& e) {
        std::cerr << "CRITICAL ERROR in simulation: " << e.what() << std::endl;
        sim.stop();
        return EXIT_FAILURE;
    }
    
    sim.print_survivors(); 
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    return EXIT_SUCCESS;
}
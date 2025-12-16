#include "gtest/gtest.h"
#include "../include/npc.h" 
#include "../include/npc_factory.h"
#include "../include/battle_logic.h"

using std::shared_ptr;
using std::make_shared;
using std::to_string;

std::mutex g_test_mutex; 

std::string make_name(const std::string& type, int id) {
    return type + "_" + to_string(id);
}


TEST(NPCTest, InitialPositionAndAliveStatus) {
    auto knight = make_shared<Knight>(make_name("Knight", 1), 10, 20); 
    int x, y;
    knight->get_position(x, y);
    EXPECT_EQ(x, 10);
    EXPECT_EQ(y, 20);
    EXPECT_TRUE(knight->is_alive());
}

TEST(NPCTest, MoveWithinBounds) {
    auto elf = make_shared<Elf>(make_name("Elf", 2), 50, 50); 
    elf->move(10, -5); 
    int x, y;
    elf->get_position(x, y);
    EXPECT_EQ(x, 60);
    EXPECT_EQ(y, 45);
}

TEST(NPCTest, MoveClampingToBounds) {
    auto dragon = make_shared<Dragon>(make_name("Dragon", 3), 5, 5); 
    dragon->move(-100, 1000); 
    int x, y;
    dragon->get_position(x, y);
    
    EXPECT_EQ(x, 0); 
    EXPECT_EQ(y, MAP_SIZE); 
}



TEST(BattleLogicTest, DragonKillsDragonRule) {
    BattleLogic logic(g_test_mutex);
    auto dragon1 = make_shared<Dragon>(make_name("Dragon", 10), 0, 0);
    auto dragon2 = make_shared<Dragon>(make_name("Dragon", 11), 0, 0);

    logic.start_battle(dragon1, dragon2);
    
    EXPECT_TRUE(dragon1->is_alive() || !dragon2->is_alive()); 
}

TEST(BattleLogicTest, ElfKillsKnightRule) {
    BattleLogic logic(g_test_mutex);
    auto elf = make_shared<Elf>(make_name("Elf", 30), 0, 0);
    auto knight = make_shared<Knight>(make_name("Knight", 31), 0, 0);
    
    logic.start_battle(elf, knight);
    
    EXPECT_TRUE(elf->is_alive()); 
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
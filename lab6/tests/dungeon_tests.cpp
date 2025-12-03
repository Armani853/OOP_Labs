#include "gtest/gtest.h"
#include "../include/npc.h"
#include "../include/npc_factory.h"
#include "../include/battle_visitor.h"
#include "../include/dungeon_editor.h"
#include "../include/observer.h"
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

class MockObserver : public Observer {
public:
    std::vector<std::string> events;
    void update(const std::string& event) override {
        events.push_back(event);
    }
};


TEST(NPCTest, DistanceCalculation) {
    auto npc1 = std::make_shared<Knight>("K1", 0, 0);
    auto npc2 = std::make_shared<Elf>("E1", 3, 4); 
    auto npc3 = std::make_shared<Dragon>("D1", 10, 10);
    
    EXPECT_NEAR(NPC::distance(npc1, npc2), 5.0, 0.001);
    
    EXPECT_NEAR(NPC::distance(npc1, npc3), 14.142135, 0.001);

    EXPECT_NEAR(NPC::distance(npc1, npc1), 0.0, 0.001);
}

TEST(NPCFactoryTest, CreateValidNPC) {
    NPCFactory factory;
    auto knight = factory.create_npc("Knight", "Arthur", 50, 50);
    EXPECT_NE(knight, nullptr);
    EXPECT_EQ(knight->get_type(), "Knight");
    EXPECT_EQ(knight->get_name(), "Arthur");
    EXPECT_EQ(knight->get_x(), 50);
    EXPECT_EQ(knight->get_y(), 50);
    EXPECT_TRUE(knight->is_alive());
}

TEST(NPCFactoryTest, CreateInvalidType) {
    NPCFactory factory;
    auto unknown = factory.create_npc("Goblin", "Gobby", 10, 10);
    EXPECT_EQ(unknown, nullptr);
}

TEST(NPCFactoryTest, CoordinateValidation) {
    NPCFactory factory;
    EXPECT_NE(factory.create_npc("Elf", "Max", 500, 500), nullptr);
    EXPECT_NE(factory.create_npc("Dragon", "Min", 0, 0), nullptr);
    
    EXPECT_EQ(factory.create_npc("Knight", "OutX", 501, 100), nullptr);
    EXPECT_EQ(factory.create_npc("Knight", "OutY", 100, -1), nullptr);
}

TEST(NPCFactoryTest, CreateFromFileString) {
    NPCFactory factory;
    std::string file_string = "Elf|Legolas|150|200";
    auto elf = factory.create_npc_from_file_string(file_string);
    
    EXPECT_NE(elf, nullptr);
    EXPECT_EQ(elf->get_type(), "Elf");
    EXPECT_EQ(elf->get_name(), "Legolas");
    EXPECT_EQ(elf->get_x(), 150);
    EXPECT_EQ(elf->get_y(), 200);
}

TEST(NPCFactoryTest, CreateFromFileInvalidFormat) {
    NPCFactory factory;
    EXPECT_EQ(factory.create_npc_from_file_string("Knight|Wrong|100"), nullptr);
    EXPECT_EQ(factory.create_npc_from_file_string("Goblin|Gobby|10|10"), nullptr);
}

class BattleTest : public ::testing::Test {
protected:
    BattleVisitor visitor;
    std::shared_ptr<MockObserver> mock_obs = std::make_shared<MockObserver>();

    void SetUp() override {
        visitor.add_observer(mock_obs);
    }
    
    template <typename T>
    std::shared_ptr<T> create_npc(const std::string& name, int x, int y) {
        return std::make_shared<T>(name, x, y);
    }
};

TEST_F(BattleTest, KnightVsDragon_MutualKill) {
    auto knight = create_npc<Knight>("K", 10, 10);
    auto dragon = create_npc<Dragon>("D", 10, 10);

    knight->accept(visitor, dragon); 

    EXPECT_FALSE(dragon->is_alive());
    EXPECT_FALSE(knight->is_alive());
    
    ASSERT_EQ(mock_obs->events.size(), 2);
    EXPECT_EQ(mock_obs->events[0], "Knight (K) killed Dragon (D)");
    EXPECT_EQ(mock_obs->events[1], "Dragon (D) killed Knight (K)");
}

TEST_F(BattleTest, ElfVsKnight_ElfWins) {
    auto elf = create_npc<Elf>("E", 10, 10);
    auto knight = create_npc<Knight>("K", 10, 10);

    elf->accept(visitor, knight);

    EXPECT_TRUE(elf->is_alive());
    EXPECT_FALSE(knight->is_alive());
    
    ASSERT_EQ(mock_obs->events.size(), 1);
    EXPECT_EQ(mock_obs->events[0], "Elf (E) killed Knight (K)");
}

TEST_F(BattleTest, DragonVsElf_DragonWins) {
    auto dragon = create_npc<Dragon>("D", 10, 10);
    auto elf = create_npc<Elf>("E", 10, 10);

    dragon->accept(visitor, elf); 

    EXPECT_FALSE(elf->is_alive());
    EXPECT_TRUE(dragon->is_alive());

    ASSERT_EQ(mock_obs->events.size(), 1);
    EXPECT_EQ(mock_obs->events[0], "Dragon (D) killed Elf (E)");
}

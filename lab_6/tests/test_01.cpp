#include <gtest/gtest.h>
#include "../include/BattleArena.h"
#include "../include/ork.h"
#include "../include/druids.h"
#include "../include/squirell.h"
#include "../include/ConsoleObserver.h"
#include "../include/FileObserver.h"

TEST(BattleArenaTests, CheckNPCName) {
    Arena arena(500, 500);
    arena.SpawnNPC("Ork", "OrkTest", 100, 100);

    const auto& npcs = arena.GetAllNPCsCopy();
    ASSERT_FALSE(npcs.empty());
    EXPECT_EQ(npcs[0]->getNpcName(), "OrkTest");
}

TEST(BattleArenaTests, SpawnIncreasesNPCCount) {
    Arena arena(500, 500);

    arena.SpawnNPC("Ork", "OrkTest", 100, 100);
    arena.SpawnNPC("Druid", "DruidTest", 200, 200);

    const auto& npcs = arena.GetAllNPCsCopy();
    EXPECT_EQ(npcs.size(), 2);
}


TEST(BattleArenaTests, VerifyNPCPosition) {
    Arena arena(500, 500);

    arena.SpawnNPC("Ork", "OrkTest", 150, 250);
    const auto& npcs = arena.GetAllNPCsCopy();

    ASSERT_FALSE(npcs.empty());
    std::pair<int, int> coord = npcs[0].get()->getCoordinates();
    int x = coord.first;
    int y = coord.second;
    EXPECT_EQ(x, 150);
    EXPECT_EQ(y, 250);
}

TEST(BattleArenaTests, SpawnOutOfBounds) {
    Arena arena(500, 500);

    EXPECT_THROW(arena.SpawnNPC("Ork", "OutOfBoundsTest", 600, 600), std::out_of_range);
}

TEST(BattleArenaTests, RemoveNPC) {
    Arena arena(500, 500);

    arena.SpawnNPC("Ork", "OrkTest", 100, 100);
    arena.SpawnNPC("Druid", "DruidTest", 200, 200);

    const auto& npcs = arena.GetAllNPCsCopy();
    ASSERT_EQ(npcs.size(), 2);

    arena.RemoveNPC("OrkTest");
    const auto& npcs_2 = arena.GetAllNPCsCopy(); 
    EXPECT_EQ(npcs_2.size(), 1);
    EXPECT_EQ(npcs_2[0]->getNpcName(), "DruidTest");
}
TEST(BattleArenaTests, RemoveNPCSingle) {
    Arena arena(500, 500);
    arena.SpawnNPC("Ork", "OrkTest", 100, 100);

    EXPECT_EQ(arena.GetAllNPCsCopy().size(), 1);

    arena.RemoveNPC("OrkTest");
    EXPECT_EQ(arena.GetAllNPCsCopy().size(), 0);
}

TEST(BattleArenaTests, RemoveNPCMultiple) {
    Arena arena(500, 500);
    arena.SpawnNPC("Ork", "OrkTest", 100, 100);
    arena.SpawnNPC("Druid", "DruidTest", 200, 200);

    EXPECT_EQ(arena.GetAllNPCsCopy().size(), 2);

    arena.RemoveNPC("OrkTest");
    EXPECT_EQ(arena.GetAllNPCsCopy().size(), 1);

    std::vector<std::unique_ptr<NPC>> npcs = arena.GetAllNPCsCopy();
    EXPECT_EQ(npcs[0]->getNpcName(), "DruidTest");
}

TEST(BattleArenaTests, SpawnDuplicateNPCNames) {
    Arena arena(500, 500);
    arena.SpawnNPC("Ork", "Duplicate", 100, 100);
    EXPECT_THROW(arena.SpawnNPC("Druid", "Duplicate", 200, 200), std::invalid_argument);
}

TEST(BattleArenaTests, TestConsoleObserver) {
    Arena arena(10, 10);
    auto observer = std::make_shared<ConsoleObserver>();
    arena.AddObserver(observer);
    EXPECT_EQ(arena.getSizeObservers(), 1);
}


TEST(BattleArenaTests, TestFileObserver) {
    Arena arena(10, 10);
    auto observer = std::make_shared<FileObserver>();
    arena.AddObserver(observer);
    EXPECT_EQ(arena.getSizeObservers(), 1);
}

TEST(BattleArenaTests, TestAddNPC) {
    Arena arena(10, 10);
    auto npc = std::make_unique<Ork>("NPC1", 0, 0);
    arena.AddNPC(std::move(npc));
    EXPECT_EQ(arena.GetAllNPCsCopy().size(), 1);
}

TEST(BattleArenaTests, TestCheckForDuplicate) {
    Arena arena(10, 10);

    auto npc1 = std::make_unique<Ork>("NPC1", 0, 0);
    auto npc2 = std::make_unique<Ork>("NPC2", 0, 0);

    arena.AddNPC(std::move(npc1));
    EXPECT_FALSE(arena.CheckForDuplicate("NPC2", 0, 0));
    EXPECT_TRUE(arena.CheckForDuplicate("NPC2", 1, 1));
}

TEST(BattleArenaTests, StarterBattleWithoutNPCs){
    Arena arena(10, 10);
    EXPECT_NO_THROW(arena.ToStartBattle(5));
}

TEST(BattleArenaTests, StarterBattleWithoutNPCsWrongRange){
    Arena arena(10, 10);
    EXPECT_THROW(arena.ToStartBattle(15), std::out_of_range);
}

TEST(BattleArenaTests, FileSaverTest){
    Arena arena(500, 500);
    arena.SpawnNPC("Ork", "OrkTest", 100, 100);
    arena.SpawnNPC("Druid", "DruidTest", 200, 200);
    std::string filename = "npcs_text.txt";
    EXPECT_NO_THROW(arena.SaveToFile(filename));
}

TEST(BattleArenaTests, SpawnerWithRandomCoordinates){
    Arena arena(500, 500);
    arena.SpawnNPC("Ork", "OrkTest");
    arena.SpawnNPC("Druid", "DruidTest");
    EXPECT_EQ(arena.GetAllNPCsCopy().size(), 2);
}
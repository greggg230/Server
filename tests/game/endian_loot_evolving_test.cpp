#include <gtest/gtest.h>
#include "common/net/endian.h"
#include "common/loot.h"
#include "common/evolving_items.h"

#include <cstdint>
#include <string>

// ============================================================
// EQ::Net::IsLittleEndian
// ============================================================
TEST(EndianTest, IsLittleEndianConsistent) {
    EXPECT_EQ(EQ::Net::IsLittleEndian(), EQ::Net::IsLittleEndian());
}

TEST(EndianTest, HostIsLittleEndian) {
    // Test server is x86_64 Linux — always little endian
    EXPECT_TRUE(EQ::Net::IsLittleEndian());
}

TEST(EndianTest, HostToNetworkIsSwapOnLittleEndian) {
    // On little endian host, HostToNetwork byte-swaps
    uint32_t v = 0x12345678u;
    EXPECT_EQ(EQ::Net::HostToNetwork(v), uint32_t{0x78563412u});
}

// ============================================================
// LootItem struct
// ============================================================
TEST(LootItemTest, DefaultInitOrnamentFieldsAreZero) {
    LootItem item{};
    EXPECT_EQ(item.ornamenticon,        0u);
    EXPECT_EQ(item.ornamentidfile,      0u);
    EXPECT_EQ(item.ornament_hero_model, 0u);
}

TEST(LootItemTest, FieldsReadWrite) {
    LootItem item{};
    item.item_id     = 1001u;
    item.charges     = 5u;
    item.lootslot    = 3u;
    item.attuned     = true;
    item.custom_data = "custom";
    EXPECT_EQ(item.item_id,  1001u);
    EXPECT_EQ(item.charges,  5u);
    EXPECT_EQ(item.lootslot, 3u);
    EXPECT_TRUE(item.attuned);
    EXPECT_EQ(item.custom_data, "custom");
}

TEST(LootItemTest, DefaultCustomDataIsEmpty) {
    LootItem item{};
    EXPECT_TRUE(item.custom_data.empty());
}

TEST(LootItemTest, TrivialLevelFieldsReadWrite) {
    LootItem item{};
    item.trivial_min_level = 10u;
    item.trivial_max_level = 50u;
    item.npc_min_level     = 1u;
    item.npc_max_level     = 60u;
    EXPECT_EQ(item.trivial_min_level, 10u);
    EXPECT_EQ(item.trivial_max_level, 50u);
    EXPECT_EQ(item.npc_min_level,      1u);
    EXPECT_EQ(item.npc_max_level,     60u);
}

TEST(LootItemTest, LootDropIdReadWrite) {
    LootItem item{};
    item.lootdrop_id = 999u;
    EXPECT_EQ(item.lootdrop_id, 999u);
}

// ============================================================
// EvolvingItems constants
// ============================================================
TEST(EvolvingItemsActionsTest, UpdateItemsIsZero) {
    EXPECT_EQ(EvolvingItems::Actions::UPDATE_ITEMS, 0);
}

TEST(EvolvingItemsActionsTest, SequentialValues) {
    EXPECT_EQ(EvolvingItems::Actions::TRANSFER_WINDOW_OPEN,    1);
    EXPECT_EQ(EvolvingItems::Actions::TRANSFER_WINDOW_DETAILS, 2);
    EXPECT_EQ(EvolvingItems::Actions::TRANSFER_XP,             3);
    EXPECT_EQ(EvolvingItems::Actions::FINAL_RESULT,            4);
}

TEST(EvolvingItemsTypesTest, AmountOfExpIsOne) {
    EXPECT_EQ(EvolvingItems::Types::AMOUNT_OF_EXP, 1);
}

TEST(EvolvingItemsTypesTest, SequentialValues) {
    EXPECT_EQ(EvolvingItems::Types::NUMBER_OF_KILLS,   2);
    EXPECT_EQ(EvolvingItems::Types::SPECIFIC_MOB_RACE, 3);
    EXPECT_EQ(EvolvingItems::Types::SPECIFIC_ZONE_ID,  4);
}

TEST(EvolvingItemsSubTypesTest, AllExpIsZero) {
    EXPECT_EQ(EvolvingItems::SubTypes::ALL_EXP, 0);
}

TEST(EvolvingItemsSubTypesTest, SequentialValues) {
    EXPECT_EQ(EvolvingItems::SubTypes::SOLO_EXP,  1);
    EXPECT_EQ(EvolvingItems::SubTypes::GROUP_EXP, 2);
    EXPECT_EQ(EvolvingItems::SubTypes::RAID_EXP,  3);
}

#include <gtest/gtest.h>
#include "common/emu_limits.h"

// ============================================================
// EntityLimits — sentinel and trade-size constants for each
// entity category. IINVALID=-1, INULL=0 are universal across
// all namespaces; TRADE_SIZE varies by type.
// ============================================================

// --- NPC ---
TEST(EntityLimitsNPCTest, IInvalidIsNegativeOne) {
    int16 v = EntityLimits::NPC::IINVALID;
    EXPECT_EQ(v, -1);
}

TEST(EntityLimitsNPCTest, INullIsZero) {
    int16 v = EntityLimits::NPC::INULL;
    EXPECT_EQ(v, 0);
}

TEST(EntityLimitsNPCTest, TradeSizeIsFour) {
    int16 v = EntityLimits::NPC::invtype::TRADE_SIZE;
    EXPECT_EQ(v, 4);
}

// --- NPCMerchant ---
TEST(EntityLimitsNPCMerchantTest, IInvalidIsNegativeOne) {
    int16 v = EntityLimits::NPCMerchant::IINVALID;
    EXPECT_EQ(v, -1);
}

TEST(EntityLimitsNPCMerchantTest, TradeSizeIsFour) {
    int16 v = EntityLimits::NPCMerchant::invtype::TRADE_SIZE;
    EXPECT_EQ(v, 4);
}

// --- Merc ---
TEST(EntityLimitsMercTest, IInvalidIsNegativeOne) {
    int16 v = EntityLimits::Merc::IINVALID;
    EXPECT_EQ(v, -1);
}

TEST(EntityLimitsMercTest, TradeSizeIsFour) {
    int16 v = EntityLimits::Merc::invtype::TRADE_SIZE;
    EXPECT_EQ(v, 4);
}

// --- Bot (has 8-slot trade and bitmasks) ---
TEST(EntityLimitsBotTest, IInvalidIsNegativeOne) {
    int16 v = EntityLimits::Bot::IINVALID;
    EXPECT_EQ(v, -1);
}

TEST(EntityLimitsBotTest, TradeSizeIsEight) {
    int16 v = EntityLimits::Bot::invtype::TRADE_SIZE;
    EXPECT_EQ(v, 8);
}

TEST(EntityLimitsBotTest, TradeSizeLargerThanNPC) {
    EXPECT_GT(EntityLimits::Bot::invtype::TRADE_SIZE,
              EntityLimits::NPC::invtype::TRADE_SIZE);
}

TEST(EntityLimitsBotTest, EquipmentBitmaskNonZero) {
    uint64 v = EntityLimits::Bot::invslot::EQUIPMENT_BITMASK;
    EXPECT_NE(v, 0u);
}

TEST(EntityLimitsBotTest, GeneralBitmaskIsZero) {
    uint64 v = EntityLimits::Bot::invslot::GENERAL_BITMASK;
    EXPECT_EQ(v, 0u);
}

TEST(EntityLimitsBotTest, CursorBitmaskIsZero) {
    uint64 v = EntityLimits::Bot::invslot::CURSOR_BITMASK;
    EXPECT_EQ(v, 0u);
}

TEST(EntityLimitsBotTest, PossessionsBitmaskEqualsEquipment) {
    // POSSESSIONS = EQUIPMENT | GENERAL | CURSOR; GENERAL and CURSOR are 0
    EXPECT_EQ(EntityLimits::Bot::invslot::POSSESSIONS_BITMASK,
              EntityLimits::Bot::invslot::EQUIPMENT_BITMASK);
}

// --- ClientPet ---
TEST(EntityLimitsClientPetTest, IInvalidIsNegativeOne) {
    int16 v = EntityLimits::ClientPet::IINVALID;
    EXPECT_EQ(v, -1);
}

TEST(EntityLimitsClientPetTest, TradeSizeIsFour) {
    int16 v = EntityLimits::ClientPet::invtype::TRADE_SIZE;
    EXPECT_EQ(v, 4);
}

// --- NPCPet ---
TEST(EntityLimitsNPCPetTest, IInvalidIsNegativeOne) {
    int16 v = EntityLimits::NPCPet::IINVALID;
    EXPECT_EQ(v, -1);
}

TEST(EntityLimitsNPCPetTest, TradeSizeIsFour) {
    int16 v = EntityLimits::NPCPet::invtype::TRADE_SIZE;
    EXPECT_EQ(v, 4);
}

// --- MercPet ---
TEST(EntityLimitsMercPetTest, TradeSizeIsFour) {
    int16 v = EntityLimits::MercPet::invtype::TRADE_SIZE;
    EXPECT_EQ(v, 4);
}

// --- BotPet ---
TEST(EntityLimitsBotPetTest, IInvalidIsNegativeOne) {
    int16 v = EntityLimits::BotPet::IINVALID;
    EXPECT_EQ(v, -1);
}

TEST(EntityLimitsBotPetTest, TradeSizeIsFour) {
    int16 v = EntityLimits::BotPet::invtype::TRADE_SIZE;
    EXPECT_EQ(v, 4);
}

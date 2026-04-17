#include <gtest/gtest.h>
#include "common/patches/rof2_limits.h"

TEST(RoF2SentinelTest, IInvalidIsNegativeOne) {
    int16 v = RoF2::IINVALID;
    EXPECT_EQ(v, -1);
}

TEST(RoF2SentinelTest, INullIsZero) {
    int16 v = RoF2::INULL;
    EXPECT_EQ(v, 0);
}

TEST(RoF2InventoryFlagsTest, ConcatenateInvTypeLimboIsFalse) {
    EXPECT_FALSE(RoF2::inventory::ConcatenateInvTypeLimbo);
}

TEST(RoF2InventoryFlagsTest, AllowOverLevelEquipmentIsTrue) {
    EXPECT_TRUE(RoF2::inventory::AllowOverLevelEquipment);
}

TEST(RoF2InventoryFlagsTest, AllowEmptyBagInBagIsTrue) {
    EXPECT_TRUE(RoF2::inventory::AllowEmptyBagInBag);
}

TEST(RoF2InvTypeSizeTest, PossessionsSizeIs34) {
    int16 v = RoF2::invtype::POSSESSIONS_SIZE;
    EXPECT_EQ(v, 34);
}

TEST(RoF2InvTypeSizeTest, BankSizeIs24) {
    int16 v = RoF2::invtype::BANK_SIZE;
    EXPECT_EQ(v, 24);
}

TEST(RoF2InvTypeSizeTest, SharedBankSizeIsTwo) {
    int16 v = RoF2::invtype::SHARED_BANK_SIZE;
    EXPECT_EQ(v, 2);
}

TEST(RoF2InvTypeSizeTest, TradeSizeIsEight) {
    int16 v = RoF2::invtype::TRADE_SIZE;
    EXPECT_EQ(v, 8);
}

TEST(RoF2InvTypeSizeTest, BazaarSizeIs200) {
    int16 v = RoF2::invtype::BAZAAR_SIZE;
    EXPECT_EQ(v, 200);
}

TEST(RoF2InvTypeSizeTest, MerchantSizeIs500) {
    int16 v = RoF2::invtype::MERCHANT_SIZE;
    EXPECT_EQ(v, 500);
}

TEST(RoF2InvTypeSizeTest, CorpseSizeEqualsPossessionsSize) {
    EXPECT_EQ(RoF2::invtype::CORPSE_SIZE, RoF2::invtype::POSSESSIONS_SIZE);
}

TEST(RoF2InvTypeSizeTest, TypeInvalidIsNegativeOne) {
    int16 v = RoF2::invtype::TYPE_INVALID;
    EXPECT_EQ(v, -1);
}

TEST(RoF2InvTypeSizeTest, TypeBeginIsPossessions) {
    EXPECT_EQ(RoF2::invtype::TYPE_BEGIN, RoF2::invtype::typePossessions);
}

TEST(RoF2InvSlotTest, CharmIsFirst) {
    int16 v = RoF2::invslot::slotCharm;
    EXPECT_EQ(v, 0);
}

TEST(RoF2InvSlotTest, SlotBeginIsZero) {
    int16 v = RoF2::invslot::SLOT_BEGIN;
    EXPECT_EQ(v, 0);
}

TEST(RoF2InvSlotTest, SlotInvalidIsNegativeOne) {
    int16 v = RoF2::invslot::SLOT_INVALID;
    EXPECT_EQ(v, -1);
}

TEST(RoF2InvSlotTest, BankBeginIs2000) {
    int16 v = RoF2::invslot::BANK_BEGIN;
    EXPECT_EQ(v, 2000);
}

TEST(RoF2InvSlotTest, BankEndIsBankBeginPlusSizeMinus1) {
    int16 expected = RoF2::invslot::BANK_BEGIN + RoF2::invtype::BANK_SIZE - 1;
    EXPECT_EQ(RoF2::invslot::BANK_END, expected);
}

TEST(RoF2InvSlotTest, SharedBankBeginIs2500) {
    int16 v = RoF2::invslot::SHARED_BANK_BEGIN;
    EXPECT_EQ(v, 2500);
}

TEST(RoF2InvSlotTest, TradeBeginIs3000) {
    int16 v = RoF2::invslot::TRADE_BEGIN;
    EXPECT_EQ(v, 3000);
}

TEST(RoF2InvSlotTest, WorldBeginIs4000) {
    int16 v = RoF2::invslot::WORLD_BEGIN;
    EXPECT_EQ(v, 4000);
}

TEST(RoF2InvSlotTest, TributeBeginIs400) {
    int16 v = RoF2::invslot::TRIBUTE_BEGIN;
    EXPECT_EQ(v, 400);
}

TEST(RoF2InvSlotTest, PossessionsCountIs34) {
    int16 v = RoF2::invslot::POSSESSIONS_COUNT;
    EXPECT_EQ(v, 34);
}

TEST(RoF2InvSlotTest, EquipmentCountIs23) {
    int16 v = RoF2::invslot::EQUIPMENT_COUNT;
    EXPECT_EQ(v, 23);
}

TEST(RoF2InvSlotTest, GeneralCountIs10) {
    int16 v = RoF2::invslot::GENERAL_COUNT;
    EXPECT_EQ(v, 10);
}

TEST(RoF2InvSlotTest, SlotTradeskillIs1000) {
    int16 v = RoF2::invslot::SLOT_TRADESKILL_EXPERIMENT_COMBINE;
    EXPECT_EQ(v, 1000);
}

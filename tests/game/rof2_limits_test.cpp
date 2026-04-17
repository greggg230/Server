#include <gtest/gtest.h>
#include "common/patches/rof2_limits.h"

// ============================================================
// RoF2 global sentinel values
// ============================================================
TEST(RoF2SentinelTest, IInvalidIsNegativeOne) {
    EXPECT_EQ(RoF2::IINVALID, -1);
}

TEST(RoF2SentinelTest, INullIsZero) {
    EXPECT_EQ(RoF2::INULL, 0);
}

// ============================================================
// RoF2::invtype — InventoryTypes enum (sequential from 0)
// ============================================================
TEST(RoF2InvTypeEnumTest, PossessionsIsZero) {
    EXPECT_EQ(RoF2::invtype::typePossessions, 0);
}

TEST(RoF2InvTypeEnumTest, BankIsOne) {
    EXPECT_EQ(RoF2::invtype::typeBank, 1);
}

TEST(RoF2InvTypeEnumTest, SharedBankIsTwo) {
    EXPECT_EQ(RoF2::invtype::typeSharedBank, 2);
}

TEST(RoF2InvTypeEnumTest, TradeIsThree) {
    EXPECT_EQ(RoF2::invtype::typeTrade, 3);
}

TEST(RoF2InvTypeEnumTest, WorldIsFour) {
    EXPECT_EQ(RoF2::invtype::typeWorld, 4);
}

TEST(RoF2InvTypeEnumTest, TypeBeginIsZero) {
    EXPECT_EQ(RoF2::invtype::TYPE_BEGIN, 0);
}

TEST(RoF2InvTypeEnumTest, TypeInvalidIsIInvalid) {
    EXPECT_EQ(RoF2::invtype::TYPE_INVALID, RoF2::IINVALID);
}

TEST(RoF2InvTypeEnumTest, TypeEndGreaterThanBegin) {
    EXPECT_GT(RoF2::invtype::TYPE_END, RoF2::invtype::TYPE_BEGIN);
}

TEST(RoF2InvTypeEnumTest, TypeCountIsConsistent) {
    int16 expected = (RoF2::invtype::TYPE_END - RoF2::invtype::TYPE_BEGIN) + 1;
    EXPECT_EQ(RoF2::invtype::TYPE_COUNT, expected);
}

// ============================================================
// RoF2::invtype — inventory size constants
// ============================================================
TEST(RoF2InvTypeSizeTest, PossessionsIs34) {
    EXPECT_EQ(RoF2::invtype::POSSESSIONS_SIZE, 34);
}

TEST(RoF2InvTypeSizeTest, BankIs24) {
    EXPECT_EQ(RoF2::invtype::BANK_SIZE, 24);
}

TEST(RoF2InvTypeSizeTest, SharedBankIs2) {
    EXPECT_EQ(RoF2::invtype::SHARED_BANK_SIZE, 2);
}

TEST(RoF2InvTypeSizeTest, TradeIs8) {
    EXPECT_EQ(RoF2::invtype::TRADE_SIZE, 8);
}

TEST(RoF2InvTypeSizeTest, WorldIs10) {
    EXPECT_EQ(RoF2::invtype::WORLD_SIZE, 10);
}

TEST(RoF2InvTypeSizeTest, MerchantIs500) {
    EXPECT_EQ(RoF2::invtype::MERCHANT_SIZE, 500);
}

TEST(RoF2InvTypeSizeTest, BazaarIs200) {
    EXPECT_EQ(RoF2::invtype::BAZAAR_SIZE, 200);
}

TEST(RoF2InvTypeSizeTest, CorpseSizeEqualsPossessions) {
    EXPECT_EQ(RoF2::invtype::CORPSE_SIZE, RoF2::invtype::POSSESSIONS_SIZE);
}

TEST(RoF2InvTypeSizeTest, TradeNPCSizeIs4) {
    EXPECT_EQ(RoF2::invtype::TRADE_NPC_SIZE, 4);
}

// ============================================================
// RoF2::invslot — equipment slot enum values
// ============================================================
TEST(RoF2InvSlotEnumTest, SlotCharmIsZero) {
    EXPECT_EQ(RoF2::invslot::slotCharm, 0);
}

TEST(RoF2InvSlotEnumTest, SlotEar1IsOne) {
    EXPECT_EQ(RoF2::invslot::slotEar1, 1);
}

TEST(RoF2InvSlotEnumTest, SlotPrimaryIs13) {
    EXPECT_EQ(RoF2::invslot::slotPrimary, 13);
}

TEST(RoF2InvSlotEnumTest, SlotSecondaryIs14) {
    EXPECT_EQ(RoF2::invslot::slotSecondary, 14);
}

TEST(RoF2InvSlotEnumTest, SlotAmmoIs22) {
    EXPECT_EQ(RoF2::invslot::slotAmmo, 22);
}

TEST(RoF2InvSlotEnumTest, SlotCursorIs33) {
    EXPECT_EQ(RoF2::invslot::slotCursor, 33);
}

// ============================================================
// RoF2::invslot — slot range constants
// ============================================================
TEST(RoF2InvSlotRangeTest, BankBeginIs2000) {
    EXPECT_EQ(RoF2::invslot::BANK_BEGIN, 2000);
}

TEST(RoF2InvSlotRangeTest, BankEndIsBankBeginPlusSizeMinus1) {
    EXPECT_EQ(RoF2::invslot::BANK_END, RoF2::invslot::BANK_BEGIN + RoF2::invtype::BANK_SIZE - 1);
}

TEST(RoF2InvSlotRangeTest, SharedBankBeginIs2500) {
    EXPECT_EQ(RoF2::invslot::SHARED_BANK_BEGIN, 2500);
}

TEST(RoF2InvSlotRangeTest, TradeBeginIs3000) {
    EXPECT_EQ(RoF2::invslot::TRADE_BEGIN, 3000);
}

TEST(RoF2InvSlotRangeTest, WorldBeginIs4000) {
    EXPECT_EQ(RoF2::invslot::WORLD_BEGIN, 4000);
}

TEST(RoF2InvSlotRangeTest, SlotInvalidIsNegativeOne) {
    EXPECT_EQ(RoF2::invslot::SLOT_INVALID, RoF2::IINVALID);
}

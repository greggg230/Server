#include <gtest/gtest.h>
#include "common/patches/sod_limits.h"

// ============================================================
// SoD global sentinel values
// ============================================================
TEST(SoDSentinelTest, IInvalidIsNegativeOne) {
    int16 v = SoD::IINVALID;
    EXPECT_EQ(v, -1);
}

TEST(SoDSentinelTest, INullIsZero) {
    int16 v = SoD::INULL;
    EXPECT_EQ(v, 0);
}

// ============================================================
// SoD::invtype — InventoryTypes enum
// ============================================================
TEST(SoDInvTypeEnumTest, PossessionsIsZero) {
    EXPECT_EQ(SoD::invtype::typePossessions, 0);
}

TEST(SoDInvTypeEnumTest, BankIsOne) {
    EXPECT_EQ(SoD::invtype::typeBank, 1);
}

TEST(SoDInvTypeEnumTest, SharedBankIsTwo) {
    EXPECT_EQ(SoD::invtype::typeSharedBank, 2);
}

TEST(SoDInvTypeEnumTest, TypeBeginIsZero) {
    int16 v = SoD::invtype::TYPE_BEGIN;
    EXPECT_EQ(v, 0);
}

TEST(SoDInvTypeEnumTest, TypeInvalidIsIInvalid) {
    int16 v = SoD::invtype::TYPE_INVALID;
    int16 inv = SoD::IINVALID;
    EXPECT_EQ(v, inv);
}

TEST(SoDInvTypeEnumTest, TypeEndGreaterThanBegin) {
    int16 end = SoD::invtype::TYPE_END;
    int16 begin = SoD::invtype::TYPE_BEGIN;
    EXPECT_GT(end, begin);
}

TEST(SoDInvTypeEnumTest, TypeCountIsConsistent) {
    int16 end = SoD::invtype::TYPE_END;
    int16 begin = SoD::invtype::TYPE_BEGIN;
    int16 count = SoD::invtype::TYPE_COUNT;
    EXPECT_EQ(count, (end - begin) + 1);
}

// ============================================================
// SoD::invtype — inventory size constants
// ============================================================
TEST(SoDInvTypeSizeTest, PossessionsIs32) {
    int16 v = SoD::invtype::POSSESSIONS_SIZE;
    EXPECT_EQ(v, 32);
}

TEST(SoDInvTypeSizeTest, BankIs24) {
    int16 v = SoD::invtype::BANK_SIZE;
    EXPECT_EQ(v, 24);
}

TEST(SoDInvTypeSizeTest, SharedBankIs2) {
    int16 v = SoD::invtype::SHARED_BANK_SIZE;
    EXPECT_EQ(v, 2);
}

TEST(SoDInvTypeSizeTest, TradeIs8) {
    int16 v = SoD::invtype::TRADE_SIZE;
    EXPECT_EQ(v, 8);
}

TEST(SoDInvTypeSizeTest, WorldIs10) {
    int16 v = SoD::invtype::WORLD_SIZE;
    EXPECT_EQ(v, 10);
}

TEST(SoDInvTypeSizeTest, MerchantIs80) {
    int16 v = SoD::invtype::MERCHANT_SIZE;
    EXPECT_EQ(v, 80);
}

TEST(SoDInvTypeSizeTest, BazaarIs80) {
    int16 v = SoD::invtype::BAZAAR_SIZE;
    EXPECT_EQ(v, 80);
}

TEST(SoDInvTypeSizeTest, CorpseSizeEqualsPossessions) {
    int16 corpse = SoD::invtype::CORPSE_SIZE;
    int16 poss = SoD::invtype::POSSESSIONS_SIZE;
    EXPECT_EQ(corpse, poss);
}

TEST(SoDInvTypeSizeTest, TradeNPCSizeIs4) {
    int16 v = SoD::invtype::TRADE_NPC_SIZE;
    EXPECT_EQ(v, 4);
}

// ============================================================
// SoD::invslot — equipment slot enum values
// ============================================================
TEST(SoDInvSlotEnumTest, SlotCharmIsZero) {
    EXPECT_EQ(SoD::invslot::slotCharm, 0);
}

TEST(SoDInvSlotEnumTest, SlotPrimaryIs13) {
    EXPECT_EQ(SoD::invslot::slotPrimary, 13);
}

TEST(SoDInvSlotEnumTest, SlotAmmoIs22) {
    EXPECT_EQ(SoD::invslot::slotAmmo, 22);
}

TEST(SoDInvSlotEnumTest, SlotCursorIs31) {
    EXPECT_EQ(SoD::invslot::slotCursor, 31);
}

// ============================================================
// SoD::invslot — slot range constants
// ============================================================
TEST(SoDInvSlotRangeTest, SlotInvalidIsNegativeOne) {
    int16 v = SoD::invslot::SLOT_INVALID;
    EXPECT_EQ(v, -1);
}

TEST(SoDInvSlotRangeTest, SlotBeginIsZero) {
    int16 v = SoD::invslot::SLOT_BEGIN;
    EXPECT_EQ(v, 0);
}

TEST(SoDInvSlotRangeTest, PossessionsCountIs32) {
    int16 count = SoD::invslot::POSSESSIONS_COUNT;
    EXPECT_EQ(count, 32);
}

TEST(SoDInvSlotRangeTest, EquipmentCountIs23) {
    int16 count = SoD::invslot::EQUIPMENT_COUNT;
    EXPECT_EQ(count, 23);
}

TEST(SoDInvSlotRangeTest, GeneralCountIs8) {
    int16 count = SoD::invslot::GENERAL_COUNT;
    EXPECT_EQ(count, 8);
}

TEST(SoDInvSlotRangeTest, BankBeginIs2000) {
    int16 v = SoD::invslot::BANK_BEGIN;
    EXPECT_EQ(v, 2000);
}

TEST(SoDInvSlotRangeTest, BankEndIsBankBeginPlusSizeMinus1) {
    int16 end = SoD::invslot::BANK_END;
    int16 begin = SoD::invslot::BANK_BEGIN;
    int16 size = SoD::invtype::BANK_SIZE;
    EXPECT_EQ(end, begin + size - 1);
}

TEST(SoDInvSlotRangeTest, SharedBankBeginIs2500) {
    int16 v = SoD::invslot::SHARED_BANK_BEGIN;
    EXPECT_EQ(v, 2500);
}

TEST(SoDInvSlotRangeTest, TradeBeginIs3000) {
    int16 v = SoD::invslot::TRADE_BEGIN;
    EXPECT_EQ(v, 3000);
}

TEST(SoDInvSlotRangeTest, WorldBeginIs4000) {
    int16 v = SoD::invslot::WORLD_BEGIN;
    EXPECT_EQ(v, 4000);
}

// ============================================================
// SoD::invbag — bag slot constants
// ============================================================
TEST(SoDInvBagTest, SlotBeginIsZero) {
    int16 v = SoD::invbag::SLOT_BEGIN;
    EXPECT_EQ(v, 0);
}

TEST(SoDInvBagTest, SlotEndIs9) {
    int16 v = SoD::invbag::SLOT_END;
    EXPECT_EQ(v, 9);
}

TEST(SoDInvBagTest, SlotCountIs10) {
    int16 v = SoD::invbag::SLOT_COUNT;
    EXPECT_EQ(v, 10);
}

TEST(SoDInvBagTest, SlotInvalidIsNegativeOne) {
    int16 v = SoD::invbag::SLOT_INVALID;
    EXPECT_EQ(v, -1);
}

// ============================================================
// SoD::invaug — augment socket constants (5 sockets, not 6)
// ============================================================
TEST(SoDInvAugTest, SocketBeginIsZero) {
    int16 v = SoD::invaug::SOCKET_BEGIN;
    EXPECT_EQ(v, 0);
}

TEST(SoDInvAugTest, SocketEndIs4) {
    int16 v = SoD::invaug::SOCKET_END;
    EXPECT_EQ(v, 4);
}

TEST(SoDInvAugTest, SocketCountIs5) {
    int16 v = SoD::invaug::SOCKET_COUNT;
    EXPECT_EQ(v, 5);
}

// ============================================================
// SoD::profile — profile size constants
// ============================================================
TEST(SoDProfileTest, BandoliersSizeIs20) {
    int16 v = SoD::profile::BANDOLIERS_SIZE;
    EXPECT_EQ(v, 20);
}

TEST(SoDProfileTest, BandolierItemCountIs4) {
    int16 v = SoD::profile::BANDOLIER_ITEM_COUNT;
    EXPECT_EQ(v, 4);
}

TEST(SoDProfileTest, PotionBeltSizeIs5) {
    int16 v = SoD::profile::POTION_BELT_SIZE;
    EXPECT_EQ(v, 5);
}

TEST(SoDProfileTest, SkillArraySizeIs100) {
    int16 v = SoD::profile::SKILL_ARRAY_SIZE;
    EXPECT_EQ(v, 100);
}

// ============================================================
// SoD::constants — character/spell constants
// ============================================================
TEST(SoDConstantsTest, CharacterCreationLimitIs12) {
    size_t v = SoD::constants::CHARACTER_CREATION_LIMIT;
    EXPECT_EQ(v, static_cast<size_t>(12));
}

TEST(SoDConstantsTest, SayLinkBodySizeIs50) {
    size_t v = SoD::constants::SAY_LINK_BODY_SIZE;
    EXPECT_EQ(v, static_cast<size_t>(50));
}

// ============================================================
// SoD::spells — spell constants
// ============================================================
TEST(SoDSpellsTest, SpellIdMaxIs23000) {
    EXPECT_EQ(SoD::spells::SPELL_ID_MAX, 23000);
}

TEST(SoDSpellsTest, SpellbookSizeIs480) {
    EXPECT_EQ(SoD::spells::SPELLBOOK_SIZE, 480);
}

TEST(SoDSpellsTest, LongBuffsIs25) {
    EXPECT_EQ(SoD::spells::LONG_BUFFS, 25);
}

TEST(SoDSpellsTest, ShortBuffsIs15) {
    EXPECT_EQ(SoD::spells::SHORT_BUFFS, 15);
}

TEST(SoDSpellsTest, TotalBuffsIsLongPlusShortPlusDisc) {
    int total = SoD::spells::TOTAL_BUFFS;
    int expected = SoD::spells::LONG_BUFFS + SoD::spells::SHORT_BUFFS + SoD::spells::DISC_BUFFS;
    EXPECT_EQ(total, expected);
}

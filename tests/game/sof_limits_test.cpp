#include <gtest/gtest.h>
#include "common/patches/sof_limits.h"

// ============================================================
// SoF global sentinel values
// ============================================================
TEST(SoFSentinelTest, IInvalidIsNegativeOne) {
    int16 v = SoF::IINVALID;
    EXPECT_EQ(v, -1);
}

TEST(SoFSentinelTest, INullIsZero) {
    int16 v = SoF::INULL;
    EXPECT_EQ(v, 0);
}

// ============================================================
// SoF::invtype — InventoryTypes enum
// ============================================================
TEST(SoFInvTypeEnumTest, PossessionsIsZero) {
    EXPECT_EQ(SoF::invtype::typePossessions, 0);
}

TEST(SoFInvTypeEnumTest, BankIsOne) {
    EXPECT_EQ(SoF::invtype::typeBank, 1);
}

TEST(SoFInvTypeEnumTest, TypeBeginIsZero) {
    int16 v = SoF::invtype::TYPE_BEGIN;
    EXPECT_EQ(v, 0);
}

TEST(SoFInvTypeEnumTest, TypeInvalidIsIInvalid) {
    int16 v = SoF::invtype::TYPE_INVALID;
    int16 inv = SoF::IINVALID;
    EXPECT_EQ(v, inv);
}

TEST(SoFInvTypeEnumTest, TypeEndGreaterThanBegin) {
    int16 end = SoF::invtype::TYPE_END;
    int16 begin = SoF::invtype::TYPE_BEGIN;
    EXPECT_GT(end, begin);
}

TEST(SoFInvTypeEnumTest, TypeCountIsConsistent) {
    int16 end = SoF::invtype::TYPE_END;
    int16 begin = SoF::invtype::TYPE_BEGIN;
    int16 count = SoF::invtype::TYPE_COUNT;
    EXPECT_EQ(count, (end - begin) + 1);
}

// ============================================================
// SoF::invtype — inventory size constants
// ============================================================
TEST(SoFInvTypeSizeTest, PossessionsIs32) {
    int16 v = SoF::invtype::POSSESSIONS_SIZE;
    EXPECT_EQ(v, 32);
}

TEST(SoFInvTypeSizeTest, BankIs24) {
    int16 v = SoF::invtype::BANK_SIZE;
    EXPECT_EQ(v, 24);
}

TEST(SoFInvTypeSizeTest, SharedBankIs2) {
    int16 v = SoF::invtype::SHARED_BANK_SIZE;
    EXPECT_EQ(v, 2);
}

TEST(SoFInvTypeSizeTest, TradeIs8) {
    int16 v = SoF::invtype::TRADE_SIZE;
    EXPECT_EQ(v, 8);
}

TEST(SoFInvTypeSizeTest, MerchantIs80) {
    int16 v = SoF::invtype::MERCHANT_SIZE;
    EXPECT_EQ(v, 80);
}

TEST(SoFInvTypeSizeTest, CorpseSizeEqualsPossessions) {
    int16 corpse = SoF::invtype::CORPSE_SIZE;
    int16 poss = SoF::invtype::POSSESSIONS_SIZE;
    EXPECT_EQ(corpse, poss);
}

TEST(SoFInvTypeSizeTest, TradeNPCSizeIs4) {
    int16 v = SoF::invtype::TRADE_NPC_SIZE;
    EXPECT_EQ(v, 4);
}

// ============================================================
// SoF::invslot — equipment slot enum values
// ============================================================
TEST(SoFInvSlotEnumTest, SlotCharmIsZero) {
    EXPECT_EQ(SoF::invslot::slotCharm, 0);
}

TEST(SoFInvSlotEnumTest, SlotPrimaryIs13) {
    EXPECT_EQ(SoF::invslot::slotPrimary, 13);
}

TEST(SoFInvSlotEnumTest, SlotAmmoIs22) {
    EXPECT_EQ(SoF::invslot::slotAmmo, 22);
}

TEST(SoFInvSlotEnumTest, SlotCursorIs31) {
    EXPECT_EQ(SoF::invslot::slotCursor, 31);
}

// ============================================================
// SoF::invslot — slot range constants
// ============================================================
TEST(SoFInvSlotRangeTest, SlotInvalidIsNegativeOne) {
    int16 v = SoF::invslot::SLOT_INVALID;
    EXPECT_EQ(v, -1);
}

TEST(SoFInvSlotRangeTest, PossessionsCountIs32) {
    int16 count = SoF::invslot::POSSESSIONS_COUNT;
    EXPECT_EQ(count, 32);
}

TEST(SoFInvSlotRangeTest, EquipmentCountIs23) {
    int16 count = SoF::invslot::EQUIPMENT_COUNT;
    EXPECT_EQ(count, 23);
}

TEST(SoFInvSlotRangeTest, GeneralCountIs8) {
    int16 count = SoF::invslot::GENERAL_COUNT;
    EXPECT_EQ(count, 8);
}

TEST(SoFInvSlotRangeTest, BankBeginIs2000) {
    int16 v = SoF::invslot::BANK_BEGIN;
    EXPECT_EQ(v, 2000);
}

TEST(SoFInvSlotRangeTest, BankEndIsBankBeginPlusSizeMinus1) {
    int16 end = SoF::invslot::BANK_END;
    int16 begin = SoF::invslot::BANK_BEGIN;
    int16 size = SoF::invtype::BANK_SIZE;
    EXPECT_EQ(end, begin + size - 1);
}

TEST(SoFInvSlotRangeTest, SharedBankBeginIs2500) {
    int16 v = SoF::invslot::SHARED_BANK_BEGIN;
    EXPECT_EQ(v, 2500);
}

TEST(SoFInvSlotRangeTest, TradeBeginIs3000) {
    int16 v = SoF::invslot::TRADE_BEGIN;
    EXPECT_EQ(v, 3000);
}

// ============================================================
// SoF::invbag — bag slot constants
// ============================================================
TEST(SoFInvBagTest, SlotBeginIsZero) {
    int16 v = SoF::invbag::SLOT_BEGIN;
    EXPECT_EQ(v, 0);
}

TEST(SoFInvBagTest, SlotEndIs9) {
    int16 v = SoF::invbag::SLOT_END;
    EXPECT_EQ(v, 9);
}

TEST(SoFInvBagTest, SlotCountIs10) {
    int16 v = SoF::invbag::SLOT_COUNT;
    EXPECT_EQ(v, 10);
}

TEST(SoFInvBagTest, SlotInvalidIsNegativeOne) {
    int16 v = SoF::invbag::SLOT_INVALID;
    EXPECT_EQ(v, -1);
}

// ============================================================
// SoF::invaug — augment socket constants
// ============================================================
TEST(SoFInvAugTest, SocketBeginIsZero) {
    int16 v = SoF::invaug::SOCKET_BEGIN;
    EXPECT_EQ(v, 0);
}

TEST(SoFInvAugTest, SocketEndIs4) {
    int16 v = SoF::invaug::SOCKET_END;
    EXPECT_EQ(v, 4);
}

TEST(SoFInvAugTest, SocketCountIs5) {
    int16 v = SoF::invaug::SOCKET_COUNT;
    EXPECT_EQ(v, 5);
}

// ============================================================
// SoF::profile — profile size constants
// ============================================================
TEST(SoFProfileTest, BandoliersSizeIs20) {
    int16 v = SoF::profile::BANDOLIERS_SIZE;
    EXPECT_EQ(v, 20);
}

TEST(SoFProfileTest, BandolierItemCountIs4) {
    int16 v = SoF::profile::BANDOLIER_ITEM_COUNT;
    EXPECT_EQ(v, 4);
}

TEST(SoFProfileTest, PotionBeltSizeIs5) {
    int16 v = SoF::profile::POTION_BELT_SIZE;
    EXPECT_EQ(v, 5);
}

TEST(SoFProfileTest, SkillArraySizeIs100) {
    int16 v = SoF::profile::SKILL_ARRAY_SIZE;
    EXPECT_EQ(v, 100);
}

// ============================================================
// SoF::constants — character/spell constants
// ============================================================
TEST(SoFConstantsTest, CharacterCreationLimitIs12) {
    size_t v = SoF::constants::CHARACTER_CREATION_LIMIT;
    EXPECT_EQ(v, static_cast<size_t>(12));
}

TEST(SoFConstantsTest, SayLinkBodySizeIs50) {
    size_t v = SoF::constants::SAY_LINK_BODY_SIZE;
    EXPECT_EQ(v, static_cast<size_t>(50));
}

// ============================================================
// SoF::spells — spell constants (distinct from UF: 15999, 480)
// ============================================================
TEST(SoFSpellsTest, SpellIdMaxIs15999) {
    EXPECT_EQ(SoF::spells::SPELL_ID_MAX, 15999);
}

TEST(SoFSpellsTest, SpellbookSizeIs480) {
    EXPECT_EQ(SoF::spells::SPELLBOOK_SIZE, 480);
}

TEST(SoFSpellsTest, LongBuffsIs25) {
    EXPECT_EQ(SoF::spells::LONG_BUFFS, 25);
}

TEST(SoFSpellsTest, ShortBuffsIs15) {
    EXPECT_EQ(SoF::spells::SHORT_BUFFS, 15);
}

TEST(SoFSpellsTest, TotalBuffsIsLongPlusShortPlusDisc) {
    int total = SoF::spells::TOTAL_BUFFS;
    int expected = SoF::spells::LONG_BUFFS + SoF::spells::SHORT_BUFFS + SoF::spells::DISC_BUFFS;
    EXPECT_EQ(total, expected);
}

#include <gtest/gtest.h>
#include "common/patches/rof_limits.h"

// ============================================================
// RoF global sentinel values
// ============================================================
TEST(RoFSentinelTest, IInvalidIsNegativeOne) {
    int16 v = RoF::IINVALID;
    EXPECT_EQ(v, -1);
}

TEST(RoFSentinelTest, INullIsZero) {
    int16 v = RoF::INULL;
    EXPECT_EQ(v, 0);
}

// ============================================================
// RoF::invtype — InventoryTypes enum
// ============================================================
TEST(RoFInvTypeEnumTest, PossessionsIsZero) {
    EXPECT_EQ(RoF::invtype::typePossessions, 0);
}

TEST(RoFInvTypeEnumTest, BankIsOne) {
    EXPECT_EQ(RoF::invtype::typeBank, 1);
}

TEST(RoFInvTypeEnumTest, SharedBankIsTwo) {
    EXPECT_EQ(RoF::invtype::typeSharedBank, 2);
}

TEST(RoFInvTypeEnumTest, TradeIsThree) {
    EXPECT_EQ(RoF::invtype::typeTrade, 3);
}

TEST(RoFInvTypeEnumTest, WorldIsFour) {
    EXPECT_EQ(RoF::invtype::typeWorld, 4);
}

TEST(RoFInvTypeEnumTest, TypeBeginIsZero) {
    int16 v = RoF::invtype::TYPE_BEGIN;
    EXPECT_EQ(v, 0);
}

TEST(RoFInvTypeEnumTest, TypeInvalidIsIInvalid) {
    int16 v = RoF::invtype::TYPE_INVALID;
    int16 inv = RoF::IINVALID;
    EXPECT_EQ(v, inv);
}

TEST(RoFInvTypeEnumTest, TypeEndGreaterThanBegin) {
    int16 end = RoF::invtype::TYPE_END;
    int16 begin = RoF::invtype::TYPE_BEGIN;
    EXPECT_GT(end, begin);
}

TEST(RoFInvTypeEnumTest, TypeCountIsConsistent) {
    int16 end = RoF::invtype::TYPE_END;
    int16 begin = RoF::invtype::TYPE_BEGIN;
    int16 count = RoF::invtype::TYPE_COUNT;
    EXPECT_EQ(count, (end - begin) + 1);
}

// ============================================================
// RoF::invtype — inventory size constants
// ============================================================
TEST(RoFInvTypeSizeTest, PossessionsIs34) {
    int16 v = RoF::invtype::POSSESSIONS_SIZE;
    EXPECT_EQ(v, 34);
}

TEST(RoFInvTypeSizeTest, BankIs24) {
    int16 v = RoF::invtype::BANK_SIZE;
    EXPECT_EQ(v, 24);
}

TEST(RoFInvTypeSizeTest, SharedBankIs2) {
    int16 v = RoF::invtype::SHARED_BANK_SIZE;
    EXPECT_EQ(v, 2);
}

TEST(RoFInvTypeSizeTest, TradeIs8) {
    int16 v = RoF::invtype::TRADE_SIZE;
    EXPECT_EQ(v, 8);
}

TEST(RoFInvTypeSizeTest, WorldIs10) {
    int16 v = RoF::invtype::WORLD_SIZE;
    EXPECT_EQ(v, 10);
}

TEST(RoFInvTypeSizeTest, MerchantIs200) {
    int16 v = RoF::invtype::MERCHANT_SIZE;
    EXPECT_EQ(v, 200);
}

TEST(RoFInvTypeSizeTest, BazaarIs200) {
    int16 v = RoF::invtype::BAZAAR_SIZE;
    EXPECT_EQ(v, 200);
}

TEST(RoFInvTypeSizeTest, CorpseSizeEqualsPossessions) {
    int16 corpse = RoF::invtype::CORPSE_SIZE;
    int16 poss = RoF::invtype::POSSESSIONS_SIZE;
    EXPECT_EQ(corpse, poss);
}

TEST(RoFInvTypeSizeTest, TradeNPCSizeIs4) {
    int16 v = RoF::invtype::TRADE_NPC_SIZE;
    EXPECT_EQ(v, 4);
}

// ============================================================
// RoF::invslot — equipment slot enum values
// ============================================================
TEST(RoFInvSlotEnumTest, SlotCharmIsZero) {
    EXPECT_EQ(RoF::invslot::slotCharm, 0);
}

TEST(RoFInvSlotEnumTest, SlotEar1IsOne) {
    EXPECT_EQ(RoF::invslot::slotEar1, 1);
}

TEST(RoFInvSlotEnumTest, SlotPrimaryIs13) {
    EXPECT_EQ(RoF::invslot::slotPrimary, 13);
}

TEST(RoFInvSlotEnumTest, SlotSecondaryIs14) {
    EXPECT_EQ(RoF::invslot::slotSecondary, 14);
}

TEST(RoFInvSlotEnumTest, SlotAmmoIs22) {
    EXPECT_EQ(RoF::invslot::slotAmmo, 22);
}

TEST(RoFInvSlotEnumTest, SlotCursorIs33) {
    EXPECT_EQ(RoF::invslot::slotCursor, 33);
}

// ============================================================
// RoF::invslot — slot range constants
// ============================================================
TEST(RoFInvSlotRangeTest, SlotInvalidIsNegativeOne) {
    int16 v = RoF::invslot::SLOT_INVALID;
    EXPECT_EQ(v, -1);
}

TEST(RoFInvSlotRangeTest, SlotBeginIsZero) {
    int16 v = RoF::invslot::SLOT_BEGIN;
    EXPECT_EQ(v, 0);
}

TEST(RoFInvSlotRangeTest, PossessionsBeginIsCharm) {
    int16 pb = RoF::invslot::POSSESSIONS_BEGIN;
    EXPECT_EQ(pb, RoF::invslot::slotCharm);
}

TEST(RoFInvSlotRangeTest, PossessionsEndIsCursor) {
    int16 pe = RoF::invslot::POSSESSIONS_END;
    EXPECT_EQ(pe, RoF::invslot::slotCursor);
}

TEST(RoFInvSlotRangeTest, PossessionsCountIs34) {
    int16 count = RoF::invslot::POSSESSIONS_COUNT;
    EXPECT_EQ(count, 34);
}

TEST(RoFInvSlotRangeTest, EquipmentBeginIsCharm) {
    int16 v = RoF::invslot::EQUIPMENT_BEGIN;
    EXPECT_EQ(v, RoF::invslot::slotCharm);
}

TEST(RoFInvSlotRangeTest, EquipmentEndIsAmmo) {
    int16 v = RoF::invslot::EQUIPMENT_END;
    EXPECT_EQ(v, RoF::invslot::slotAmmo);
}

TEST(RoFInvSlotRangeTest, EquipmentCountIs23) {
    int16 count = RoF::invslot::EQUIPMENT_COUNT;
    EXPECT_EQ(count, 23);
}

TEST(RoFInvSlotRangeTest, GeneralCountIs10) {
    int16 count = RoF::invslot::GENERAL_COUNT;
    EXPECT_EQ(count, 10);
}

// ============================================================
// RoF::invbag — bag slot constants
// ============================================================
TEST(RoFInvBagTest, SlotBeginIsZero) {
    int16 v = RoF::invbag::SLOT_BEGIN;
    EXPECT_EQ(v, 0);
}

TEST(RoFInvBagTest, SlotEndIs9) {
    int16 v = RoF::invbag::SLOT_END;
    EXPECT_EQ(v, 9);
}

TEST(RoFInvBagTest, SlotCountIs10) {
    int16 v = RoF::invbag::SLOT_COUNT;
    EXPECT_EQ(v, 10);
}

TEST(RoFInvBagTest, SlotInvalidIsNegativeOne) {
    int16 v = RoF::invbag::SLOT_INVALID;
    EXPECT_EQ(v, -1);
}

// ============================================================
// RoF::invaug — augment socket constants
// ============================================================
TEST(RoFInvAugTest, SocketBeginIsZero) {
    int16 v = RoF::invaug::SOCKET_BEGIN;
    EXPECT_EQ(v, 0);
}

TEST(RoFInvAugTest, SocketEndIs5) {
    int16 v = RoF::invaug::SOCKET_END;
    EXPECT_EQ(v, 5);
}

TEST(RoFInvAugTest, SocketCountIs6) {
    int16 v = RoF::invaug::SOCKET_COUNT;
    EXPECT_EQ(v, 6);
}

// ============================================================
// RoF::profile — profile size constants
// ============================================================
TEST(RoFProfileTest, BandoliersSizeIs20) {
    int16 v = RoF::profile::BANDOLIERS_SIZE;
    EXPECT_EQ(v, 20);
}

TEST(RoFProfileTest, BandolierItemCountIs4) {
    int16 v = RoF::profile::BANDOLIER_ITEM_COUNT;
    EXPECT_EQ(v, 4);
}

TEST(RoFProfileTest, PotionBeltSizeIs5) {
    int16 v = RoF::profile::POTION_BELT_SIZE;
    EXPECT_EQ(v, 5);
}

TEST(RoFProfileTest, SkillArraySizeIs100) {
    int16 v = RoF::profile::SKILL_ARRAY_SIZE;
    EXPECT_EQ(v, 100);
}

// ============================================================
// RoF::constants — character/spell constants
// ============================================================
TEST(RoFConstantsTest, CharacterCreationLimitIs12) {
    size_t v = RoF::constants::CHARACTER_CREATION_LIMIT;
    EXPECT_EQ(v, static_cast<size_t>(12));
}

TEST(RoFConstantsTest, SayLinkBodySizeIs55) {
    size_t v = RoF::constants::SAY_LINK_BODY_SIZE;
    EXPECT_EQ(v, static_cast<size_t>(55));
}

// ============================================================
// RoF::spells — spell constants
// ============================================================
TEST(RoFSpellsTest, SpellIdMaxIs45000) {
    EXPECT_EQ(RoF::spells::SPELL_ID_MAX, 45000);
}

TEST(RoFSpellsTest, SpellbookSizeIs720) {
    EXPECT_EQ(RoF::spells::SPELLBOOK_SIZE, 720);
}

TEST(RoFSpellsTest, LongBuffsIs42) {
    EXPECT_EQ(RoF::spells::LONG_BUFFS, 42);
}

TEST(RoFSpellsTest, ShortBuffsIs20) {
    EXPECT_EQ(RoF::spells::SHORT_BUFFS, 20);
}

TEST(RoFSpellsTest, TotalBuffsIsLongPlusShortPlusDisc) {
    int total = RoF::spells::TOTAL_BUFFS;
    int expected = RoF::spells::LONG_BUFFS + RoF::spells::SHORT_BUFFS + RoF::spells::DISC_BUFFS;
    EXPECT_EQ(total, expected);
}

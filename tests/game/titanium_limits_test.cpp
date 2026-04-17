#include <gtest/gtest.h>
#include "common/patches/titanium_limits.h"

// ============================================================
// Titanium global sentinel values
// ============================================================
TEST(TitaniumSentinelTest, IInvalidIsNegativeOne) {
    int16 v = Titanium::IINVALID;
    EXPECT_EQ(v, -1);
}

TEST(TitaniumSentinelTest, INullIsZero) {
    int16 v = Titanium::INULL;
    EXPECT_EQ(v, 0);
}

// ============================================================
// Titanium::invtype — InventoryTypes enum
// ============================================================
TEST(TitaniumInvTypeEnumTest, PossessionsIsZero) {
    EXPECT_EQ(Titanium::invtype::typePossessions, 0);
}

TEST(TitaniumInvTypeEnumTest, BankIsOne) {
    EXPECT_EQ(Titanium::invtype::typeBank, 1);
}

TEST(TitaniumInvTypeEnumTest, TypeBeginIsZero) {
    int16 v = Titanium::invtype::TYPE_BEGIN;
    EXPECT_EQ(v, 0);
}

TEST(TitaniumInvTypeEnumTest, TypeInvalidIsIInvalid) {
    int16 v = Titanium::invtype::TYPE_INVALID;
    int16 inv = Titanium::IINVALID;
    EXPECT_EQ(v, inv);
}

TEST(TitaniumInvTypeEnumTest, TypeEndGreaterThanBegin) {
    int16 end = Titanium::invtype::TYPE_END;
    int16 begin = Titanium::invtype::TYPE_BEGIN;
    EXPECT_GT(end, begin);
}

TEST(TitaniumInvTypeEnumTest, TypeCountIsConsistent) {
    int16 end = Titanium::invtype::TYPE_END;
    int16 begin = Titanium::invtype::TYPE_BEGIN;
    int16 count = Titanium::invtype::TYPE_COUNT;
    EXPECT_EQ(count, (end - begin) + 1);
}

// ============================================================
// Titanium::invtype — inventory size constants
// ============================================================
TEST(TitaniumInvTypeSizeTest, PossessionsIs31) {
    int16 v = Titanium::invtype::POSSESSIONS_SIZE;
    EXPECT_EQ(v, 31);
}

TEST(TitaniumInvTypeSizeTest, BankIs16) {
    int16 v = Titanium::invtype::BANK_SIZE;
    EXPECT_EQ(v, 16);
}

TEST(TitaniumInvTypeSizeTest, SharedBankIs2) {
    int16 v = Titanium::invtype::SHARED_BANK_SIZE;
    EXPECT_EQ(v, 2);
}

TEST(TitaniumInvTypeSizeTest, TradeIs8) {
    int16 v = Titanium::invtype::TRADE_SIZE;
    EXPECT_EQ(v, 8);
}

TEST(TitaniumInvTypeSizeTest, CorpseSizeEqualsPossessions) {
    int16 corpse = Titanium::invtype::CORPSE_SIZE;
    int16 poss = Titanium::invtype::POSSESSIONS_SIZE;
    EXPECT_EQ(corpse, poss);
}

TEST(TitaniumInvTypeSizeTest, TradeNPCSizeIs4) {
    int16 v = Titanium::invtype::TRADE_NPC_SIZE;
    EXPECT_EQ(v, 4);
}

// ============================================================
// Titanium::invslot — equipment slot enum values (no PowerSource)
// ============================================================
TEST(TitaniumInvSlotEnumTest, SlotCharmIsZero) {
    EXPECT_EQ(Titanium::invslot::slotCharm, 0);
}

TEST(TitaniumInvSlotEnumTest, SlotPrimaryIs13) {
    EXPECT_EQ(Titanium::invslot::slotPrimary, 13);
}

TEST(TitaniumInvSlotEnumTest, SlotAmmoIs21) {
    // Titanium has no PowerSource slot, so Ammo is 21 (not 22)
    EXPECT_EQ(Titanium::invslot::slotAmmo, 21);
}

TEST(TitaniumInvSlotEnumTest, SlotCursorIs30) {
    EXPECT_EQ(Titanium::invslot::slotCursor, 30);
}

// ============================================================
// Titanium::invslot — slot range constants
// ============================================================
TEST(TitaniumInvSlotRangeTest, SlotInvalidIsNegativeOne) {
    int16 v = Titanium::invslot::SLOT_INVALID;
    EXPECT_EQ(v, -1);
}

TEST(TitaniumInvSlotRangeTest, PossessionsCountIs31) {
    int16 count = Titanium::invslot::POSSESSIONS_COUNT;
    EXPECT_EQ(count, 31);
}

TEST(TitaniumInvSlotRangeTest, EquipmentCountIs22) {
    int16 count = Titanium::invslot::EQUIPMENT_COUNT;
    EXPECT_EQ(count, 22);
}

TEST(TitaniumInvSlotRangeTest, GeneralCountIs8) {
    int16 count = Titanium::invslot::GENERAL_COUNT;
    EXPECT_EQ(count, 8);
}

TEST(TitaniumInvSlotRangeTest, BankBeginIs2000) {
    int16 v = Titanium::invslot::BANK_BEGIN;
    EXPECT_EQ(v, 2000);
}

TEST(TitaniumInvSlotRangeTest, BankEndIsBankBeginPlusSizeMinus1) {
    int16 end = Titanium::invslot::BANK_END;
    int16 begin = Titanium::invslot::BANK_BEGIN;
    int16 size = Titanium::invtype::BANK_SIZE;
    EXPECT_EQ(end, begin + size - 1);
}

TEST(TitaniumInvSlotRangeTest, SharedBankBeginIs2500) {
    int16 v = Titanium::invslot::SHARED_BANK_BEGIN;
    EXPECT_EQ(v, 2500);
}

// ============================================================
// Titanium::invbag — bag slot constants
// ============================================================
TEST(TitaniumInvBagTest, SlotBeginIsZero) {
    int16 v = Titanium::invbag::SLOT_BEGIN;
    EXPECT_EQ(v, 0);
}

TEST(TitaniumInvBagTest, SlotEndIs9) {
    int16 v = Titanium::invbag::SLOT_END;
    EXPECT_EQ(v, 9);
}

TEST(TitaniumInvBagTest, SlotCountIs10) {
    int16 v = Titanium::invbag::SLOT_COUNT;
    EXPECT_EQ(v, 10);
}

TEST(TitaniumInvBagTest, SlotInvalidIsNegativeOne) {
    int16 v = Titanium::invbag::SLOT_INVALID;
    EXPECT_EQ(v, -1);
}

// ============================================================
// Titanium::invaug — augment socket constants
// ============================================================
TEST(TitaniumInvAugTest, SocketBeginIsZero) {
    int16 v = Titanium::invaug::SOCKET_BEGIN;
    EXPECT_EQ(v, 0);
}

TEST(TitaniumInvAugTest, SocketEndIs4) {
    int16 v = Titanium::invaug::SOCKET_END;
    EXPECT_EQ(v, 4);
}

TEST(TitaniumInvAugTest, SocketCountIs5) {
    int16 v = Titanium::invaug::SOCKET_COUNT;
    EXPECT_EQ(v, 5);
}

// ============================================================
// Titanium::profile — profile size constants
// ============================================================
TEST(TitaniumProfileTest, BandoliersSizeIs4) {
    int16 v = Titanium::profile::BANDOLIERS_SIZE;
    EXPECT_EQ(v, 4);
}

TEST(TitaniumProfileTest, BandolierItemCountIs4) {
    int16 v = Titanium::profile::BANDOLIER_ITEM_COUNT;
    EXPECT_EQ(v, 4);
}

TEST(TitaniumProfileTest, PotionBeltSizeIs4) {
    int16 v = Titanium::profile::POTION_BELT_SIZE;
    EXPECT_EQ(v, 4);
}

TEST(TitaniumProfileTest, SkillArraySizeIs100) {
    int16 v = Titanium::profile::SKILL_ARRAY_SIZE;
    EXPECT_EQ(v, 100);
}

// ============================================================
// Titanium::constants — character/spell constants
// ============================================================
TEST(TitaniumConstantsTest, CharacterCreationLimitIs8) {
    // Hard-coded in Titanium client - must not change
    size_t v = Titanium::constants::CHARACTER_CREATION_LIMIT;
    EXPECT_EQ(v, static_cast<size_t>(8));
}

TEST(TitaniumConstantsTest, SayLinkBodySizeIs45) {
    size_t v = Titanium::constants::SAY_LINK_BODY_SIZE;
    EXPECT_EQ(v, static_cast<size_t>(45));
}

// ============================================================
// Titanium::spells — spell constants
// ============================================================
TEST(TitaniumSpellsTest, SpellIdMaxIs9999) {
    EXPECT_EQ(Titanium::spells::SPELL_ID_MAX, 9999);
}

TEST(TitaniumSpellsTest, SpellbookSizeIs400) {
    EXPECT_EQ(Titanium::spells::SPELLBOOK_SIZE, 400);
}

TEST(TitaniumSpellsTest, LongBuffsIs25) {
    EXPECT_EQ(Titanium::spells::LONG_BUFFS, 25);
}

TEST(TitaniumSpellsTest, ShortBuffsIs12) {
    EXPECT_EQ(Titanium::spells::SHORT_BUFFS, 12);
}

TEST(TitaniumSpellsTest, TotalBuffsIsLongPlusShortPlusDisc) {
    int total = Titanium::spells::TOTAL_BUFFS;
    int expected = Titanium::spells::LONG_BUFFS + Titanium::spells::SHORT_BUFFS + Titanium::spells::DISC_BUFFS;
    EXPECT_EQ(total, expected);
}

#include <gtest/gtest.h>
#include "common/patches/uf_limits.h"

// ============================================================
// UF global sentinel values
// ============================================================
TEST(UFSentinelTest, IInvalidIsNegativeOne) {
    int16 v = UF::IINVALID;
    EXPECT_EQ(v, -1);
}

TEST(UFSentinelTest, INullIsZero) {
    int16 v = UF::INULL;
    EXPECT_EQ(v, 0);
}

// ============================================================
// UF::invtype — InventoryTypes enum
// ============================================================
TEST(UFInvTypeEnumTest, PossessionsIsZero) {
    EXPECT_EQ(UF::invtype::typePossessions, 0);
}

TEST(UFInvTypeEnumTest, BankIsOne) {
    EXPECT_EQ(UF::invtype::typeBank, 1);
}

TEST(UFInvTypeEnumTest, SharedBankIsTwo) {
    EXPECT_EQ(UF::invtype::typeSharedBank, 2);
}

TEST(UFInvTypeEnumTest, TypeBeginIsZero) {
    int16 v = UF::invtype::TYPE_BEGIN;
    EXPECT_EQ(v, 0);
}

TEST(UFInvTypeEnumTest, TypeInvalidIsIInvalid) {
    int16 v = UF::invtype::TYPE_INVALID;
    int16 inv = UF::IINVALID;
    EXPECT_EQ(v, inv);
}

TEST(UFInvTypeEnumTest, TypeEndGreaterThanBegin) {
    int16 end = UF::invtype::TYPE_END;
    int16 begin = UF::invtype::TYPE_BEGIN;
    EXPECT_GT(end, begin);
}

TEST(UFInvTypeEnumTest, TypeCountIsConsistent) {
    int16 end = UF::invtype::TYPE_END;
    int16 begin = UF::invtype::TYPE_BEGIN;
    int16 count = UF::invtype::TYPE_COUNT;
    EXPECT_EQ(count, (end - begin) + 1);
}

// ============================================================
// UF::invtype — inventory size constants
// ============================================================
TEST(UFInvTypeSizeTest, PossessionsIs32) {
    int16 v = UF::invtype::POSSESSIONS_SIZE;
    EXPECT_EQ(v, 32);
}

TEST(UFInvTypeSizeTest, BankIs24) {
    int16 v = UF::invtype::BANK_SIZE;
    EXPECT_EQ(v, 24);
}

TEST(UFInvTypeSizeTest, SharedBankIs2) {
    int16 v = UF::invtype::SHARED_BANK_SIZE;
    EXPECT_EQ(v, 2);
}

TEST(UFInvTypeSizeTest, TradeIs8) {
    int16 v = UF::invtype::TRADE_SIZE;
    EXPECT_EQ(v, 8);
}

TEST(UFInvTypeSizeTest, WorldIs10) {
    int16 v = UF::invtype::WORLD_SIZE;
    EXPECT_EQ(v, 10);
}

TEST(UFInvTypeSizeTest, MerchantIs80) {
    int16 v = UF::invtype::MERCHANT_SIZE;
    EXPECT_EQ(v, 80);
}

TEST(UFInvTypeSizeTest, BazaarIs80) {
    int16 v = UF::invtype::BAZAAR_SIZE;
    EXPECT_EQ(v, 80);
}

TEST(UFInvTypeSizeTest, CorpseSizeEqualsPossessions) {
    int16 corpse = UF::invtype::CORPSE_SIZE;
    int16 poss = UF::invtype::POSSESSIONS_SIZE;
    EXPECT_EQ(corpse, poss);
}

TEST(UFInvTypeSizeTest, TradeNPCSizeIs4) {
    int16 v = UF::invtype::TRADE_NPC_SIZE;
    EXPECT_EQ(v, 4);
}

// ============================================================
// UF::invslot — equipment slot enum values
// ============================================================
TEST(UFInvSlotEnumTest, SlotCharmIsZero) {
    EXPECT_EQ(UF::invslot::slotCharm, 0);
}

TEST(UFInvSlotEnumTest, SlotPrimaryIs13) {
    EXPECT_EQ(UF::invslot::slotPrimary, 13);
}

TEST(UFInvSlotEnumTest, SlotAmmoIs22) {
    EXPECT_EQ(UF::invslot::slotAmmo, 22);
}

TEST(UFInvSlotEnumTest, SlotCursorIs31) {
    EXPECT_EQ(UF::invslot::slotCursor, 31);
}

// ============================================================
// UF::invslot — slot range constants
// ============================================================
TEST(UFInvSlotRangeTest, SlotInvalidIsNegativeOne) {
    int16 v = UF::invslot::SLOT_INVALID;
    EXPECT_EQ(v, -1);
}

TEST(UFInvSlotRangeTest, SlotBeginIsZero) {
    int16 v = UF::invslot::SLOT_BEGIN;
    EXPECT_EQ(v, 0);
}

TEST(UFInvSlotRangeTest, PossessionsCountIs32) {
    int16 count = UF::invslot::POSSESSIONS_COUNT;
    EXPECT_EQ(count, 32);
}

TEST(UFInvSlotRangeTest, EquipmentCountIs23) {
    int16 count = UF::invslot::EQUIPMENT_COUNT;
    EXPECT_EQ(count, 23);
}

TEST(UFInvSlotRangeTest, GeneralCountIs8) {
    int16 count = UF::invslot::GENERAL_COUNT;
    EXPECT_EQ(count, 8);
}

TEST(UFInvSlotRangeTest, BankBeginIs2000) {
    int16 v = UF::invslot::BANK_BEGIN;
    EXPECT_EQ(v, 2000);
}

TEST(UFInvSlotRangeTest, BankEndIsBankBeginPlusSizeMinus1) {
    int16 end = UF::invslot::BANK_END;
    int16 begin = UF::invslot::BANK_BEGIN;
    int16 size = UF::invtype::BANK_SIZE;
    EXPECT_EQ(end, begin + size - 1);
}

TEST(UFInvSlotRangeTest, SharedBankBeginIs2500) {
    int16 v = UF::invslot::SHARED_BANK_BEGIN;
    EXPECT_EQ(v, 2500);
}

TEST(UFInvSlotRangeTest, TradeBeginIs3000) {
    int16 v = UF::invslot::TRADE_BEGIN;
    EXPECT_EQ(v, 3000);
}

TEST(UFInvSlotRangeTest, WorldBeginIs4000) {
    int16 v = UF::invslot::WORLD_BEGIN;
    EXPECT_EQ(v, 4000);
}

// ============================================================
// UF::invbag — bag slot constants
// ============================================================
TEST(UFInvBagTest, SlotBeginIsZero) {
    int16 v = UF::invbag::SLOT_BEGIN;
    EXPECT_EQ(v, 0);
}

TEST(UFInvBagTest, SlotEndIs9) {
    int16 v = UF::invbag::SLOT_END;
    EXPECT_EQ(v, 9);
}

TEST(UFInvBagTest, SlotCountIs10) {
    int16 v = UF::invbag::SLOT_COUNT;
    EXPECT_EQ(v, 10);
}

TEST(UFInvBagTest, SlotInvalidIsNegativeOne) {
    int16 v = UF::invbag::SLOT_INVALID;
    EXPECT_EQ(v, -1);
}

// ============================================================
// UF::invaug — augment socket constants
// ============================================================
TEST(UFInvAugTest, SocketBeginIsZero) {
    int16 v = UF::invaug::SOCKET_BEGIN;
    EXPECT_EQ(v, 0);
}

TEST(UFInvAugTest, SocketEndIs4) {
    int16 v = UF::invaug::SOCKET_END;
    EXPECT_EQ(v, 4);
}

TEST(UFInvAugTest, SocketCountIs5) {
    int16 v = UF::invaug::SOCKET_COUNT;
    EXPECT_EQ(v, 5);
}

// ============================================================
// UF::profile — profile size constants
// ============================================================
TEST(UFProfileTest, BandoliersSizeIs20) {
    int16 v = UF::profile::BANDOLIERS_SIZE;
    EXPECT_EQ(v, 20);
}

TEST(UFProfileTest, BandolierItemCountIs4) {
    int16 v = UF::profile::BANDOLIER_ITEM_COUNT;
    EXPECT_EQ(v, 4);
}

TEST(UFProfileTest, PotionBeltSizeIs5) {
    int16 v = UF::profile::POTION_BELT_SIZE;
    EXPECT_EQ(v, 5);
}

TEST(UFProfileTest, SkillArraySizeIs100) {
    int16 v = UF::profile::SKILL_ARRAY_SIZE;
    EXPECT_EQ(v, 100);
}

// ============================================================
// UF::constants — character/spell constants
// ============================================================
TEST(UFConstantsTest, CharacterCreationLimitIs12) {
    size_t v = UF::constants::CHARACTER_CREATION_LIMIT;
    EXPECT_EQ(v, static_cast<size_t>(12));
}

TEST(UFConstantsTest, SayLinkBodySizeIs50) {
    size_t v = UF::constants::SAY_LINK_BODY_SIZE;
    EXPECT_EQ(v, static_cast<size_t>(50));
}

// ============================================================
// UF::spells — spell constants
// ============================================================
TEST(UFSpellsTest, SpellIdMaxIs28000) {
    EXPECT_EQ(UF::spells::SPELL_ID_MAX, 28000);
}

TEST(UFSpellsTest, SpellbookSizeIs720) {
    EXPECT_EQ(UF::spells::SPELLBOOK_SIZE, 720);
}

TEST(UFSpellsTest, LongBuffsIs30) {
    EXPECT_EQ(UF::spells::LONG_BUFFS, 30);
}

TEST(UFSpellsTest, ShortBuffsIs20) {
    EXPECT_EQ(UF::spells::SHORT_BUFFS, 20);
}

TEST(UFSpellsTest, TotalBuffsIsLongPlusShortPlusDisc) {
    int total = UF::spells::TOTAL_BUFFS;
    int expected = UF::spells::LONG_BUFFS + UF::spells::SHORT_BUFFS + UF::spells::DISC_BUFFS;
    EXPECT_EQ(total, expected);
}

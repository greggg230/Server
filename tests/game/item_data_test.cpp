#include <gtest/gtest.h>
#include "common/item_data.h"

namespace item = EQ::item;

// ============================================================
// ItemClass enum
// ============================================================
TEST(ItemClassTest, CommonIsZero) {
    EXPECT_EQ(item::ItemClass::ItemClassCommon, 0);
}

TEST(ItemClassTest, SequentialValues) {
    EXPECT_EQ(item::ItemClass::ItemClassBag,   1);
    EXPECT_EQ(item::ItemClass::ItemClassBook,  2);
    EXPECT_EQ(item::ItemClass::ItemClassCount, 3);
}

// ============================================================
// ItemType enum
// ============================================================
TEST(ItemTypeTest, WeaponTypesSequential) {
    EXPECT_EQ(item::ItemType::ItemType1HSlash,    0);
    EXPECT_EQ(item::ItemType::ItemType2HSlash,    1);
    EXPECT_EQ(item::ItemType::ItemType1HPiercing, 2);
    EXPECT_EQ(item::ItemType::ItemType1HBlunt,    3);
    EXPECT_EQ(item::ItemType::ItemType2HBlunt,    4);
    EXPECT_EQ(item::ItemType::ItemTypeBow,        5);
}

TEST(ItemTypeTest, CommonTypes) {
    EXPECT_EQ(item::ItemType::ItemTypeShield, 8);
    EXPECT_EQ(item::ItemType::ItemTypeScroll, 9);
    EXPECT_EQ(item::ItemType::ItemTypeArmor,  10);
    EXPECT_EQ(item::ItemType::ItemTypeMisc,   11);
}

TEST(ItemTypeTest, LaterTypes) {
    EXPECT_EQ(item::ItemType::ItemTypeMartial, 45);
    EXPECT_EQ(item::ItemType::ItemTypeCharm,   52);
}

TEST(ItemTypeTest, AllIsMaxByte) {
    EXPECT_EQ(item::ItemType::ItemTypeAll, 0xFF);
}

// ============================================================
// ItemSize enum
// ============================================================
TEST(ItemSizeTest, Sequential) {
    EXPECT_EQ(item::ItemSize::ItemSizeTiny,   0);
    EXPECT_EQ(item::ItemSize::ItemSizeSmall,  1);
    EXPECT_EQ(item::ItemSize::ItemSizeMedium, 2);
    EXPECT_EQ(item::ItemSize::ItemSizeLarge,  3);
    EXPECT_EQ(item::ItemSize::ItemSizeGiant,  4);
    EXPECT_EQ(item::ItemSize::ItemSizeCount,  5);
}

// ============================================================
// ItemEffect enum
// ============================================================
TEST(ItemEffectTest, Sequential) {
    EXPECT_EQ(item::ItemEffect::ItemEffectCombatProc, 0);
    EXPECT_EQ(item::ItemEffect::ItemEffectClick,      1);
    EXPECT_EQ(item::ItemEffect::ItemEffectWorn,       2);
    EXPECT_EQ(item::ItemEffect::ItemEffectExpendable, 3);
    EXPECT_EQ(item::ItemEffect::ItemEffectEquipClick, 4);
    EXPECT_EQ(item::ItemEffect::ItemEffectClick2,     5);
    EXPECT_EQ(item::ItemEffect::ItemEffectFocus,      6);
    EXPECT_EQ(item::ItemEffect::ItemEffectScroll,     7);
    EXPECT_EQ(item::ItemEffect::ItemEffectCount,      8);
}

// ============================================================
// ItemDataType enum
// ============================================================
TEST(ItemDataTypeTest, Sequential) {
    EXPECT_EQ(item::ItemDataType::ItemDataBase,     0);
    EXPECT_EQ(item::ItemDataType::ItemDataScaling,  1);
    EXPECT_EQ(item::ItemDataType::ItemDataEvolving, 2);
    EXPECT_EQ(item::ItemDataType::ItemDataCount,    3);
}

// ============================================================
// AugType enum
// ============================================================
TEST(AugTypeTest, NoneIsZero) {
    EXPECT_EQ(item::AugType::AugTypeNone, 0);
}

TEST(AugTypeTest, EarlySequential) {
    EXPECT_EQ(item::AugType::AugTypeGeneralSingleStat,   1);
    EXPECT_EQ(item::AugType::AugTypeGeneralMultipleStat, 2);
    EXPECT_EQ(item::AugType::AugTypeGeneralSpellEffect,  3);
    EXPECT_EQ(item::AugType::AugTypeWeaponGeneral,       4);
    EXPECT_EQ(item::AugType::AugTypeWeaponElemDamage,    5);
}

TEST(AugTypeTest, EmblemIs15) {
    EXPECT_EQ(item::AugType::AugTypeEmblem, 15);
}

// ============================================================
// AugTypeBit enum
// ============================================================
TEST(AugTypeBitTest, NoneIsZero) {
    EXPECT_EQ(item::AugTypeBit::bit_AugTypeNone, 0u);
}

TEST(AugTypeBitTest, PowersOfTwo) {
    EXPECT_EQ(item::AugTypeBit::bit_AugTypeGeneralSingleStat,   0x00000001u);
    EXPECT_EQ(item::AugTypeBit::bit_AugTypeGeneralMultipleStat, 0x00000002u);
    EXPECT_EQ(item::AugTypeBit::bit_AugTypeGeneralSpellEffect,  0x00000004u);
    EXPECT_EQ(item::AugTypeBit::bit_AugTypeWeaponGeneral,       0x00000008u);
}

TEST(AugTypeBitTest, AllBitsSetIsMaxUint32) {
    EXPECT_EQ(item::AugTypeBit::bit_AugTypeAll, 0xFFFFFFFFu);
}

TEST(AugTypeBitTest, EachBitIsPowerOfTwo) {
    EXPECT_EQ(item::AugTypeBit::bit_AugTypeGeneralGroup,        0x00000040u);
    EXPECT_EQ(item::AugTypeBit::bit_AugTypeGeneralRaid,         0x00000080u);
    EXPECT_EQ(item::AugTypeBit::bit_AugTypeOrnamentation,       0x00080000u);
}

// ============================================================
// AugRestriction enum
// ============================================================
TEST(AugRestrictionTest, AnyIsZero) {
    EXPECT_EQ(item::AugRestriction::AugRestrictionAny, 0);
}

TEST(AugRestrictionTest, EarlySequential) {
    EXPECT_EQ(item::AugRestriction::AugRestrictionArmor,    1);
    EXPECT_EQ(item::AugRestriction::AugRestrictionWeapons,  2);
    EXPECT_EQ(item::AugRestriction::AugRestriction1HSlash,  5);
    EXPECT_EQ(item::AugRestriction::AugRestriction2HBlunt, 10);
}

// ============================================================
// BagType enum
// ============================================================
TEST(BagTypeTest, SmallBagIsZero) {
    EXPECT_EQ(item::BagType::BagTypeSmallBag, 0);
}

TEST(BagTypeTest, EarlySequential) {
    EXPECT_EQ(item::BagType::BagTypeLargeBag,   1);
    EXPECT_EQ(item::BagType::BagTypeQuiver,     2);
    EXPECT_EQ(item::BagType::BagTypeBeltPouch,  3);
    EXPECT_EQ(item::BagType::BagTypeWristPouch, 4);
    EXPECT_EQ(item::BagType::BagTypeBackPack,   5);
}

// ============================================================
// ConvertAugTypeToAugTypeBit — pure lookup table
// ============================================================
TEST(ConvertAugTypeTest, SingleStatRoundTrip) {
    uint32_t bit = item::ConvertAugTypeToAugTypeBit(item::AugTypeGeneralSingleStat);
    EXPECT_EQ(bit, item::bit_AugTypeGeneralSingleStat);
    EXPECT_EQ(item::ConvertAugTypeBitToAugType(bit), item::AugTypeGeneralSingleStat);
}

TEST(ConvertAugTypeTest, WeaponGeneralRoundTrip) {
    uint32_t bit = item::ConvertAugTypeToAugTypeBit(item::AugTypeWeaponGeneral);
    EXPECT_EQ(bit, item::bit_AugTypeWeaponGeneral);
    EXPECT_EQ(item::ConvertAugTypeBitToAugType(bit), item::AugTypeWeaponGeneral);
}

TEST(ConvertAugTypeTest, EmblemRoundTrip) {
    uint32_t bit = item::ConvertAugTypeToAugTypeBit(item::AugTypeEmblem);
    EXPECT_EQ(bit, item::bit_AugTypeEmblem);
    EXPECT_EQ(item::ConvertAugTypeBitToAugType(bit), item::AugTypeEmblem);
}

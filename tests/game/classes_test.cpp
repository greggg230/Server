#include <gtest/gtest.h>
#include "common/classes.h"

// ============================================================
// IsPlayerClass
// ============================================================
TEST(IsPlayerClassTest, AllSixteenPlayerClasses) {
    for (uint8_t c = Class::Warrior; c <= Class::Berserker; ++c) {
        EXPECT_TRUE(IsPlayerClass(c)) << "Class " << (int)c << " should be a player class";
    }
}

TEST(IsPlayerClassTest, NonPlayerClasses) {
    EXPECT_FALSE(IsPlayerClass(Class::None));
    EXPECT_FALSE(IsPlayerClass(Class::WarriorGM));
    EXPECT_FALSE(IsPlayerClass(Class::Banker));
    EXPECT_FALSE(IsPlayerClass(Class::Merchant));
    EXPECT_FALSE(IsPlayerClass(255));
}

// ============================================================
// GetPlayerClassAbbreviation
// ============================================================
TEST(ClassAbbreviationTest, AllAbbreviations) {
    EXPECT_EQ(GetPlayerClassAbbreviation(Class::Warrior),     "WAR");
    EXPECT_EQ(GetPlayerClassAbbreviation(Class::Cleric),      "CLR");
    EXPECT_EQ(GetPlayerClassAbbreviation(Class::Paladin),     "PAL");
    EXPECT_EQ(GetPlayerClassAbbreviation(Class::Ranger),      "RNG");
    EXPECT_EQ(GetPlayerClassAbbreviation(Class::ShadowKnight),"SHD");
    EXPECT_EQ(GetPlayerClassAbbreviation(Class::Druid),       "DRU");
    EXPECT_EQ(GetPlayerClassAbbreviation(Class::Monk),        "MNK");
    EXPECT_EQ(GetPlayerClassAbbreviation(Class::Bard),        "BRD");
    EXPECT_EQ(GetPlayerClassAbbreviation(Class::Rogue),       "ROG");
    EXPECT_EQ(GetPlayerClassAbbreviation(Class::Shaman),      "SHM");
    EXPECT_EQ(GetPlayerClassAbbreviation(Class::Necromancer), "NEC");
    EXPECT_EQ(GetPlayerClassAbbreviation(Class::Wizard),      "WIZ");
    EXPECT_EQ(GetPlayerClassAbbreviation(Class::Magician),    "MAG");
    EXPECT_EQ(GetPlayerClassAbbreviation(Class::Enchanter),   "ENC");
    EXPECT_EQ(GetPlayerClassAbbreviation(Class::Beastlord),   "BST");
    EXPECT_EQ(GetPlayerClassAbbreviation(Class::Berserker),   "BER");
}

TEST(ClassAbbreviationTest, NonPlayerClassReturnsUNK) {
    EXPECT_EQ(GetPlayerClassAbbreviation(Class::None),      "UNK");
    EXPECT_EQ(GetPlayerClassAbbreviation(Class::Banker),    "UNK");
    EXPECT_EQ(GetPlayerClassAbbreviation(255),              "UNK");
}

// ============================================================
// GetPlayerClassBit
// ============================================================
TEST(ClassBitmaskTest, AllPlayerClassesPowerOfTwo) {
    uint16_t seen = 0;
    for (uint8_t c = Class::Warrior; c <= Class::Berserker; ++c) {
        uint16_t bit = GetPlayerClassBit(c);
        EXPECT_NE(bit, 0u) << "Class " << (int)c << " should have non-zero bit";
        EXPECT_EQ(bit & seen, 0u) << "Class " << (int)c << " bit collides with another";
        EXPECT_EQ(bit & (bit - 1), 0u) << "Class " << (int)c << " bit should be power of 2";
        seen |= bit;
    }
}

TEST(ClassBitmaskTest, NonPlayerClassReturnsZero) {
    EXPECT_EQ(GetPlayerClassBit(Class::None), 0u);
    EXPECT_EQ(GetPlayerClassBit(Class::Banker), 0u);
}

TEST(ClassBitmaskTest, WarriorBitIsOne) {
    EXPECT_EQ(GetPlayerClassBit(Class::Warrior), 1u);
}

TEST(ClassBitmaskTest, AllBitsCoverALLCLASSES) {
    uint16_t all = 0;
    for (uint8_t c = Class::Warrior; c <= Class::Berserker; ++c)
        all |= GetPlayerClassBit(c);
    EXPECT_EQ(all, Class::ALL_CLASSES_BITMASK);
}

// ============================================================
// IsFighterClass / IsSpellFighterClass / IsNonSpellFighterClass
// ============================================================
TEST(ClassTypeTest, FighterClasses) {
    EXPECT_TRUE(IsFighterClass(Class::Warrior));
    EXPECT_TRUE(IsFighterClass(Class::Paladin));
    EXPECT_TRUE(IsFighterClass(Class::Ranger));
    EXPECT_TRUE(IsFighterClass(Class::ShadowKnight));
    EXPECT_TRUE(IsFighterClass(Class::Monk));
    EXPECT_TRUE(IsFighterClass(Class::Bard));
    EXPECT_TRUE(IsFighterClass(Class::Rogue));
    EXPECT_TRUE(IsFighterClass(Class::Beastlord));
    EXPECT_TRUE(IsFighterClass(Class::Berserker));
}

TEST(ClassTypeTest, NonFighterClasses) {
    EXPECT_FALSE(IsFighterClass(Class::Cleric));
    EXPECT_FALSE(IsFighterClass(Class::Wizard));
    EXPECT_FALSE(IsFighterClass(Class::None));
}

TEST(ClassTypeTest, SpellFighterClasses) {
    EXPECT_TRUE(IsSpellFighterClass(Class::Paladin));
    EXPECT_TRUE(IsSpellFighterClass(Class::Ranger));
    EXPECT_TRUE(IsSpellFighterClass(Class::ShadowKnight));
    EXPECT_TRUE(IsSpellFighterClass(Class::Beastlord));
}

TEST(ClassTypeTest, NonSpellFighterClasses) {
    EXPECT_TRUE(IsNonSpellFighterClass(Class::Warrior));
    EXPECT_TRUE(IsNonSpellFighterClass(Class::Monk));
    EXPECT_TRUE(IsNonSpellFighterClass(Class::Bard));
    EXPECT_TRUE(IsNonSpellFighterClass(Class::Rogue));
    EXPECT_TRUE(IsNonSpellFighterClass(Class::Berserker));
    EXPECT_FALSE(IsNonSpellFighterClass(Class::Paladin));
}

// ============================================================
// Hybrid / Caster / INT caster / WIS caster
// ============================================================
TEST(ClassTypeTest, HybridClasses) {
    EXPECT_TRUE(IsHybridClass(Class::Paladin));
    EXPECT_TRUE(IsHybridClass(Class::Ranger));
    EXPECT_TRUE(IsHybridClass(Class::ShadowKnight));
    EXPECT_TRUE(IsHybridClass(Class::Bard));
    EXPECT_TRUE(IsHybridClass(Class::Beastlord));
    EXPECT_FALSE(IsHybridClass(Class::Warrior));
    EXPECT_FALSE(IsHybridClass(Class::Wizard));
}

TEST(ClassTypeTest, CasterClasses) {
    EXPECT_TRUE(IsCasterClass(Class::Cleric));
    EXPECT_TRUE(IsCasterClass(Class::Druid));
    EXPECT_TRUE(IsCasterClass(Class::Shaman));
    EXPECT_TRUE(IsCasterClass(Class::Necromancer));
    EXPECT_TRUE(IsCasterClass(Class::Wizard));
    EXPECT_TRUE(IsCasterClass(Class::Magician));
    EXPECT_TRUE(IsCasterClass(Class::Enchanter));
    EXPECT_FALSE(IsCasterClass(Class::Warrior));
    EXPECT_FALSE(IsCasterClass(Class::Paladin)); // hybrid, not pure caster
}

TEST(ClassTypeTest, INTCasterClasses) {
    EXPECT_TRUE(IsINTCasterClass(Class::Necromancer));
    EXPECT_TRUE(IsINTCasterClass(Class::Wizard));
    EXPECT_TRUE(IsINTCasterClass(Class::Magician));
    EXPECT_TRUE(IsINTCasterClass(Class::Enchanter));
    EXPECT_FALSE(IsINTCasterClass(Class::Cleric));
    EXPECT_FALSE(IsINTCasterClass(Class::Druid));
}

TEST(ClassTypeTest, WISCasterClasses) {
    EXPECT_TRUE(IsWISCasterClass(Class::Cleric));
    EXPECT_TRUE(IsWISCasterClass(Class::Druid));
    EXPECT_TRUE(IsWISCasterClass(Class::Shaman));
    EXPECT_FALSE(IsWISCasterClass(Class::Wizard));
    EXPECT_FALSE(IsWISCasterClass(Class::Paladin));
}

// ============================================================
// Armor type classification
// ============================================================
TEST(ClassArmorTest, PlateClasses) {
    EXPECT_TRUE(IsPlateClass(Class::Warrior));
    EXPECT_TRUE(IsPlateClass(Class::Cleric));
    EXPECT_TRUE(IsPlateClass(Class::Paladin));
    EXPECT_TRUE(IsPlateClass(Class::ShadowKnight));
    EXPECT_TRUE(IsPlateClass(Class::Bard));
    EXPECT_FALSE(IsPlateClass(Class::Ranger));
    EXPECT_FALSE(IsPlateClass(Class::Wizard));
}

TEST(ClassArmorTest, ChainClasses) {
    EXPECT_TRUE(IsChainClass(Class::Ranger));
    EXPECT_TRUE(IsChainClass(Class::Rogue));
    EXPECT_TRUE(IsChainClass(Class::Shaman));
    EXPECT_TRUE(IsChainClass(Class::Berserker));
    EXPECT_FALSE(IsChainClass(Class::Warrior));
}

TEST(ClassArmorTest, LeatherClasses) {
    EXPECT_TRUE(IsLeatherClass(Class::Druid));
    EXPECT_TRUE(IsLeatherClass(Class::Monk));
    EXPECT_TRUE(IsLeatherClass(Class::Beastlord));
    EXPECT_FALSE(IsLeatherClass(Class::Rogue));
}

TEST(ClassArmorTest, ClothClasses) {
    EXPECT_TRUE(IsClothClass(Class::Necromancer));
    EXPECT_TRUE(IsClothClass(Class::Wizard));
    EXPECT_TRUE(IsClothClass(Class::Magician));
    EXPECT_TRUE(IsClothClass(Class::Enchanter));
    EXPECT_FALSE(IsClothClass(Class::Druid));
}

TEST(ClassArmorTest, ClassArmorTypeCorrect) {
    EXPECT_EQ(ClassArmorType(Class::Warrior),     ARMOR_TYPE_PLATE);
    EXPECT_EQ(ClassArmorType(Class::Ranger),      ARMOR_TYPE_CHAIN);
    EXPECT_EQ(ClassArmorType(Class::Druid),       ARMOR_TYPE_LEATHER);
    EXPECT_EQ(ClassArmorType(Class::Wizard),      ARMOR_TYPE_CLOTH);
    EXPECT_EQ(ClassArmorType(Class::None),        ARMOR_TYPE_UNKNOWN);
}

// ============================================================
// GetClassIDName (level-based titles)
// ============================================================
TEST(ClassIDNameTest, LowLevelReturnsBaseName) {
    EXPECT_STREQ(GetClassIDName(Class::Warrior,    1),  "Warrior");
    EXPECT_STREQ(GetClassIDName(Class::Cleric,     1),  "Cleric");
    EXPECT_STREQ(GetClassIDName(Class::Paladin,    1),  "Paladin");
    EXPECT_STREQ(GetClassIDName(Class::Ranger,     1),  "Ranger");
    EXPECT_STREQ(GetClassIDName(Class::Druid,      1),  "Druid");
    EXPECT_STREQ(GetClassIDName(Class::Monk,       1),  "Monk");
    EXPECT_STREQ(GetClassIDName(Class::Rogue,      1),  "Rogue");
}

TEST(ClassIDNameTest, HighLevelWarriorTitle) {
    EXPECT_STREQ(GetClassIDName(Class::Warrior, 51), "Champion");
    EXPECT_STREQ(GetClassIDName(Class::Warrior, 60), "Warlord");
    EXPECT_STREQ(GetClassIDName(Class::Warrior, 75), "Imperator");
}

TEST(ClassIDNameTest, HighLevelClericTitle) {
    EXPECT_STREQ(GetClassIDName(Class::Cleric, 51), "Vicar");
    EXPECT_STREQ(GetClassIDName(Class::Cleric, 60), "High Priest");
    EXPECT_STREQ(GetClassIDName(Class::Cleric, 75), "Exemplar");
}

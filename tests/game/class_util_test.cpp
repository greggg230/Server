#include <gtest/gtest.h>
#include "common/classes.h"

// ── IsPlayerClass ─────────────────────────────────────────────────────────────

TEST(ClassUtilTest, IsPlayerClass_ValidClasses) {
	EXPECT_TRUE(IsPlayerClass(Class::Warrior));
	EXPECT_TRUE(IsPlayerClass(Class::Cleric));
	EXPECT_TRUE(IsPlayerClass(Class::Berserker)); // highest player class (16)
	EXPECT_TRUE(IsPlayerClass(Class::Beastlord));
}

TEST(ClassUtilTest, IsPlayerClass_InvalidIds) {
	EXPECT_FALSE(IsPlayerClass(Class::None));
	EXPECT_FALSE(IsPlayerClass(Class::WarriorGM)); // GM classes
	EXPECT_FALSE(IsPlayerClass(Class::Banker));
	EXPECT_FALSE(IsPlayerClass(255));
}

// ── IsHybridClass ─────────────────────────────────────────────────────────────

TEST(ClassUtilTest, IsHybridClass_Hybrids) {
	EXPECT_TRUE(IsHybridClass(Class::Paladin));
	EXPECT_TRUE(IsHybridClass(Class::Ranger));
	EXPECT_TRUE(IsHybridClass(Class::ShadowKnight));
	EXPECT_TRUE(IsHybridClass(Class::Bard));
	EXPECT_TRUE(IsHybridClass(Class::Beastlord));
}

TEST(ClassUtilTest, IsHybridClass_NonHybrids) {
	EXPECT_FALSE(IsHybridClass(Class::Warrior));
	EXPECT_FALSE(IsHybridClass(Class::Wizard));
	EXPECT_FALSE(IsHybridClass(Class::Cleric));
	EXPECT_FALSE(IsHybridClass(Class::Rogue));
}

// ── IsCasterClass ─────────────────────────────────────────────────────────────

TEST(ClassUtilTest, IsCasterClass_Casters) {
	EXPECT_TRUE(IsCasterClass(Class::Cleric));
	EXPECT_TRUE(IsCasterClass(Class::Druid));
	EXPECT_TRUE(IsCasterClass(Class::Shaman));
	EXPECT_TRUE(IsCasterClass(Class::Necromancer));
	EXPECT_TRUE(IsCasterClass(Class::Wizard));
	EXPECT_TRUE(IsCasterClass(Class::Magician));
	EXPECT_TRUE(IsCasterClass(Class::Enchanter));
}

TEST(ClassUtilTest, IsCasterClass_NonCasters) {
	EXPECT_FALSE(IsCasterClass(Class::Warrior));
	EXPECT_FALSE(IsCasterClass(Class::Paladin)); // hybrid
	EXPECT_FALSE(IsCasterClass(Class::Ranger));
	EXPECT_FALSE(IsCasterClass(Class::Monk));
	EXPECT_FALSE(IsCasterClass(Class::Rogue));
	EXPECT_FALSE(IsCasterClass(Class::Berserker));
}

// ── IsINTCasterClass / IsWISCasterClass ───────────────────────────────────────

TEST(ClassUtilTest, IsINTCasterClass) {
	EXPECT_TRUE(IsINTCasterClass(Class::Necromancer));
	EXPECT_TRUE(IsINTCasterClass(Class::Wizard));
	EXPECT_TRUE(IsINTCasterClass(Class::Magician));
	EXPECT_TRUE(IsINTCasterClass(Class::Enchanter));
	EXPECT_FALSE(IsINTCasterClass(Class::Cleric));
	EXPECT_FALSE(IsINTCasterClass(Class::Shaman));
}

TEST(ClassUtilTest, IsWISCasterClass) {
	EXPECT_TRUE(IsWISCasterClass(Class::Cleric));
	EXPECT_TRUE(IsWISCasterClass(Class::Druid));
	EXPECT_TRUE(IsWISCasterClass(Class::Shaman));
	EXPECT_FALSE(IsWISCasterClass(Class::Wizard));
	EXPECT_FALSE(IsWISCasterClass(Class::Paladin));
}

// ── Armor type predicates ─────────────────────────────────────────────────────

TEST(ClassUtilTest, IsPlateClass) {
	EXPECT_TRUE(IsPlateClass(Class::Warrior));
	EXPECT_TRUE(IsPlateClass(Class::Cleric));
	EXPECT_TRUE(IsPlateClass(Class::Paladin));
	EXPECT_TRUE(IsPlateClass(Class::ShadowKnight));
	EXPECT_TRUE(IsPlateClass(Class::Bard));
	EXPECT_FALSE(IsPlateClass(Class::Wizard));
	EXPECT_FALSE(IsPlateClass(Class::Rogue));
}

TEST(ClassUtilTest, IsChainClass) {
	EXPECT_TRUE(IsChainClass(Class::Ranger));
	EXPECT_TRUE(IsChainClass(Class::Rogue));
	EXPECT_TRUE(IsChainClass(Class::Shaman));
	EXPECT_TRUE(IsChainClass(Class::Berserker));
	EXPECT_FALSE(IsChainClass(Class::Warrior));
}

TEST(ClassUtilTest, IsLeatherClass) {
	EXPECT_TRUE(IsLeatherClass(Class::Druid));
	EXPECT_TRUE(IsLeatherClass(Class::Monk));
	EXPECT_TRUE(IsLeatherClass(Class::Beastlord));
	EXPECT_FALSE(IsLeatherClass(Class::Warrior));
}

TEST(ClassUtilTest, IsClothClass) {
	EXPECT_TRUE(IsClothClass(Class::Necromancer));
	EXPECT_TRUE(IsClothClass(Class::Wizard));
	EXPECT_TRUE(IsClothClass(Class::Magician));
	EXPECT_TRUE(IsClothClass(Class::Enchanter));
	EXPECT_FALSE(IsClothClass(Class::Cleric));
}

// ── ClassArmorType ────────────────────────────────────────────────────────────

TEST(ClassUtilTest, ClassArmorType_Plate) {
	EXPECT_EQ(ARMOR_TYPE_PLATE, ClassArmorType(Class::Warrior));
	EXPECT_EQ(ARMOR_TYPE_PLATE, ClassArmorType(Class::Cleric));
	EXPECT_EQ(ARMOR_TYPE_PLATE, ClassArmorType(Class::Paladin));
}

TEST(ClassUtilTest, ClassArmorType_Chain) {
	EXPECT_EQ(ARMOR_TYPE_CHAIN, ClassArmorType(Class::Ranger));
	EXPECT_EQ(ARMOR_TYPE_CHAIN, ClassArmorType(Class::Rogue));
}

TEST(ClassUtilTest, ClassArmorType_Leather) {
	EXPECT_EQ(ARMOR_TYPE_LEATHER, ClassArmorType(Class::Monk));
	EXPECT_EQ(ARMOR_TYPE_LEATHER, ClassArmorType(Class::Druid));
}

TEST(ClassUtilTest, ClassArmorType_Cloth) {
	EXPECT_EQ(ARMOR_TYPE_CLOTH, ClassArmorType(Class::Wizard));
	EXPECT_EQ(ARMOR_TYPE_CLOTH, ClassArmorType(Class::Enchanter));
}

TEST(ClassUtilTest, ClassArmorType_Unknown) {
	EXPECT_EQ(ARMOR_TYPE_UNKNOWN, ClassArmorType(Class::None));
	EXPECT_EQ(ARMOR_TYPE_UNKNOWN, ClassArmorType(255));
}

// ── Class constants ────────────────────────────────────────────────────────────

TEST(ClassUtilTest, PlayerClassCount) {
	EXPECT_EQ(16u, Class::PLAYER_CLASS_COUNT);
}

TEST(ClassUtilTest, AllClassesBitmask) {
	// 16 classes = bits 0-15 = 0xFFFF = 65535
	EXPECT_EQ(65535u, Class::ALL_CLASSES_BITMASK);
}

TEST(ClassUtilTest, ClassIds_Spot) {
	EXPECT_EQ(1u,  Class::Warrior);
	EXPECT_EQ(16u, Class::Berserker);
	EXPECT_EQ(11u, Class::Necromancer);
}

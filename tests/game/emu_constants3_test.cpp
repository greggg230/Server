#include <gtest/gtest.h>
#include "common/emu_constants.h"

// ============================================================
// EQ::spells::CastingSlot enum class
// ============================================================
TEST(CastingSlotTest, Gem1IsZero) {
    EXPECT_EQ(static_cast<uint32>(EQ::spells::CastingSlot::Gem1), 0u);
}

TEST(CastingSlotTest, Gem12Is11) {
    EXPECT_EQ(static_cast<uint32>(EQ::spells::CastingSlot::Gem12), 11u);
}

TEST(CastingSlotTest, MaxGemsIs12) {
    EXPECT_EQ(static_cast<uint32>(EQ::spells::CastingSlot::MaxGems), 12u);
}

TEST(CastingSlotTest, AbilityIs20) {
    EXPECT_EQ(static_cast<uint32>(EQ::spells::CastingSlot::Ability), 20u);
}

TEST(CastingSlotTest, PotionBeltIs21) {
    EXPECT_EQ(static_cast<uint32>(EQ::spells::CastingSlot::PotionBelt), 21u);
}

TEST(CastingSlotTest, DisciplineIs23) {
    EXPECT_EQ(static_cast<uint32>(EQ::spells::CastingSlot::Discipline), 23u);
}

TEST(CastingSlotTest, AltAbilityIs0xFF) {
    EXPECT_EQ(static_cast<uint32>(EQ::spells::CastingSlot::AltAbility), 0xFFu);
}

// ============================================================
// ApplySpellType enum class
// ============================================================
TEST(ApplySpellTypeTest, SoloIsZero) {
    EXPECT_EQ(static_cast<int>(ApplySpellType::Solo), 0);
}

TEST(ApplySpellTypeTest, GroupIsOne) {
    EXPECT_EQ(static_cast<int>(ApplySpellType::Group), 1);
}

TEST(ApplySpellTypeTest, RaidIsTwo) {
    EXPECT_EQ(static_cast<int>(ApplySpellType::Raid), 2);
}

// ============================================================
// EntityFilterType enum class
// ============================================================
TEST(EntityFilterTypeTest, AllIsZero) {
    EXPECT_EQ(static_cast<int>(EntityFilterType::All), 0);
}

TEST(EntityFilterTypeTest, BotsIsOne) {
    EXPECT_EQ(static_cast<int>(EntityFilterType::Bots), 1);
}

TEST(EntityFilterTypeTest, ClientsIsTwo) {
    EXPECT_EQ(static_cast<int>(EntityFilterType::Clients), 2);
}

TEST(EntityFilterTypeTest, NPCsIsThree) {
    EXPECT_EQ(static_cast<int>(EntityFilterType::NPCs), 3);
}

// ============================================================
// EQ::profile namespace constants (from RoF2)
// ============================================================
TEST(EQProfileTest, BandoliersSizeIs20) {
    EXPECT_EQ(EQ::profile::BANDOLIERS_SIZE, 20);
}

TEST(EQProfileTest, BandolierItemCountIs4) {
    EXPECT_EQ(EQ::profile::BANDOLIER_ITEM_COUNT, 4);
}

TEST(EQProfileTest, PotionBeltSizeIs5) {
    EXPECT_EQ(EQ::profile::POTION_BELT_SIZE, 5);
}

TEST(EQProfileTest, SkillArraySizeIs100) {
    EXPECT_EQ(EQ::profile::SKILL_ARRAY_SIZE, 100);
}

// ============================================================
// EQ::behavior namespace constants (from RoF2)
// ============================================================
TEST(EQBehaviorTest, CoinHasWeightIsFalse) {
    EXPECT_FALSE(EQ::behavior::CoinHasWeight);
}


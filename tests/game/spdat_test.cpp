#include <gtest/gtest.h>
#include "common/spdat.h"

// ============================================================
// Spell ID macros — well-known hard-coded spell IDs
// ============================================================
TEST(SpdatMacroTest, SpellUnknownIs0xFFFF) {
    EXPECT_EQ(SPELL_UNKNOWN, 0xFFFFu);
}

TEST(SpdatMacroTest, PoisonProcIs0xFFFE) {
    EXPECT_EQ(POISON_PROC, 0xFFFEu);
}

TEST(SpdatMacroTest, CompleteHealIs13) {
    EXPECT_EQ(SPELL_COMPLETE_HEAL, 13);
}

TEST(SpdatMacroTest, LayOnHandsIs87) {
    EXPECT_EQ(SPELL_LAY_ON_HANDS, 87);
}

TEST(SpdatMacroTest, HarmTouchIs88) {
    EXPECT_EQ(SPELL_HARM_TOUCH, 88);
}

TEST(SpdatMacroTest, HarmTouch2Is2821) {
    EXPECT_EQ(SPELL_HARM_TOUCH2, 2821);
}

TEST(SpdatMacroTest, CharmIs300) {
    EXPECT_EQ(SPELL_CHARM, 300);
}

// ============================================================
// MobAISpellRange constant
// ============================================================
TEST(SpdatConstTest, MobAISpellRangeIs100) {
    EXPECT_EQ(MobAISpellRange, 100u);
}

// ============================================================
// FocusLimitIncludes enum
// ============================================================
TEST(FocusLimitIncludesTest, ExistsLimitResistIsZero) {
    EXPECT_EQ(IncludeExistsSELimitResist, 0);
}

TEST(FocusLimitIncludesTest, FoundLimitResistIsOne) {
    EXPECT_EQ(IncludeFoundSELimitResist, 1);
}

TEST(FocusLimitIncludesTest, ExistsLimitEffectIsFour) {
    EXPECT_EQ(IncludeExistsSELimitEffect, 4);
}

TEST(FocusLimitIncludesTest, FoundFFItemClassIs17) {
    EXPECT_EQ(IncludeFoundSEFFItemClass, 17);
}

// ============================================================
// SpellRestriction enum
// ============================================================
TEST(SpellRestrictionTest, IsAnimalOrHumanoidIs100) {
    EXPECT_EQ(IS_ANIMAL_OR_HUMANOID, 100);
}

TEST(SpellRestrictionTest, IsDragonIs101) {
    EXPECT_EQ(IS_DRAGON, 101);
}

TEST(SpellRestrictionTest, IsUndeadIs120) {
    EXPECT_EQ(IS_UNDEAD, 120);
}

TEST(SpellRestrictionTest, IsHumanoidIs123) {
    EXPECT_EQ(IS_HUMANOID, 123);
}

// ============================================================
// InvisType enum
// ============================================================
TEST(InvisTypeTest, InvisibleIsZero) {
    EXPECT_EQ(T_INVISIBLE, 0);
}

TEST(InvisTypeTest, InvisVerseUndeadIsOne) {
    EXPECT_EQ(T_INVISIBLE_VERSE_UNDEAD, 1);
}

TEST(InvisTypeTest, InvisVerseAnimalIsTwo) {
    EXPECT_EQ(T_INVISIBLE_VERSE_ANIMAL, 2);
}

// ============================================================
// ProcType enum
// ============================================================
TEST(ProcTypeTest, MeleeProcIsOne) {
    EXPECT_EQ(MELEE_PROC, 1);
}

TEST(ProcTypeTest, RangedProcIsTwo) {
    EXPECT_EQ(RANGED_PROC, 2);
}

TEST(ProcTypeTest, DefensiveProcIsThree) {
    EXPECT_EQ(DEFENSIVE_PROC, 3);
}

TEST(ProcTypeTest, SkillProcSuccessIsFive) {
    EXPECT_EQ(SKILL_PROC_SUCCESS, 5);
}

// ============================================================
// SpellTypes bitmask enum
// ============================================================
TEST(SpellTypesTest, NukeIsBit0) {
    EXPECT_EQ(SpellType_Nuke, 1u << 0);
}

TEST(SpellTypesTest, HealIsBit1) {
    EXPECT_EQ(SpellType_Heal, 1u << 1);
}

TEST(SpellTypesTest, BuffIsBit3) {
    EXPECT_EQ(SpellType_Buff, 1u << 3);
}

TEST(SpellTypesTest, MezIsBit11) {
    EXPECT_EQ(SpellType_Mez, 1u << 11);
}

TEST(SpellTypesTest, ResurrectIsBit16) {
    EXPECT_EQ(SpellType_Resurrect, 1u << 16);
}

TEST(SpellTypesTest, PreCombatBuffSongIsBit21) {
    EXPECT_EQ(SpellType_PreCombatBuffSong, 1u << 21);
}

// ============================================================
// BotSpellTypes namespace constexpr values
// ============================================================
TEST(BotSpellTypesTest, NukeIsZero) {
    constexpr uint16 v = BotSpellTypes::Nuke;
    EXPECT_EQ(v, 0u);
}

TEST(BotSpellTypesTest, RegularHealIsOne) {
    constexpr uint16 v = BotSpellTypes::RegularHeal;
    EXPECT_EQ(v, 1u);
}

TEST(BotSpellTypesTest, CharmIs12) {
    constexpr uint16 v = BotSpellTypes::Charm;
    EXPECT_EQ(v, 12u);
}

TEST(BotSpellTypesTest, HateReduxIs17) {
    constexpr uint16 v = BotSpellTypes::HateRedux;
    EXPECT_EQ(v, 17u);
}

TEST(BotSpellTypesTest, PreCombatBuffSongIs21) {
    constexpr uint16 v = BotSpellTypes::PreCombatBuffSong;
    EXPECT_EQ(v, 21u);
}

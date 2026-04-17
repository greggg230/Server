#include <gtest/gtest.h>
#include "common/eq_constants.h"
#include "common/features.h"

// ============================================================
// Language namespace
// ============================================================
TEST(LanguageConstantsTest, CommonTongueIsZero) {
    EXPECT_EQ(Language::CommonTongue, 0u);
}

TEST(LanguageConstantsTest, SequentialRaces) {
    EXPECT_EQ(Language::Barbarian,  1u);
    EXPECT_EQ(Language::Erudian,    2u);
    EXPECT_EQ(Language::Elvish,     3u);
    EXPECT_EQ(Language::DarkElvish, 4u);
    EXPECT_EQ(Language::Dwarvish,   5u);
    EXPECT_EQ(Language::Troll,      6u);
    EXPECT_EQ(Language::Ogre,       7u);
    EXPECT_EQ(Language::Gnomish,    8u);
    EXPECT_EQ(Language::Halfling,   9u);
}

TEST(LanguageConstantsTest, HigherLanguages) {
    EXPECT_EQ(Language::ThievesCant,   10u);
    EXPECT_EQ(Language::Froglok,       13u);
    EXPECT_EQ(Language::Dragon,        21u);
    EXPECT_EQ(Language::ElderDragon,   22u);
    EXPECT_EQ(Language::VahShir,       24u);
    EXPECT_EQ(Language::Alaran,        25u);
    EXPECT_EQ(Language::Hadal,         26u);
}

TEST(LanguageConstantsTest, MaxValueIs100) {
    EXPECT_EQ(Language::MaxValue, 100u);
}

// ============================================================
// PetInfoType namespace
// ============================================================
TEST(PetInfoTypeTest, CurrentIsZero) {
    EXPECT_EQ(PetInfoType::Current,   0);
}

TEST(PetInfoTypeTest, SuspendedIsOne) {
    EXPECT_EQ(PetInfoType::Suspended, 1);
}

// ============================================================
// BuffEffectType namespace
// ============================================================
TEST(BuffEffectTypeTest, NoneIsZero) {
    EXPECT_EQ(BuffEffectType::None,        0u);
}

TEST(BuffEffectTypeTest, BuffIsTwo) {
    EXPECT_EQ(BuffEffectType::Buff,        2u);
}

TEST(BuffEffectTypeTest, InverseBuffIsFour) {
    EXPECT_EQ(BuffEffectType::InverseBuff, 4u);
}

// ============================================================
// AlternateCurrencyMode namespace
// ============================================================
TEST(AlternateCurrencyModeTest, UpdateIsSeven) {
    EXPECT_EQ(AlternateCurrencyMode::Update,   7u);
}

TEST(AlternateCurrencyModeTest, PopulateIsEight) {
    EXPECT_EQ(AlternateCurrencyMode::Populate, 8u);
}

// ============================================================
// ChatChannelNames enum
// ============================================================
TEST(ChatChannelNamesTest, GuildIsZero) {
    EXPECT_EQ(ChatChannel_Guild,   0u);
}

TEST(ChatChannelNamesTest, CoreChannelValues) {
    EXPECT_EQ(ChatChannel_Group,   2u);
    EXPECT_EQ(ChatChannel_Shout,   3u);
    EXPECT_EQ(ChatChannel_Auction, 4u);
    EXPECT_EQ(ChatChannel_OOC,     5u);
    EXPECT_EQ(ChatChannel_Tell,    7u);
    EXPECT_EQ(ChatChannel_Say,     8u);
}

TEST(ChatChannelNamesTest, HigherChannels) {
    EXPECT_EQ(ChatChannel_GMSAY,   11u);
    EXPECT_EQ(ChatChannel_Raid,    15u);
    EXPECT_EQ(ChatChannel_Emotes,  22u);
}

// ============================================================
// ZoneBlockedSpellTypes namespace
// ============================================================
TEST(ZoneBlockedSpellTypesTest, ZoneWideIsOne) {
    EXPECT_EQ(ZoneBlockedSpellTypes::ZoneWide, 1u);
}

TEST(ZoneBlockedSpellTypesTest, RegionIsTwo) {
    EXPECT_EQ(ZoneBlockedSpellTypes::Region,   2u);
}

// ============================================================
// StartZoneIndex enum
// ============================================================
TEST(StartZoneIndexTest, OdusIsZero) {
    EXPECT_EQ(Odus, 0);
}

TEST(StartZoneIndexTest, SequentialValues) {
    EXPECT_EQ(Qeynos,        1);
    EXPECT_EQ(Halas,         2);
    EXPECT_EQ(Rivervale,     3);
    EXPECT_EQ(Freeport,      4);
    EXPECT_EQ(Neriak,        5);
    EXPECT_EQ(Grobb,         6);
    EXPECT_EQ(Oggok,         7);
    EXPECT_EQ(Kaladim,       8);
    EXPECT_EQ(GreaterFaydark,9);
    EXPECT_EQ(Felwithe,      10);
    EXPECT_EQ(Akanon,        11);
    EXPECT_EQ(Cabilis,       12);
    EXPECT_EQ(SharVahl,      13);
    EXPECT_EQ(RatheMtn,      14);
}

// ============================================================
// DB faction constants
// ============================================================
TEST(DBFactionConstantsTest, KnownValues) {
    EXPECT_EQ(DB_FACTION_GEM_CHOPPERS, 255u);
    EXPECT_EQ(DB_FACTION_HERETICS,     265u);
    EXPECT_EQ(DB_FACTION_KING_AKANON,  333u);
}

TEST(DBFactionConstantsTest, MaxSpellDBId) {
    EXPECT_EQ(MAX_SPELL_DB_ID_VAL, 65535u);
}

// ============================================================
// features.h — skill reuse times (enum values)
// ============================================================
TEST(SkillReuseTimeTest, FeignDeathIs9) {
    EXPECT_EQ(FeignDeathReuseTime, 9);
}

TEST(SkillReuseTimeTest, SneakIs7) {
    EXPECT_EQ(SneakReuseTime, 7);
}

TEST(SkillReuseTimeTest, HideIs8) {
    EXPECT_EQ(HideReuseTime, 8);
}

TEST(SkillReuseTimeTest, TauntIs5) {
    EXPECT_EQ(TauntReuseTime, 5);
}

TEST(SkillReuseTimeTest, HarmTouchLargerThan1000) {
    // HarmTouchReuseTime = 4300
    EXPECT_EQ(HarmTouchReuseTime, 4300);
}

TEST(SkillReuseTimeTest, LayOnHandsMatchesHarmTouch) {
    EXPECT_EQ(LayOnHandsReuseTime, HarmTouchReuseTime);
}

// ============================================================
// features.h — AI timer values (milliseconds)
// ============================================================
TEST(AITimerTest, MovementIs100ms) {
    EXPECT_EQ(AImovement_duration, 100);
}

TEST(AITimerTest, ThinkIs50ms) {
    EXPECT_EQ(AIthink_duration, 50);
}

TEST(AITimerTest, ScanAreaIs6000ms) {
    EXPECT_EQ(AIscanarea_delay, 6000);
}

// ============================================================
// features.h — NPC attack modifiers
// ============================================================
TEST(NPCAttackModifierTest, DualAttackIs20) {
    EXPECT_EQ(NPCDualAttackModifier,  20);
}

TEST(NPCAttackModifierTest, TripleAttackIsZero) {
    EXPECT_EQ(NPCTripleAttackModifier, 0);
}

TEST(NPCAttackModifierTest, QuadAttackIsNegative) {
    EXPECT_EQ(NPCQuadAttackModifier, -20);
}

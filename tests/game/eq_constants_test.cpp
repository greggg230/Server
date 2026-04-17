#include <gtest/gtest.h>
#include "common/eq_constants.h"

// ============================================================
// Animation constants
// ============================================================
TEST(AnimationConstantsTest, StandingIs100) {
    EXPECT_EQ(Animation::Standing,  100u);
}

TEST(AnimationConstantsTest, FreezeIs102) {
    EXPECT_EQ(Animation::Freeze, 102u);
}

TEST(AnimationConstantsTest, LootingIs105) {
    EXPECT_EQ(Animation::Looting, 105u);
}

TEST(AnimationConstantsTest, SittingIs110) {
    EXPECT_EQ(Animation::Sitting, 110u);
}

TEST(AnimationConstantsTest, CrouchingIs111) {
    EXPECT_EQ(Animation::Crouching, 111u);
}

TEST(AnimationConstantsTest, LyingIs115) {
    EXPECT_EQ(Animation::Lying, 115u);
}

// ============================================================
// EmuAppearance enum
// ============================================================
TEST(EmuAppearanceTest, StandingIsZero) {
    EXPECT_EQ(eaStanding, 0);
}

TEST(EmuAppearanceTest, ValuesAreSequential) {
    EXPECT_EQ(eaSitting,   1);
    EXPECT_EQ(eaCrouching, 2);
    EXPECT_EQ(eaDead,      3);
    EXPECT_EQ(eaLooting,   4);
}

TEST(EmuAppearanceTest, MaxAppearanceIs5) {
    EXPECT_EQ(_eaMaxAppearance, 5);
}

// ============================================================
// Chat color constants (color IDs)
// ============================================================
TEST(ChatColorTest, BasicColorsStartAtZero) {
    EXPECT_EQ(Chat::White,    0u);
    EXPECT_EQ(Chat::DimGray,  1u);
    EXPECT_EQ(Chat::Default,  1u);  // alias for DimGray
    EXPECT_EQ(Chat::Green,    2u);
}

TEST(ChatColorTest, HigherColorIDs) {
    EXPECT_EQ(Chat::Red,     13u);
    EXPECT_EQ(Chat::Yellow,  15u);
    EXPECT_EQ(Chat::Blue,    16u);
    EXPECT_EQ(Chat::Cyan,    18u);
    EXPECT_EQ(Chat::Black,   20u);
}

// ============================================================
// Chat channel IDs (256+)
// ============================================================
TEST(ChatChannelTest, SayIs256) {
    EXPECT_EQ(Chat::Say,     256u);
    EXPECT_EQ(Chat::Tell,    257u);
    EXPECT_EQ(Chat::Group,   258u);
    EXPECT_EQ(Chat::Guild,   259u);
    EXPECT_EQ(Chat::OOC,     260u);
    EXPECT_EQ(Chat::Auction, 261u);
    EXPECT_EQ(Chat::Shout,   262u);
    EXPECT_EQ(Chat::Emote,   263u);
}

TEST(ChatChannelTest, CombatChannels) {
    EXPECT_EQ(Chat::YouHitOther,  265u);
    EXPECT_EQ(Chat::OtherHitYou,  266u);
    EXPECT_EQ(Chat::YouMissOther,  267u);
    EXPECT_EQ(Chat::OtherMissYou, 268u);
}

TEST(ChatChannelTest, HighChannels) {
    EXPECT_EQ(Chat::RaidSay,      327u);
    EXPECT_EQ(Chat::ItemLink,     326u);
    EXPECT_EQ(Chat::Experience,   334u);
    EXPECT_EQ(Chat::Stun,         340u);
}

// ============================================================
// MoneyTypes enum
// ============================================================
TEST(MoneyTypesTest, CopperIsZero) {
    EXPECT_EQ(Copper,   0);
}

TEST(MoneyTypesTest, SequentialValues) {
    EXPECT_EQ(Silver,   1);
    EXPECT_EQ(Gold,     2);
    EXPECT_EQ(Platinum, 3);
}

// ============================================================
// MoneySubtypes enum
// ============================================================
TEST(MoneySubtypesTest, PersonalIsZero) {
    EXPECT_EQ(Personal,    0);
}

TEST(MoneySubtypesTest, SequentialValues) {
    EXPECT_EQ(Bank,        1);
    EXPECT_EQ(Cursor,      2);
    EXPECT_EQ(SharedBank,  3);
}

// ============================================================
// ZoningMessage enum
// ============================================================
TEST(ZoningMessageTest, SuccessIsOne) {
    EXPECT_EQ(ZoneSuccess, 1);
}

TEST(ZoningMessageTest, NoMessageIsZero) {
    EXPECT_EQ(ZoneNoMessage, 0);
}

TEST(ZoningMessageTest, ErrorsAreNegative) {
    EXPECT_LT(ZoneNotReady,    0);
    EXPECT_LT(ZoneValidPC,     0);
    EXPECT_LT(ZoneStoryZone,   0);
    EXPECT_LT(ZoneNoExpansion, 0);
    EXPECT_LT(ZoneNoExperience, 0);
}

TEST(ZoningMessageTest, SpecificErrorValues) {
    EXPECT_EQ(ZoneNotReady,     -1);
    EXPECT_EQ(ZoneValidPC,      -2);
    EXPECT_EQ(ZoneStoryZone,    -3);
    EXPECT_EQ(ZoneNoExpansion,  -6);
    EXPECT_EQ(ZoneNoExperience, -7);
}

// ============================================================
// ResurrectionActions enum
// ============================================================
TEST(ResurrectionActionsTest, DeclineIsZero) {
    EXPECT_EQ(Decline, 0);
    EXPECT_EQ(Accept,  1);
}

// ============================================================
// SpellTimeRestrictions enum
// ============================================================
TEST(SpellTimeRestrictionsTest, NoRestrictionIsZero) {
    EXPECT_EQ(NoRestriction, 0);
    EXPECT_EQ(Day,           1);
    EXPECT_EQ(Night,         2);
}

// ============================================================
// ExpSource enum
// ============================================================
TEST(ExpSourceTest, QuestIsZero) {
    EXPECT_EQ(Quest,        0);
    EXPECT_EQ(GM,           1);
    EXPECT_EQ(Kill,         2);
    EXPECT_EQ(Death,        3);
    EXPECT_EQ(Resurrection, 4);
    EXPECT_EQ(LDoNChest,    5);
    EXPECT_EQ(Task,         6);
    EXPECT_EQ(Sacrifice,    7);
}

// ============================================================
// ScribeSpellActions enum
// ============================================================
TEST(ScribeSpellActionsTest, ScribeIsZero) {
    EXPECT_EQ(Scribe,     0);
    EXPECT_EQ(Memorize,   1);
    EXPECT_EQ(Unmemorize, 2);
}

// ============================================================
// RaidLootType constants
// ============================================================
TEST(RaidLootTypeTest, LeaderOnlyIs1) {
    EXPECT_EQ(RaidLootType::LeaderOnly,                1u);
    EXPECT_EQ(RaidLootType::LeaderAndGroupLeadersOnly, 2u);
    EXPECT_EQ(RaidLootType::LeaderSelected,            3u);
    EXPECT_EQ(RaidLootType::EntireRaid,                4u);
}

// ============================================================
// Anonymity enum
// ============================================================
TEST(AnonymityTest, NotAnonymousIsZero) {
    EXPECT_EQ(NotAnonymous, 0);
    EXPECT_EQ(Anonymous,    1);
    EXPECT_EQ(Roleplaying,  2);
}

// ============================================================
// RECAST_TYPE_UNLINKED_ITEM constant
// ============================================================
TEST(RecastTypeTest, UnlinkedItemIsNegativeOne) {
    EXPECT_EQ(RECAST_TYPE_UNLINKED_ITEM, -1);
}

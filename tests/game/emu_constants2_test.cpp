#include <gtest/gtest.h>
#include "common/emu_constants.h"

// ============================================================
// ServerLockType enum
// ============================================================
TEST(ServerLockTypeTest, ListIsZero) {
    EXPECT_EQ(ServerLockType::List, 0);
}

TEST(ServerLockTypeTest, LockIsOne) {
    EXPECT_EQ(ServerLockType::Lock, 1);
}

TEST(ServerLockTypeTest, UnlockIsTwo) {
    EXPECT_EQ(ServerLockType::Unlock, 2);
}

// ============================================================
// Invisibility enum
// ============================================================
TEST(InvisibilityEnumTest, VisibleIsZero) {
    EXPECT_EQ(Invisibility::Visible, 0u);
}

TEST(InvisibilityEnumTest, InvisibleIsOne) {
    EXPECT_EQ(Invisibility::Invisible, 1u);
}

TEST(InvisibilityEnumTest, SpecialIs255) {
    EXPECT_EQ(Invisibility::Special, 255u);
}

// ============================================================
// AugmentActions enum
// ============================================================
TEST(AugmentActionsTest, InsertIsZero) {
    EXPECT_EQ(AugmentActions::Insert, 0);
}

TEST(AugmentActionsTest, RemoveIsOne) {
    EXPECT_EQ(AugmentActions::Remove, 1);
}

TEST(AugmentActionsTest, SwapIsTwo) {
    EXPECT_EQ(AugmentActions::Swap, 2);
}

TEST(AugmentActionsTest, DestroyIsThree) {
    EXPECT_EQ(AugmentActions::Destroy, 3);
}

// ============================================================
// TargetDescriptionType enum
// ============================================================
TEST(TargetDescriptionTypeTest, LCSelfIsZero) {
    EXPECT_EQ(TargetDescriptionType::LCSelf, 0u);
}

TEST(TargetDescriptionTypeTest, UCSelfIsOne) {
    EXPECT_EQ(TargetDescriptionType::UCSelf, 1u);
}

TEST(TargetDescriptionTypeTest, UCYourIsFive) {
    EXPECT_EQ(TargetDescriptionType::UCYour, 5u);
}

// ============================================================
// ReloadWorld enum
// ============================================================
TEST(ReloadWorldTest, NoRepopIsZero) {
    EXPECT_EQ(ReloadWorld::NoRepop, 0u);
}

TEST(ReloadWorldTest, RepopIsOne) {
    EXPECT_EQ(ReloadWorld::Repop, 1u);
}

TEST(ReloadWorldTest, ForceRepopIsTwo) {
    EXPECT_EQ(ReloadWorld::ForceRepop, 2u);
}

// ============================================================
// EQ::constants::BotSpellIDs
// ============================================================
TEST(BotSpellIDsTest, WarriorIs3001) {
    EXPECT_EQ(EQ::constants::BotSpellIDs::Warrior, 3001);
}

TEST(BotSpellIDsTest, BerserkerIs3016) {
    // 16 classes starting at 3001
    EXPECT_EQ(EQ::constants::BotSpellIDs::Berserker, 3016);
}

TEST(BotSpellIDsTest, ClassesAreSequential) {
    EXPECT_EQ(EQ::constants::BotSpellIDs::Cleric,   EQ::constants::BotSpellIDs::Warrior + 1);
    EXPECT_EQ(EQ::constants::BotSpellIDs::Paladin,  EQ::constants::BotSpellIDs::Warrior + 2);
    EXPECT_EQ(EQ::constants::BotSpellIDs::Enchanter,EQ::constants::BotSpellIDs::Warrior + 13);
}

// ============================================================
// EQ::constants::GravityBehavior
// ============================================================
TEST(GravityBehaviorTest, GroundIsZero) {
    EXPECT_EQ(static_cast<int8>(EQ::constants::GravityBehavior::Ground), 0);
}

TEST(GravityBehaviorTest, FlyingIsOne) {
    EXPECT_EQ(static_cast<int8>(EQ::constants::GravityBehavior::Flying), 1);
}

TEST(GravityBehaviorTest, LevitateWhileRunningIsFive) {
    EXPECT_EQ(static_cast<int8>(EQ::constants::GravityBehavior::LevitateWhileRunning), 5);
}

// ============================================================
// EQ::constants::EmoteEventTypes
// ============================================================
TEST(EmoteEventTypesTest, LeaveCombatIsZero) {
    EXPECT_EQ(static_cast<uint8>(EQ::constants::EmoteEventTypes::LeaveCombat), 0u);
}

TEST(EmoteEventTypesTest, EnterCombatIsOne) {
    EXPECT_EQ(static_cast<uint8>(EQ::constants::EmoteEventTypes::EnterCombat), 1u);
}

TEST(EmoteEventTypesTest, OnDespawnIsEight) {
    EXPECT_EQ(static_cast<uint8>(EQ::constants::EmoteEventTypes::OnDespawn), 8u);
}

// ============================================================
// EQ::constants::EmoteTypes
// ============================================================
TEST(EmoteTypesTest, SayIsZero) {
    EXPECT_EQ(static_cast<uint8>(EQ::constants::EmoteTypes::Say), 0u);
}

TEST(EmoteTypesTest, EmoteIsOne) {
    EXPECT_EQ(static_cast<uint8>(EQ::constants::EmoteTypes::Emote), 1u);
}

TEST(EmoteTypesTest, ProximityIsThree) {
    EXPECT_EQ(static_cast<uint8>(EQ::constants::EmoteTypes::Proximity), 3u);
}

// ============================================================
// EQ::WaypointStatus
// ============================================================
TEST(WaypointStatusTest, RoamBoxPauseInProgressIsNeg3) {
    EXPECT_EQ(EQ::WaypointStatus::RoamBoxPauseInProgress, -3);
}

TEST(WaypointStatusTest, QuestControlNoGridIsNeg2) {
    EXPECT_EQ(EQ::WaypointStatus::QuestControlNoGrid, -2);
}

TEST(WaypointStatusTest, QuestControlGridIsNeg1) {
    EXPECT_EQ(EQ::WaypointStatus::QuestControlGrid, -1);
}

// ============================================================
// EQ::consent::eConsentType
// ============================================================
TEST(ConsentTypeTest, NormalIsZero) {
    EXPECT_EQ(static_cast<uint8>(EQ::consent::eConsentType::Normal), 0u);
}

TEST(ConsentTypeTest, GroupIsOne) {
    EXPECT_EQ(static_cast<uint8>(EQ::consent::eConsentType::Group), 1u);
}

TEST(ConsentTypeTest, GuildIsThree) {
    EXPECT_EQ(static_cast<uint8>(EQ::consent::eConsentType::Guild), 3u);
}

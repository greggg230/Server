/*	EQEmu: EQEmulator

	Copyright (C) 2001-2026 EQEmu Development Team

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 3 of the License, or
	(at your option) any later version.
*/
#include <gtest/gtest.h>
#include "common/npc_ai_util.h"

using namespace NPCAIUtil;

// ---------------------------------------------------------------------------
// IsAETargetType
// ---------------------------------------------------------------------------

TEST(IsAETargetType, HateListTypesAreAE) {
	EXPECT_TRUE(IsAETargetType(ST_AETargetHateList));
	EXPECT_TRUE(IsAETargetType(ST_HateList));
}

TEST(IsAETargetType, CasterCenteredAEIsAE) {
	EXPECT_TRUE(IsAETargetType(ST_AECaster));   // e.g. Trakanon Poison Breath
	EXPECT_TRUE(IsAETargetType(ST_AEClientV1));
	EXPECT_TRUE(IsAETargetType(ST_AETarget));
	EXPECT_TRUE(IsAETargetType(ST_AEBard));
}

TEST(IsAETargetType, OtherAETypesAreAE) {
	EXPECT_TRUE(IsAETargetType(ST_UndeadAE));
	EXPECT_TRUE(IsAETargetType(ST_SummonedAE));
	EXPECT_TRUE(IsAETargetType(ST_AreaClientOnly));
	EXPECT_TRUE(IsAETargetType(ST_AreaNPCOnly));
	EXPECT_TRUE(IsAETargetType(ST_Beam));
	EXPECT_TRUE(IsAETargetType(ST_Ring));
	EXPECT_TRUE(IsAETargetType(ST_Directional));
	EXPECT_TRUE(IsAETargetType(ST_TargetAETap));
	EXPECT_TRUE(IsAETargetType(ST_TargetAENoPlayersPets));
}

TEST(IsAETargetType, SingleTargetTypesAreNotAE) {
	EXPECT_FALSE(IsAETargetType(ST_Target));
	EXPECT_FALSE(IsAETargetType(ST_Self));
	EXPECT_FALSE(IsAETargetType(ST_Pet));
	EXPECT_FALSE(IsAETargetType(ST_Corpse));
	EXPECT_FALSE(IsAETargetType(ST_Group));
	EXPECT_FALSE(IsAETargetType(ST_GroupNoPets));
	EXPECT_FALSE(IsAETargetType(ST_GroupClientAndPet));
	EXPECT_FALSE(IsAETargetType(ST_GroupTeleport));
	EXPECT_FALSE(IsAETargetType(ST_Animal));
	EXPECT_FALSE(IsAETargetType(ST_Undead));
	EXPECT_FALSE(IsAETargetType(ST_Summoned));
	EXPECT_FALSE(IsAETargetType(ST_Dragon));
	EXPECT_FALSE(IsAETargetType(ST_Giant));
	EXPECT_FALSE(IsAETargetType(ST_SummonedPet));
	EXPECT_FALSE(IsAETargetType(ST_Tap));
	EXPECT_FALSE(IsAETargetType(ST_Muramite));
	EXPECT_FALSE(IsAETargetType(ST_TargetsTarget));
	EXPECT_FALSE(IsAETargetType(ST_PetMaster));
}

// ---------------------------------------------------------------------------
// CanAffordSpell
// ---------------------------------------------------------------------------

TEST(CanAffordSpell, CanCastWhenManaSufficient) {
	EXPECT_TRUE(CanAffordSpell(70, 200, 500));   // 70 cost, 200 current
	EXPECT_TRUE(CanAffordSpell(70, 70, 500));    // exactly enough
}

TEST(CanAffordSpell, CannotCastWhenManaInsufficient) {
	EXPECT_FALSE(CanAffordSpell(70, 69, 500));   // one short
	EXPECT_FALSE(CanAffordSpell(100, 0, 500));   // no mana
}

TEST(CanAffordSpell, AlwaysCanCastAtFullMana) {
	// Edge case: current == max overrides the cost check entirely.
	// This handles tick-boundary full-mana NPCs.
	EXPECT_TRUE(CanAffordSpell(9999, 500, 500));
}

TEST(CanAffordSpell, ZeroCostAlwaysAffordable) {
	EXPECT_TRUE(CanAffordSpell(0, 0, 500));
	EXPECT_TRUE(CanAffordSpell(0, 1, 500));
}

// ---------------------------------------------------------------------------
// ShouldAttemptGate
// ---------------------------------------------------------------------------

TEST(ShouldAttemptGate, GatesAtOrBelowThreshold) {
	EXPECT_TRUE(ShouldAttemptGate(20.0f, 20));   // exactly at threshold
	EXPECT_TRUE(ShouldAttemptGate(10.0f, 20));   // below threshold
	EXPECT_TRUE(ShouldAttemptGate(1.0f,  20));
}

TEST(ShouldAttemptGate, DoesNotGateAboveThreshold) {
	EXPECT_FALSE(ShouldAttemptGate(21.0f, 20));
	EXPECT_FALSE(ShouldAttemptGate(50.0f, 20));
	EXPECT_FALSE(ShouldAttemptGate(100.0f, 20));
}

TEST(ShouldAttemptGate, RespectsCustomThreshold) {
	EXPECT_TRUE(ShouldAttemptGate(30.0f, 30));
	EXPECT_FALSE(ShouldAttemptGate(31.0f, 30));
}

// ---------------------------------------------------------------------------
// IsTooCloseToGate
// ---------------------------------------------------------------------------

TEST(IsTooCloseToGate, BlocksGateWhenWithinBindDistance) {
	// Default NPCGateDistanceBind = 75; 74 units away should block
	EXPECT_TRUE(IsTooCloseToGate(74.0f * 74.0f, 75.0f));
	EXPECT_TRUE(IsTooCloseToGate(0.0f, 75.0f));   // at spawn point
}

TEST(IsTooCloseToGate, AllowsGateWhenBeyondBindDistance) {
	EXPECT_FALSE(IsTooCloseToGate(75.0f * 75.0f, 75.0f));  // exactly at limit
	EXPECT_FALSE(IsTooCloseToGate(100.0f * 100.0f, 75.0f));
}

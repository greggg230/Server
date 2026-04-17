#include <gtest/gtest.h>
#include "common/eq_packet_structs.h"

// ============================================================
// AdventureObjective enum
// ============================================================
TEST(AdventureObjectiveTest, RandomIsZero) {
    EXPECT_EQ(Adventure_Random, 0);
}

TEST(AdventureObjectiveTest, AssassinateIsOne) {
    EXPECT_EQ(Adventure_Assassinate, 1);
}

TEST(AdventureObjectiveTest, KillIsTwo) {
    EXPECT_EQ(Adventure_Kill, 2);
}

TEST(AdventureObjectiveTest, CollectIsThree) {
    EXPECT_EQ(Adventure_Collect, 3);
}

TEST(AdventureObjectiveTest, RescueIsFour) {
    EXPECT_EQ(Adventure_Rescue, 4);
}

// ============================================================
// LDoNChestTypes enum
// ============================================================
TEST(LDoNChestTypesTest, MechanicalIsOne) {
    EXPECT_EQ(LDoNTypeMechanical, 1);
}

TEST(LDoNChestTypesTest, MagicalIsTwo) {
    EXPECT_EQ(LDoNTypeMagical, 2);
}

TEST(LDoNChestTypesTest, CursedIsThree) {
    EXPECT_EQ(LDoNTypeCursed, 3);
}

// ============================================================
// CrystalReclaimTypes enum
// ============================================================
TEST(CrystalReclaimTypesTest, EbonIsFive) {
    EXPECT_EQ(CrystalReclaimTypes::Ebon, 5);
}

TEST(CrystalReclaimTypesTest, RadiantIsFour) {
    EXPECT_EQ(CrystalReclaimTypes::Radiant, 4);
}

// ============================================================
// ItemStackSizeConstraint namespace
// ============================================================
TEST(ItemStackSizeConstraintTest, MinimumIsOne) {
    int16 v = ItemStackSizeConstraint::Minimum;
    EXPECT_EQ(v, 1);
}

TEST(ItemStackSizeConstraintTest, MaximumIs1000) {
    int16 v = ItemStackSizeConstraint::Maximum;
    EXPECT_EQ(v, 1000);
}

TEST(ItemStackSizeConstraintTest, MinimumLessThanMaximum) {
    EXPECT_LT(ItemStackSizeConstraint::Minimum, ItemStackSizeConstraint::Maximum);
}

// ============================================================
// ChangeNameResponse enum
// ============================================================
TEST(ChangeNameResponseTest, DeniedIsZero) {
    EXPECT_EQ(ChangeNameResponse::Denied, 0);
}

TEST(ChangeNameResponseTest, AcceptedIsOne) {
    EXPECT_EQ(ChangeNameResponse::Accepted, 1);
}

TEST(ChangeNameResponseTest, TimeoutIsNegativeOne) {
    EXPECT_EQ(ChangeNameResponse::Timeout, -1);
}

TEST(ChangeNameResponseTest, ServerErrorIsNegativeTwo) {
    EXPECT_EQ(ChangeNameResponse::ServerError, -2);
}

TEST(ChangeNameResponseTest, RateLimitedIsNegativeThree) {
    EXPECT_EQ(ChangeNameResponse::RateLimited, -3);
}

TEST(ChangeNameResponseTest, IneligibleIsNegativeFour) {
    EXPECT_EQ(ChangeNameResponse::Ineligible, -4);
}

TEST(ChangeNameResponseTest, PendingIsNegativeFive) {
    EXPECT_EQ(ChangeNameResponse::Pending, -5);
}

// ============================================================
// eq_packet_structs.h top-level constants
// ============================================================
TEST(PacketStructConstantsTest, MaxMercIs100) {
    EXPECT_EQ(MAX_MERC, 100u);
}

TEST(PacketStructConstantsTest, MaxMercGradesIs10) {
    EXPECT_EQ(MAX_MERC_GRADES, 10u);
}

TEST(PacketStructConstantsTest, MaxMercStancesIs10) {
    EXPECT_EQ(MAX_MERC_STANCES, 10u);
}

TEST(PacketStructConstantsTest, QuestRewardCountIs8) {
    EXPECT_EQ(QUESTREWARD_COUNT, 8u);
}

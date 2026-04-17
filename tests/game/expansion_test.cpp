#include <gtest/gtest.h>
#include "common/content/world_content_service.h"

// ============================================================
// Expansion constants
// ============================================================
TEST(ExpansionConstantsTest, ExpansionAllIsNegativeOne) {
    int v = Expansion::EXPANSION_ALL;
    EXPECT_EQ(v, -1);
}

TEST(ExpansionConstantsTest, ExpansionFilterMaxIs99) {
    int v = Expansion::EXPANSION_FILTER_MAX;
    EXPECT_EQ(v, 99);
}

// ============================================================
// Expansion::ExpansionNumber enum values
// ============================================================
TEST(ExpansionNumberTest, ClassicIsZero) {
    EXPECT_EQ(Expansion::ExpansionNumber::Classic, 0);
}

TEST(ExpansionNumberTest, TheRuinsOfKunarkIsOne) {
    EXPECT_EQ(Expansion::ExpansionNumber::TheRuinsOfKunark, 1);
}

TEST(ExpansionNumberTest, TheScarsOfVeliousIsTwo) {
    EXPECT_EQ(Expansion::ExpansionNumber::TheScarsOfVelious, 2);
}

TEST(ExpansionNumberTest, TheShadowsOfLuclinIsThree) {
    EXPECT_EQ(Expansion::ExpansionNumber::TheShadowsOfLuclin, 3);
}

TEST(ExpansionNumberTest, ThePlanesOfPowerIsFour) {
    EXPECT_EQ(Expansion::ExpansionNumber::ThePlanesOfPower, 4);
}

TEST(ExpansionNumberTest, GatesOfDiscordIsSeven) {
    EXPECT_EQ(Expansion::ExpansionNumber::GatesOfDiscord, 7);
}

TEST(ExpansionNumberTest, TormentOfVeliousIs26) {
    EXPECT_EQ(Expansion::ExpansionNumber::TormentOfVelious, 26);
}

TEST(ExpansionNumberTest, MaxIdIs27) {
    EXPECT_EQ(Expansion::ExpansionNumber::MaxId, 27);
}

TEST(ExpansionNumberTest, EnumsAreSequential) {
    // Each expansion is one greater than the previous
    EXPECT_EQ(Expansion::ExpansionNumber::TheRuinsOfKunark,
              Expansion::ExpansionNumber::Classic + 1);
    EXPECT_EQ(Expansion::ExpansionNumber::TheScarsOfVelious,
              Expansion::ExpansionNumber::TheRuinsOfKunark + 1);
}

// ============================================================
// Expansion::ExpansionName array
// ============================================================
TEST(ExpansionNameTest, ClassicNameIsCorrect) {
    EXPECT_STREQ(Expansion::ExpansionName[Expansion::ExpansionNumber::Classic], "Classic");
}

TEST(ExpansionNameTest, KunarkNameIsCorrect) {
    EXPECT_STREQ(Expansion::ExpansionName[Expansion::ExpansionNumber::TheRuinsOfKunark],
                 "The Ruins of Kunark");
}

TEST(ExpansionNameTest, VeliousNameIsCorrect) {
    EXPECT_STREQ(Expansion::ExpansionName[Expansion::ExpansionNumber::TheScarsOfVelious],
                 "The Scars of Velious");
}

TEST(ExpansionNameTest, LuclinNameIsCorrect) {
    EXPECT_STREQ(Expansion::ExpansionName[Expansion::ExpansionNumber::TheShadowsOfLuclin],
                 "The Shadows of Luclin");
}

TEST(ExpansionNameTest, PlanesOfPowerNameIsCorrect) {
    EXPECT_STREQ(Expansion::ExpansionName[Expansion::ExpansionNumber::ThePlanesOfPower],
                 "The Planes of Power");
}

TEST(ExpansionNameTest, TormentOfVeliousNameIsCorrect) {
    EXPECT_STREQ(Expansion::ExpansionName[Expansion::ExpansionNumber::TormentOfVelious],
                 "Torment of Velious");
}

TEST(ExpansionNameTest, EmpiresOfKunarkNameIsCorrect) {
    EXPECT_STREQ(Expansion::ExpansionName[Expansion::ExpansionNumber::EmpiresOfKunark],
                 "Empires of Kunark");
}

TEST(ExpansionNameTest, NamesArraySizeMatchesMaxId) {
    // The array is sized [MaxId] so valid indices are 0..MaxId-1
    int max = Expansion::ExpansionNumber::MaxId;
    EXPECT_EQ(max, 27);
    EXPECT_NE(Expansion::ExpansionName[0], nullptr);
    EXPECT_NE(Expansion::ExpansionName[max - 1], nullptr);
}

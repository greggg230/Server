#include <gtest/gtest.h>
#include "common/eqemu_logsys.h"

#include <cstring>

// ============================================================
// Logs::DebugLevel
// ============================================================
TEST(LogsDebugLevelTest, GeneralIsOne) {
    EXPECT_EQ(Logs::DebugLevel::General, 1);
}

TEST(LogsDebugLevelTest, DetailIsTwo) {
    EXPECT_EQ(Logs::DebugLevel::Detail, 2);
}

// ============================================================
// Logs::LogCategory enum values
// ============================================================
TEST(LogsCategoryTest, NoneIsZero) {
    EXPECT_EQ(Logs::LogCategory::None, 0);
}

TEST(LogsCategoryTest, EarlyValues) {
    EXPECT_EQ(Logs::LogCategory::AA,       1);
    EXPECT_EQ(Logs::LogCategory::AI,       2);
    EXPECT_EQ(Logs::LogCategory::Aggro,    3);
    EXPECT_EQ(Logs::LogCategory::Attack,   4);
    EXPECT_EQ(Logs::LogCategory::Combat,   6);
    EXPECT_EQ(Logs::LogCategory::Commands, 7);
}

TEST(LogsCategoryTest, DebugAndErrorValues) {
    EXPECT_EQ(Logs::LogCategory::Debug, 9);
    EXPECT_EQ(Logs::LogCategory::Error, 11);
}

TEST(LogsCategoryTest, MaxCategoryIDIsPositive) {
    EXPECT_GT(Logs::LogCategory::MaxCategoryID, 0);
    EXPECT_GT(Logs::LogCategory::MaxCategoryID, Logs::LogCategory::Spells);
}

TEST(LogsCategoryTest, LaterValues) {
    EXPECT_EQ(Logs::LogCategory::Hate,    80);
    EXPECT_EQ(Logs::LogCategory::Discord, 81);
    EXPECT_EQ(Logs::LogCategory::Faction, 82);
}

// ============================================================
// Logs::LogCategoryName static array
// ============================================================
TEST(LogsCategoryNameTest, NoneHasEmptyName) {
    EXPECT_STREQ(Logs::LogCategoryName[Logs::LogCategory::None], "");
}

TEST(LogsCategoryNameTest, AAIsAA) {
    EXPECT_STREQ(Logs::LogCategoryName[Logs::LogCategory::AA], "AA");
}

TEST(LogsCategoryNameTest, AIIsAI) {
    EXPECT_STREQ(Logs::LogCategoryName[Logs::LogCategory::AI], "AI");
}

TEST(LogsCategoryNameTest, ErrorIsError) {
    EXPECT_STREQ(Logs::LogCategoryName[Logs::LogCategory::Error], "Error");
}

TEST(LogsCategoryNameTest, SkillsIsSkills) {
    EXPECT_STREQ(Logs::LogCategoryName[Logs::LogCategory::Skills], "Skills");
}

TEST(LogsCategoryNameTest, QuestsIsQuests) {
    EXPECT_STREQ(Logs::LogCategoryName[Logs::LogCategory::Quests], "Quests");
}

TEST(LogsCategoryNameTest, AllEntriesNonNull) {
    for (int i = 0; i < Logs::LogCategory::MaxCategoryID; ++i) {
        EXPECT_NE(Logs::LogCategoryName[i], nullptr) << "Null at index " << i;
    }
}

TEST(LogsCategoryNameTest, AllAfterNoneNonEmpty) {
    for (int i = 1; i < Logs::LogCategory::MaxCategoryID; ++i) {
        EXPECT_GT(strlen(Logs::LogCategoryName[i]), 0u)
            << "Empty name at index " << i;
    }
}

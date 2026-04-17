#include <gtest/gtest.h>
#include "common/rulesys.h"

// ============================================================
// RuleManager — static counts (derived from ruletypes.h X-macros)
// ============================================================
TEST(RuleManagerCountTest, IntRuleCountIsPositive) {
    int v = RuleManager::IntRuleCount;
    EXPECT_GT(v, 0);
}

TEST(RuleManagerCountTest, RealRuleCountIsPositive) {
    int v = RuleManager::RealRuleCount;
    EXPECT_GT(v, 0);
}

TEST(RuleManagerCountTest, BoolRuleCountIsPositive) {
    int v = RuleManager::BoolRuleCount;
    EXPECT_GT(v, 0);
}

TEST(RuleManagerCountTest, TotalRulesCountMatchesSumOfTypes) {
    int ints = RuleManager::IntRuleCount;
    int reals = RuleManager::RealRuleCount;
    int bools = RuleManager::BoolRuleCount;
    int strs = RuleManager::StringRuleCount;
    uint32 expected = static_cast<uint32>(ints + reals + bools + strs);
    EXPECT_EQ(RuleManager::CountRules(), expected);
}

TEST(RuleManagerCountTest, CountRulesIsPositive) {
    EXPECT_GT(RuleManager::CountRules(), 0u);
}

// ============================================================
// RuleManager — InvalidX sentinels match count enums
// ============================================================
TEST(RuleManagerInvalidTest, InvalidIntEqualsIntRuleCount) {
    int count = RuleManager::IntRuleCount;
    EXPECT_EQ(static_cast<int>(RuleManager::InvalidInt), count);
}

TEST(RuleManagerInvalidTest, InvalidRealEqualsRealRuleCount) {
    int count = RuleManager::RealRuleCount;
    EXPECT_EQ(static_cast<int>(RuleManager::InvalidReal), count);
}

TEST(RuleManagerInvalidTest, InvalidBoolEqualsBoolRuleCount) {
    int count = RuleManager::BoolRuleCount;
    EXPECT_EQ(static_cast<int>(RuleManager::InvalidBool), count);
}

// ============================================================
// RuleManager — GetRuleName (static, no DB)
// ============================================================
TEST(RuleManagerGetRuleNameTest, MaxLevelRuleNameIsNonEmpty) {
    std::string name = RuleManager::GetRuleName(RuleManager::Int__MaxLevel);
    EXPECT_FALSE(name.empty());
}

TEST(RuleManagerGetRuleNameTest, MaxLevelRuleNameContainsMaxLevel) {
    std::string name = RuleManager::GetRuleName(RuleManager::Int__MaxLevel);
    EXPECT_NE(name.find("MaxLevel"), std::string::npos);
}

TEST(RuleManagerGetRuleNameTest, PerCharacterQglobalMaxLevelIsNonEmpty) {
    std::string name = RuleManager::GetRuleName(RuleManager::Bool__PerCharacterQglobalMaxLevel);
    EXPECT_FALSE(name.empty());
}

TEST(RuleManagerGetRuleNameTest, DeathExpLossLevelRuleNameIsNonEmpty) {
    std::string name = RuleManager::GetRuleName(RuleManager::Int__DeathExpLossLevel);
    EXPECT_FALSE(name.empty());
}

// ============================================================
// RuleManager — GetRuleNotes (static, no DB)
// ============================================================
TEST(RuleManagerGetRuleNotesTest, MaxLevelNotesIsNonEmpty) {
    const std::string& notes = RuleManager::GetRuleNotes(RuleManager::Int__MaxLevel);
    EXPECT_FALSE(notes.empty());
}

// ============================================================
// RuleManager — Instance (singleton, default values loaded)
// ============================================================
TEST(RuleManagerInstanceTest, InstanceIsNotNull) {
    EXPECT_NE(RuleManager::Instance(), nullptr);
}

TEST(RuleManagerInstanceTest, InstanceIsSameObject) {
    EXPECT_EQ(RuleManager::Instance(), RuleManager::Instance());
}

TEST(RuleManagerInstanceTest, MaxLevelDefaultIs65) {
    int v = RuleManager::Instance()->GetIntRule(RuleManager::Int__MaxLevel);
    EXPECT_EQ(v, 65);
}

TEST(RuleManagerInstanceTest, DeathExpLossLevelDefaultIs10) {
    int v = RuleManager::Instance()->GetIntRule(RuleManager::Int__DeathExpLossLevel);
    EXPECT_EQ(v, 10);
}

TEST(RuleManagerInstanceTest, PerCharQglobalMaxLevelDefaultIsFalse) {
    bool v = RuleManager::Instance()->GetBoolRule(RuleManager::Bool__PerCharacterQglobalMaxLevel);
    EXPECT_FALSE(v);
}

// ============================================================
// RuleManager — FindCategory (static)
// ============================================================
TEST(RuleManagerFindCategoryTest, FindCharacterCategorySucceeds) {
    auto cat = RuleManager::FindCategory("Character");
    RuleManager::CategoryType invalid = RuleManager::InvalidCategory;
    EXPECT_NE(cat, invalid);
}

TEST(RuleManagerFindCategoryTest, FindUnknownCategoryReturnsInvalid) {
    auto cat = RuleManager::FindCategory("NoSuchCategoryXYZ");
    RuleManager::CategoryType invalid = RuleManager::InvalidCategory;
    EXPECT_EQ(cat, invalid);
}

TEST(RuleManagerFindCategoryTest, FindSpellsCategorySucceeds) {
    auto cat = RuleManager::FindCategory("Spells");
    RuleManager::CategoryType invalid = RuleManager::InvalidCategory;
    EXPECT_NE(cat, invalid);
}

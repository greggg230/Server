#include <gtest/gtest.h>
#include "common/skills.h"

using namespace EQ::skills;

// ---- IsTradeskill ----

TEST(SkillsTest, TradeskillsReturnTrue) {
    EXPECT_TRUE(IsTradeskill(SkillFishing));
    EXPECT_TRUE(IsTradeskill(SkillMakePoison));
    EXPECT_TRUE(IsTradeskill(SkillTinkering));
    EXPECT_TRUE(IsTradeskill(SkillResearch));
    EXPECT_TRUE(IsTradeskill(SkillAlchemy));
    EXPECT_TRUE(IsTradeskill(SkillBaking));
    EXPECT_TRUE(IsTradeskill(SkillTailoring));
    EXPECT_TRUE(IsTradeskill(SkillBlacksmithing));
    EXPECT_TRUE(IsTradeskill(SkillFletching));
    EXPECT_TRUE(IsTradeskill(SkillBrewing));
    EXPECT_TRUE(IsTradeskill(SkillPottery));
    EXPECT_TRUE(IsTradeskill(SkillJewelryMaking));
}

TEST(SkillsTest, CombatSkillsAreNotTradeskill) {
    EXPECT_FALSE(IsTradeskill(Skill1HBlunt));
    EXPECT_FALSE(IsTradeskill(SkillArchery));
    EXPECT_FALSE(IsTradeskill(SkillBackstab));
    EXPECT_FALSE(IsTradeskill(SkillKick));
}

// ---- IsSpecializedSkill ----

TEST(SkillsTest, SpecializeSkillsReturnTrue) {
    EXPECT_TRUE(IsSpecializedSkill(SkillSpecializeAbjure));
    EXPECT_TRUE(IsSpecializedSkill(SkillSpecializeAlteration));
    EXPECT_TRUE(IsSpecializedSkill(SkillSpecializeConjuration));
    EXPECT_TRUE(IsSpecializedSkill(SkillSpecializeDivination));
    EXPECT_TRUE(IsSpecializedSkill(SkillSpecializeEvocation));
}

TEST(SkillsTest, NonSpecializeSkillsReturnFalse) {
    EXPECT_FALSE(IsSpecializedSkill(SkillAbjuration));
    EXPECT_FALSE(IsSpecializedSkill(SkillEvocation));
    EXPECT_FALSE(IsSpecializedSkill(Skill1HBlunt));
}

// ---- IsBardInstrumentSkill ----

TEST(SkillsTest, BardInstrumentSkillsReturnTrue) {
    EXPECT_TRUE(IsBardInstrumentSkill(SkillBrassInstruments));
    EXPECT_TRUE(IsBardInstrumentSkill(SkillSinging));
    EXPECT_TRUE(IsBardInstrumentSkill(SkillStringedInstruments));
    EXPECT_TRUE(IsBardInstrumentSkill(SkillWindInstruments));
    EXPECT_TRUE(IsBardInstrumentSkill(SkillPercussionInstruments));
}

TEST(SkillsTest, NonBardSkillsAreNotInstrument) {
    EXPECT_FALSE(IsBardInstrumentSkill(SkillArchery));
    EXPECT_FALSE(IsBardInstrumentSkill(SkillBackstab));
    EXPECT_FALSE(IsBardInstrumentSkill(SkillFishing));
}

// ---- IsCastingSkill ----

TEST(SkillsTest, CastingSkillsReturnTrue) {
    EXPECT_TRUE(IsCastingSkill(SkillAbjuration));
    EXPECT_TRUE(IsCastingSkill(SkillAlteration));
    EXPECT_TRUE(IsCastingSkill(SkillConjuration));
    EXPECT_TRUE(IsCastingSkill(SkillDivination));
    EXPECT_TRUE(IsCastingSkill(SkillEvocation));
}

TEST(SkillsTest, NonCastingSkillsReturnFalse) {
    EXPECT_FALSE(IsCastingSkill(Skill1HBlunt));
    EXPECT_FALSE(IsCastingSkill(SkillBash));
    EXPECT_FALSE(IsCastingSkill(SkillSinging));
}

// ---- GetSkillMeleePushForce ----

TEST(SkillsTest, GetSkillMeleePushForceKnownValues) {
    EXPECT_FLOAT_EQ(GetSkillMeleePushForce(Skill1HBlunt), 0.1f);
    EXPECT_FLOAT_EQ(GetSkillMeleePushForce(Skill2HBlunt), 0.2f);
    EXPECT_FLOAT_EQ(GetSkillMeleePushForce(SkillArchery),  0.15f);
    EXPECT_FLOAT_EQ(GetSkillMeleePushForce(SkillBackstab), 0.3f);
    EXPECT_FLOAT_EQ(GetSkillMeleePushForce(SkillFlyingKick), 0.4f);
    EXPECT_FLOAT_EQ(GetSkillMeleePushForce(Skill1HPiercing), 0.05f);
    EXPECT_FLOAT_EQ(GetSkillMeleePushForce(SkillIntimidation), 2.5f);
}

TEST(SkillsTest, GetSkillMeleePushForceUnknownReturnsZero) {
    EXPECT_FLOAT_EQ(GetSkillMeleePushForce(SkillHide), 0.0f);
    EXPECT_FLOAT_EQ(GetSkillMeleePushForce(SkillFishing), 0.0f);
}

// ---- GetSkillTypeMap ----

TEST(SkillsTest, GetSkillTypeMapContainsKnownSkills) {
    const auto& m = GetSkillTypeMap();
    EXPECT_FALSE(m.empty());
    EXPECT_NE(m.find(Skill1HBlunt), m.end());
    EXPECT_NE(m.find(SkillArchery), m.end());
    EXPECT_NE(m.find(SkillFishing), m.end());
    EXPECT_EQ(m.at(Skill1HBlunt), "1H Blunt");
    EXPECT_EQ(m.at(SkillArchery),  "Archery");
    EXPECT_EQ(m.at(SkillSinging),  "Singing");
}

// ---- GetSkillName ----

TEST(SkillsTest, GetSkillNameReturnsCorrectNames) {
    EXPECT_EQ(GetSkillName(Skill1HBlunt),  "1H Blunt");
    EXPECT_EQ(GetSkillName(SkillArchery),  "Archery");
    EXPECT_EQ(GetSkillName(SkillBackstab), "Backstab");
    EXPECT_EQ(GetSkillName(SkillFishing),  "Fishing");
    EXPECT_EQ(GetSkillName(Skill2HPiercing), "2H Piercing");
}

TEST(SkillsTest, GetSkillNameOutOfRangeReturnsEmpty) {
    EXPECT_EQ(GetSkillName(SkillCount), "");
}

// ---- GetExtraDamageSkills ----

TEST(SkillsTest, GetExtraDamageSkillsContainsExpected) {
    const auto& v = GetExtraDamageSkills();
    EXPECT_FALSE(v.empty());
    auto has = [&](SkillType s) {
        return std::find(v.begin(), v.end(), s) != v.end();
    };
    EXPECT_TRUE(has(SkillBackstab));
    EXPECT_TRUE(has(SkillBash));
    EXPECT_TRUE(has(SkillKick));
    EXPECT_TRUE(has(SkillFrenzy));
}

// ---- SkillProfile ----

TEST(SkillsTest, SkillProfileDefaultZero) {
    EQ::SkillProfile profile;
    EXPECT_EQ(profile.GetSkill(0),  0u);
    EXPECT_EQ(profile.GetSkill(50), 0u);
    EXPECT_EQ(profile.GetSkill(99), 0u);
}

TEST(SkillsTest, SkillProfileOutOfRangeReturnsZero) {
    EQ::SkillProfile profile;
    EXPECT_EQ(profile.GetSkill(-1),  0u);
    EXPECT_EQ(profile.GetSkill(100), 0u);
    EXPECT_EQ(profile.GetSkill(200), 0u);
}

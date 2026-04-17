#include <gtest/gtest.h>
#include "common/emu_constants.h"
#include "common/eq_constants.h"

// ============================================================
// EQ::invtype::GetInvTypeSize
// ============================================================
TEST(InvTypeSizeTest, PossessionsTypePositiveSize) {
    int16 sz = EQ::invtype::GetInvTypeSize(EQ::invtype::typePossessions);
    EXPECT_GT(sz, 0);
}

TEST(InvTypeSizeTest, InvalidTypeReturnsINULL) {
    // out-of-range types return INULL (0), not IINVALID (-1)
    EXPECT_EQ(EQ::invtype::GetInvTypeSize(EQ::invtype::TYPE_INVALID), EQ::INULL);
    EXPECT_EQ(EQ::invtype::GetInvTypeSize(-99), EQ::INULL);
    EXPECT_EQ(EQ::invtype::GetInvTypeSize(9999), EQ::INULL);
}

TEST(InvTypeSizeTest, AllValidTypesReturnPositive) {
    for (int16 t = EQ::invtype::TYPE_BEGIN; t <= EQ::invtype::TYPE_END; ++t) {
        EXPECT_GE(EQ::invtype::GetInvTypeSize(t), 0) << "invtype " << t << " returned negative size";
    }
}

// ============================================================
// Bug::GetName / IsValid
// ============================================================
TEST(BugTest, IsValidKnownCategories) {
    EXPECT_TRUE(Bug::IsValid(Bug::Category::Other));
    EXPECT_TRUE(Bug::IsValid(Bug::Category::Quest));
    EXPECT_TRUE(Bug::IsValid(Bug::Category::Mercenaries));
}

TEST(BugTest, IsValidUnknownCategory) {
    EXPECT_FALSE(Bug::IsValid(999));
}

TEST(BugTest, GetNameKnownCategories) {
    EXPECT_EQ(Bug::GetName(Bug::Category::Other),       "Other");
    EXPECT_EQ(Bug::GetName(Bug::Category::Video),       "Video");
    EXPECT_EQ(Bug::GetName(Bug::Category::Audio),       "Audio");
    EXPECT_EQ(Bug::GetName(Bug::Category::Quest),       "Quest");
    EXPECT_EQ(Bug::GetName(Bug::Category::NPC),         "NPC");
    EXPECT_EQ(Bug::GetName(Bug::Category::Mercenaries), "Mercenaries");
}

// ============================================================
// Stance::GetName / IsValid
// ============================================================
TEST(StanceTest, IsValidKnownStances) {
    EXPECT_TRUE(Stance::IsValid(Stance::Passive));
    EXPECT_TRUE(Stance::IsValid(Stance::Balanced));
    EXPECT_TRUE(Stance::IsValid(Stance::Aggressive));
    EXPECT_TRUE(Stance::IsValid(Stance::AEBurn));
}

TEST(StanceTest, IsValidUnknownStance) {
    EXPECT_FALSE(Stance::IsValid(100));
}

TEST(StanceTest, GetNameKnownStances) {
    EXPECT_EQ(Stance::GetName(Stance::Passive),    "Passive");
    EXPECT_EQ(Stance::GetName(Stance::Balanced),   "Balanced");
    EXPECT_EQ(Stance::GetName(Stance::Aggressive), "Aggressive");
    EXPECT_EQ(Stance::GetName(Stance::Burn),       "Burn");
    EXPECT_EQ(Stance::GetName(Stance::AEBurn),     "AE Burn");
}

// ============================================================
// LDoNTheme::GetName / GetBitmask / IsValid
// ============================================================
TEST(LDoNThemeTest, IsValidKnownThemes) {
    EXPECT_TRUE(LDoNTheme::IsValid(LDoNTheme::GUK));
    EXPECT_TRUE(LDoNTheme::IsValid(LDoNTheme::MIR));
    EXPECT_TRUE(LDoNTheme::IsValid(LDoNTheme::TAK));
}

TEST(LDoNThemeTest, IsValidUnknownTheme) {
    EXPECT_FALSE(LDoNTheme::IsValid(99));
}

TEST(LDoNThemeTest, GetNameKnownThemes) {
    EXPECT_EQ(LDoNTheme::GetName(LDoNTheme::GUK), "Deepest Guk");
    EXPECT_EQ(LDoNTheme::GetName(LDoNTheme::TAK), "Takish-Hiz");
}

TEST(LDoNThemeTest, GetBitmaskKnownThemes) {
    EXPECT_EQ(LDoNTheme::GetBitmask(LDoNTheme::GUK), LDoNTheme::GUKBit);
    EXPECT_EQ(LDoNTheme::GetBitmask(LDoNTheme::MIR), LDoNTheme::MIRBit);
    EXPECT_EQ(LDoNTheme::GetBitmask(LDoNTheme::MMC), LDoNTheme::MMCBit);
    EXPECT_EQ(LDoNTheme::GetBitmask(LDoNTheme::RUJ), LDoNTheme::RUJBit);
    EXPECT_EQ(LDoNTheme::GetBitmask(LDoNTheme::TAK), LDoNTheme::TAKBit);
}

TEST(LDoNThemeTest, GetBitmaskInvalidTheme) {
    EXPECT_EQ(LDoNTheme::GetBitmask(99), LDoNTheme::UnusedBit);
}

// ============================================================
// EQ::constants::GetLanguageName
// ============================================================
TEST(LanguageNameTest, CommonTongue) {
    EXPECT_EQ(EQ::constants::GetLanguageName(Language::CommonTongue), "Common Tongue");
}

TEST(LanguageNameTest, KnownLanguages) {
    EXPECT_EQ(EQ::constants::GetLanguageName(Language::Elvish),    "Elvish");
    EXPECT_EQ(EQ::constants::GetLanguageName(Language::Dragon),    "Dragon");
    EXPECT_EQ(EQ::constants::GetLanguageName(Language::VahShir),   "Vah Shir");
    EXPECT_EQ(EQ::constants::GetLanguageName(Language::Unknown27), "Unknown");
}

TEST(LanguageNameTest, OutOfRangeReturnsEmpty) {
    EXPECT_EQ(EQ::constants::GetLanguageName(100), "");
}

// ============================================================
// EQ::constants::GetFlyModeName
// ============================================================
TEST(FlyModeNameTest, KnownFlyModes) {
    using namespace EQ::constants;
    EXPECT_EQ(GetFlyModeName(GravityBehavior::Ground),              "Ground");
    EXPECT_EQ(GetFlyModeName(GravityBehavior::Flying),              "Flying");
    EXPECT_EQ(GetFlyModeName(GravityBehavior::Levitating),          "Levitating");
    EXPECT_EQ(GetFlyModeName(GravityBehavior::Water),               "Water");
    EXPECT_EQ(GetFlyModeName(GravityBehavior::LevitateWhileRunning),"Levitating While Running");
}

TEST(FlyModeNameTest, OutOfRangeReturnsEmpty) {
    EXPECT_EQ(EQ::constants::GetFlyModeName(50), "");
}

// ============================================================
// EQ::constants::GetConsiderLevelName
// ============================================================
TEST(ConsiderLevelNameTest, KnownConsiderLevels) {
    EXPECT_EQ(EQ::constants::GetConsiderLevelName(ConsiderLevel::Ally),            "Ally");
    EXPECT_EQ(EQ::constants::GetConsiderLevelName(ConsiderLevel::Indifferently),   "Indifferently");
    EXPECT_EQ(EQ::constants::GetConsiderLevelName(ConsiderLevel::Scowls),          "Scowls");
}

TEST(ConsiderLevelNameTest, OutOfRangeReturnsEmpty) {
    EXPECT_EQ(EQ::constants::GetConsiderLevelName(0),  "");
    EXPECT_EQ(EQ::constants::GetConsiderLevelName(50), "");
}

// ============================================================
// EQ::constants::GetEnvironmentalDamageName
// ============================================================
TEST(EnvironmentalDamageNameTest, KnownTypes) {
    using namespace EQ::constants;
    EXPECT_EQ(GetEnvironmentalDamageName(EnvironmentalDamage::Lava),     "Lava");
    EXPECT_EQ(GetEnvironmentalDamageName(EnvironmentalDamage::Drowning), "Drowning");
    EXPECT_EQ(GetEnvironmentalDamageName(EnvironmentalDamage::Falling),  "Falling");
    EXPECT_EQ(GetEnvironmentalDamageName(EnvironmentalDamage::Trap),     "Trap");
}

TEST(EnvironmentalDamageNameTest, OutOfRangeReturnsEmpty) {
    EXPECT_EQ(EQ::constants::GetEnvironmentalDamageName(0), "");
}

// ============================================================
// EQ::constants::GetStuckBehaviorName
// ============================================================
TEST(StuckBehaviorNameTest, KnownBehaviors) {
    using namespace EQ::constants;
    EXPECT_EQ(GetStuckBehaviorName(StuckBehavior::RunToTarget),  "Run To Target");
    EXPECT_EQ(GetStuckBehaviorName(StuckBehavior::WarpToTarget), "Warp To Target");
    EXPECT_EQ(GetStuckBehaviorName(StuckBehavior::TakeNoAction), "Take No Action");
    EXPECT_EQ(GetStuckBehaviorName(StuckBehavior::EvadeCombat),  "Evade Combat");
}

// ============================================================
// EQ::constants::GetWeatherTypeName
// ============================================================
TEST(WeatherTypeNameTest, KnownTypes) {
    using namespace EQ::constants;
    EXPECT_EQ(GetWeatherTypeName(WeatherTypes::None),    "None");
    EXPECT_EQ(GetWeatherTypeName(WeatherTypes::Raining), "Raining");
    EXPECT_EQ(GetWeatherTypeName(WeatherTypes::Snowing), "Snowing");
}

TEST(WeatherTypeNameTest, OutOfRangeReturnsEmpty) {
    EXPECT_EQ(EQ::constants::GetWeatherTypeName(99), "");
}

// ============================================================
// EQ::constants::GetSpawnAnimationName
// ============================================================
TEST(SpawnAnimationNameTest, KnownAnimations) {
    using namespace EQ::constants;
    EXPECT_EQ(GetSpawnAnimationName(SpawnAnimations::Standing),  "Standing");
    EXPECT_EQ(GetSpawnAnimationName(SpawnAnimations::Sitting),   "Sitting");
    EXPECT_EQ(GetSpawnAnimationName(SpawnAnimations::Crouching), "Crouching");
    EXPECT_EQ(GetSpawnAnimationName(SpawnAnimations::Laying),    "Laying");
    EXPECT_EQ(GetSpawnAnimationName(SpawnAnimations::Looting),   "Looting");
}

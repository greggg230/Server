#include <gtest/gtest.h>
#include "common/light_source.h"

using namespace EQ::lightsource;

// TypeToLevel mapping tests
TEST(LightSourceTypeToLevelTest, NoneReturnsUnlit) {
    EXPECT_EQ(TypeToLevel(LightTypeNone), LightLevelUnlit);
}

TEST(LightSourceTypeToLevelTest, CandleReturnsCandle) {
    EXPECT_EQ(TypeToLevel(LightTypeCandle), LightLevelCandle);
}

TEST(LightSourceTypeToLevelTest, TorchReturnsTorch) {
    EXPECT_EQ(TypeToLevel(LightTypeTorch), LightLevelTorch);
}

TEST(LightSourceTypeToLevelTest, SmallLanternReturnsSmallLantern) {
    EXPECT_EQ(TypeToLevel(LightTypeSmallLantern), LightLevelSmallLantern);
}

TEST(LightSourceTypeToLevelTest, LargeLanternReturnsLargeLantern) {
    EXPECT_EQ(TypeToLevel(LightTypeLargeLantern), LightLevelLargeLantern);
}

TEST(LightSourceTypeToLevelTest, GlobeOfStarsReturnsBrilliant) {
    EXPECT_EQ(TypeToLevel(LightTypeGlobeOfStars), LightLevelBrilliant);
}

TEST(LightSourceTypeToLevelTest, FlamelessLanternReturnsLargeMagic) {
    EXPECT_EQ(TypeToLevel(LightTypeFlamelessLantern), LightLevelLargeMagic);
}

TEST(LightSourceTypeToLevelTest, GreaterLightstoneReturnsLargeMagic) {
    EXPECT_EQ(TypeToLevel(LightTypeGreaterLightstone), LightLevelLargeMagic);
}

TEST(LightSourceTypeToLevelTest, SteinOfMoggokReturnsMagicLantern) {
    EXPECT_EQ(TypeToLevel(LightTypeSteinOfMoggok), LightLevelMagicLantern);
}

TEST(LightSourceTypeToLevelTest, LightstoneReturnsMagicLantern) {
    EXPECT_EQ(TypeToLevel(LightTypeLightstone), LightLevelMagicLantern);
}

TEST(LightSourceTypeToLevelTest, FireBeetleEyeReturnsRedLight) {
    EXPECT_EQ(TypeToLevel(LightTypeFireBeetleEye), LightLevelRedLight);
}

TEST(LightSourceTypeToLevelTest, ColdlightReturnsBlueLight) {
    EXPECT_EQ(TypeToLevel(LightTypeColdlight), LightLevelBlueLight);
}

TEST(LightSourceTypeToLevelTest, TinyGlowingSkullReturnsSmallMagic) {
    EXPECT_EQ(TypeToLevel(LightTypeTinyGlowingSkull), LightLevelSmallMagic);
}

TEST(LightSourceTypeToLevelTest, LightGlobeReturnsSmallMagic) {
    EXPECT_EQ(TypeToLevel(LightTypeLightGlobe), LightLevelSmallMagic);
}

TEST(LightSourceTypeToLevelTest, OutOfBoundsReturnsUnlit) {
    EXPECT_EQ(TypeToLevel(255), LightLevelUnlit);
    EXPECT_EQ(TypeToLevel(LightTypeCount), LightLevelUnlit);
}

// IsLevelGreater tests
TEST(LightSourceIsLevelGreaterTest, HigherTypeBeatsLower) {
    // GlobeOfStars (Brilliant=10) > Candle (Candle=1)
    EXPECT_TRUE(IsLevelGreater(LightTypeGlobeOfStars, LightTypeCandle));
}

TEST(LightSourceIsLevelGreaterTest, LowerTypeDoesNotBeatHigher) {
    EXPECT_FALSE(IsLevelGreater(LightTypeCandle, LightTypeGlobeOfStars));
}

TEST(LightSourceIsLevelGreaterTest, EqualTypesAreNotGreater) {
    EXPECT_FALSE(IsLevelGreater(LightTypeTorch, LightTypeTorch));
    EXPECT_FALSE(IsLevelGreater(LightTypeNone, LightTypeNone));
}

TEST(LightSourceIsLevelGreaterTest, NoneBeatenByCandle) {
    EXPECT_TRUE(IsLevelGreater(LightTypeCandle, LightTypeNone));
    EXPECT_FALSE(IsLevelGreater(LightTypeNone, LightTypeCandle));
}

TEST(LightSourceIsLevelGreaterTest, OutOfBoundsTreatedAsNone) {
    // out-of-range left_type becomes LightTypeNone (level=0), candle=1 > 0
    EXPECT_FALSE(IsLevelGreater(255, LightTypeCandle));
    // candle=1 > 0=none(out-of-range right)
    EXPECT_TRUE(IsLevelGreater(LightTypeCandle, 255));
}

TEST(LightSourceIsLevelGreaterTest, FlamelessLanternBeatsLargeLantern) {
    // FlamelessLantern=LargeMagic(9) > LargeLantern(8)
    EXPECT_TRUE(IsLevelGreater(LightTypeFlamelessLantern, LightTypeLargeLantern));
}

// LightSource_Struct tests
TEST(LightSourceStructTest, DefaultConstructClearsAllSlots) {
    EQ::LightSource_Struct ls;
    for (int i = 0; i < LightCount; ++i) {
        EXPECT_EQ(ls.Slot[i], 0);
    }
}

TEST(LightSourceStructTest, ClearResetsSlots) {
    EQ::LightSource_Struct ls;
    ls.Slot[LightInnate] = 5;
    ls.Slot[LightEquipment] = 7;
    ls.Clear();
    for (int i = 0; i < LightCount; ++i) {
        EXPECT_EQ(ls.Slot[i], 0);
    }
}

TEST(LightSourceStructTest, BracketOperatorReadsAndWrites) {
    EQ::LightSource_Struct ls;
    ls[LightInnate] = LightTypeTorch;
    ls[LightEquipment] = LightTypeGlobeOfStars;
    EXPECT_EQ(ls[LightInnate], LightTypeTorch);
    EXPECT_EQ(ls[LightEquipment], LightTypeGlobeOfStars);
}

// LightSourceProfile tests
TEST(LightSourceProfileTest, ClearResetsBothTypeAndLevel) {
    EQ::LightSourceProfile profile;
    profile.Type[LightInnate] = 5;
    profile.Level[LightInnate] = 7;
    profile.Clear();
    for (int i = 0; i < LightCount; ++i) {
        EXPECT_EQ(profile.Type.Slot[i], 0);
        EXPECT_EQ(profile.Level.Slot[i], 0);
    }
}

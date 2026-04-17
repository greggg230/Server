#include <gtest/gtest.h>
#include "common/faction.h"
#include "common/features.h"

// ============================================================
// FACTION_VALUE enum
// ============================================================
TEST(FactionValueEnumTest, AllyIsOne) {
    EXPECT_EQ(FACTION_ALLY,           1);
}

TEST(FactionValueEnumTest, SequentialValues) {
    EXPECT_EQ(FACTION_WARMLY,         2);
    EXPECT_EQ(FACTION_KINDLY,         3);
    EXPECT_EQ(FACTION_AMIABLY,        4);
    EXPECT_EQ(FACTION_INDIFFERENTLY,  5);
    EXPECT_EQ(FACTION_APPREHENSIVELY, 6);
    EXPECT_EQ(FACTION_DUBIOUSLY,      7);
    EXPECT_EQ(FACTION_THREATENINGLY,  8);
    EXPECT_EQ(FACTION_SCOWLS,         9);
}

TEST(FactionValueEnumTest, AllyIsBestFaction) {
    EXPECT_LT(FACTION_ALLY, FACTION_WARMLY);
    EXPECT_LT(FACTION_ALLY, FACTION_SCOWLS);
}

TEST(FactionValueEnumTest, ScowlsIsWorstFaction) {
    EXPECT_GT(FACTION_SCOWLS, FACTION_THREATENINGLY);
    EXPECT_GT(FACTION_SCOWLS, FACTION_ALLY);
}

// ============================================================
// FactionValueToString
// ============================================================
TEST(FactionValueToStringTest, AllyReturnsAlly) {
    EXPECT_STREQ(FactionValueToString(FACTION_ALLY), "Ally");
}

TEST(FactionValueToStringTest, WarmlyReturnsWarmly) {
    EXPECT_STREQ(FactionValueToString(FACTION_WARMLY), "Warmly");
}

TEST(FactionValueToStringTest, KindlyReturnsKindly) {
    EXPECT_STREQ(FactionValueToString(FACTION_KINDLY), "Kindly");
}

TEST(FactionValueToStringTest, AmiablyReturnsAmiably) {
    EXPECT_STREQ(FactionValueToString(FACTION_AMIABLY), "Amiably");
}

TEST(FactionValueToStringTest, IndifferentlyReturnsIndifferently) {
    EXPECT_STREQ(FactionValueToString(FACTION_INDIFFERENTLY), "Indifferently");
}

TEST(FactionValueToStringTest, ApprehensivelyReturnsApprehensively) {
    EXPECT_STREQ(FactionValueToString(FACTION_APPREHENSIVELY), "Apprehensively");
}

TEST(FactionValueToStringTest, DubiouslyReturnsDubiously) {
    EXPECT_STREQ(FactionValueToString(FACTION_DUBIOUSLY), "Dubiously");
}

TEST(FactionValueToStringTest, ThreateninglyReturnsThreateningly) {
    EXPECT_STREQ(FactionValueToString(FACTION_THREATENINGLY), "Threateningly");
}

TEST(FactionValueToStringTest, ScowlsReturnsScowls) {
    EXPECT_STREQ(FactionValueToString(FACTION_SCOWLS), "Scowls");
}

TEST(FactionValueToStringTest, UnknownValueReturnsUnknown) {
    EXPECT_STREQ(FactionValueToString(static_cast<FACTION_VALUE>(99)),  "Unknown");
    EXPECT_STREQ(FactionValueToString(static_cast<FACTION_VALUE>(0)),   "Unknown");
    EXPECT_STREQ(FactionValueToString(static_cast<FACTION_VALUE>(100)), "Unknown");
}

TEST(FactionValueToStringTest, AllKnownValuesReturnNonEmpty) {
    const FACTION_VALUE all_values[] = {
        FACTION_ALLY, FACTION_WARMLY, FACTION_KINDLY, FACTION_AMIABLY,
        FACTION_INDIFFERENTLY, FACTION_APPREHENSIVELY, FACTION_DUBIOUSLY,
        FACTION_THREATENINGLY, FACTION_SCOWLS
    };
    for (auto v : all_values) {
        const char *s = FactionValueToString(v);
        EXPECT_NE(s, nullptr) << "Null for value " << v;
        EXPECT_GT(strlen(s), 0u) << "Empty for value " << v;
        EXPECT_STRNE(s, "Unknown") << "Got Unknown for valid value " << v;
    }
}

// ============================================================
// Faction limit constants (features.h)
// ============================================================
TEST(FactionConstantsTest, MaxNPCFactions) {
    EXPECT_EQ(MAX_NPC_FACTIONS, 20);
}

TEST(FactionConstantsTest, PersonalFactionLimits) {
    EXPECT_EQ(MAX_PERSONAL_FACTION,  2000);
    EXPECT_EQ(MIN_PERSONAL_FACTION, -2000);
}

TEST(FactionConstantsTest, PersonalRangeIsSymmetric) {
    EXPECT_EQ(MAX_PERSONAL_FACTION, -MIN_PERSONAL_FACTION);
}

// ============================================================
// FactionMods struct — field access and arithmetic
// ============================================================
TEST(FactionModsTest, DefaultValuesAreZero) {
    FactionMods fm{};
    EXPECT_EQ(fm.base,      0);
    EXPECT_EQ(fm.class_mod, 0);
    EXPECT_EQ(fm.race_mod,  0);
    EXPECT_EQ(fm.deity_mod, 0);
}

TEST(FactionModsTest, SetAndReadFields) {
    FactionMods fm{};
    fm.base      = 500;
    fm.class_mod = -100;
    fm.race_mod  =  50;
    fm.deity_mod =  25;

    int32_t total = fm.base + fm.class_mod + fm.race_mod + fm.deity_mod;
    EXPECT_EQ(total, 475);
}

TEST(FactionModsTest, MinMaxBounds) {
    FactionMods fm{};
    fm.min = -2000;
    fm.max =  2000;
    EXPECT_LT(fm.min, fm.max);
}

#include <gtest/gtest.h>
#include "common/races.h"

// IsPlayerRace tests
TEST(RacesIsPlayerRaceTest, BasicRacesOneToTwelveArePlayer) {
    // Human(1) through Gnome(12)
    for (uint16_t r = Race::Human; r <= Race::Gnome; ++r) {
        EXPECT_TRUE(IsPlayerRace(r)) << "race_id=" << r;
    }
}

TEST(RacesIsPlayerRaceTest, ExtendedPlayerRacesArePlayer) {
    EXPECT_TRUE(IsPlayerRace(Race::Iksar));
    EXPECT_TRUE(IsPlayerRace(Race::VahShir));
    EXPECT_TRUE(IsPlayerRace(Race::Froglok2));
    EXPECT_TRUE(IsPlayerRace(Race::Drakkin));
}

TEST(RacesIsPlayerRaceTest, NonPlayerRacesAreNotPlayer) {
    EXPECT_FALSE(IsPlayerRace(Race::Doug));     // 0
    EXPECT_FALSE(IsPlayerRace(Race::Aviak));    // 13
    EXPECT_FALSE(IsPlayerRace(Race::Werewolf)); // 14
    EXPECT_FALSE(IsPlayerRace(255));
}

// GetGenderName tests
TEST(RacesGetGenderNameTest, MaleReturnsMale) {
    EXPECT_STREQ(GetGenderName(Gender::Male), "Male");
}

TEST(RacesGetGenderNameTest, FemaleReturnsFemale) {
    EXPECT_STREQ(GetGenderName(Gender::Female), "Female");
}

TEST(RacesGetGenderNameTest, NeuterReturnsNeuter) {
    EXPECT_STREQ(GetGenderName(Gender::Neuter), "Neuter");
}

TEST(RacesGetGenderNameTest, UnknownValueReturnsUnknown) {
    EXPECT_STREQ(GetGenderName(99), "Unknown");
}

// GetPlayerRaceAbbreviation tests
TEST(RacesGetPlayerRaceAbbreviationTest, AllPlayerRacesReturnAbbreviations) {
    EXPECT_EQ(GetPlayerRaceAbbreviation(Race::Human),     "HUM");
    EXPECT_EQ(GetPlayerRaceAbbreviation(Race::Barbarian), "BAR");
    EXPECT_EQ(GetPlayerRaceAbbreviation(Race::Erudite),   "ERU");
    EXPECT_EQ(GetPlayerRaceAbbreviation(Race::WoodElf),   "ELF");
    EXPECT_EQ(GetPlayerRaceAbbreviation(Race::HighElf),   "HIE");
    EXPECT_EQ(GetPlayerRaceAbbreviation(Race::DarkElf),   "DEF");
    EXPECT_EQ(GetPlayerRaceAbbreviation(Race::HalfElf),   "HEF");
    EXPECT_EQ(GetPlayerRaceAbbreviation(Race::Dwarf),     "DWF");
    EXPECT_EQ(GetPlayerRaceAbbreviation(Race::Troll),     "TRL");
    EXPECT_EQ(GetPlayerRaceAbbreviation(Race::Ogre),      "OGR");
    EXPECT_EQ(GetPlayerRaceAbbreviation(Race::Halfling),  "HFL");
    EXPECT_EQ(GetPlayerRaceAbbreviation(Race::Gnome),     "GNM");
    EXPECT_EQ(GetPlayerRaceAbbreviation(Race::Iksar),     "IKS");
    EXPECT_EQ(GetPlayerRaceAbbreviation(Race::VahShir),   "VAH");
    EXPECT_EQ(GetPlayerRaceAbbreviation(Race::Froglok2),  "FRG");
    EXPECT_EQ(GetPlayerRaceAbbreviation(Race::Drakkin),   "DRK");
}

TEST(RacesGetPlayerRaceAbbreviationTest, NonPlayerRaceReturnsUNK) {
    EXPECT_EQ(GetPlayerRaceAbbreviation(Race::Doug),    "UNK");
    EXPECT_EQ(GetPlayerRaceAbbreviation(Race::Aviak),   "UNK");
    EXPECT_EQ(GetPlayerRaceAbbreviation(255),           "UNK");
}

// GetPlayerRaceValue tests
TEST(RacesGetPlayerRaceValueTest, BasicRacesReturnTheirOwnID) {
    EXPECT_EQ(GetPlayerRaceValue(Race::Human),     (uint32_t)Race::Human);
    EXPECT_EQ(GetPlayerRaceValue(Race::Dwarf),     (uint32_t)Race::Dwarf);
    EXPECT_EQ(GetPlayerRaceValue(Race::Gnome),     (uint32_t)Race::Gnome);
}

TEST(RacesGetPlayerRaceValueTest, ExtendedRacesReturnIndex) {
    EXPECT_EQ(GetPlayerRaceValue(Race::Iksar),   (uint32_t)RaceIndex::Iksar);
    EXPECT_EQ(GetPlayerRaceValue(Race::VahShir), (uint32_t)RaceIndex::VahShir);
    EXPECT_EQ(GetPlayerRaceValue(Race::Froglok2),(uint32_t)RaceIndex::Froglok);
    EXPECT_EQ(GetPlayerRaceValue(Race::Drakkin), (uint32_t)RaceIndex::Drakkin);
}

TEST(RacesGetPlayerRaceValueTest, NonPlayerRaceReturnsDougZero) {
    EXPECT_EQ(GetPlayerRaceValue(Race::Aviak), (uint32_t)Race::Doug);
    EXPECT_EQ(GetPlayerRaceValue(255),         (uint32_t)Race::Doug);
}

// GetPlayerRaceBit tests
TEST(RacesGetPlayerRaceBitTest, PlayerRacesReturnCorrectBitmask) {
    EXPECT_EQ(GetPlayerRaceBit(Race::Human),     RaceBitmask::Human);
    EXPECT_EQ(GetPlayerRaceBit(Race::Barbarian), RaceBitmask::Barbarian);
    EXPECT_EQ(GetPlayerRaceBit(Race::Iksar),     RaceBitmask::Iksar);
    EXPECT_EQ(GetPlayerRaceBit(Race::VahShir),   RaceBitmask::VahShir);
    EXPECT_EQ(GetPlayerRaceBit(Race::Froglok2),  RaceBitmask::Froglok);
    EXPECT_EQ(GetPlayerRaceBit(Race::Drakkin),   RaceBitmask::Drakkin);
}

TEST(RacesGetPlayerRaceBitTest, NonPlayerRaceReturnsUnknownBitmask) {
    EXPECT_EQ(GetPlayerRaceBit(Race::Aviak), RaceBitmask::Unknown);
    EXPECT_EQ(GetPlayerRaceBit(255),         RaceBitmask::Unknown);
}

// GetRaceIDFromPlayerRaceValue tests
TEST(RacesGetRaceIDFromPlayerRaceValueTest, BasicRaceValuesRoundTrip) {
    EXPECT_EQ(GetRaceIDFromPlayerRaceValue(Race::Human),    Race::Human);
    EXPECT_EQ(GetRaceIDFromPlayerRaceValue(Race::Gnome),    Race::Gnome);
    EXPECT_EQ(GetRaceIDFromPlayerRaceValue(Race::Barbarian),Race::Barbarian);
}

TEST(RacesGetRaceIDFromPlayerRaceValueTest, ExtendedRaceIndicesReturnCorrectID) {
    EXPECT_EQ(GetRaceIDFromPlayerRaceValue(RaceIndex::Iksar),   Race::Iksar);
    EXPECT_EQ(GetRaceIDFromPlayerRaceValue(RaceIndex::VahShir), Race::VahShir);
    EXPECT_EQ(GetRaceIDFromPlayerRaceValue(RaceIndex::Froglok), Race::Froglok2);
    EXPECT_EQ(GetRaceIDFromPlayerRaceValue(RaceIndex::Drakkin), Race::Drakkin);
}

TEST(RacesGetRaceIDFromPlayerRaceValueTest, InvalidValueReturnsDougZero) {
    EXPECT_EQ(GetRaceIDFromPlayerRaceValue(999), Race::Doug);
    EXPECT_EQ(GetRaceIDFromPlayerRaceValue(0),   Race::Doug);
}

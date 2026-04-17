#include <gtest/gtest.h>
#include "common/bodytypes.h"

// ============================================================
// BodyType constexpr values
// ============================================================
TEST(BodyTypeConstTest, HumanoidIsOne) {
    EXPECT_EQ(BodyType::Humanoid, 1u);
}

TEST(BodyTypeConstTest, EarlySequential) {
    EXPECT_EQ(BodyType::Lycanthrope,    2u);
    EXPECT_EQ(BodyType::Undead,         3u);
    EXPECT_EQ(BodyType::Giant,          4u);
    EXPECT_EQ(BodyType::Construct,      5u);
    EXPECT_EQ(BodyType::Extraplanar,    6u);
    EXPECT_EQ(BodyType::Magical,        7u);
    EXPECT_EQ(BodyType::SummonedUndead, 8u);
    EXPECT_EQ(BodyType::RaidGiant,      9u);
}

TEST(BodyTypeConstTest, MidRange) {
    EXPECT_EQ(BodyType::Animal,   21u);
    EXPECT_EQ(BodyType::Insect,   22u);
    EXPECT_EQ(BodyType::Monster,  23u);
    EXPECT_EQ(BodyType::Summoned, 24u);
    EXPECT_EQ(BodyType::Plant,    25u);
    EXPECT_EQ(BodyType::Dragon,   26u);
}

TEST(BodyTypeConstTest, HighValues) {
    EXPECT_EQ(BodyType::NoTarget2,     60u);
    EXPECT_EQ(BodyType::SwarmPet,      63u);
    EXPECT_EQ(BodyType::MonsterSummon, 64u);
    EXPECT_EQ(BodyType::InvisibleMan,  66u);
    EXPECT_EQ(BodyType::Special,       67u);
}

// ============================================================
// BodyType::IsValid
// ============================================================
TEST(BodyTypeIsValidTest, ValidHumanoid) {
    EXPECT_TRUE(BodyType::IsValid(BodyType::Humanoid));
}

TEST(BodyTypeIsValidTest, ValidDragon) {
    EXPECT_TRUE(BodyType::IsValid(BodyType::Dragon));
}

TEST(BodyTypeIsValidTest, ValidSpecial) {
    EXPECT_TRUE(BodyType::IsValid(BodyType::Special));
}

TEST(BodyTypeIsValidTest, InvalidZeroIsNotValid) {
    EXPECT_FALSE(BodyType::IsValid(0));
}

TEST(BodyTypeIsValidTest, InvalidArbitraryIdIsNotValid) {
    EXPECT_FALSE(BodyType::IsValid(50));
    EXPECT_FALSE(BodyType::IsValid(100));
    EXPECT_FALSE(BodyType::IsValid(255));
}

// ============================================================
// BodyType::GetName
// ============================================================
TEST(BodyTypeGetNameTest, HumanoidName) {
    EXPECT_EQ(BodyType::GetName(BodyType::Humanoid), "Humanoid");
}

TEST(BodyTypeGetNameTest, UndeadName) {
    EXPECT_EQ(BodyType::GetName(BodyType::Undead), "Undead");
}

TEST(BodyTypeGetNameTest, DragonName) {
    EXPECT_EQ(BodyType::GetName(BodyType::Dragon), "Dragon");
}

TEST(BodyTypeGetNameTest, AnimalName) {
    EXPECT_EQ(BodyType::GetName(BodyType::Animal), "Animal");
}

TEST(BodyTypeGetNameTest, SwarmPetName) {
    EXPECT_EQ(BodyType::GetName(BodyType::SwarmPet), "Swarm Pet");
}

TEST(BodyTypeGetNameTest, InvisibleManName) {
    EXPECT_EQ(BodyType::GetName(BodyType::InvisibleMan), "Invisible Man");
}

TEST(BodyTypeGetNameTest, InvalidReturnsUnknown) {
    EXPECT_EQ(BodyType::GetName(0), "UNKNOWN BODY TYPE");
    EXPECT_EQ(BodyType::GetName(50), "UNKNOWN BODY TYPE");
    EXPECT_EQ(BodyType::GetName(255), "UNKNOWN BODY TYPE");
}

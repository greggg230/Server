#include <gtest/gtest.h>
#include "common/bodytypes.h"
#include "common/deity.h"

// ====== BodyType tests ======

TEST(BodyTypeTest, HumanoidIsValid) {
    EXPECT_TRUE(BodyType::IsValid(BodyType::Humanoid));
}

TEST(BodyTypeTest, UndeadIsValid) {
    EXPECT_TRUE(BodyType::IsValid(BodyType::Undead));
}

TEST(BodyTypeTest, DragonIsValid) {
    EXPECT_TRUE(BodyType::IsValid(BodyType::Dragon));
}

TEST(BodyTypeTest, SpecialIsValid) {
    EXPECT_TRUE(BodyType::IsValid(BodyType::Special));
}

TEST(BodyTypeTest, ZeroIsNotValid) {
    EXPECT_FALSE(BodyType::IsValid(0));
}

TEST(BodyTypeTest, UnknownValueIsNotValid) {
    EXPECT_FALSE(BodyType::IsValid(50));
    EXPECT_FALSE(BodyType::IsValid(255));
}

TEST(BodyTypeTest, GetNameReturnsCorrectName) {
    EXPECT_EQ(BodyType::GetName(BodyType::Humanoid), "Humanoid");
    EXPECT_EQ(BodyType::GetName(BodyType::Undead), "Undead");
    EXPECT_EQ(BodyType::GetName(BodyType::Dragon), "Dragon");
    EXPECT_EQ(BodyType::GetName(BodyType::Animal), "Animal");
    EXPECT_EQ(BodyType::GetName(BodyType::Plant), "Plant");
    EXPECT_EQ(BodyType::GetName(BodyType::Insect), "Insect");
}

TEST(BodyTypeTest, GetNameForInvalidReturnsUnknown) {
    EXPECT_EQ(BodyType::GetName(0), "UNKNOWN BODY TYPE");
    EXPECT_EQ(BodyType::GetName(50), "UNKNOWN BODY TYPE");
}

TEST(BodyTypeTest, NoTargetBodiesAreValid) {
    EXPECT_TRUE(BodyType::IsValid(BodyType::NoTarget));
    EXPECT_TRUE(BodyType::IsValid(BodyType::NoTarget2));
}

TEST(BodyTypeTest, SwarmPetAndMonsterSummonAreValid) {
    EXPECT_TRUE(BodyType::IsValid(BodyType::SwarmPet));
    EXPECT_TRUE(BodyType::IsValid(BodyType::MonsterSummon));
}

TEST(BodyTypeTest, SummonedVariantsAreValid) {
    EXPECT_TRUE(BodyType::IsValid(BodyType::Summoned));
    EXPECT_TRUE(BodyType::IsValid(BodyType::Summoned2));
    EXPECT_TRUE(BodyType::IsValid(BodyType::Summoned3));
    EXPECT_TRUE(BodyType::IsValid(BodyType::SummonedUndead));
}

TEST(BodyTypeTest, DragonVariantsAreValid) {
    EXPECT_TRUE(BodyType::IsValid(BodyType::Dragon));
    EXPECT_TRUE(BodyType::IsValid(BodyType::Dragon2));
    EXPECT_TRUE(BodyType::IsValid(BodyType::Dragon3));
    EXPECT_TRUE(BodyType::IsValid(BodyType::VeliousDragon));
}

TEST(BodyTypeTest, ConstantsHaveCorrectValues) {
    EXPECT_EQ(BodyType::Humanoid, 1);
    EXPECT_EQ(BodyType::Undead, 3);
    EXPECT_EQ(BodyType::Animal, 21);
    EXPECT_EQ(BodyType::Dragon, 26);
    EXPECT_EQ(BodyType::Special, 67);
}

// ====== Deity tests ======

TEST(DeityTest, AllNamedDeitiesAreValid) {
    EXPECT_TRUE(Deity::IsValid(Deity::Bertoxxulous));
    EXPECT_TRUE(Deity::IsValid(Deity::BrellSirilis));
    EXPECT_TRUE(Deity::IsValid(Deity::CazicThule));
    EXPECT_TRUE(Deity::IsValid(Deity::ErollisiMarr));
    EXPECT_TRUE(Deity::IsValid(Deity::Bristlebane));
    EXPECT_TRUE(Deity::IsValid(Deity::Innoruuk));
    EXPECT_TRUE(Deity::IsValid(Deity::Karana));
    EXPECT_TRUE(Deity::IsValid(Deity::MithanielMarr));
    EXPECT_TRUE(Deity::IsValid(Deity::Prexus));
    EXPECT_TRUE(Deity::IsValid(Deity::Quellious));
    EXPECT_TRUE(Deity::IsValid(Deity::RallosZek));
    EXPECT_TRUE(Deity::IsValid(Deity::RodcetNife));
    EXPECT_TRUE(Deity::IsValid(Deity::SolusekRo));
    EXPECT_TRUE(Deity::IsValid(Deity::TheTribunal));
    EXPECT_TRUE(Deity::IsValid(Deity::Tunare));
    EXPECT_TRUE(Deity::IsValid(Deity::Veeshan));
}

TEST(DeityTest, AgnosticBothValuesAreValid) {
    EXPECT_TRUE(Deity::IsValid(Deity::Agnostic1));
    EXPECT_TRUE(Deity::IsValid(Deity::Agnostic2));
}

TEST(DeityTest, UnknownAndArbitraryAreNotValid) {
    EXPECT_FALSE(Deity::IsValid(Deity::Unknown));
    EXPECT_FALSE(Deity::IsValid(999));
    EXPECT_FALSE(Deity::IsValid(1));
    EXPECT_FALSE(Deity::IsValid(200));
}

TEST(DeityTest, GetNameReturnsCorrectStrings) {
    EXPECT_EQ(Deity::GetName(Deity::Innoruuk), "Innoruuk");
    EXPECT_EQ(Deity::GetName(Deity::Tunare), "Tunare");
    EXPECT_EQ(Deity::GetName(Deity::CazicThule), "Cazic-Thule");
    EXPECT_EQ(Deity::GetName(Deity::MithanielMarr), "Mithaniel Marr");
    EXPECT_EQ(Deity::GetName(Deity::TheTribunal), "The Tribunal");
    EXPECT_EQ(Deity::GetName(Deity::BrellSirilis), "Brell Serilis");
}

TEST(DeityTest, AgnosticBothReturnAgnosticName) {
    EXPECT_EQ(Deity::GetName(Deity::Agnostic1), "Agnostic");
    EXPECT_EQ(Deity::GetName(Deity::Agnostic2), "Agnostic");
}

TEST(DeityTest, GetNameForInvalidReturnsUnknown) {
    EXPECT_EQ(Deity::GetName(Deity::Unknown), "UNKNOWN DEITY");
    EXPECT_EQ(Deity::GetName(999), "UNKNOWN DEITY");
}

TEST(DeityTest, GetBitmaskReturnsCorrectBits) {
    EXPECT_EQ(Deity::GetBitmask(Deity::Bertoxxulous), Deity::Bitmask::Bertoxxulous);
    EXPECT_EQ(Deity::GetBitmask(Deity::Innoruuk), Deity::Bitmask::Innoruuk);
    EXPECT_EQ(Deity::GetBitmask(Deity::Tunare), Deity::Bitmask::Tunare);
    EXPECT_EQ(Deity::GetBitmask(Deity::Veeshan), Deity::Bitmask::Veeshan);
}

TEST(DeityTest, AgnosticBothReturnSameBitmask) {
    EXPECT_EQ(Deity::GetBitmask(Deity::Agnostic1), Deity::Bitmask::Agnostic);
    EXPECT_EQ(Deity::GetBitmask(Deity::Agnostic2), Deity::Bitmask::Agnostic);
}

TEST(DeityTest, GetBitmaskForInvalidReturnsAll) {
    EXPECT_EQ(Deity::GetBitmask(Deity::Unknown), Deity::Bitmask::All);
    EXPECT_EQ(Deity::GetBitmask(999), Deity::Bitmask::All);
}

TEST(DeityTest, BitmaskValuesArePowersOfTwo) {
    // Each deity bitmask must be a unique power of two (or All for invalid)
    uint32_t bitmask = Deity::GetBitmask(Deity::Bertoxxulous);
    EXPECT_EQ(bitmask & (bitmask - 1), 0u);  // power of two check
    bitmask = Deity::GetBitmask(Deity::Veeshan);
    EXPECT_EQ(bitmask & (bitmask - 1), 0u);
}

TEST(DeityTest, AllBitmaskIsMaxUint32) {
    EXPECT_EQ(Deity::Bitmask::All, std::numeric_limits<uint32_t>::max());
}

TEST(DeityTest, DeityConstantsHaveCorrectValues) {
    EXPECT_EQ(Deity::Bertoxxulous, 201u);
    EXPECT_EQ(Deity::Veeshan, 216u);
    EXPECT_EQ(Deity::Agnostic1, 140u);
    EXPECT_EQ(Deity::Agnostic2, 396u);
}

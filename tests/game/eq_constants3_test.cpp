#include <gtest/gtest.h>
#include "common/eq_constants.h"

// ============================================================
// AppearanceType namespace constants
// ============================================================
TEST(AppearanceTypeTest, DieIsZero) {
    EXPECT_EQ(AppearanceType::Die, 0u);
}

TEST(AppearanceTypeTest, WhoLevelIsOne) {
    EXPECT_EQ(AppearanceType::WhoLevel, 1u);
}

TEST(AppearanceTypeTest, MaxHealthIsTwo) {
    EXPECT_EQ(AppearanceType::MaxHealth, 2u);
}

TEST(AppearanceTypeTest, InvisibilityIsThree) {
    EXPECT_EQ(AppearanceType::Invisibility, 3u);
}

TEST(AppearanceTypeTest, PVPIsFour) {
    EXPECT_EQ(AppearanceType::PVP, 4u);
}

TEST(AppearanceTypeTest, AnimationIs14) {
    EXPECT_EQ(AppearanceType::Animation, 14u);
}

TEST(AppearanceTypeTest, GMIs20) {
    EXPECT_EQ(AppearanceType::GM, 20u);
}

TEST(AppearanceTypeTest, AnonymousIs21) {
    EXPECT_EQ(AppearanceType::Anonymous, 21u);
}

TEST(AppearanceTypeTest, SizeIs29) {
    EXPECT_EQ(AppearanceType::Size, 29u);
}

TEST(AppearanceTypeTest, DamageStateIs44) {
    EXPECT_EQ(AppearanceType::DamageState, 44u);
}

TEST(AppearanceTypeTest, OfflineModeIs53) {
    EXPECT_EQ(AppearanceType::OfflineMode, 53u);
}

// ============================================================
// Zones namespace — classic zone IDs
// ============================================================
TEST(ZonesConstantTest, QeynosIs1) {
    EXPECT_EQ(Zones::QEYNOS, 1u);
}

TEST(ZonesConstantTest, HighpassIs5) {
    EXPECT_EQ(Zones::HIGHPASS, 5u);
}

TEST(ZonesConstantTest, FreportNIs8) {
    EXPECT_EQ(Zones::FREPORTN, 8u);
}

TEST(ZonesConstantTest, BlackburrowIs17) {
    EXPECT_EQ(Zones::BLACKBURROW, 17u);
}

TEST(ZonesConstantTest, GreaterFaydarkIs54) {
    EXPECT_EQ(Zones::GFAYDARK, 54u);
}

TEST(ZonesConstantTest, CrushboneIs58) {
    EXPECT_EQ(Zones::CRUSHBONE, 58u);
}

TEST(ZonesConstantTest, PlaneOfSkyIs71) {
    EXPECT_EQ(Zones::AIRPLANE, 71u);
}

TEST(ZonesConstantTest, PlaneOfFearIs72) {
    EXPECT_EQ(Zones::FEARPLANE, 72u);
}

TEST(ZonesConstantTest, PlaneOfHateIs76) {
    EXPECT_EQ(Zones::HATEPLANE, 76u);
}

// ============================================================
// LeadershipAbilitySlot namespace
// ============================================================
TEST(LeadershipAbilitySlotTest, HealthOfTargetsTargetIs14) {
    uint16 v = LeadershipAbilitySlot::HealthOfTargetsTarget;
    EXPECT_EQ(v, 14u);
}

// ============================================================
// DoorType namespace
// ============================================================
TEST(DoorTypeTest, BuyerStallIs155) {
    EXPECT_EQ(DoorType::BuyerStall, 155u);
}

// ============================================================
// RaidLootType namespace
// ============================================================
TEST(RaidLootTypeTest2, LeaderOnlyIs1) {
    EXPECT_EQ(RaidLootType::LeaderOnly, 1u);
}

TEST(RaidLootTypeTest2, EntireRaidIs4) {
    EXPECT_EQ(RaidLootType::EntireRaid, 4u);
}

TEST(RaidLootTypeTest2, SequentialValues) {
    EXPECT_EQ(RaidLootType::LeaderAndGroupLeadersOnly, 2u);
    EXPECT_EQ(RaidLootType::LeaderSelected,            3u);
}

// ============================================================
// FVNoDropFlagRule enum
// ============================================================
TEST(FVNoDropFlagRuleTest, DisabledIsZero) {
    EXPECT_EQ(FVNoDropFlagRule::Disabled, 0);
}

TEST(FVNoDropFlagRuleTest, EnabledIsOne) {
    EXPECT_EQ(FVNoDropFlagRule::Enabled, 1);
}

TEST(FVNoDropFlagRuleTest, AdminOnlyIsTwo) {
    EXPECT_EQ(FVNoDropFlagRule::AdminOnly, 2);
}

// ============================================================
// RecipeCountType enum class
// ============================================================
TEST(RecipeCountTypeTest, ComponentIsZero) {
    EXPECT_EQ(static_cast<uint8_t>(RecipeCountType::Component), 0u);
}

TEST(RecipeCountTypeTest, ContainerIsOne) {
    EXPECT_EQ(static_cast<uint8_t>(RecipeCountType::Container), 1u);
}

TEST(RecipeCountTypeTest, SuccessIsFour) {
    EXPECT_EQ(static_cast<uint8_t>(RecipeCountType::Success), 4u);
}

// ============================================================
// Parcel macros
// ============================================================
TEST(ParcelConstantsTest, SendItemsIsZero) {
    EXPECT_EQ(PARCEL_SEND_ITEMS, 0);
}

TEST(ParcelConstantsTest, SendMoneyIsOne) {
    EXPECT_EQ(PARCEL_SEND_MONEY, 1);
}

TEST(ParcelConstantsTest, LimitIsFive) {
    EXPECT_EQ(PARCEL_LIMIT, 5);
}

TEST(ParcelConstantsTest, BeginSlotIsOne) {
    EXPECT_EQ(PARCEL_BEGIN_SLOT, 1);
}

TEST(ParcelConstantsTest, MoneyItemIdIs99990) {
    EXPECT_EQ(PARCEL_MONEY_ITEM_ID, 99990);
}

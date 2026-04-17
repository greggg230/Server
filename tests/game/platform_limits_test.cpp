#include <gtest/gtest.h>
#include "common/platform.h"
#include "common/emu_limits.h"
#include "common/eq_limits.h"
#include "common/emu_versions.h"

// ============================================================
// EQEmuExePlatform enum
// ============================================================
TEST(ExePlatformTest, NoneIsZero) {
    EXPECT_EQ(ExePlatformNone, 0);
}

TEST(ExePlatformTest, SequentialValues) {
    EXPECT_EQ(ExePlatformZone,         1);
    EXPECT_EQ(ExePlatformWorld,        2);
    EXPECT_EQ(ExePlatformLogin,        3);
    EXPECT_EQ(ExePlatformQueryServ,    4);
    EXPECT_EQ(ExePlatformSocket_Server,5);
    EXPECT_EQ(ExePlatformUCS,          6);
    EXPECT_EQ(ExePlatformLaunch,       7);
    EXPECT_EQ(ExePlatformSharedMemory, 8);
    EXPECT_EQ(ExePlatformClientImport, 9);
    EXPECT_EQ(ExePlatformClientExport, 10);
    EXPECT_EQ(ExePlatformHC,           11);
    EXPECT_EQ(ExePlatformTests,        12);
    EXPECT_EQ(ExePlatformZoneSidecar,  13);
}

TEST(ExePlatformTest, TestsAndZoneAreDistinct) {
    EXPECT_NE(ExePlatformTests, ExePlatformZone);
}

// ============================================================
// EntityLimits namespace constants
// ============================================================
TEST(EntityLimitsTest, NPCInvalidIsNegativeOne) {
    EXPECT_EQ(EntityLimits::NPC::IINVALID, -1);
}

TEST(EntityLimitsTest, NPCNullIsZero) {
    EXPECT_EQ(EntityLimits::NPC::INULL, 0);
}

TEST(EntityLimitsTest, NPCTradeSizeIs4) {
    EXPECT_EQ(EntityLimits::NPC::invtype::TRADE_SIZE, 4);
}

TEST(EntityLimitsTest, BotTradeSizeIsLarger) {
    EXPECT_GT(EntityLimits::Bot::invtype::TRADE_SIZE,
              EntityLimits::NPC::invtype::TRADE_SIZE);
    EXPECT_EQ(EntityLimits::Bot::invtype::TRADE_SIZE, 8);
}

TEST(EntityLimitsTest, BotEquipmentBitmask23Bits) {
    // 0x00000000007FFFFF = (1<<23) - 1
    EXPECT_EQ(EntityLimits::Bot::invslot::EQUIPMENT_BITMASK, 0x00000000007FFFFFu);
}

TEST(EntityLimitsTest, BotPossessionsBitmaskEqualsEquipment) {
    EXPECT_EQ(EntityLimits::Bot::invslot::POSSESSIONS_BITMASK,
              EntityLimits::Bot::invslot::EQUIPMENT_BITMASK);
}

TEST(EntityLimitsTest, MercAndNPCMerchantSameTradeSize) {
    EXPECT_EQ(EntityLimits::Merc::invtype::TRADE_SIZE,
              EntityLimits::NPCMerchant::invtype::TRADE_SIZE);
}

// ============================================================
// EQ::behavior::StaticLookup — pure read of static table
// ============================================================
TEST(BehaviorStaticLookupTest, UnknownMobVersionReturnsNonNull) {
    using namespace EQ::versions;
    const EQ::behavior::LookupEntry *entry =
        EQ::behavior::StaticLookup(MobVersion::Unknown);
    EXPECT_NE(entry, nullptr);
}

TEST(BehaviorStaticLookupTest, NPCVersionReturnsNonNull) {
    const EQ::behavior::LookupEntry *entry =
        EQ::behavior::StaticLookup(EQ::versions::MobVersion::NPC);
    EXPECT_NE(entry, nullptr);
}

TEST(BehaviorStaticLookupTest, RoF2VersionReturnsNonNull) {
    const EQ::behavior::LookupEntry *entry =
        EQ::behavior::StaticLookup(EQ::versions::MobVersion::RoF2);
    EXPECT_NE(entry, nullptr);
}

// ============================================================
// EQ::constants::StaticLookup — pure read of static table
// ============================================================
TEST(ConstantsStaticLookupTest, UnknownClientVersionReturnsNonNull) {
    const EQ::constants::LookupEntry *entry =
        EQ::constants::StaticLookup(EQ::versions::ClientVersion::Unknown);
    EXPECT_NE(entry, nullptr);
}

TEST(ConstantsStaticLookupTest, TitaniumVersionReturnsNonNull) {
    const EQ::constants::LookupEntry *entry =
        EQ::constants::StaticLookup(EQ::versions::ClientVersion::Titanium);
    EXPECT_NE(entry, nullptr);
}

TEST(ConstantsStaticLookupTest, RoF2VersionReturnsNonNull) {
    const EQ::constants::LookupEntry *entry =
        EQ::constants::StaticLookup(EQ::versions::ClientVersion::RoF2);
    EXPECT_NE(entry, nullptr);
}

TEST(ConstantsStaticLookupTest, OutOfRangeFallsBackToUnknown) {
    // ValidateClientVersion clamped to Unknown
    const EQ::constants::LookupEntry *out_of_range =
        EQ::constants::StaticLookup(static_cast<EQ::versions::ClientVersion>(999));
    const EQ::constants::LookupEntry *unknown =
        EQ::constants::StaticLookup(EQ::versions::ClientVersion::Unknown);
    EXPECT_EQ(out_of_range, unknown);
}

// ============================================================
// EQ::spells::StaticLookup — spell gem and buff counts
// ============================================================
TEST(SpellsStaticLookupTest, RoF2ReturnsNonNull) {
    const EQ::spells::LookupEntry *entry =
        EQ::spells::StaticLookup(EQ::versions::ClientVersion::RoF2);
    EXPECT_NE(entry, nullptr);
}

TEST(SpellsStaticLookupTest, RoF2HasMoreGemsThanTitanium) {
    const EQ::spells::LookupEntry *rof2 =
        EQ::spells::StaticLookup(EQ::versions::ClientVersion::RoF2);
    const EQ::spells::LookupEntry *tit =
        EQ::spells::StaticLookup(EQ::versions::ClientVersion::Titanium);
    ASSERT_NE(rof2, nullptr);
    ASSERT_NE(tit,  nullptr);
    EXPECT_GE(rof2->SpellGemCount, tit->SpellGemCount);
}

TEST(SpellsStaticLookupTest, TotalBuffsPositive) {
    const EQ::spells::LookupEntry *entry =
        EQ::spells::StaticLookup(EQ::versions::ClientVersion::RoF2);
    ASSERT_NE(entry, nullptr);
    EXPECT_GT(entry->TotalBuffs, 0);
}

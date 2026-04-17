#include <gtest/gtest.h>
#include "common/platform.h"

// ============================================================
// RegisterExecutablePlatform / GetExecutablePlatform
// ============================================================
TEST(PlatformRegisterTest, DefaultIsNone) {
    // After registration with None, getter returns None
    RegisterExecutablePlatform(ExePlatformNone);
    EXPECT_EQ(GetExecutablePlatform(), ExePlatformNone);
}

TEST(PlatformRegisterTest, RegisterAndGetZone) {
    RegisterExecutablePlatform(ExePlatformZone);
    EXPECT_EQ(GetExecutablePlatform(), ExePlatformZone);
    RegisterExecutablePlatform(ExePlatformNone); // cleanup
}

TEST(PlatformRegisterTest, GetIntMatchesEnum) {
    RegisterExecutablePlatform(ExePlatformWorld);
    EXPECT_EQ(GetExecutablePlatformInt(), static_cast<int>(ExePlatformWorld));
    RegisterExecutablePlatform(ExePlatformNone);
}

// ============================================================
// GetPlatformName
// ============================================================
TEST(GetPlatformNameTest, WorldReturnsWorld) {
    RegisterExecutablePlatform(ExePlatformWorld);
    EXPECT_EQ(GetPlatformName(), "World");
    RegisterExecutablePlatform(ExePlatformNone);
}

TEST(GetPlatformNameTest, ZoneReturnsZone) {
    RegisterExecutablePlatform(ExePlatformZone);
    EXPECT_EQ(GetPlatformName(), "Zone");
    RegisterExecutablePlatform(ExePlatformNone);
}

TEST(GetPlatformNameTest, TestsReturnsTests) {
    RegisterExecutablePlatform(ExePlatformTests);
    EXPECT_EQ(GetPlatformName(), "Tests");
    RegisterExecutablePlatform(ExePlatformNone);
}

TEST(GetPlatformNameTest, NoneReturnsEmpty) {
    RegisterExecutablePlatform(ExePlatformNone);
    EXPECT_EQ(GetPlatformName(), "");
}

// ============================================================
// IsWorld / IsQueryServ
// ============================================================
TEST(IsWorldTest, TrueWhenWorld) {
    RegisterExecutablePlatform(ExePlatformWorld);
    EXPECT_TRUE(IsWorld());
    RegisterExecutablePlatform(ExePlatformNone);
}

TEST(IsWorldTest, FalseWhenZone) {
    RegisterExecutablePlatform(ExePlatformZone);
    EXPECT_FALSE(IsWorld());
    RegisterExecutablePlatform(ExePlatformNone);
}

TEST(IsQueryServTest, TrueWhenQueryServ) {
    RegisterExecutablePlatform(ExePlatformQueryServ);
    EXPECT_TRUE(IsQueryServ());
    RegisterExecutablePlatform(ExePlatformNone);
}

TEST(IsQueryServTest, FalseWhenWorld) {
    RegisterExecutablePlatform(ExePlatformWorld);
    EXPECT_FALSE(IsQueryServ());
    RegisterExecutablePlatform(ExePlatformNone);
}


#include <gtest/gtest.h>
#include "common/dynamic_zone_base.h"

#include <cstring>
#include <string>

// ============================================================
// DzLockMsg enum class
// ============================================================
TEST(DzLockMsgTest, NoneIsZero) {
    EXPECT_EQ(static_cast<uint8_t>(DzLockMsg::None), 0u);
}

TEST(DzLockMsgTest, Sequential) {
    EXPECT_EQ(static_cast<uint8_t>(DzLockMsg::Close), 1u);
    EXPECT_EQ(static_cast<uint8_t>(DzLockMsg::Begin), 2u);
}

TEST(DzLockMsgTest, Distinct) {
    EXPECT_NE(DzLockMsg::None, DzLockMsg::Close);
    EXPECT_NE(DzLockMsg::Close, DzLockMsg::Begin);
}

// ============================================================
// DynamicZoneType enum class
// ============================================================
TEST(DynamicZoneTypeTest, NoneIsZero) {
    EXPECT_EQ(static_cast<int>(DynamicZoneType::None), 0);
}

TEST(DynamicZoneTypeTest, SequentialValues) {
    EXPECT_EQ(static_cast<int>(DynamicZoneType::Expedition), 1);
    EXPECT_EQ(static_cast<int>(DynamicZoneType::Tutorial),   2);
    EXPECT_EQ(static_cast<int>(DynamicZoneType::Task),       3);
    EXPECT_EQ(static_cast<int>(DynamicZoneType::Mission),    4);
    EXPECT_EQ(static_cast<int>(DynamicZoneType::Quest),      5);
}

TEST(DynamicZoneTypeTest, AllDistinct) {
    EXPECT_NE(DynamicZoneType::None,       DynamicZoneType::Expedition);
    EXPECT_NE(DynamicZoneType::Expedition, DynamicZoneType::Tutorial);
    EXPECT_NE(DynamicZoneType::Mission,    DynamicZoneType::Quest);
}

// ============================================================
// DynamicZoneMemberStatus enum class
// ============================================================
TEST(DzMemberStatusTest, UnknownIsZero) {
    EXPECT_EQ(static_cast<int>(DynamicZoneMemberStatus::Unknown), 0);
}

TEST(DzMemberStatusTest, SequentialValues) {
    EXPECT_EQ(static_cast<int>(DynamicZoneMemberStatus::Online),        1);
    EXPECT_EQ(static_cast<int>(DynamicZoneMemberStatus::Offline),       2);
    EXPECT_EQ(static_cast<int>(DynamicZoneMemberStatus::InDynamicZone), 3);
    EXPECT_EQ(static_cast<int>(DynamicZoneMemberStatus::LinkDead),      4);
}

// ============================================================
// DzNotAllAdded constexpr string
// ============================================================
TEST(DzConstantsTest, NotAllAddedIsNonEmpty) {
    EXPECT_GT(std::strlen(DzNotAllAdded), 0u);
}

TEST(DzConstantsTest, NotAllAddedContainsPlaceholders) {
    std::string msg = DzNotAllAdded;
    EXPECT_NE(msg.find("{0}"), std::string::npos);
    EXPECT_NE(msg.find("{1}"), std::string::npos);
    EXPECT_NE(msg.find("{2}"), std::string::npos);
    EXPECT_NE(msg.find("{3}"), std::string::npos);
}

// ============================================================
// DynamicZoneLocation struct
// ============================================================
TEST(DynamicZoneLocationTest, DefaultConstructorZeros) {
    DynamicZoneLocation loc;
    EXPECT_EQ(loc.zone_id, 0u);
    EXPECT_FLOAT_EQ(loc.x, 0.0f);
    EXPECT_FLOAT_EQ(loc.y, 0.0f);
    EXPECT_FLOAT_EQ(loc.z, 0.0f);
    EXPECT_FLOAT_EQ(loc.heading, 0.0f);
}

TEST(DynamicZoneLocationTest, ParameterizedConstructor) {
    DynamicZoneLocation loc(100, 1.5f, 2.5f, 3.5f, 90.0f);
    EXPECT_EQ(loc.zone_id, 100u);
    EXPECT_FLOAT_EQ(loc.x, 1.5f);
    EXPECT_FLOAT_EQ(loc.y, 2.5f);
    EXPECT_FLOAT_EQ(loc.z, 3.5f);
    EXPECT_FLOAT_EQ(loc.heading, 90.0f);
}

TEST(DynamicZoneLocationTest, FieldsAreWritable) {
    DynamicZoneLocation loc;
    loc.zone_id = 42u;
    loc.x = -10.0f;
    EXPECT_EQ(loc.zone_id, 42u);
    EXPECT_FLOAT_EQ(loc.x, -10.0f);
}

// ============================================================
// DynamicZoneMember struct
// ============================================================
TEST(DynamicZoneMemberTest, DefaultConstructorZeroId) {
    DynamicZoneMember m;
    EXPECT_EQ(m.id, 0u);
    EXPECT_TRUE(m.name.empty());
    EXPECT_EQ(m.status, DynamicZoneMemberStatus::Unknown);
}

TEST(DynamicZoneMemberTest, IdNameConstructor) {
    DynamicZoneMember m(1234, "TestPlayer");
    EXPECT_EQ(m.id, 1234u);
    EXPECT_EQ(m.name, "TestPlayer");
    EXPECT_EQ(m.status, DynamicZoneMemberStatus::Unknown);
}

TEST(DynamicZoneMemberTest, FullConstructor) {
    DynamicZoneMember m(5, "Player", DynamicZoneMemberStatus::Online);
    EXPECT_EQ(m.id, 5u);
    EXPECT_EQ(m.name, "Player");
    EXPECT_EQ(m.status, DynamicZoneMemberStatus::Online);
}

TEST(DynamicZoneMemberTest, IsOnlineForOnlineStatus) {
    DynamicZoneMember m(1, "P", DynamicZoneMemberStatus::Online);
    EXPECT_TRUE(m.IsOnline());
}

TEST(DynamicZoneMemberTest, IsOnlineForInDynamicZone) {
    DynamicZoneMember m(1, "P", DynamicZoneMemberStatus::InDynamicZone);
    EXPECT_TRUE(m.IsOnline());
}

TEST(DynamicZoneMemberTest, IsNotOnlineForOffline) {
    DynamicZoneMember m(1, "P", DynamicZoneMemberStatus::Offline);
    EXPECT_FALSE(m.IsOnline());
}

TEST(DynamicZoneMemberTest, IsValidRequiresNonzeroIdAndName) {
    DynamicZoneMember valid(1, "Player");
    EXPECT_TRUE(valid.IsValid());

    DynamicZoneMember no_id(0, "Player");
    EXPECT_FALSE(no_id.IsValid());

    DynamicZoneMember no_name(1, "");
    EXPECT_FALSE(no_name.IsValid());
}

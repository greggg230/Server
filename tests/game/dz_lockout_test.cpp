#include <gtest/gtest.h>
#include "common/dynamic_zone_lockout.h"

#include <chrono>
#include <ctime>

// Helper: construct a DzLockout with a fixed future expire time
static DzLockout MakeLockout(
    const std::string& uuid,
    const std::string& expedition,
    const std::string& event,
    uint32_t duration_seconds = 3600)
{
    uint64_t expire_time = static_cast<uint64_t>(
        std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now()
        ) + duration_seconds
    );
    return DzLockout(uuid, expedition, event, expire_time, duration_seconds);
}

// ============================================================
// Constructor / Accessors
// ============================================================
TEST(DzLockoutTest, ConstructorStoresExpeditionName) {
    auto lockout = MakeLockout("uuid1", "Plane of Fear", "Cazic-Thule", 3600);
    EXPECT_EQ(lockout.DzName(), "Plane of Fear");
}

TEST(DzLockoutTest, ConstructorStoresEventName) {
    auto lockout = MakeLockout("uuid1", "Plane of Fear", "Cazic-Thule", 3600);
    EXPECT_EQ(lockout.Event(), "Cazic-Thule");
}

TEST(DzLockoutTest, ConstructorStoresUUID) {
    auto lockout = MakeLockout("test-uuid-123", "Expedition", "Event", 3600);
    EXPECT_EQ(lockout.UUID(), "test-uuid-123");
}

TEST(DzLockoutTest, ConstructorStoresDuration) {
    auto lockout = MakeLockout("uuid1", "Raid", "Boss", 7200);
    EXPECT_EQ(lockout.GetDuration(), 7200u);
}

TEST(DzLockoutTest, DefaultConstructorNotReplay) {
    DzLockout lockout;
    EXPECT_FALSE(lockout.IsReplay());
}

// ============================================================
// IsReplay
// ============================================================
TEST(DzLockoutTest, ReplayTimerEventSetsIsReplay) {
    auto lockout = MakeLockout("u", "Expedition", DzLockout::ReplayTimer, 3600);
    EXPECT_TRUE(lockout.IsReplay());
}

TEST(DzLockoutTest, NonReplayEventIsNotReplay) {
    auto lockout = MakeLockout("u", "Expedition", "Boss Kill", 3600);
    EXPECT_FALSE(lockout.IsReplay());
}

// ============================================================
// IsEvent
// ============================================================
TEST(DzLockoutTest, IsEventMatchesStoredEvent) {
    auto lockout = MakeLockout("u", "Expedition", "Boss Kill", 3600);
    EXPECT_TRUE(lockout.IsEvent("Boss Kill"));
}

TEST(DzLockoutTest, IsEventMismatch) {
    auto lockout = MakeLockout("u", "Expedition", "Boss Kill", 3600);
    EXPECT_FALSE(lockout.IsEvent("Other Event"));
}

TEST(DzLockoutTest, IsEventCaseSensitive) {
    auto lockout = MakeLockout("u", "Expedition", "Boss Kill", 3600);
    EXPECT_FALSE(lockout.IsEvent("boss kill"));
}

// ============================================================
// IsUUID
// ============================================================
TEST(DzLockoutTest, IsUUIDMatchesStoredUUID) {
    auto lockout = MakeLockout("abc-123", "Exp", "Evt", 3600);
    EXPECT_TRUE(lockout.IsUUID("abc-123"));
}

TEST(DzLockoutTest, IsUUIDMismatch) {
    auto lockout = MakeLockout("abc-123", "Exp", "Evt", 3600);
    EXPECT_FALSE(lockout.IsUUID("xyz-456"));
}

// ============================================================
// IsSame
// ============================================================
TEST(DzLockoutTest, IsSameExpeditionAndEventMatches) {
    auto lockout = MakeLockout("u", "Plane of Fear", "Cazic-Thule", 3600);
    EXPECT_TRUE(lockout.IsSame("Plane of Fear", "Cazic-Thule"));
}

TEST(DzLockoutTest, IsSameExpeditionMismatch) {
    auto lockout = MakeLockout("u", "Plane of Fear", "Cazic-Thule", 3600);
    EXPECT_FALSE(lockout.IsSame("Plane of Hate", "Cazic-Thule"));
}

TEST(DzLockoutTest, IsSameEventMismatch) {
    auto lockout = MakeLockout("u", "Plane of Fear", "Cazic-Thule", 3600);
    EXPECT_FALSE(lockout.IsSame("Plane of Fear", "Other Boss"));
}

TEST(DzLockoutTest, IsSameOtherLockout) {
    auto a = MakeLockout("u1", "Expedition", "Event", 3600);
    auto b = MakeLockout("u2", "Expedition", "Event", 7200);
    EXPECT_TRUE(a.IsSame(b));
}

TEST(DzLockoutTest, IsSameDifferentExpedition) {
    auto a = MakeLockout("u1", "ExpA", "Event", 3600);
    auto b = MakeLockout("u2", "ExpB", "Event", 3600);
    EXPECT_FALSE(a.IsSame(b));
}

// ============================================================
// SetDuration / GetDuration
// ============================================================
TEST(DzLockoutTest, SetDurationUpdatesGetter) {
    auto lockout = MakeLockout("u", "Exp", "Evt", 3600);
    lockout.SetDuration(7200);
    EXPECT_EQ(lockout.GetDuration(), 7200u);
}

TEST(DzLockoutTest, SetDurationToZero) {
    auto lockout = MakeLockout("u", "Exp", "Evt", 3600);
    lockout.SetDuration(0);
    EXPECT_EQ(lockout.GetDuration(), 0u);
}

// ============================================================
// SetUUID / UUID
// ============================================================
TEST(DzLockoutTest, SetUUIDUpdatesGetter) {
    auto lockout = MakeLockout("old-uuid", "Exp", "Evt", 3600);
    lockout.SetUUID("new-uuid");
    EXPECT_EQ(lockout.UUID(), "new-uuid");
}

// ============================================================
// GetExpireTime / GetStartTime relationship
// ============================================================
TEST(DzLockoutTest, StartTimePlusDurationEqualsExpireTime) {
    uint32_t duration = 3600;
    auto lockout = MakeLockout("u", "Exp", "Evt", duration);
    uint64_t expire = lockout.GetExpireTime();
    uint64_t start  = lockout.GetStartTime();
    EXPECT_EQ(expire - start, static_cast<uint64_t>(duration));
}

// ============================================================
// ReplayTimer constant
// ============================================================
TEST(DzLockoutTest, ReplayTimerConstantNotEmpty) {
    EXPECT_GT(strlen(DzLockout::ReplayTimer), 0u);
    EXPECT_STREQ(DzLockout::ReplayTimer, "Replay Timer");
}

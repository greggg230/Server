#include <gtest/gtest.h>
#include "common/timer.h"

// timer.cpp declares these as globals — we manipulate them to control time
extern uint32 current_time;

class TimerTest : public ::testing::Test {
protected:
    void SetUp() override {
        current_time = 1000; // start at a known non-zero time
    }
};

TEST_F(TimerTest, DefaultConstructorDisabled) {
    Timer t;
    EXPECT_FALSE(t.Enabled());
    EXPECT_EQ(t.GetDuration(), 0u);
    EXPECT_EQ(t.GetTimerTime(), 0u);
}

TEST_F(TimerTest, ConstructorWithTimeEnables) {
    Timer t(500);
    EXPECT_TRUE(t.Enabled());
    EXPECT_EQ(t.GetDuration(), 500u);
    EXPECT_EQ(t.GetTimerTime(), 500u);
}

TEST_F(TimerTest, ConstructorWithZeroTimeDisables) {
    Timer t(0);
    EXPECT_FALSE(t.Enabled());
}

TEST_F(TimerTest, ThreeArgConstructorSetsFields) {
    Timer t(200, 300, false);
    EXPECT_TRUE(t.Enabled());
    EXPECT_EQ(t.GetDuration(), 300u);
    EXPECT_EQ(t.GetStartTime(), 200u);
}

TEST_F(TimerTest, EnableDisableToggle) {
    Timer t(500);
    EXPECT_TRUE(t.Enabled());
    t.Disable();
    EXPECT_FALSE(t.Enabled());
    t.Enable();
    EXPECT_TRUE(t.Enabled());
}

TEST_F(TimerTest, CheckReturnsFalseBeforeExpiry) {
    current_time = 1000;
    Timer t(500);
    current_time = 1200; // 200ms elapsed, timer is 500ms
    EXPECT_FALSE(t.Check());
}

TEST_F(TimerTest, CheckReturnsTrueAfterExpiry) {
    current_time = 1000;
    Timer t(500);
    current_time = 1600; // 600ms elapsed, timer is 500ms
    EXPECT_TRUE(t.Check());
}

TEST_F(TimerTest, CheckResetsStartTimeByDefault) {
    current_time = 1000;
    Timer t(500);
    current_time = 1600;
    t.Check(); // fires and resets
    current_time = 1700; // only 100ms after reset
    EXPECT_FALSE(t.Check()); // should not fire again
}

TEST_F(TimerTest, CheckWithNoResetDoesNotReset) {
    current_time = 1000;
    Timer t(500);
    current_time = 1600;
    EXPECT_TRUE(t.Check(false)); // fires, no reset
    EXPECT_TRUE(t.Check(false)); // still expired, fires again
}

TEST_F(TimerTest, CheckDisabledTimerReturnsFalse) {
    current_time = 1000;
    Timer t(500);
    t.Disable();
    current_time = 9999;
    EXPECT_FALSE(t.Check());
}

TEST_F(TimerTest, GetRemainingTimeWhenNotExpired) {
    current_time = 1000;
    Timer t(500);
    current_time = 1200; // 200ms elapsed
    uint32 remaining = t.GetRemainingTime();
    EXPECT_EQ(remaining, 300u); // 500 - 200
}

TEST_F(TimerTest, GetRemainingTimeWhenExpired) {
    current_time = 1000;
    Timer t(500);
    current_time = 1600;
    EXPECT_EQ(t.GetRemainingTime(), 0u);
}

TEST_F(TimerTest, GetRemainingTimeWhenDisabledReturnsMax) {
    Timer t(500);
    t.Disable();
    EXPECT_EQ(t.GetRemainingTime(), 0xFFFFFFFFu);
}

TEST_F(TimerTest, StartEnablesAndResetsStartTime) {
    current_time = 1000;
    Timer t(500);
    t.Disable();
    current_time = 2000;
    t.Start();
    EXPECT_TRUE(t.Enabled());
    EXPECT_EQ(t.GetStartTime(), 2000u);
}

TEST_F(TimerTest, StartWithNewTimerTimeChangesTimer) {
    current_time = 1000;
    Timer t(500);
    current_time = 2000;
    t.Start(1000);
    EXPECT_EQ(t.GetDuration(), 1000u);
}

TEST_F(TimerTest, SetTimerChangesTimerTime) {
    Timer t(500);
    t.SetTimer(1000);
    EXPECT_EQ(t.GetDuration(), 1000u);
}

TEST_F(TimerTest, SetTimerEnablesIfDisabled) {
    current_time = 1000;
    Timer t(500);
    t.Disable();
    current_time = 2000;
    t.SetTimer(200);
    EXPECT_TRUE(t.Enabled());
    EXPECT_EQ(t.GetStartTime(), 2000u);
}

TEST_F(TimerTest, SetAtTriggerUpdatesSetAtTrigger) {
    Timer t(500);
    t.SetAtTrigger(999);
    EXPECT_EQ(t.GetSetAtTrigger(), 999u);
}

TEST_F(TimerTest, SetAtTriggerWithEnableIfDisabled) {
    Timer t(500);
    t.Disable();
    EXPECT_FALSE(t.Enabled());
    t.SetAtTrigger(200, true);
    EXPECT_TRUE(t.Enabled());
}

TEST_F(TimerTest, SetAtTriggerWithChangeTimerTime) {
    Timer t(500);
    t.SetAtTrigger(200, false, true);
    EXPECT_EQ(t.GetDuration(), 200u);
}

TEST_F(TimerTest, TriggerMakesCheckFireImmediately) {
    current_time = 1000;
    Timer t(500);
    t.Trigger();
    // After Trigger, Check() should return true without advancing time
    EXPECT_TRUE(t.Check(false));
}

TEST_F(TimerTest, SetAtTriggerUsedAfterCheckFires) {
    current_time = 1000;
    Timer t(500);
    t.SetAtTrigger(100); // after firing, reset to 100ms
    current_time = 1600; // expire the timer
    t.Check(); // fires, resets timer_time to set_at_trigger (100)
    EXPECT_EQ(t.GetDuration(), 100u);
}

TEST_F(TimerTest, AccurateTimingAddsToStartTime) {
    current_time = 1000;
    Timer t(500, true); // accurate timing
    current_time = 1600;
    t.Check(); // fires, start_time += 500 → 1500
    EXPECT_EQ(t.GetStartTime(), 1500u);
}

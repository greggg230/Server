#include <gtest/gtest.h>
#include "common/profanity_manager.h"
#include "common/rdtsc.h"

#include <string>

// ============================================================
// ProfanityManager — constants
// ============================================================
TEST(ProfanityConstTest, RedactionCharIsStar) {
    char rc = EQ::ProfanityManager::REDACTION_CHARACTER;
    EXPECT_EQ(rc, '*');
}

TEST(ProfanityConstTest, RedactionLengthMinIsThree) {
    int min_len = EQ::ProfanityManager::REDACTION_LENGTH_MIN;
    EXPECT_EQ(min_len, 3);
}

// ============================================================
// ProfanityManager — empty list (no DB loaded)
// ============================================================
TEST(ProfanityEmptyListTest, ListStartsEmpty) {
    EXPECT_TRUE(EQ::ProfanityManager::GetProfanityList().empty());
}

TEST(ProfanityEmptyListTest, IsCensorshipInactiveWhenListEmpty) {
    EXPECT_FALSE(EQ::ProfanityManager::IsCensorshipActive());
}

TEST(ProfanityEmptyListTest, ContainsCensoredReturnsFalseWhenListEmpty) {
    EXPECT_FALSE(EQ::ProfanityManager::ContainsCensoredLanguage("hello world"));
}

// ============================================================
// ProfanityManager — boundary conditions (independent of list)
// ============================================================
TEST(ProfanityBoundaryTest, TooShortStringReturnsFalseFromContains) {
    // Strings shorter than REDACTION_LENGTH_MIN are always safe
    EXPECT_FALSE(EQ::ProfanityManager::ContainsCensoredLanguage(""));
    EXPECT_FALSE(EQ::ProfanityManager::ContainsCensoredLanguage("ab"));
}

TEST(ProfanityBoundaryTest, ExactlyMinLengthIsChecked) {
    // "abc" has length 3 == REDACTION_LENGTH_MIN, should be checked (but list is empty)
    EXPECT_FALSE(EQ::ProfanityManager::ContainsCensoredLanguage("abc"));
}

TEST(ProfanityBoundaryTest, VeryLongStringReturnsFalse) {
    std::string long_msg(4096, 'x');
    EXPECT_FALSE(EQ::ProfanityManager::ContainsCensoredLanguage(long_msg));
}

TEST(ProfanityBoundaryTest, JustUnder4096IsChecked) {
    std::string near_limit(4095, 'a');
    // Still returns false because list is empty
    EXPECT_FALSE(EQ::ProfanityManager::ContainsCensoredLanguage(near_limit));
}

// ============================================================
// ProfanityManager — RedactMessage (string overload)
// ============================================================
TEST(ProfanityRedactTest, ShortStringUnchanged) {
    std::string msg = "hi";
    EQ::ProfanityManager::RedactMessage(msg);
    EXPECT_EQ(msg, "hi");
}

TEST(ProfanityRedactTest, EmptyStringUnchanged) {
    std::string msg;
    EQ::ProfanityManager::RedactMessage(msg);
    EXPECT_TRUE(msg.empty());
}

TEST(ProfanityRedactTest, NormalStringUnchangedWithEmptyList) {
    std::string msg = "Hello world";
    EQ::ProfanityManager::RedactMessage(msg);
    EXPECT_EQ(msg, "Hello world");
}

TEST(ProfanityRedactTest, VeryLongStringUnchangedWithEmptyList) {
    std::string msg(4096, 'z');
    std::string original = msg;
    EQ::ProfanityManager::RedactMessage(msg);
    EXPECT_EQ(msg, original);
}

// ============================================================
// ProfanityManager — RedactMessage (char* overload)
// ============================================================
TEST(ProfanityRedactCharTest, NullptrDoesNotCrash) {
    EXPECT_NO_THROW(EQ::ProfanityManager::RedactMessage(static_cast<char*>(nullptr)));
}

TEST(ProfanityRedactCharTest, NormalMessageUnchangedWithEmptyList) {
    char msg[] = "Hello world";
    EQ::ProfanityManager::RedactMessage(msg);
    EXPECT_STREQ(msg, "Hello world");
}

// ============================================================
// RDTSC_Timer — construction and static properties
// ============================================================
TEST(RDTSCTimerTest, DefaultConstructDoesNotCrash) {
    EXPECT_NO_THROW(RDTSC_Timer t);
}

TEST(RDTSCTimerTest, BoolConstructDoesNotCrash) {
    EXPECT_NO_THROW(RDTSC_Timer t(false));
    EXPECT_NO_THROW(RDTSC_Timer t2(true));
}

TEST(RDTSCTimerTest, TicksPerMSIsPositive) {
    RDTSC_Timer t;
    EXPECT_GT(RDTSC_Timer::ticksPerMS(), 0);
}

TEST(RDTSCTimerTest, StartStopDoesNotCrash) {
    RDTSC_Timer t;
    EXPECT_NO_THROW(t.start());
    EXPECT_NO_THROW(t.stop());
}

TEST(RDTSCTimerTest, GetDurationAfterStartStopIsNonNegative) {
    RDTSC_Timer t;
    t.start();
    t.stop();
    EXPECT_GE(t.getDuration(), 0.0);
}

TEST(RDTSCTimerTest, GetTicksAfterStopIsNonNegative) {
    RDTSC_Timer t;
    t.start();
    t.stop();
    EXPECT_GE(t.getTicks(), 0);
}

// ============================================================
// RDTSC_Collector — accumulated timing
// ============================================================
TEST(RDTSCCollectorTest, DefaultConstructDoesNotCrash) {
    EXPECT_NO_THROW(RDTSC_Collector c);
}

TEST(RDTSCCollectorTest, InitialCountAndSumAreZero) {
    RDTSC_Collector c;
    EXPECT_EQ(c.getCount(), 0);
    EXPECT_EQ(c.getTotalTicks(), 0);
}

TEST(RDTSCCollectorTest, ResetClearsAccumulator) {
    RDTSC_Collector c;
    c.start();
    c.stop();
    c.reset();
    EXPECT_EQ(c.getCount(), 0);
    EXPECT_EQ(c.getTotalTicks(), 0);
}

TEST(RDTSCCollectorTest, AfterOneStopCountIsOne) {
    RDTSC_Collector c;
    c.start();
    c.stop();
    EXPECT_EQ(c.getCount(), 1);
}

TEST(RDTSCCollectorTest, TotalDurationIsNonNegative) {
    RDTSC_Collector c;
    c.start();
    c.stop();
    EXPECT_GE(c.getTotalDuration(), 0.0);
}

#include <gtest/gtest.h>
#include "common/net/crc32.h"
#include "common/strings.h"
#include "common/cron/croncpp.h"

#include <cstdint>
#include <stdexcept>
#include <ctime>

// ============================================================
// EQ::Crc32 — distinct from common/crc32.h CRC32 class
// ============================================================
TEST(EQNetCrc32Test, EmptySizeReturnsZero) {
    const char buf[] = "x";
    EXPECT_EQ(EQ::Crc32(buf, 0), 0);
}

TEST(EQNetCrc32Test, HelloKnownValue) {
    EXPECT_EQ(EQ::Crc32("hello", 5), 907060870);
}

TEST(EQNetCrc32Test, ABCKnownValue) {
    EXPECT_EQ(EQ::Crc32("abc", 3), 891568578);
}

TEST(EQNetCrc32Test, WithKeyHelloKey0) {
    EXPECT_EQ(EQ::Crc32("hello", 5, 0), 372983093);
}

TEST(EQNetCrc32Test, WithKeyHelloKey1) {
    EXPECT_EQ(EQ::Crc32("hello", 5, 1), 20992374);
}

TEST(EQNetCrc32Test, Deterministic) {
    int a = EQ::Crc32("deterministic", 13);
    int b = EQ::Crc32("deterministic", 13);
    EXPECT_EQ(a, b);
}

TEST(EQNetCrc32Test, DifferentInputsDifferentResults) {
    EXPECT_NE(EQ::Crc32("hello", 5), EQ::Crc32("world", 5));
}

TEST(EQNetCrc32Test, DifferentKeysDifferentResults) {
    EXPECT_NE(EQ::Crc32("hello", 5, 0), EQ::Crc32("hello", 5, 1));
}

// ============================================================
// cron::INVALID_TIME sentinel
// ============================================================
TEST(CronConstantsTest, InvalidTimeIsNegativeOne) {
    EXPECT_EQ(cron::INVALID_TIME, static_cast<std::time_t>(-1));
}

// ============================================================
// cron::make_cron — valid and invalid expressions
// Standard traits use 6 fields: second minute hour day_of_month month day_of_week
// ============================================================
TEST(CronMakeCronTest, ValidEveryMinuteNothrows) {
    // "0 * * * * *" = second=0, every minute, every hour, every day/month/dow
    EXPECT_NO_THROW(cron::make_cron("0 * * * * *"));
}

TEST(CronMakeCronTest, ValidEverySecondNothrows) {
    EXPECT_NO_THROW(cron::make_cron("* * * * * *"));
}

TEST(CronMakeCronTest, ValidSpecificFieldsNothrow) {
    // "0 30 9 * * 1" = 09:30:00 every Monday
    EXPECT_NO_THROW(cron::make_cron("0 30 9 * * 1"));
}

TEST(CronMakeCronTest, InvalidFieldCountThrows) {
    // Only 3 fields is invalid
    EXPECT_THROW(cron::make_cron("* * *"), cron::bad_cronexpr);
}

TEST(CronMakeCronTest, EmptyExpressionThrows) {
    EXPECT_THROW(cron::make_cron(""), cron::bad_cronexpr);
}

TEST(CronMakeCronTest, OutOfRangeMinuteThrows) {
    // Minute 60 is out of range (0-59)
    EXPECT_THROW(cron::make_cron("0 60 * * * *"), cron::bad_cronexpr);
}

TEST(CronMakeCronTest, BadCronexprIsDerivedFromRuntimeError) {
    // bad_cronexpr must be catchable as std::runtime_error
    try {
        cron::make_cron("invalid expr here");
        FAIL() << "Expected bad_cronexpr";
    } catch (const std::runtime_error &) {
        SUCCEED();
    }
}

// ============================================================
// cron::cron_next — next fire time is in the future
// ============================================================
TEST(CronNextTest, NextTimeIsAfterBase) {
    auto expr = cron::make_cron("* * * * * *"); // every second
    // Use a fixed known base: 2024-01-01 00:00:00 UTC
    std::tm base{};
    base.tm_year = 124; // 2024
    base.tm_mon  = 0;   // January
    base.tm_mday = 1;
    base.tm_hour = 0;
    base.tm_min  = 0;
    base.tm_sec  = 0;
    std::time_t base_t = std::mktime(&base);
    ASSERT_NE(base_t, static_cast<std::time_t>(-1));

    std::time_t next_t = cron::cron_next(expr, base_t);
    EXPECT_NE(next_t, cron::INVALID_TIME);
    EXPECT_GT(next_t, base_t);
}

TEST(CronNextTest, EveryMinuteAdvancesBy60Seconds) {
    // "0 * * * * *" fires at second=0 of each minute
    auto expr = cron::make_cron("0 * * * * *");
    // Start exactly at a minute boundary: 2024-01-01 00:00:00
    std::tm base{};
    base.tm_year = 124;
    base.tm_mon  = 0;
    base.tm_mday = 1;
    base.tm_hour = 0;
    base.tm_min  = 0;
    base.tm_sec  = 0;
    std::time_t base_t = std::mktime(&base);
    ASSERT_NE(base_t, static_cast<std::time_t>(-1));

    std::time_t next_t = cron::cron_next(expr, base_t);
    ASSERT_NE(next_t, cron::INVALID_TIME);
    // Next fire is 60 seconds later (next :00)
    EXPECT_EQ(next_t - base_t, 60);
}

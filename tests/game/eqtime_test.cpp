#include <gtest/gtest.h>
#include <cstring>
#include "common/eqtime.h"

// Helper to build a TimeOfDay_Struct
static TimeOfDay_Struct MakeTOD(uint32 year, uint8 month, uint8 day, uint8 hour, uint8 minute) {
	TimeOfDay_Struct t{};
	t.year   = year;
	t.month  = month;
	t.day    = day;
	t.hour   = hour;
	t.minute = minute;
	return t;
}

// ── EQTime::IsTimeBefore(base, test) ─────────────────────────────────────────
// Returns true if 'test' is chronologically before 'base'

TEST(EQTimeTest, IsTimeBefore_EarlierYear) {
	auto base = MakeTOD(500, 6, 15, 12, 0);
	auto test = MakeTOD(499, 6, 15, 12, 0);
	EXPECT_TRUE(EQTime::IsTimeBefore(&base, &test));
}

TEST(EQTimeTest, IsTimeBefore_LaterYear) {
	auto base = MakeTOD(499, 6, 15, 12, 0);
	auto test = MakeTOD(500, 6, 15, 12, 0);
	EXPECT_FALSE(EQTime::IsTimeBefore(&base, &test));
}

TEST(EQTimeTest, IsTimeBefore_EarlierMonth) {
	auto base = MakeTOD(500, 7, 1, 1, 0);
	auto test = MakeTOD(500, 6, 1, 1, 0);
	EXPECT_TRUE(EQTime::IsTimeBefore(&base, &test));
}

TEST(EQTimeTest, IsTimeBefore_LaterMonth) {
	auto base = MakeTOD(500, 6, 1, 1, 0);
	auto test = MakeTOD(500, 7, 1, 1, 0);
	EXPECT_FALSE(EQTime::IsTimeBefore(&base, &test));
}

TEST(EQTimeTest, IsTimeBefore_EarlierDay) {
	auto base = MakeTOD(500, 6, 15, 1, 0);
	auto test = MakeTOD(500, 6, 14, 1, 0);
	EXPECT_TRUE(EQTime::IsTimeBefore(&base, &test));
}

TEST(EQTimeTest, IsTimeBefore_EarlierHour) {
	auto base = MakeTOD(500, 6, 15, 12, 0);
	auto test = MakeTOD(500, 6, 15, 11, 0);
	EXPECT_TRUE(EQTime::IsTimeBefore(&base, &test));
}

TEST(EQTimeTest, IsTimeBefore_EarlierMinute) {
	auto base = MakeTOD(500, 6, 15, 12, 30);
	auto test = MakeTOD(500, 6, 15, 12, 29);
	EXPECT_TRUE(EQTime::IsTimeBefore(&base, &test));
}

TEST(EQTimeTest, IsTimeBefore_Identical) {
	auto tod = MakeTOD(500, 6, 15, 12, 30);
	// Equal timestamps: minute comparison: base->minute > test->minute → false
	EXPECT_FALSE(EQTime::IsTimeBefore(&tod, &tod));
}

// ── EQTime::AddMinutes ────────────────────────────────────────────────────────
// EQ calendar: 60 min/hr, 24 hr/day (1-24), 28 day/month (1-28), 12 month/yr

TEST(EQTimeTest, AddMinutes_NoCarry) {
	auto t = MakeTOD(500, 6, 15, 12, 10);
	EQTime::AddMinutes(15, &t);
	EXPECT_EQ(25, t.minute);
	EXPECT_EQ(12, t.hour);
	EXPECT_EQ(15, t.day);
}

TEST(EQTimeTest, AddMinutes_CarriesHour) {
	auto t = MakeTOD(500, 6, 15, 12, 50);
	EQTime::AddMinutes(30, &t);
	EXPECT_EQ(20, t.minute);
	EXPECT_EQ(13, t.hour);
}

TEST(EQTimeTest, AddMinutes_ExactHourBoundary) {
	auto t = MakeTOD(500, 6, 15, 12, 0);
	EQTime::AddMinutes(60, &t);
	EXPECT_EQ(0, t.minute);
	EXPECT_EQ(13, t.hour);
}

TEST(EQTimeTest, AddMinutes_CarriesDay) {
	// Hour 24 + 1 hr = wraps to hour 1, day increments
	auto t = MakeTOD(500, 6, 15, 24, 0);
	EQTime::AddMinutes(60, &t);
	EXPECT_EQ(1, t.hour);
	EXPECT_EQ(16, t.day);
}

TEST(EQTimeTest, AddMinutes_CarriesMonth) {
	// Day 28 + 1 day = wraps to day 1, month increments
	auto t = MakeTOD(500, 6, 28, 24, 0);
	EQTime::AddMinutes(60, &t);
	EXPECT_EQ(1, t.day);
	EXPECT_EQ(7, t.month);
}

TEST(EQTimeTest, AddMinutes_CarriesYear) {
	// Month 12 + 1 month = wraps to month 1, year increments
	auto t = MakeTOD(500, 12, 28, 24, 0);
	EQTime::AddMinutes(60, &t);
	EXPECT_EQ(1, t.day);
	EXPECT_EQ(1, t.month);
	EXPECT_EQ(501u, t.year);
}

TEST(EQTimeTest, AddMinutes_Zero) {
	auto t = MakeTOD(500, 6, 15, 12, 30);
	EQTime::AddMinutes(0, &t);
	EXPECT_EQ(30, t.minute);
	EXPECT_EQ(12, t.hour);
}

TEST(EQTimeTest, AddMinutes_MultipleHours) {
	auto t = MakeTOD(500, 6, 15, 1, 0);
	EQTime::AddMinutes(120, &t); // 2 hours
	EXPECT_EQ(0, t.minute);
	EXPECT_EQ(3, t.hour);
}

// ── EQTime::ToString ──────────────────────────────────────────────────────────

TEST(EQTimeTest, ToString_Format) {
	auto t = MakeTOD(500, 6, 15, 12, 30);
	std::string s;
	EQTime::ToString(&t, s);
	EXPECT_EQ("06/15/0500 12:30", s);
}

TEST(EQTimeTest, ToString_PadsZeros) {
	auto t = MakeTOD(1, 1, 1, 1, 1);
	std::string s;
	EQTime::ToString(&t, s);
	EXPECT_EQ("01/01/0001 01:01", s);
}

TEST(EQTimeTest, ToString_LargeYear) {
	auto t = MakeTOD(3100, 12, 28, 24, 59);
	std::string s;
	EQTime::ToString(&t, s);
	EXPECT_EQ("12/28/3100 24:59", s);
}

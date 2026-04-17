#include <gtest/gtest.h>
#include "common/termcolor/rang.hpp"

// ============================================================
// rang::style enum class — ANSI SGR codes
// ============================================================
TEST(RangStyleTest, ResetIsZero) {
    EXPECT_EQ(static_cast<int>(rang::style::reset), 0);
}

TEST(RangStyleTest, BoldIsOne) {
    EXPECT_EQ(static_cast<int>(rang::style::bold), 1);
}

TEST(RangStyleTest, DimIsTwo) {
    EXPECT_EQ(static_cast<int>(rang::style::dim), 2);
}

TEST(RangStyleTest, UnderlineIsFour) {
    EXPECT_EQ(static_cast<int>(rang::style::underline), 4);
}

TEST(RangStyleTest, CrossedIsNine) {
    EXPECT_EQ(static_cast<int>(rang::style::crossed), 9);
}

TEST(RangStyleTest, ValuesAreSequential) {
    EXPECT_EQ(static_cast<int>(rang::style::italic),   3);
    EXPECT_EQ(static_cast<int>(rang::style::blink),    5);
    EXPECT_EQ(static_cast<int>(rang::style::rblink),   6);
    EXPECT_EQ(static_cast<int>(rang::style::reversed), 7);
    EXPECT_EQ(static_cast<int>(rang::style::conceal),  8);
}

// ============================================================
// rang::fg enum class — foreground ANSI color codes
// ============================================================
TEST(RangFgTest, BlackIs30) {
    EXPECT_EQ(static_cast<int>(rang::fg::black), 30);
}

TEST(RangFgTest, RedIs31) {
    EXPECT_EQ(static_cast<int>(rang::fg::red), 31);
}

TEST(RangFgTest, GreenIs32) {
    EXPECT_EQ(static_cast<int>(rang::fg::green), 32);
}

TEST(RangFgTest, YellowIs33) {
    EXPECT_EQ(static_cast<int>(rang::fg::yellow), 33);
}

TEST(RangFgTest, BlueIs34) {
    EXPECT_EQ(static_cast<int>(rang::fg::blue), 34);
}

TEST(RangFgTest, CyanIs36) {
    EXPECT_EQ(static_cast<int>(rang::fg::cyan), 36);
}

TEST(RangFgTest, ResetIs39) {
    EXPECT_EQ(static_cast<int>(rang::fg::reset), 39);
}

// ============================================================
// rang::bg enum class — background ANSI color codes
// ============================================================
TEST(RangBgTest, BlackIs40) {
    EXPECT_EQ(static_cast<int>(rang::bg::black), 40);
}

TEST(RangBgTest, ForegroundAndBackgroundOffset10) {
    // bg starts 10 above fg for each color
    EXPECT_EQ(static_cast<int>(rang::bg::red),
              static_cast<int>(rang::fg::red) + 10);
    EXPECT_EQ(static_cast<int>(rang::bg::green),
              static_cast<int>(rang::fg::green) + 10);
    EXPECT_EQ(static_cast<int>(rang::bg::blue),
              static_cast<int>(rang::fg::blue) + 10);
}

TEST(RangBgTest, ResetIs49) {
    EXPECT_EQ(static_cast<int>(rang::bg::reset), 49);
}

// ============================================================
// rang::fgB enum class — bright foreground codes (90-97)
// ============================================================
TEST(RangFgBTest, BlackIs90) {
    EXPECT_EQ(static_cast<int>(rang::fgB::black), 90);
}

TEST(RangFgBTest, RedIs91) {
    EXPECT_EQ(static_cast<int>(rang::fgB::red), 91);
}

TEST(RangFgBTest, GrayIs97) {
    EXPECT_EQ(static_cast<int>(rang::fgB::gray), 97);
}

// ============================================================
// rang::bgB enum class — bright background codes (100-107)
// ============================================================
TEST(RangBgBTest, BlackIs100) {
    EXPECT_EQ(static_cast<int>(rang::bgB::black), 100);
}

TEST(RangBgBTest, GrayIs107) {
    EXPECT_EQ(static_cast<int>(rang::bgB::gray), 107);
}

TEST(RangBgBTest, BrightFgAndBgOffset10) {
    EXPECT_EQ(static_cast<int>(rang::bgB::red),
              static_cast<int>(rang::fgB::red) + 10);
}

// ============================================================
// rang::control enum class
// ============================================================
TEST(RangControlTest, OffIsZero) {
    EXPECT_EQ(static_cast<int>(rang::control::Off), 0);
}

TEST(RangControlTest, AutoIsOne) {
    EXPECT_EQ(static_cast<int>(rang::control::Auto), 1);
}

TEST(RangControlTest, ForceIsTwo) {
    EXPECT_EQ(static_cast<int>(rang::control::Force), 2);
}

// ============================================================
// rang::winTerm enum class
// ============================================================
TEST(RangWinTermTest, AutoIsZero) {
    EXPECT_EQ(static_cast<int>(rang::winTerm::Auto), 0);
}

TEST(RangWinTermTest, AnsiIsOne) {
    EXPECT_EQ(static_cast<int>(rang::winTerm::Ansi), 1);
}

TEST(RangWinTermTest, NativeIsTwo) {
    EXPECT_EQ(static_cast<int>(rang::winTerm::Native), 2);
}

/*	EQEmu: EQEmulator

	Copyright (C) 2001-2026 EQEmu Development Team

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 3 of the License, or
	(at your option) any later version.
*/
#include <gtest/gtest.h>
#include "common/seperator.h"

// ---------------------------------------------------------------------------
// Basic splitting
// ---------------------------------------------------------------------------

TEST(Seperator, SplitsOnSpaces) {
	Seperator sep("hello world foo");
	EXPECT_STREQ(sep.arg[0], "hello");
	EXPECT_STREQ(sep.arg[1], "world");
	EXPECT_STREQ(sep.arg[2], "foo");
	EXPECT_EQ(sep.argnum, 2);  // argnum is index of last arg
}

TEST(Seperator, SingleWord) {
	Seperator sep("hello");
	EXPECT_STREQ(sep.arg[0], "hello");
	EXPECT_EQ(sep.argnum, 0);
}

TEST(Seperator, EmptyString) {
	Seperator sep("");
	EXPECT_EQ(sep.argnum, 0);
	EXPECT_STREQ(sep.arg[0], "");
}

TEST(Seperator, LeadingSpacesSkipped) {
	Seperator sep("  hello world");
	EXPECT_STREQ(sep.arg[0], "hello");
	EXPECT_STREQ(sep.arg[1], "world");
}

TEST(Seperator, MultipleSpacesBetweenArgs) {
	Seperator sep("hello   world");
	EXPECT_STREQ(sep.arg[0], "hello");
	EXPECT_STREQ(sep.arg[1], "world");
}

TEST(Seperator, TabIsDefaultDelimiter) {
	Seperator sep("hello\tworld");
	EXPECT_STREQ(sep.arg[0], "hello");
	EXPECT_STREQ(sep.arg[1], "world");
}

// ---------------------------------------------------------------------------
// argplus — pointer into original string from that arg onward
// ---------------------------------------------------------------------------

TEST(Seperator, ArgplusPointsToRestOfString) {
	Seperator sep("say hello world");
	// argplus[1] should point to "hello world", not just "hello"
	EXPECT_STREQ(sep.argplus[1], "hello world");
	EXPECT_STREQ(sep.argplus[2], "world");
}

// ---------------------------------------------------------------------------
// IsNumber
// ---------------------------------------------------------------------------

TEST(Seperator, IsNumberPositiveInteger) {
	Seperator sep("42");
	EXPECT_TRUE(sep.IsNumber(0));
}

TEST(Seperator, IsNumberNegativeInteger) {
	Seperator sep("-5");
	EXPECT_TRUE(sep.IsNumber(0));
}

TEST(Seperator, IsNumberFloat) {
	Seperator sep("3.14");
	EXPECT_TRUE(sep.IsNumber(0));
}

TEST(Seperator, IsNumberWord) {
	Seperator sep("hello");
	EXPECT_FALSE(sep.IsNumber(0));
}

TEST(Seperator, IsNumberEmpty) {
	EXPECT_FALSE(Seperator::IsNumber(""));
}

TEST(Seperator, IsNumberMixedAlphaNum) {
	Seperator sep("12abc");
	EXPECT_FALSE(sep.IsNumber(0));
}

// ---------------------------------------------------------------------------
// IsHexNumber
// ---------------------------------------------------------------------------

TEST(Seperator, IsHexNumberValid) {
	EXPECT_TRUE(Seperator::IsHexNumber(const_cast<char*>("0xFF")));
	EXPECT_TRUE(Seperator::IsHexNumber(const_cast<char*>("0x1A2B")));
	EXPECT_TRUE(Seperator::IsHexNumber(const_cast<char*>("0xdeadbeef")));
}

TEST(Seperator, IsHexNumberNoPrefix) {
	EXPECT_FALSE(Seperator::IsHexNumber(const_cast<char*>("FF")));
	EXPECT_FALSE(Seperator::IsHexNumber(const_cast<char*>("1A")));
}

TEST(Seperator, IsHexNumberTooShort) {
	EXPECT_FALSE(Seperator::IsHexNumber(const_cast<char*>("0x")));
}

TEST(Seperator, IsHexNumberInvalidChar) {
	EXPECT_FALSE(Seperator::IsHexNumber(const_cast<char*>("0xGG")));
}

// ---------------------------------------------------------------------------
// Custom delimiter
// ---------------------------------------------------------------------------

TEST(Seperator, CustomDelimiter) {
	Seperator sep("one:two:three", ':');
	EXPECT_STREQ(sep.arg[0], "one");
	EXPECT_STREQ(sep.arg[1], "two");
	EXPECT_STREQ(sep.arg[2], "three");
}

// ---------------------------------------------------------------------------
// Quote handling
// ---------------------------------------------------------------------------

TEST(Seperator, QuotedArgTreatedAsSingle) {
	Seperator sep("say \"hello world\" now", ' ', 10, 100, true);
	EXPECT_STREQ(sep.arg[0], "say");
	EXPECT_STREQ(sep.arg[1], "hello world");
	EXPECT_STREQ(sep.arg[2], "now");
}

// ---------------------------------------------------------------------------
// Max arg limit
// ---------------------------------------------------------------------------

TEST(Seperator, RespectsMaxArgNum) {
	// Default maxargnum is 10; verify it doesn't overrun
	Seperator sep("a b c d e f g h i j k l m n", ' ', 3);
	EXPECT_LE(sep.argnum, static_cast<uint16>(sep.GetMaxArgNum() + 1));
	EXPECT_STREQ(sep.arg[0], "a");
	EXPECT_STREQ(sep.arg[3], "d");
}

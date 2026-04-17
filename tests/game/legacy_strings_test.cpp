#include <gtest/gtest.h>
#include <cstring>
#include "common/strings.h"

// ── strn0cpy ─────────────────────────────────────────────────────────────────

TEST(LegacyStringsTest, strn0cpy_Basic) {
	char buf[16] = {};
	strn0cpy(buf, "hello", sizeof(buf));
	EXPECT_STREQ("hello", buf);
}

TEST(LegacyStringsTest, strn0cpy_Truncates) {
	char buf[4] = {};
	strn0cpy(buf, "hello", sizeof(buf));
	EXPECT_STREQ("hel", buf);
	EXPECT_EQ('\0', buf[3]);
}

TEST(LegacyStringsTest, strn0cpy_NullSource) {
	char buf[16] = "original";
	strn0cpy(buf, nullptr, sizeof(buf));
	EXPECT_EQ('\0', buf[0]);
}

TEST(LegacyStringsTest, strn0cpy_ZeroSize) {
	char buf[16] = "original";
	strn0cpy(buf, "hello", 0);
	EXPECT_EQ('\0', buf[0]);
}

// ── strn0cpyt ─────────────────────────────────────────────────────────────────

TEST(LegacyStringsTest, strn0cpyt_FitsReturnsTrue) {
	char buf[16] = {};
	bool fit = strn0cpyt(buf, "hello", sizeof(buf));
	EXPECT_TRUE(fit);
	EXPECT_STREQ("hello", buf);
}

TEST(LegacyStringsTest, strn0cpyt_TruncatedReturnsFalse) {
	char buf[4] = {};
	bool fit = strn0cpyt(buf, "hello", sizeof(buf));
	EXPECT_FALSE(fit);
	EXPECT_STREQ("hel", buf);
}

TEST(LegacyStringsTest, strn0cpyt_ExactFitReturnsTrue) {
	char buf[6] = {};
	// "hello" is 5 chars + null = 6 bytes
	bool fit = strn0cpyt(buf, "hello", 6);
	EXPECT_TRUE(fit);
	EXPECT_STREQ("hello", buf);
}

// ── hextoi ────────────────────────────────────────────────────────────────────

TEST(LegacyStringsTest, hextoi_Basic) {
	EXPECT_EQ(0xDEADBEEFu, hextoi("0xDEADBEEF"));
}

TEST(LegacyStringsTest, hextoi_Lowercase) {
	EXPECT_EQ(0xdeadbeefu, hextoi("0xdeadbeef"));
}

TEST(LegacyStringsTest, hextoi_Zero) {
	EXPECT_EQ(0u, hextoi("0x00"));
}

TEST(LegacyStringsTest, hextoi_Small) {
	EXPECT_EQ(0xFFu, hextoi("0xFF"));
}

TEST(LegacyStringsTest, hextoi_NullReturnsZero) {
	EXPECT_EQ(0u, hextoi(nullptr));
}

TEST(LegacyStringsTest, hextoi_TooShortReturnsZero) {
	EXPECT_EQ(0u, hextoi("0x"));
}

TEST(LegacyStringsTest, hextoi_NoPrefixReturnsZero) {
	EXPECT_EQ(0u, hextoi("DEADBEEF"));
}

TEST(LegacyStringsTest, hextoi_InvalidCharReturnsZero) {
	EXPECT_EQ(0u, hextoi("0xGGGG"));
}

TEST(LegacyStringsTest, hextoi_UpperX) {
	EXPECT_EQ(0x1Au, hextoi("0X1A"));
}

// ── hextoi64 ──────────────────────────────────────────────────────────────────

TEST(LegacyStringsTest, hextoi64_Large) {
	EXPECT_EQ(0xDEADBEEFCAFEBABEull, hextoi64("0xDEADBEEFCAFEBABE"));
}

TEST(LegacyStringsTest, hextoi64_Zero) {
	EXPECT_EQ(0ull, hextoi64("0x00"));
}

TEST(LegacyStringsTest, hextoi64_Null) {
	EXPECT_EQ(0ull, hextoi64(nullptr));
}

// ── atobool ───────────────────────────────────────────────────────────────────

TEST(LegacyStringsTest, atobool_True_Variants) {
	EXPECT_TRUE(atobool("true"));
	EXPECT_TRUE(atobool("TRUE"));
	EXPECT_TRUE(atobool("yes"));
	EXPECT_TRUE(atobool("YES"));
	EXPECT_TRUE(atobool("on"));
	EXPECT_TRUE(atobool("enable"));
	EXPECT_TRUE(atobool("enabled"));
	EXPECT_TRUE(atobool("y"));
	EXPECT_TRUE(atobool("1"));
}

TEST(LegacyStringsTest, atobool_False_Variants) {
	EXPECT_FALSE(atobool("false"));
	EXPECT_FALSE(atobool("FALSE"));
	EXPECT_FALSE(atobool("no"));
	EXPECT_FALSE(atobool("NO"));
	EXPECT_FALSE(atobool("off"));
	EXPECT_FALSE(atobool("disable"));
	EXPECT_FALSE(atobool("disabled"));
	EXPECT_FALSE(atobool("n"));
	EXPECT_FALSE(atobool("0"));
}

TEST(LegacyStringsTest, atobool_Null) {
	EXPECT_FALSE(atobool(nullptr));
}

TEST(LegacyStringsTest, atobool_UnknownReturnsFalse) {
	EXPECT_FALSE(atobool("maybe"));
}

// ── CleanMobName ─────────────────────────────────────────────────────────────

TEST(LegacyStringsTest, CleanMobName_UnderscoresToSpaces) {
	char out[64] = {};
	CleanMobName("a_dark_elf", out);
	EXPECT_STREQ("a dark elf", out);
}

TEST(LegacyStringsTest, CleanMobName_StripsNumbers) {
	char out[64] = {};
	CleanMobName("Mob123", out);
	EXPECT_STREQ("Mob", out);
}

TEST(LegacyStringsTest, CleanMobName_PreservesBacktick) {
	char out[64] = {};
	CleanMobName("test`name", out);
	EXPECT_STREQ("test`name", out);
}

TEST(LegacyStringsTest, CleanMobName_StripsHash) {
	char out[64] = {};
	CleanMobName("#Echo_of_Sebilis", out);
	EXPECT_STREQ("Echo of Sebilis", out);
}

TEST(LegacyStringsTest, CleanMobName_EmptyInput) {
	char out[64] = {};
	CleanMobName("", out);
	EXPECT_STREQ("", out);
}

// ── isAlphaNumeric ────────────────────────────────────────────────────────────

TEST(LegacyStringsTest, isAlphaNumeric_Pure) {
	EXPECT_TRUE(isAlphaNumeric("Hello123"));
}

TEST(LegacyStringsTest, isAlphaNumeric_SpaceFails) {
	EXPECT_FALSE(isAlphaNumeric("Hello World"));
}

TEST(LegacyStringsTest, isAlphaNumeric_SpecialFails) {
	EXPECT_FALSE(isAlphaNumeric("hello!"));
}

TEST(LegacyStringsTest, isAlphaNumeric_DigitsOnly) {
	EXPECT_TRUE(isAlphaNumeric("123456"));
}

TEST(LegacyStringsTest, isAlphaNumeric_Empty) {
	// Empty string: loop never fires, returns true (same pattern as IsNumber)
	EXPECT_TRUE(isAlphaNumeric(""));
}

// ── FormatName ────────────────────────────────────────────────────────────────

TEST(LegacyStringsTest, FormatName_Capitalizes) {
	EXPECT_EQ("Gregg", FormatName("gregg"));
}

TEST(LegacyStringsTest, FormatName_LowercasesRest) {
	EXPECT_EQ("Gregg", FormatName("GREGG"));
}

TEST(LegacyStringsTest, FormatName_Empty) {
	EXPECT_EQ("", FormatName(""));
}

TEST(LegacyStringsTest, FormatName_SingleChar) {
	EXPECT_EQ("A", FormatName("a"));
}

// ── MakeLowerString ───────────────────────────────────────────────────────────

TEST(LegacyStringsTest, MakeLowerString_InPlace) {
	char buf[16] = "HELLO";
	MakeLowerString("HELLO", buf);
	EXPECT_STREQ("hello", buf);
}

TEST(LegacyStringsTest, MakeLowerString_AlreadyLower) {
	char buf[16] = {};
	MakeLowerString("hello", buf);
	EXPECT_STREQ("hello", buf);
}

// ── RemoveApostrophes ─────────────────────────────────────────────────────────

TEST(LegacyStringsTest, RemoveApostrophes_String) {
	std::string s = "it's a test";
	RemoveApostrophes(s);
	EXPECT_EQ("it_s a test", s);
}

TEST(LegacyStringsTest, RemoveApostrophes_NoApostrophe) {
	std::string s = "hello";
	RemoveApostrophes(s);
	EXPECT_EQ("hello", s);
}

// ── ConvertArray / ConvertArrayF ──────────────────────────────────────────────

TEST(LegacyStringsTest, ConvertArray_Positive) {
	char buf[32];
	EXPECT_STREQ("12345", ConvertArray(12345, buf));
}

TEST(LegacyStringsTest, ConvertArray_Negative) {
	char buf[32];
	EXPECT_STREQ("-1", ConvertArray(-1, buf));
}

TEST(LegacyStringsTest, ConvertArrayF_TwoDecimals) {
	char buf[32];
	EXPECT_STREQ("3.14", ConvertArrayF(3.14f, buf));
}

TEST(LegacyStringsTest, ConvertArrayF_Zero) {
	char buf[32];
	EXPECT_STREQ("0.00", ConvertArrayF(0.0f, buf));
}

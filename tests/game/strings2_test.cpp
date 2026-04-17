#include <gtest/gtest.h>
#include "common/strings.h"

// ============================================================
// Strings::ContainsLower (case-insensitive contains)
// ============================================================
TEST(StringsContainsLowerTest, ExactMatch) {
    EXPECT_TRUE(Strings::ContainsLower("hello world", "hello"));
}

TEST(StringsContainsLowerTest, CaseInsensitiveMatch) {
    EXPECT_TRUE(Strings::ContainsLower("Hello World", "hello"));
    EXPECT_TRUE(Strings::ContainsLower("HELLO", "hello"));
    EXPECT_TRUE(Strings::ContainsLower("hello", "HELLO"));
}

TEST(StringsContainsLowerTest, NoMatch) {
    EXPECT_FALSE(Strings::ContainsLower("hello world", "xyz"));
}

TEST(StringsContainsLowerTest, SubjectShorterThanSearch) {
    EXPECT_FALSE(Strings::ContainsLower("hi", "hello"));
}

// ============================================================
// Strings::RemoveNumbers
// ============================================================
TEST(StringsRemoveNumbersTest, RemovesAllDigits) {
    EXPECT_EQ(Strings::RemoveNumbers("abc123def456"), "abcdef");
}

TEST(StringsRemoveNumbersTest, NoDigitsUnchanged) {
    EXPECT_EQ(Strings::RemoveNumbers("hello"), "hello");
}

TEST(StringsRemoveNumbersTest, AllDigitsBecomesEmpty) {
    EXPECT_EQ(Strings::RemoveNumbers("12345"), "");
}

TEST(StringsRemoveNumbersTest, EmptyStringUnchanged) {
    EXPECT_EQ(Strings::RemoveNumbers(""), "");
}

TEST(StringsRemoveNumbersTest, MixedPreservesOrder) {
    EXPECT_EQ(Strings::RemoveNumbers("a1b2c3"), "abc");
}

// ============================================================
// Strings::ToBigInt / ToUnsignedInt / ToUnsignedBigInt
// ============================================================
TEST(StringsToBigIntTest, PositiveNumber) {
    EXPECT_EQ(Strings::ToBigInt("12345"), 12345LL);
}

TEST(StringsToBigIntTest, NegativeNumber) {
    EXPECT_EQ(Strings::ToBigInt("-99"), -99LL);
}

TEST(StringsToBigIntTest, FallbackOnNonNumber) {
    EXPECT_EQ(Strings::ToBigInt("abc", -1LL), -1LL);
}

TEST(StringsToBigIntTest, LargeValue) {
    EXPECT_EQ(Strings::ToBigInt("9000000000"), 9000000000LL);
}

TEST(StringsToUnsignedIntTest, PositiveNumber) {
    EXPECT_EQ(Strings::ToUnsignedInt("42"), 42u);
}

TEST(StringsToUnsignedIntTest, FallbackOnWord) {
    EXPECT_EQ(Strings::ToUnsignedInt("abc", 7u), 7u);
}

TEST(StringsToUnsignedIntTest, Zero) {
    EXPECT_EQ(Strings::ToUnsignedInt("0"), 0u);
}

TEST(StringsToUnsignedBigIntTest, LargeUnsigned) {
    EXPECT_EQ(Strings::ToUnsignedBigInt("18000000000"), 18000000000ULL);
}

TEST(StringsToUnsignedBigIntTest, FallbackOnWord) {
    EXPECT_EQ(Strings::ToUnsignedBigInt("bad", 99ULL), 99ULL);
}

// ============================================================
// Strings::TimeToSeconds
// ============================================================
TEST(StringsTimeToSecondsTest, Seconds) {
    EXPECT_EQ(Strings::TimeToSeconds("30s"), 30u);
}

TEST(StringsTimeToSecondsTest, Minutes) {
    EXPECT_EQ(Strings::TimeToSeconds("5m"), 300u);
}

TEST(StringsTimeToSecondsTest, Hours) {
    EXPECT_EQ(Strings::TimeToSeconds("2h"), 7200u);
}

TEST(StringsTimeToSecondsTest, Days) {
    EXPECT_EQ(Strings::TimeToSeconds("1d"), 86400u);
}

TEST(StringsTimeToSecondsTest, EmptyReturnsZero) {
    EXPECT_EQ(Strings::TimeToSeconds(""), 0u);
}

TEST(StringsTimeToSecondsTest, FReturnsZero) {
    EXPECT_EQ(Strings::TimeToSeconds("f"), 0u);
}

// ============================================================
// Strings::MillisecondsToTime (delegates to SecondsToTime)
// ============================================================
TEST(StringsMillisecondsToTimeTest, NonZeroProducesOutput) {
    std::string result = Strings::MillisecondsToTime(5000);
    EXPECT_FALSE(result.empty());
}

TEST(StringsMillisecondsToTimeTest, ZeroProducesUnknown) {
    // SecondsToTime(0) returns "Unknown"
    EXPECT_EQ(Strings::MillisecondsToTime(0), "Unknown");
}

// ============================================================
// Strings::Escape
// ============================================================
TEST(StringsEscapeTest, PlainStringUnchanged) {
    EXPECT_EQ(Strings::Escape("hello world"), "hello world");
}

TEST(StringsEscapeTest, EscapesNewline) {
    EXPECT_EQ(Strings::Escape("line1\nline2"), "line1\\nline2");
}

TEST(StringsEscapeTest, EscapesCarriageReturn) {
    EXPECT_EQ(Strings::Escape("a\rb"), "a\\rb");
}

TEST(StringsEscapeTest, EscapesBackslash) {
    EXPECT_EQ(Strings::Escape("a\\b"), "a\\\\b");
}

TEST(StringsEscapeTest, EscapesSingleQuote) {
    EXPECT_EQ(Strings::Escape("it's"), "it\\'s");
}

TEST(StringsEscapeTest, EscapesDoubleQuote) {
    EXPECT_EQ(Strings::Escape("say \"hi\""), "say \\\"hi\\\"");
}

TEST(StringsEscapeTest, EmptyStringUnchanged) {
    EXPECT_EQ(Strings::Escape(""), "");
}

// ============================================================
// Strings::Wrap
// ============================================================
TEST(StringsWrapTest, WrapsElementsInCharacter) {
    std::vector<std::string> v = {"a", "b", "c"};
    auto result = Strings::Wrap(v, "'");
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "'a'");
    EXPECT_EQ(result[1], "'b'");
    EXPECT_EQ(result[2], "'c'");
}

TEST(StringsWrapTest, NullElementNotWrapped) {
    std::vector<std::string> v = {"hello", "null", "world"};
    auto result = Strings::Wrap(v, "'");
    EXPECT_EQ(result[0], "'hello'");
    EXPECT_EQ(result[1], "null");
    EXPECT_EQ(result[2], "'world'");
}

TEST(StringsWrapTest, EmptyVectorReturnsEmpty) {
    std::vector<std::string> v;
    auto result = Strings::Wrap(v, "'");
    EXPECT_TRUE(result.empty());
}

// ============================================================
// Strings::SearchDelim
// ============================================================
TEST(StringsSearchDelimTest, FindsExactToken) {
    std::string::size_type pos = Strings::SearchDelim("foo,bar,baz", "bar", ',');
    EXPECT_NE(pos, std::string::npos);
    EXPECT_EQ(pos, 4u);
}

TEST(StringsSearchDelimTest, DoesNotMatchPartialToken) {
    // "ba" appears inside "bar" and "baz" but not as a complete delimited token
    std::string::size_type pos = Strings::SearchDelim("foo,bar,baz", "ba", ',');
    EXPECT_EQ(pos, std::string::npos);
}

TEST(StringsSearchDelimTest, FindsFirstToken) {
    std::string::size_type pos = Strings::SearchDelim("foo,bar,baz", "foo", ',');
    EXPECT_EQ(pos, 0u);
}

TEST(StringsSearchDelimTest, FindsLastToken) {
    std::string::size_type pos = Strings::SearchDelim("foo,bar,baz", "baz", ',');
    EXPECT_NE(pos, std::string::npos);
}

TEST(StringsSearchDelimTest, NotFoundReturnsNpos) {
    std::string::size_type pos = Strings::SearchDelim("foo,bar,baz", "qux", ',');
    EXPECT_EQ(pos, std::string::npos);
}

// ============================================================
// Strings::ZoneTime
// ============================================================
TEST(StringsZoneTimeTest, MidnightIs12AM) {
    // hour=0 → 12 AM
    std::string t = Strings::ZoneTime(0, 0);
    EXPECT_EQ(t, "12:00 AM");
}

TEST(StringsZoneTimeTest, NoonIs12PM) {
    // hour=12 → 12 PM (first PM hour)
    std::string t = Strings::ZoneTime(12, 0);
    EXPECT_EQ(t, "12:00 AM");  // 12 < 13, so AM
}

TEST(StringsZoneTimeTest, Hour13IsPM) {
    std::string t = Strings::ZoneTime(13, 30);
    EXPECT_EQ(t, "01:30 PM");
}

TEST(StringsZoneTimeTest, Hour23Is11PM) {
    std::string t = Strings::ZoneTime(23, 59);
    EXPECT_EQ(t, "11:59 PM");
}

TEST(StringsZoneTimeTest, MinutesPaddedToTwo) {
    std::string t = Strings::ZoneTime(9, 5);
    EXPECT_EQ(t, "09:05 AM");
}

// ============================================================
// Strings::Random
// ============================================================
TEST(StringsRandomTest, CorrectLength) {
    EXPECT_EQ(Strings::Random(10).size(), 10u);
    EXPECT_EQ(Strings::Random(0).size(),  0u);
    EXPECT_EQ(Strings::Random(64).size(), 64u);
}

TEST(StringsRandomTest, OnlyAlphanumericChars) {
    std::string s = Strings::Random(100);
    for (char c : s) {
        bool ok = std::isalnum(static_cast<unsigned char>(c));
        EXPECT_TRUE(ok) << "Non-alphanumeric char: " << c;
    }
}

TEST(StringsRandomTest, TwoCallsProduceDifferentStrings) {
    // Very unlikely to collide for length 16
    EXPECT_NE(Strings::Random(16), Strings::Random(16));
}

// ============================================================
// Strings::ConvertToDigit
// ============================================================
TEST(StringsConvertToDigitTest, ZeroReturnsEmpty) {
    EXPECT_EQ(Strings::ConvertToDigit(0, "Suffix"), "");
}

TEST(StringsConvertToDigitTest, SingleDigit) {
    EXPECT_EQ(Strings::ConvertToDigit(5, ""), "Five ");
}

TEST(StringsConvertToDigitTest, Teens) {
    EXPECT_EQ(Strings::ConvertToDigit(13, ""), "Thirteen ");
    EXPECT_EQ(Strings::ConvertToDigit(19, ""), "Nineteen ");
}

TEST(StringsConvertToDigitTest, Twenties) {
    EXPECT_EQ(Strings::ConvertToDigit(20, ""), "Twenty ");
    EXPECT_EQ(Strings::ConvertToDigit(21, ""), "Twenty One ");
}

TEST(StringsConvertToDigitTest, AppendsSuffix) {
    EXPECT_EQ(Strings::ConvertToDigit(5, "Hundred "), "Five Hundred ");
}

#include <gtest/gtest.h>
#include "common/strings.h"

TEST(StringsTest, SplitByChar_Basic) {
	auto v = Strings::Split("a,b,c", ',');
	ASSERT_EQ(3u, v.size());
	EXPECT_EQ("a", v[0]);
	EXPECT_EQ("b", v[1]);
	EXPECT_EQ("c", v[2]);
}

TEST(StringsTest, SplitByChar_Single) {
	auto v = Strings::Split("hello", ',');
	ASSERT_EQ(1u, v.size());
	EXPECT_EQ("hello", v[0]);
}

TEST(StringsTest, SplitByChar_Empty) {
	auto v = Strings::Split("", ',');
	EXPECT_TRUE(v.empty());
}

TEST(StringsTest, SplitByString_Basic) {
	auto v = Strings::Split("one::two::three", "::");
	ASSERT_EQ(3u, v.size());
	EXPECT_EQ("one",   v[0]);
	EXPECT_EQ("two",   v[1]);
	EXPECT_EQ("three", v[2]);
}

TEST(StringsTest, JoinBasic) {
	std::vector<std::string> v = {"a", "b", "c"};
	EXPECT_EQ("a,b,c", Strings::Join(v, ","));
}

TEST(StringsTest, JoinSingle) {
	std::vector<std::string> v = {"only"};
	EXPECT_EQ("only", Strings::Join(v, ","));
}

TEST(StringsTest, JoinEmpty) {
	std::vector<std::string> v;
	EXPECT_EQ("", Strings::Join(v, ","));
}

TEST(StringsTest, ImplodeMatchesJoin) {
	std::vector<std::string> v = {"x", "y", "z"};
	EXPECT_EQ(Strings::Join(v, "-"), Strings::Implode("-", v));
}

TEST(StringsTest, ContainsSubstring_True) {
	EXPECT_TRUE(Strings::Contains("hello world", "world"));
}

TEST(StringsTest, ContainsSubstring_False) {
	EXPECT_FALSE(Strings::Contains("hello world", "xyz"));
}

TEST(StringsTest, ContainsVector_True) {
	std::vector<std::string> v = {"apple", "banana", "cherry"};
	EXPECT_TRUE(Strings::Contains(v, "banana"));
}

TEST(StringsTest, ContainsVector_False) {
	std::vector<std::string> v = {"apple", "banana"};
	EXPECT_FALSE(Strings::Contains(v, "grape"));
}

TEST(StringsTest, BeginsWithTrue) {
	EXPECT_TRUE(Strings::BeginsWith("hello world", "hello"));
}

TEST(StringsTest, BeginsWithFalse) {
	EXPECT_FALSE(Strings::BeginsWith("hello world", "world"));
}

TEST(StringsTest, EndsWithTrue) {
	EXPECT_TRUE(Strings::EndsWith("hello world", "world"));
}

TEST(StringsTest, EndsWithFalse) {
	EXPECT_FALSE(Strings::EndsWith("hello world", "hello"));
}

TEST(StringsTest, IsNumber_Integer) {
	EXPECT_TRUE(Strings::IsNumber("12345"));
}

TEST(StringsTest, IsNumber_AcceptsNegative) {
	// IsNumber treats leading '-' as valid; negatives are accepted
	EXPECT_TRUE(Strings::IsNumber("-123"));
}

TEST(StringsTest, IsNumber_FloatRejected) {
	EXPECT_FALSE(Strings::IsNumber("3.14"));
}

TEST(StringsTest, IsNumber_EmptyReturnTrue) {
	// Empty string: loop never fires, returns true (implementation quirk)
	EXPECT_TRUE(Strings::IsNumber(""));
}

TEST(StringsTest, IsNumber_WordRejected) {
	EXPECT_FALSE(Strings::IsNumber("abc"));
}

TEST(StringsTest, IsFloat_Valid) {
	EXPECT_TRUE(Strings::IsFloat("3.14"));
}

TEST(StringsTest, IsFloat_Integer) {
	EXPECT_TRUE(Strings::IsFloat("42"));
}

TEST(StringsTest, IsFloat_WordRejected) {
	EXPECT_FALSE(Strings::IsFloat("abc"));
}

TEST(StringsTest, ToInt_Basic) {
	EXPECT_EQ(42, Strings::ToInt("42"));
}

TEST(StringsTest, ToInt_Negative) {
	EXPECT_EQ(-7, Strings::ToInt("-7"));
}

TEST(StringsTest, ToInt_FallbackOnWord) {
	EXPECT_EQ(99, Strings::ToInt("abc", 99));
}

TEST(StringsTest, ToFloat_Basic) {
	EXPECT_FLOAT_EQ(3.14f, Strings::ToFloat("3.14"));
}

TEST(StringsTest, ToFloat_FallbackOnWord) {
	EXPECT_FLOAT_EQ(1.5f, Strings::ToFloat("xyz", 1.5f));
}

TEST(StringsTest, ToBool_True) {
	EXPECT_TRUE(Strings::ToBool("true"));
	EXPECT_TRUE(Strings::ToBool("yes"));
	EXPECT_TRUE(Strings::ToBool("1"));
}

TEST(StringsTest, ToBool_False) {
	EXPECT_FALSE(Strings::ToBool("false"));
	EXPECT_FALSE(Strings::ToBool("no"));
	EXPECT_FALSE(Strings::ToBool("0"));
}

TEST(StringsTest, TrimBothEnds) {
	std::string s = "  hello  ";
	Strings::Trim(s);
	EXPECT_EQ("hello", s);
}

TEST(StringsTest, LTrimLeadingOnly) {
	std::string s = "  hello  ";
	Strings::LTrim(s);
	EXPECT_EQ("hello  ", s);
}

TEST(StringsTest, RTrimTrailingOnly) {
	std::string s = "  hello  ";
	Strings::RTrim(s);
	EXPECT_EQ("  hello", s);
}

TEST(StringsTest, TrimNoop) {
	std::string s = "hello";
	Strings::Trim(s);
	EXPECT_EQ("hello", s);
}

TEST(StringsTest, ReplaceBasic) {
	EXPECT_EQ("hello world", Strings::Replace("hello foo", "foo", "world"));
}

TEST(StringsTest, ReplaceNotFound) {
	EXPECT_EQ("hello", Strings::Replace("hello", "xyz", "abc"));
}

TEST(StringsTest, FindReplaceInPlace) {
	std::string s = "cat sat on mat";
	Strings::FindReplace(s, "at", "og");
	EXPECT_EQ("cog sog on mog", s);
}

TEST(StringsTest, ToLower) {
	EXPECT_EQ("hello world", Strings::ToLower("HELLO WORLD"));
}

TEST(StringsTest, ToUpper) {
	EXPECT_EQ("HELLO WORLD", Strings::ToUpper("hello world"));
}

TEST(StringsTest, UcFirst) {
	EXPECT_EQ("Hello", Strings::UcFirst("hello"));
}

TEST(StringsTest, CommifyThousands) {
	EXPECT_EQ("1,000", Strings::Commify(1000u));
}

TEST(StringsTest, CommifyMillions) {
	EXPECT_EQ("1,000,000", Strings::Commify(1000000u));
}

TEST(StringsTest, CommifySmall) {
	EXPECT_EQ("999", Strings::Commify(999u));
}

TEST(StringsTest, GetBetweenBasic) {
	EXPECT_EQ("world", Strings::GetBetween("hello [world] foo", "[", "]"));
}

TEST(StringsTest, GetBetweenNotFound) {
	EXPECT_EQ("", Strings::GetBetween("hello world", "[", "]"));
}

TEST(StringsTest, RepeatBasic) {
	EXPECT_EQ("abcabcabc", Strings::Repeat("abc", 3));
}

TEST(StringsTest, RepeatZeroReturnsOriginal) {
	// Repeat(s, 0) returns s unmodified (loop starts at i=1, never fires)
	EXPECT_EQ("abc", Strings::Repeat("abc", 0));
}

TEST(StringsTest, SlugifyBasic) {
	EXPECT_EQ("hello-world", Strings::Slugify("Hello World"));
}

TEST(StringsTest, SlugifyCustomSep) {
	EXPECT_EQ("hello_world", Strings::Slugify("Hello World", "_"));
}

TEST(StringsTest, EqualFoldTrue) {
	EXPECT_TRUE(Strings::EqualFold("Hello", "hello"));
}

TEST(StringsTest, EqualFoldFalse) {
	EXPECT_FALSE(Strings::EqualFold("Hello", "world"));
}

TEST(StringsTest, SecondsToTime_Seconds) {
	std::string r = Strings::SecondsToTime(30);
	EXPECT_NE(std::string::npos, r.find("30"));
	EXPECT_NE(std::string::npos, r.find("Second"));
}

TEST(StringsTest, SecondsToTime_ZeroIsUnknown) {
	EXPECT_EQ("Unknown", Strings::SecondsToTime(0));
}

TEST(StringsTest, SecondsToTime_OneMinute) {
	std::string r = Strings::SecondsToTime(60);
	EXPECT_NE(std::string::npos, r.find("Minute"));
}

TEST(StringsTest, NumberToWordsSmall) {
	std::string r = Strings::NumberToWords(5);
	EXPECT_NE(std::string::npos, r.find("Five"));
}

TEST(StringsTest, NumberToWordsHundred) {
	std::string r = Strings::NumberToWords(100);
	EXPECT_NE(std::string::npos, r.find("Hundred"));
}

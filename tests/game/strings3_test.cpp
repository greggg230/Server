#include <gtest/gtest.h>
#include "common/strings.h"

// ============================================================
// Strings::Money — denomination formatting
// ============================================================
TEST(StringsMoneyTest, OnlyPlatinum) {
    EXPECT_EQ(Strings::Money(5), "5 platinum");
}

TEST(StringsMoneyTest, OnlyGold) {
    EXPECT_EQ(Strings::Money(0, 3), "3 gold");
}

TEST(StringsMoneyTest, OnlySilver) {
    EXPECT_EQ(Strings::Money(0, 0, 7), "7 silver");
}

TEST(StringsMoneyTest, OnlyCopper) {
    EXPECT_EQ(Strings::Money(0, 0, 0, 9), "9 copper");
}

TEST(StringsMoneyTest, PlatinumAndGold) {
    std::string result = Strings::Money(1, 2, 0, 0);
    EXPECT_NE(result.find("1 platinum"), std::string::npos);
    EXPECT_NE(result.find("2 gold"),     std::string::npos);
}

TEST(StringsMoneyTest, PlatinumAndSilver) {
    std::string result = Strings::Money(1, 0, 3, 0);
    EXPECT_NE(result.find("1 platinum"), std::string::npos);
    EXPECT_NE(result.find("3 silver"),   std::string::npos);
}

TEST(StringsMoneyTest, PlatinumAndCopper) {
    std::string result = Strings::Money(2, 0, 0, 5);
    EXPECT_NE(result.find("2 platinum"), std::string::npos);
    EXPECT_NE(result.find("5 copper"),   std::string::npos);
}

TEST(StringsMoneyTest, AllFourDenominations) {
    std::string result = Strings::Money(1, 2, 3, 4);
    EXPECT_NE(result.find("1 platinum"), std::string::npos);
    EXPECT_NE(result.find("2 gold"),     std::string::npos);
    EXPECT_NE(result.find("3 silver"),   std::string::npos);
    EXPECT_NE(result.find("4 copper"),   std::string::npos);
}

TEST(StringsMoneyTest, AllZeroReturnsUnknown) {
    EXPECT_EQ(Strings::Money(0, 0, 0, 0), "Unknown");
}

TEST(StringsMoneyTest, LargeValueCommified) {
    std::string result = Strings::Money(1000000);
    EXPECT_NE(result.find("1,000,000"), std::string::npos);
}

TEST(StringsMoneyTest, GoldAndSilver) {
    std::string result = Strings::Money(0, 5, 3, 0);
    EXPECT_NE(result.find("5 gold"),   std::string::npos);
    EXPECT_NE(result.find("3 silver"), std::string::npos);
}

TEST(StringsMoneyTest, GoldAndCopper) {
    std::string result = Strings::Money(0, 4, 0, 6);
    EXPECT_NE(result.find("4 gold"),   std::string::npos);
    EXPECT_NE(result.find("6 copper"), std::string::npos);
}

TEST(StringsMoneyTest, SilverAndCopper) {
    std::string result = Strings::Money(0, 0, 2, 8);
    EXPECT_NE(result.find("2 silver"), std::string::npos);
    EXPECT_NE(result.find("8 copper"), std::string::npos);
}

// ============================================================
// Strings::IsValidJson
// ============================================================
TEST(StringsIsValidJsonTest, EmptyStringIsInvalid) {
    EXPECT_FALSE(Strings::IsValidJson(""));
}

TEST(StringsIsValidJsonTest, ValidEmptyObjectIsValid) {
    EXPECT_TRUE(Strings::IsValidJson("{}"));
}

TEST(StringsIsValidJsonTest, ValidEmptyArrayIsValid) {
    EXPECT_TRUE(Strings::IsValidJson("[]"));
}

TEST(StringsIsValidJsonTest, ValidStringValueIsValid) {
    EXPECT_TRUE(Strings::IsValidJson("{\"key\": \"value\"}"));
}

TEST(StringsIsValidJsonTest, ValidIntValueIsValid) {
    EXPECT_TRUE(Strings::IsValidJson("{\"count\": 42}"));
}

TEST(StringsIsValidJsonTest, ValidBoolValueIsValid) {
    EXPECT_TRUE(Strings::IsValidJson("{\"flag\": true}"));
}

TEST(StringsIsValidJsonTest, ValidNullValueIsValid) {
    EXPECT_TRUE(Strings::IsValidJson("{\"key\": null}"));
}

TEST(StringsIsValidJsonTest, ValidArrayOfIntsIsValid) {
    EXPECT_TRUE(Strings::IsValidJson("[1, 2, 3]"));
}

TEST(StringsIsValidJsonTest, MissingClosingBraceIsInvalid) {
    EXPECT_FALSE(Strings::IsValidJson("{\"key\": 1"));
}

TEST(StringsIsValidJsonTest, UnquotedKeyIsInvalid) {
    EXPECT_FALSE(Strings::IsValidJson("{key: 1}"));
}

TEST(StringsIsValidJsonTest, TrailingCommaIsInvalid) {
    EXPECT_FALSE(Strings::IsValidJson("{\"a\": 1,}"));
}

TEST(StringsIsValidJsonTest, NestedObjectIsValid) {
    EXPECT_TRUE(Strings::IsValidJson("{\"a\": {\"b\": 2}}"));
}

TEST(StringsIsValidJsonTest, PlainStringIsInvalid) {
    EXPECT_FALSE(Strings::IsValidJson("hello world"));
}

TEST(StringsIsValidJsonTest, PlainNumberIsValid) {
    // Bare numbers are valid JSON values
    EXPECT_TRUE(Strings::IsValidJson("42"));
}

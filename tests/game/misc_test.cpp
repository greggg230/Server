#include <gtest/gtest.h>
#include "common/misc.h"

#include <map>
#include <string>

// ---- Protect ----

TEST(MiscProtectTest, EscapesTargetChar) {
    std::string s = "hello|world";
    Protect(s, '|');
    // Protect inserts backslash before each pipe: hello\|world
    EXPECT_EQ(s.size(), 12u);
    EXPECT_EQ(s[5], char(92));  // backslash
    EXPECT_EQ(s[6], '|');
}

TEST(MiscProtectTest, EscapesMultipleOccurrences) {
    std::string s = "a|b|c";
    Protect(s, '|');
    EXPECT_EQ(s.size(), 7u);  // 5 chars + 2 backslashes inserted
    EXPECT_EQ(s[1], char(92));
    EXPECT_EQ(s[2], '|');
    EXPECT_EQ(s[4], char(92));
    EXPECT_EQ(s[5], '|');
}

TEST(MiscProtectTest, NoOccurrencesUnchanged) {
    std::string s = "hello world";
    Protect(s, '|');
    EXPECT_EQ(s, "hello world");
}

TEST(MiscProtectTest, EmptyStringUnchanged) {
    std::string s = "";
    Protect(s, '|');
    EXPECT_EQ(s, "");
}

TEST(MiscProtectTest, RoundTripPipeChar) {
    std::string original = "field1|field2|field3";
    std::string s = original;
    Protect(s, '|');
    Unprotect(s, '|');
    EXPECT_EQ(s, original);
}

TEST(MiscProtectTest, RoundTripArbitraryChar) {
    std::string original = "axbxcxd";
    std::string s = original;
    Protect(s, 'x');
    Unprotect(s, 'x');
    EXPECT_EQ(s, original);
}

// ---- Unprotect ----

TEST(MiscUnprotectTest, RemovesEscapeBeforeTarget) {
    // Build "hello\|world" without escape sequences
    std::string s;
    s += "hello"; s += char(92); s += "|world";
    Unprotect(s, '|');
    EXPECT_EQ(s, "hello|world");
}

TEST(MiscUnprotectTest, RemovesMultipleEscapes) {
    std::string s;
    s += "a"; s += char(92); s += "|";
    s += "b"; s += char(92); s += "|c";
    Unprotect(s, '|');
    EXPECT_EQ(s, "a|b|c");
}

TEST(MiscUnprotectTest, NoEscapesUnchanged) {
    std::string s = "hello world";
    Unprotect(s, '|');
    EXPECT_EQ(s, "hello world");
}

TEST(MiscUnprotectTest, EmptyStringUnchanged) {
    std::string s = "";
    Unprotect(s, '|');
    EXPECT_EQ(s, "");
}

TEST(MiscUnprotectTest, DoesNotRemoveEscapeForOtherChar) {
    std::string s;
    s += "hello"; s += char(92); s += "|world";
    std::string original = s;
    Unprotect(s, '"');  // target is double-quote, not pipe
    EXPECT_EQ(s, original);
}

// ---- Tokenize ----

TEST(MiscTokenizeTest, BasicPipeSeparated) {
    std::map<int, std::string> tokens;
    int count = Tokenize("a|b|c", tokens, '|');
    EXPECT_EQ(count, 3);
    EXPECT_EQ(tokens[0], "a");
    EXPECT_EQ(tokens[1], "b");
    EXPECT_EQ(tokens[2], "c");
}

TEST(MiscTokenizeTest, SingleToken) {
    std::map<int, std::string> tokens;
    int count = Tokenize("hello", tokens, '|');
    EXPECT_EQ(count, 1);
    EXPECT_EQ(tokens[0], "hello");
}

TEST(MiscTokenizeTest, EmptyFieldAtStart) {
    std::map<int, std::string> tokens;
    int count = Tokenize("|b|c", tokens, '|');
    EXPECT_EQ(count, 3);
    EXPECT_EQ(tokens[0], "");
    EXPECT_EQ(tokens[1], "b");
    EXPECT_EQ(tokens[2], "c");
}

TEST(MiscTokenizeTest, ClearsExistingTokens) {
    std::map<int, std::string> tokens;
    tokens[99] = "stale";
    Tokenize("x|y", tokens, '|');
    EXPECT_EQ(tokens.find(99), tokens.end());
}

TEST(MiscTokenizeTest, CustomDelimiter) {
    std::map<int, std::string> tokens;
    int count = Tokenize("a,b,c", tokens, ',');
    EXPECT_EQ(count, 3);
    EXPECT_EQ(tokens[0], "a");
    EXPECT_EQ(tokens[1], "b");
    EXPECT_EQ(tokens[2], "c");
}

// ---- pop_arg ----

TEST(MiscPopArgTest, PopsFirstSpaceSeparatedWord) {
    std::string s = "hello world foo";
    std::string arg = pop_arg(s, " ", false);
    EXPECT_EQ(arg, "hello");
    EXPECT_EQ(s, "world foo");
}

TEST(MiscPopArgTest, SingleWordEmptiesString) {
    std::string s = "hello";
    std::string arg = pop_arg(s, " ", false);
    EXPECT_EQ(arg, "hello");
    EXPECT_EQ(s, "");
}

TEST(MiscPopArgTest, EmptyStringReturnsEmpty) {
    std::string s = "";
    std::string arg = pop_arg(s, " ", false);
    EXPECT_EQ(arg, "");
    EXPECT_EQ(s, "");
}

TEST(MiscPopArgTest, MultipleSeparatorChars) {
    std::string s = "hello,world";
    std::string arg = pop_arg(s, ",", false);
    EXPECT_EQ(arg, "hello");
    EXPECT_EQ(s, "world");
}

TEST(MiscPopArgTest, QuoteObeyedSpansSpace) {
    // with obey_quotes=true, space inside quotes does not split
    std::string s = "\"hello world\" foo";
    std::string arg = pop_arg(s, " ", true);
    EXPECT_EQ(arg, "\"hello world\"");
    EXPECT_EQ(s, "foo");
}

TEST(MiscPopArgTest, QuoteIgnoredSplitsInsideQuotes) {
    // without obey_quotes, splits at first space regardless of quotes
    std::string s = "\"hello world\" foo";
    std::string arg = pop_arg(s, " ", false);
    EXPECT_EQ(arg, "\"hello");
    EXPECT_EQ(s, "world\" foo");
}

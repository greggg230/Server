#include <gtest/gtest.h>
#include "common/strings.h"

// ============================================================
// StringFormat / vStringFormat
// ============================================================
TEST(StringFormatTest, BasicString) {
    EXPECT_EQ(StringFormat("hello"), "hello");
}

TEST(StringFormatTest, IntegerSubstitution) {
    EXPECT_EQ(StringFormat("%d", 42), "42");
}

TEST(StringFormatTest, FloatSubstitution) {
    EXPECT_EQ(StringFormat("%.2f", 3.14f), "3.14");
}

TEST(StringFormatTest, MultipleArguments) {
    EXPECT_EQ(StringFormat("%s=%d", "answer", 42), "answer=42");
}

TEST(StringFormatTest, EmptyFormat) {
    EXPECT_EQ(StringFormat(""), "");
}

TEST(StringFormatTest, LargeOutput) {
    // Ensure dynamic resize works for output > initial buffer
    std::string s = StringFormat("%s%s%s%s%s",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
        "ccccccccccccccccccccccccccccccc",
        "ddddddddddddddddddddddddddddddd",
        "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeee");
    EXPECT_EQ(s.size(), 155u);
}

TEST(StringFormatTest, HexFormat) {
    EXPECT_EQ(StringFormat("0x%08X", 0xDEADBEEFu), "0xDEADBEEF");
}

TEST(StringFormatTest, NegativeInteger) {
    EXPECT_EQ(StringFormat("%d", -99), "-99");
}

// ============================================================
// IsAllowedWorldServerCharacterList
// ============================================================
TEST(IsAllowedWorldServerCharTest, SpecialCharsAllowed) {
    // All chars in ":[](){}.!@#$%^&*-=+<>/\\|'\""
    const char allowed[] = ":[](){}.!@#$%^&*-=+<>/\\|'\"";
    for (char c : std::string(allowed)) {
        EXPECT_TRUE(IsAllowedWorldServerCharacterList(c)) << "Char '" << c << "' should be allowed";
    }
}

TEST(IsAllowedWorldServerCharTest, AlphanumericNotAllowed) {
    // Alphanumeric chars are NOT in the special list
    EXPECT_FALSE(IsAllowedWorldServerCharacterList('a'));
    EXPECT_FALSE(IsAllowedWorldServerCharacterList('Z'));
    EXPECT_FALSE(IsAllowedWorldServerCharacterList('0'));
    EXPECT_FALSE(IsAllowedWorldServerCharacterList('9'));
}

TEST(IsAllowedWorldServerCharTest, SpaceNotAllowed) {
    EXPECT_FALSE(IsAllowedWorldServerCharacterList(' '));
}

TEST(IsAllowedWorldServerCharTest, ColonAllowed) {
    EXPECT_TRUE(IsAllowedWorldServerCharacterList(':'));
}

TEST(IsAllowedWorldServerCharTest, ExclamationAllowed) {
    EXPECT_TRUE(IsAllowedWorldServerCharacterList('!'));
}

// ============================================================
// SanitizeWorldServerName
// ============================================================
TEST(SanitizeWorldServerNameTest, PlainNameUnchanged) {
    std::string input = "My Server 123";
    EXPECT_EQ(SanitizeWorldServerName(input), "My Server 123");
}

TEST(SanitizeWorldServerNameTest, TrimsLeadingAndTrailingSpaces) {
    std::string input = "  Hello World  ";
    EXPECT_EQ(SanitizeWorldServerName(input), "Hello World");
}

TEST(SanitizeWorldServerNameTest, StripsControlCharacters) {
    std::string input = "Server\x01Name";
    std::string result = SanitizeWorldServerName(input);
    EXPECT_EQ(result.find('\x01'), std::string::npos);
}

TEST(SanitizeWorldServerNameTest, AllowsSpecialChars) {
    std::string input = "Server: The [Best]";
    std::string result = SanitizeWorldServerName(input);
    EXPECT_NE(result.find(':'), std::string::npos);
    EXPECT_NE(result.find('['), std::string::npos);
    EXPECT_NE(result.find(']'), std::string::npos);
}

TEST(SanitizeWorldServerNameTest, EmptyStringReturnsEmpty) {
    std::string input;
    EXPECT_EQ(SanitizeWorldServerName(input), "");
}

TEST(SanitizeWorldServerNameTest, WhitespaceOnlyReturnsEmpty) {
    std::string input = "   ";
    EXPECT_EQ(SanitizeWorldServerName(input), "");
}

// ============================================================
// ParseAccountString
// ============================================================
TEST(ParseAccountStringTest, ColonSplitsLoginserverAndAccount) {
    std::string account, loginserver;
    ParseAccountString("eqemu:mycharacter", account, loginserver);
    EXPECT_EQ(loginserver, "eqemu");
    EXPECT_EQ(account, "mycharacter");
}

TEST(ParseAccountStringTest, NoColonSetsAccountOnly) {
    std::string account, loginserver;
    loginserver = "unchanged";
    ParseAccountString("justaccount", account, loginserver);
    EXPECT_EQ(account, "justaccount");
    EXPECT_EQ(loginserver, "unchanged");  // not set when no colon
}

TEST(ParseAccountStringTest, EmptyStringLeavesOutputUnchanged) {
    std::string account = "orig_account", loginserver = "orig_server";
    ParseAccountString("", account, loginserver);
    // empty split produces no segments — neither field is set
    EXPECT_EQ(account, "orig_account");
    EXPECT_EQ(loginserver, "orig_server");
}

TEST(ParseAccountStringTest, LoginserverWithSpecialChars) {
    std::string account, loginserver;
    ParseAccountString("login.server.com:player1", account, loginserver);
    EXPECT_EQ(loginserver, "login.server.com");
    EXPECT_EQ(account, "player1");
}

TEST(ParseAccountStringTest, AccountCanContainNumbers) {
    std::string account, loginserver;
    ParseAccountString("eq:player123", account, loginserver);
    EXPECT_EQ(loginserver, "eq");
    EXPECT_EQ(account, "player123");
}

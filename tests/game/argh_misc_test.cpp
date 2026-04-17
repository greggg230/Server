#include <gtest/gtest.h>
#include "common/cli/argh.h"
#include "common/misc.h"

#include <map>
#include <string>

// ============================================================
// argh::parser — flag detection
// ============================================================
TEST(ArghParserTest, NoArgsEmptyState) {
    const char* argv[] = {"prog", nullptr};
    argh::parser p(argv);
    EXPECT_EQ(p.size(), 1u); // prog itself is pos arg
    EXPECT_TRUE(p.flags().empty());
    EXPECT_TRUE(p.params().empty());
}

TEST(ArghParserTest, LongFlagDetected) {
    const char* argv[] = {"prog", "--verbose", nullptr};
    argh::parser p(argv);
    EXPECT_TRUE(p["verbose"]);
    EXPECT_FALSE(p["quiet"]);
}

TEST(ArghParserTest, ShortFlagDetected) {
    const char* argv[] = {"prog", "-v", nullptr};
    argh::parser p(argv);
    EXPECT_TRUE(p["v"]);
}

TEST(ArghParserTest, MultipleFlagsAllDetected) {
    const char* argv[] = {"prog", "--foo", "--bar", "--baz", nullptr};
    argh::parser p(argv);
    EXPECT_TRUE(p["foo"]);
    EXPECT_TRUE(p["bar"]);
    EXPECT_TRUE(p["baz"]);
}

TEST(ArghParserTest, AbsentFlagReturnsFalse) {
    const char* argv[] = {"prog", "--present", nullptr};
    argh::parser p(argv);
    EXPECT_FALSE(p["absent"]);
}

// ============================================================
// argh::parser — named parameter (--key=value)
// ============================================================
TEST(ArghParserTest, NamedParameterParsed) {
    const char* argv[] = {"prog", "--output=file.txt", nullptr};
    argh::parser p(argv);
    std::string val;
    p("output") >> val;
    EXPECT_EQ(val, "file.txt");
}

TEST(ArghParserTest, MultipleNamedParams) {
    const char* argv[] = {"prog", "--host=localhost", "--port=3306", nullptr};
    argh::parser p(argv);
    std::string host;
    int port = 0;
    p("host") >> host;
    p("port") >> port;
    EXPECT_EQ(host, "localhost");
    EXPECT_EQ(port, 3306);
}

TEST(ArghParserTest, MissingParamStreamIsFalsy) {
    const char* argv[] = {"prog", nullptr};
    argh::parser p(argv);
    auto s = p("missing");
    // stream should be in fail state — extracting fails
    int val = -1;
    EXPECT_FALSE(s >> val);
}

// ============================================================
// argh::parser — positional arguments
// ============================================================
TEST(ArghParserTest, PositionalArgParsed) {
    // argv[0] = prog, argv[1] = posarg => pos_args_[0]="prog", [1]="posarg"
    const char* argv[] = {"prog", "inputfile.txt", nullptr};
    argh::parser p(argv);
    EXPECT_EQ(p.size(), 2u);
    EXPECT_EQ(p[1], "inputfile.txt");
}

TEST(ArghParserTest, MultiplePositionalArgs) {
    const char* argv[] = {"prog", "a", "b", "c", nullptr};
    argh::parser p(argv);
    EXPECT_EQ(p.size(), 4u);
    EXPECT_EQ(p[1], "a");
    EXPECT_EQ(p[2], "b");
    EXPECT_EQ(p[3], "c");
}

TEST(ArghParserTest, FlagsDoNotAppearInPosArgs) {
    const char* argv[] = {"prog", "--flag", "value", nullptr};
    argh::parser p(argv);
    // "value" is positional, "--flag" is a flag
    EXPECT_TRUE(p["flag"]);
    EXPECT_EQ(p.size(), 2u); // prog + value
}

// ============================================================
// Protect / Unprotect (misc.h)
// ============================================================
TEST(ProtectTest, NothingToProtect) {
    std::string s = "abc";
    Protect(s, '|');
    EXPECT_EQ(s, "abc");
}

TEST(ProtectTest, SingleCharProtected) {
    std::string s = "a|b";
    Protect(s, '|');
    EXPECT_EQ(s, "a\\|b");
}

TEST(ProtectTest, MultipleCharsProtected) {
    std::string s = "a|b|c";
    Protect(s, '|');
    EXPECT_EQ(s, "a\\|b\\|c");
}

TEST(ProtectTest, EmptyStringUnchanged) {
    std::string s;
    Protect(s, '|');
    EXPECT_TRUE(s.empty());
}

TEST(UnprotectTest, NothingToUnprotect) {
    std::string s = "abc";
    Unprotect(s, '|');
    EXPECT_EQ(s, "abc");
}

TEST(UnprotectTest, BackslashBeforeCharRemoved) {
    std::string s = "a\\|b";
    Unprotect(s, '|');
    EXPECT_EQ(s, "a|b");
}

TEST(UnprotectTest, MultipleUnprotected) {
    std::string s = "a\\|b\\|c";
    Unprotect(s, '|');
    EXPECT_EQ(s, "a|b|c");
}

TEST(UnprotectTest, EmptyStringUnchanged) {
    std::string s;
    Unprotect(s, '|');
    EXPECT_TRUE(s.empty());
}

TEST(ProtectUnprotectTest, RoundTrip) {
    std::string original = "hello|world|foo";
    std::string s = original;
    Protect(s, '|');
    Unprotect(s, '|');
    EXPECT_EQ(s, original);
}

// ============================================================
// Tokenize (misc.h)
// ============================================================
TEST(TokenizeTest, SingleToken) {
    std::map<int, std::string> tokens;
    int n = Tokenize("hello", tokens, '|');
    EXPECT_EQ(n, 1);
    EXPECT_EQ(tokens[0], "hello");
}

TEST(TokenizeTest, TwoTokens) {
    std::map<int, std::string> tokens;
    int n = Tokenize("a|b", tokens, '|');
    EXPECT_EQ(n, 2);
    EXPECT_EQ(tokens[0], "a");
    EXPECT_EQ(tokens[1], "b");
}

TEST(TokenizeTest, ThreeTokens) {
    std::map<int, std::string> tokens;
    int n = Tokenize("x|y|z", tokens, '|');
    EXPECT_EQ(n, 3);
    EXPECT_EQ(tokens[0], "x");
    EXPECT_EQ(tokens[1], "y");
    EXPECT_EQ(tokens[2], "z");
}

TEST(TokenizeTest, EmptySegmentFromLeadingDelim) {
    std::map<int, std::string> tokens;
    int n = Tokenize("|a", tokens, '|');
    EXPECT_GE(n, 1);
    EXPECT_EQ(tokens[0], "");
}

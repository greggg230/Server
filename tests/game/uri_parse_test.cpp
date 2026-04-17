#include <gtest/gtest.h>
#include "common/http/uri.h"

#include <stdexcept>
#include <string>

// ============================================================
// uri — scheme parsing
// ============================================================
TEST(UriSchemeTest, HttpSchemeIsParsed) {
    uri u("http://example.com/path");
    EXPECT_EQ(u.get_scheme(), "http");
}

TEST(UriSchemeTest, HttpsSchemeIsParsed) {
    uri u("https://example.com/");
    EXPECT_EQ(u.get_scheme(), "https");
}

TEST(UriSchemeTest, FtpSchemeIsParsed) {
    uri u("ftp://ftp.example.com/file.txt");
    EXPECT_EQ(u.get_scheme(), "ftp");
}

TEST(UriSchemeTest, HierarchicalCategoryIsDefault) {
    uri u("http://example.com/");
    EXPECT_EQ(u.get_scheme_category(), uri::scheme_category::Hierarchical);
}

// ============================================================
// uri — host parsing
// ============================================================
TEST(UriHostTest, SimpleHostIsParsed) {
    uri u("http://example.com/path");
    EXPECT_EQ(u.get_host(), "example.com");
}

TEST(UriHostTest, LocalhostIsParsed) {
    uri u("http://localhost/");
    EXPECT_EQ(u.get_host(), "localhost");
}

TEST(UriHostTest, IPAddressIsParsed) {
    uri u("http://192.168.0.1/");
    EXPECT_EQ(u.get_host(), "192.168.0.1");
}

// ============================================================
// uri — port parsing
// ============================================================
TEST(UriPortTest, ExplicitPortIsParsed) {
    uri u("http://example.com:8080/path");
    EXPECT_EQ(u.get_port(), 8080u);
}

TEST(UriPortTest, NoPortIsZero) {
    uri u("http://example.com/path");
    EXPECT_EQ(u.get_port(), 0u);
}

TEST(UriPortTest, Port443IsParsed) {
    uri u("https://example.com:443/");
    EXPECT_EQ(u.get_port(), 443u);
}

// ============================================================
// uri — path parsing
// ============================================================
TEST(UriPathTest, SimplePathIsParsed) {
    uri u("http://example.com/path/to/resource");
    EXPECT_EQ(u.get_path(), "path/to/resource");
}

TEST(UriPathTest, RootPathIsParsed) {
    uri u("http://example.com/");
    EXPECT_TRUE(u.get_path().empty());
}

TEST(UriPathTest, EmptyPathIsEmpty) {
    uri u("http://example.com");
    EXPECT_TRUE(u.get_path().empty());
}

// ============================================================
// uri — query string parsing
// ============================================================
TEST(UriQueryTest, QueryStringIsParsed) {
    uri u("http://example.com/path?foo=bar");
    EXPECT_EQ(u.get_query(), "foo=bar");
}

TEST(UriQueryTest, NoQueryIsEmpty) {
    uri u("http://example.com/path");
    EXPECT_TRUE(u.get_query().empty());
}

TEST(UriQueryTest, QueryDictionaryHasKey) {
    uri u("http://example.com/?key=value");
    auto dict = u.get_query_dictionary();
    ASSERT_NE(dict.find("key"), dict.end());
    EXPECT_EQ(dict.at("key"), "value");
}

TEST(UriQueryTest, MultipleQueryParamsAreParsed) {
    uri u("http://example.com/?a=1&b=2");
    auto dict = u.get_query_dictionary();
    EXPECT_EQ(dict.at("a"), "1");
    EXPECT_EQ(dict.at("b"), "2");
}

// ============================================================
// uri — fragment parsing
// ============================================================
TEST(UriFragmentTest, FragmentIsParsed) {
    uri u("http://example.com/page#section");
    EXPECT_EQ(u.get_fragment(), "section");
}

TEST(UriFragmentTest, NoFragmentIsEmpty) {
    uri u("http://example.com/page");
    EXPECT_TRUE(u.get_fragment().empty());
}

// ============================================================
// uri — username/password
// ============================================================
TEST(UriAuthTest, UsernameIsParsed) {
    uri u("http://user:pass@example.com/");
    EXPECT_EQ(u.get_username(), "user");
}

TEST(UriAuthTest, PasswordIsParsed) {
    uri u("http://user:pass@example.com/");
    EXPECT_EQ(u.get_password(), "pass");
}

TEST(UriAuthTest, NoUsernameIsEmpty) {
    uri u("http://example.com/");
    EXPECT_TRUE(u.get_username().empty());
}

// ============================================================
// uri — non-hierarchical category
// ============================================================
TEST(UriNonHierTest, NonHierGetContentAccessible) {
    uri u("mailto:user@example.com", uri::scheme_category::NonHierarchical);
    EXPECT_FALSE(u.get_content().empty());
}

TEST(UriNonHierTest, HierGetContentThrows) {
    uri u("http://example.com/");
    EXPECT_THROW(u.get_content(), std::domain_error);
}

TEST(UriNonHierTest, NonHierGetHostThrows) {
    uri u("mailto:user@example.com", uri::scheme_category::NonHierarchical);
    EXPECT_THROW(u.get_host(), std::domain_error);
}

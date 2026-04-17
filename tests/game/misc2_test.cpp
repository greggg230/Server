#include <gtest/gtest.h>
#include "common/misc.h"

#include <cstring>
#include <string>
#include <arpa/inet.h>  // htonl

// ============================================================
// long2ip — converts a host-order 32-bit IP to dotted-decimal
// ============================================================
TEST(Misc2Long2IpTest, LoopbackIs127001) {
    // 127.0.0.1 stored little-endian in the union: a=127,b=0,c=0,d=1
    // The union reads bytes a,b,c,d of the unsigned long
    unsigned long ip = 127 | (0 << 8) | (0 << 16) | (1u << 24);
    std::string result = long2ip(ip);
    EXPECT_EQ(result, "127.0.0.1");
}

TEST(Misc2Long2IpTest, ZeroIsAllZeros) {
    EXPECT_EQ(long2ip(0), "0.0.0.0");
}

TEST(Misc2Long2IpTest, AllOnesByteValues) {
    // Each byte = 1 → "1.1.1.1"
    unsigned long ip = 1 | (1 << 8) | (1 << 16) | (1u << 24);
    EXPECT_EQ(long2ip(ip), "1.1.1.1");
}

TEST(Misc2Long2IpTest, MaxPerOctet) {
    unsigned long ip = 255 | (255 << 8) | (255 << 16) | (255u << 24);
    EXPECT_EQ(long2ip(ip), "255.255.255.255");
}

TEST(Misc2Long2IpTest, ResultLengthAtMost15) {
    unsigned long ip = 255 | (255 << 8) | (255 << 16) | (255u << 24);
    EXPECT_LE(long2ip(ip).length(), 15u);
}

// ============================================================
// EQsprintf — limited printf with %1..%9 positional args
// ============================================================
TEST(Misc2EQsprintfTest, SimpleSubstitution) {
    char buf[256];
    EQsprintf(buf, "Hello %1!", "world", "", "", "", "", "", "", "", "");
    EXPECT_STREQ(buf, "Hello world!");
}

TEST(Misc2EQsprintfTest, TwoSubstitutions) {
    char buf[256];
    EQsprintf(buf, "%1 and %2", "foo", "bar", "", "", "", "", "", "", "");
    EXPECT_STREQ(buf, "foo and bar");
}

TEST(Misc2EQsprintfTest, NoSubstitutions) {
    char buf[256];
    EQsprintf(buf, "literal", "", "", "", "", "", "", "", "", "");
    EXPECT_STREQ(buf, "literal");
}

TEST(Misc2EQsprintfTest, Arg9) {
    char buf[256];
    EQsprintf(buf, "%9", "", "", "", "", "", "", "", "", "ninth");
    EXPECT_STREQ(buf, "ninth");
}

TEST(Misc2EQsprintfTest, OrderMatters) {
    char buf[256];
    EQsprintf(buf, "%2%1", "B", "A", "", "", "", "", "", "", "");
    EXPECT_STREQ(buf, "AB");
}

// ============================================================
// build_hex_line — formats a buffer as a hex dump line
// ============================================================
TEST(Misc2BuildHexLineTest, OutputIsNonEmpty) {
    const char data[] = {0x41, 0x42, 0x43};  // "ABC"
    char out[256] = {};
    build_hex_line(data, 3, 0, out, 4);
    EXPECT_GT(strlen(out), 0u);
}

TEST(Misc2BuildHexLineTest, ContainsHexBytes) {
    const unsigned char data[] = {0xDE, 0xAD};
    char out[256] = {};
    build_hex_line(reinterpret_cast<const char*>(data), 2, 0, out, 4);
    // Should contain "DE" and "AD" in output
    std::string s(out);
    EXPECT_NE(s.find("de"), std::string::npos);
    EXPECT_NE(s.find("ad"), std::string::npos);
}

TEST(Misc2BuildHexLineTest, OffsetAppearsAtStart) {
    const char data[] = {0x00};
    char out[256] = {};
    build_hex_line(data, 1, 0, out, 4);
    // Format is "0000:" at offset 0 with padding=4
    EXPECT_EQ(strncmp(out, "0000:", 5), 0);
}

TEST(Misc2BuildHexLineTest, NonZeroOffset) {
    const char data[] = {0x01};
    char out[256] = {};
    build_hex_line(data, 1, 16, out, 4);
    EXPECT_EQ(strncmp(out, "0016:", 5), 0);
}

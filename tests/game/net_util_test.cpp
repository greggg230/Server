#include <gtest/gtest.h>
#include <cstring>
#include "common/net/endian.h"
#include "common/misc.h"

// ============================================================
// EQ::Net::ByteSwap
// ============================================================
TEST(ByteSwapTest, Uint16SwapsBytes) {
    EXPECT_EQ(EQ::Net::ByteSwap<uint16_t>(0x1234u), 0x3412u);
    EXPECT_EQ(EQ::Net::ByteSwap<uint16_t>(0x0001u), 0x0100u);
    EXPECT_EQ(EQ::Net::ByteSwap<uint16_t>(0xFF00u), 0x00FFu);
}

TEST(ByteSwapTest, Uint32SwapsBytes) {
    EXPECT_EQ(EQ::Net::ByteSwap<uint32_t>(0x12345678u), 0x78563412u);
    EXPECT_EQ(EQ::Net::ByteSwap<uint32_t>(0x00000001u), 0x01000000u);
    EXPECT_EQ(EQ::Net::ByteSwap<uint32_t>(0xFF000000u), 0x000000FFu);
}

TEST(ByteSwapTest, Uint64SwapsBytes) {
    EXPECT_EQ(EQ::Net::ByteSwap<uint64_t>(0x0102030405060708ULL),
              0x0807060504030201ULL);
}

TEST(ByteSwapTest, SwapIsItsOwnInverse) {
    EXPECT_EQ(EQ::Net::ByteSwap<uint16_t>(EQ::Net::ByteSwap<uint16_t>(0xABCDu)), 0xABCDu);
    EXPECT_EQ(EQ::Net::ByteSwap<uint32_t>(EQ::Net::ByteSwap<uint32_t>(0xDEADBEEFu)), 0xDEADBEEFu);
}

TEST(ByteSwapTest, SingleByteUnchanged) {
    EXPECT_EQ(EQ::Net::ByteSwap<uint8_t>(0x42u), 0x42u);
}

// ============================================================
// EQ::Net::HostToNetwork / NetworkToHost
// ============================================================
TEST(NetworkByteOrderTest, RoundTripUint16) {
    const uint16_t val = 0x1234u;
    EXPECT_EQ(EQ::Net::NetworkToHost(EQ::Net::HostToNetwork(val)), val);
}

TEST(NetworkByteOrderTest, RoundTripUint32) {
    const uint32_t val = 0xDEADBEEFu;
    EXPECT_EQ(EQ::Net::NetworkToHost(EQ::Net::HostToNetwork(val)), val);
}

TEST(NetworkByteOrderTest, RoundTripUint64) {
    const uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(EQ::Net::NetworkToHost(EQ::Net::HostToNetwork(val)), val);
}

TEST(NetworkByteOrderTest, HostAndNetworkAreMirrors) {
    // HostToNetwork and NetworkToHost must be the same function (both swap on LE, both identity on BE)
    const uint32_t val = 0x12345678u;
    EXPECT_EQ(EQ::Net::HostToNetwork(val), EQ::Net::NetworkToHost(val));
}

TEST(NetworkByteOrderTest, ApplyTwiceRestoresOriginal) {
    const uint32_t val = 0xCAFEBABEu;
    EXPECT_EQ(EQ::Net::HostToNetwork(EQ::Net::HostToNetwork(val)), val);
}

// ============================================================
// build_hex_line
// ============================================================
TEST(BuildHexLineTest, OffsetPrefixWithPaddingFour) {
    const char buf[] = {0x41, 0x42}; // "AB"
    char out[256] = {};
    build_hex_line(buf, 2, 0, out, 4);
    // Output should start with "0000:"
    EXPECT_EQ(strncmp(out, "0000:", 5), 0);
}

TEST(BuildHexLineTest, ContainsHexBytesForInput) {
    const char buf[] = {(char)0xDE, (char)0xAD, (char)0xBE, (char)0xEF};
    char out[256] = {};
    build_hex_line(buf, 4, 0, out, 4);
    // Should contain "de" "ad" "be" "ef" in output
    EXPECT_NE(strstr(out, "de"), nullptr);
    EXPECT_NE(strstr(out, "ad"), nullptr);
    EXPECT_NE(strstr(out, "be"), nullptr);
    EXPECT_NE(strstr(out, "ef"), nullptr);
}

TEST(BuildHexLineTest, AsciiSectionAppearsAfterSeparator) {
    const char buf[] = "ABCDEFGH"; // 8 printable chars
    char out[256] = {};
    build_hex_line(buf, 8, 0, out, 4);
    // Expect "  | " separator and then ASCII chars
    const char* sep = strstr(out, "  | ");
    ASSERT_NE(sep, nullptr);
    const char* ascii_start = sep + 4;
    EXPECT_EQ(ascii_start[0], 'A');
    EXPECT_EQ(ascii_start[1], 'B');
    EXPECT_EQ(ascii_start[7], 'H');
}

TEST(BuildHexLineTest, NonPrintableShowsAsDot) {
    const char buf[] = {0x01, 0x02}; // non-printable
    char out[256] = {};
    build_hex_line(buf, 2, 0, out, 4);
    const char* sep = strstr(out, "  | ");
    ASSERT_NE(sep, nullptr);
    EXPECT_EQ((sep + 4)[0], '.'); // non-printable → '.'
}

TEST(BuildHexLineTest, NonZeroOffsetAppearsInPrefix) {
    const char buf[32] = {};
    char out[256] = {};
    build_hex_line(buf, 32, 16, out, 4);
    // At offset 16, output should start with "0016:"
    EXPECT_EQ(strncmp(out, "0016:", 5), 0);
}

// ============================================================
// long2ip
// ============================================================
TEST(Long2IpTest, Loopback) {
    // 127.0.0.1 — on little-endian, stored as 0x0100007F in a uint32
    // But long2ip reads raw bytes, so we build it byte-by-byte
    union { unsigned long ip; struct { unsigned char a,b,c,d; } oct; } u;
    u.oct = {127, 0, 0, 1};
    EXPECT_EQ(long2ip(u.ip), "127.0.0.1");
}

TEST(Long2IpTest, AllZeros) {
    EXPECT_EQ(long2ip(0), "0.0.0.0");
}

TEST(Long2IpTest, FourDistinctOctets) {
    union { unsigned long ip; struct { unsigned char a,b,c,d; } oct; } u;
    u.oct = {192, 168, 1, 100};
    EXPECT_EQ(long2ip(u.ip), "192.168.1.100");
}

TEST(Long2IpTest, MaxAddress) {
    union { unsigned long ip; struct { unsigned char a,b,c,d; } oct; } u;
    u.oct = {255, 255, 255, 255};
    EXPECT_EQ(long2ip(u.ip), "255.255.255.255");
}

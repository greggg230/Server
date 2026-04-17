#include <gtest/gtest.h>
#include "common/ip_util.h"

// ── IPToUInt ──────────────────────────────────────────────────────────────────

TEST(IpUtilTest, IPToUInt_Loopback) {
	// 127.0.0.1 = 0x7F000001
	EXPECT_EQ(0x7F000001u, IpUtil::IPToUInt("127.0.0.1"));
}

TEST(IpUtilTest, IPToUInt_AllOnes) {
	// 255.255.255.255 = 0xFFFFFFFF
	EXPECT_EQ(0xFFFFFFFFu, IpUtil::IPToUInt("255.255.255.255"));
}

TEST(IpUtilTest, IPToUInt_AllZeros) {
	EXPECT_EQ(0u, IpUtil::IPToUInt("0.0.0.0"));
}

TEST(IpUtilTest, IPToUInt_RFC1918_192168) {
	// 192.168.1.100 = 0xC0A80164
	EXPECT_EQ(0xC0A80164u, IpUtil::IPToUInt("192.168.1.100"));
}

TEST(IpUtilTest, IPToUInt_InvalidReturnsZero) {
	EXPECT_EQ(0u, IpUtil::IPToUInt("not.an.ip"));
	EXPECT_EQ(0u, IpUtil::IPToUInt(""));
}

// ── IsIpInRange ───────────────────────────────────────────────────────────────

TEST(IpUtilTest, IsIpInRange_WithinSubnet) {
	EXPECT_TRUE(IpUtil::IsIpInRange("192.168.1.50", "192.168.1.0", "255.255.255.0"));
}

TEST(IpUtilTest, IsIpInRange_OutsideSubnet) {
	EXPECT_FALSE(IpUtil::IsIpInRange("192.168.2.1", "192.168.1.0", "255.255.255.0"));
}

TEST(IpUtilTest, IsIpInRange_NetworkAddress) {
	EXPECT_TRUE(IpUtil::IsIpInRange("10.0.0.0", "10.0.0.0", "255.0.0.0"));
}

TEST(IpUtilTest, IsIpInRange_BroadcastAddress) {
	EXPECT_TRUE(IpUtil::IsIpInRange("10.255.255.255", "10.0.0.0", "255.0.0.0"));
}

TEST(IpUtilTest, IsIpInRange_JustOutside) {
	EXPECT_FALSE(IpUtil::IsIpInRange("11.0.0.0", "10.0.0.0", "255.0.0.0"));
}

// ── IsIpInPrivateRfc1918 ──────────────────────────────────────────────────────

TEST(IpUtilTest, IsPrivate_10Block) {
	EXPECT_TRUE(IpUtil::IsIpInPrivateRfc1918("10.0.0.1"));
	EXPECT_TRUE(IpUtil::IsIpInPrivateRfc1918("10.255.255.255"));
}

TEST(IpUtilTest, IsPrivate_172Block) {
	EXPECT_TRUE(IpUtil::IsIpInPrivateRfc1918("172.16.0.1"));
	EXPECT_TRUE(IpUtil::IsIpInPrivateRfc1918("172.31.255.255"));
}

TEST(IpUtilTest, IsPrivate_192168Block) {
	EXPECT_TRUE(IpUtil::IsIpInPrivateRfc1918("192.168.0.1"));
	EXPECT_TRUE(IpUtil::IsIpInPrivateRfc1918("192.168.255.254"));
}

TEST(IpUtilTest, IsPrivate_PublicIp) {
	EXPECT_FALSE(IpUtil::IsIpInPrivateRfc1918("8.8.8.8"));
	EXPECT_FALSE(IpUtil::IsIpInPrivateRfc1918("1.1.1.1"));
}

TEST(IpUtilTest, IsPrivate_172OutsideRange) {
	// 172.32.x.x is NOT in 172.16-31 range
	EXPECT_FALSE(IpUtil::IsIpInPrivateRfc1918("172.32.0.1"));
}

// ── IsIPAddress ───────────────────────────────────────────────────────────────

TEST(IpUtilTest, IsIPAddress_Valid) {
	EXPECT_TRUE(IpUtil::IsIPAddress("192.168.1.1"));
	EXPECT_TRUE(IpUtil::IsIPAddress("0.0.0.0"));
	EXPECT_TRUE(IpUtil::IsIPAddress("255.255.255.255"));
}

TEST(IpUtilTest, IsIPAddress_Invalid) {
	EXPECT_FALSE(IpUtil::IsIPAddress("not-an-ip"));
	EXPECT_FALSE(IpUtil::IsIPAddress("256.0.0.1"));
	EXPECT_FALSE(IpUtil::IsIPAddress("192.168.1"));
	EXPECT_FALSE(IpUtil::IsIPAddress(""));
}

TEST(IpUtilTest, IsIPAddress_Loopback) {
	EXPECT_TRUE(IpUtil::IsIPAddress("127.0.0.1"));
}

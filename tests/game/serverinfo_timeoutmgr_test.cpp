#include <gtest/gtest.h>
#include "common/serverinfo.h"
#include "common/opcodemgr.h"

#include <cstring>

// ============================================================
// EQ::GetPID — process ID
// ============================================================
TEST(ServerInfoPIDTest, PIDIsPositive) {
    EXPECT_GT(EQ::GetPID(), static_cast<size_t>(0));
}

TEST(ServerInfoPIDTest, PIDIsConsistent) {
    EXPECT_EQ(EQ::GetPID(), EQ::GetPID());
}

// ============================================================
// EQ::GetRSS — resident set size
// ============================================================
TEST(ServerInfoRSSTest, RSSIsNonNegative) {
    size_t rss = EQ::GetRSS();
    EXPECT_GE(rss, static_cast<size_t>(0));
}

TEST(ServerInfoRSSTest, RSSIsReasonablySized) {
    size_t rss = EQ::GetRSS();
    if (rss > 0) {
        EXPECT_GE(rss, static_cast<size_t>(1024));
    }
}

// ============================================================
// EQ::GetUptime — system uptime
// ============================================================
TEST(ServerInfoUptimeTest, UptimeIsNonNegative) {
    EXPECT_GE(EQ::GetUptime(), 0.0);
}

TEST(ServerInfoUptimeTest, UptimeIsReasonable) {
    double uptime = EQ::GetUptime();
    if (uptime > 0.0) {
        EXPECT_GE(uptime, 1.0);
    }
}

// ============================================================
// EQ::GetCPUs — CPU information
// ============================================================
TEST(ServerInfoCPUTest, CPUListIsNonEmpty) {
    auto cpus = EQ::GetCPUs();
    EXPECT_FALSE(cpus.empty());
}

TEST(ServerInfoCPUTest, CPUModelIsNonEmpty) {
    auto cpus = EQ::GetCPUs();
    ASSERT_FALSE(cpus.empty());
    EXPECT_FALSE(cpus[0].model.empty());
}

TEST(ServerInfoCPUTest, CPUSpeedIsNonNegative) {
    auto cpus = EQ::GetCPUs();
    ASSERT_FALSE(cpus.empty());
    EXPECT_GE(cpus[0].speed, 0.0);
}

// ============================================================
// EQ::GetOS — operating system information
// ============================================================
TEST(ServerInfoOSTest, SysnameIsNonEmpty) {
    auto os = EQ::GetOS();
    EXPECT_FALSE(os.sysname.empty());
}

TEST(ServerInfoOSTest, ReleaseIsNonEmpty) {
    auto os = EQ::GetOS();
    EXPECT_FALSE(os.release.empty());
}

TEST(ServerInfoOSTest, MachineIsNonEmpty) {
    auto os = EQ::GetOS();
    EXPECT_FALSE(os.machine.empty());
}

// ============================================================
// OpcodeManager::EmuToName — static name lookup
// ============================================================
TEST(OpcodeManagerEmuToNameTest, UnknownReturnsOPUnknown) {
    const char *name = OpcodeManager::EmuToName(OP_Unknown);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "OP_Unknown");
}

TEST(OpcodeManagerEmuToNameTest, KnownOpcodeReturnsNonEmpty) {
    const char *name = OpcodeManager::EmuToName(OP_Camp);
    ASSERT_NE(name, nullptr);
    EXPECT_GT(strlen(name), 0u);
}

TEST(OpcodeManagerEmuToNameTest, KnownOpcodeHasCorrectName) {
    const char *name = OpcodeManager::EmuToName(OP_Camp);
    EXPECT_STREQ(name, "OP_Camp");
}

TEST(OpcodeManagerEmuToNameTest, ZoneChangeHasCorrectName) {
    const char *name = OpcodeManager::EmuToName(OP_ZoneChange);
    EXPECT_STREQ(name, "OP_ZoneChange");
}

TEST(OpcodeManagerEmuToNameTest, LoginHasCorrectName) {
    const char *name = OpcodeManager::EmuToName(OP_Login);
    EXPECT_STREQ(name, "OP_Login");
}

// ============================================================
// OpcodeManager::NameSearch — reverse lookup (non-static, needs instance)
// ============================================================
TEST(OpcodeManagerNameSearchTest, UnknownNameReturnsOPUnknown) {
    RegularOpcodeManager mgr;
    EXPECT_EQ(mgr.NameSearch("OP_Unknown"), OP_Unknown);
}

TEST(OpcodeManagerNameSearchTest, NonexistentNameReturnsOPUnknown) {
    RegularOpcodeManager mgr;
    EXPECT_EQ(mgr.NameSearch("OP_DoesNotExist_XYZ"), OP_Unknown);
}

TEST(OpcodeManagerNameSearchTest, CampNameReturnsOPCamp) {
    RegularOpcodeManager mgr;
    EXPECT_EQ(mgr.NameSearch("OP_Camp"), OP_Camp);
}

TEST(OpcodeManagerNameSearchTest, LoginNameReturnsOPLogin) {
    RegularOpcodeManager mgr;
    EXPECT_EQ(mgr.NameSearch("OP_Login"), OP_Login);
}

TEST(OpcodeManagerNameSearchTest, CaseInsensitiveMatch) {
    // NameSearch uses strcasecmp so lowercase should also match
    RegularOpcodeManager mgr;
    EXPECT_EQ(mgr.NameSearch("op_camp"), OP_Camp);
}

TEST(OpcodeManagerNameSearchTest, RoundTrip) {
    // EmuToName then NameSearch should give back the original opcode
    RegularOpcodeManager mgr;
    const char *name = OpcodeManager::EmuToName(OP_ZoneEntry);
    EXPECT_EQ(mgr.NameSearch(name), OP_ZoneEntry);
}

#include <gtest/gtest.h>
#include "common/memory_mapped_file.h"

#include <cstdio>
#include <cstring>
#include <string>

// ============================================================
// EQ::MemoryMappedFile — construction and basic operations
// Use /tmp paths and clean up via RAII helper
// ============================================================

namespace {
struct TempPath {
    std::string path;
    TempPath(const std::string& p) : path(p) {}
    ~TempPath() { std::remove(path.c_str()); }
};
} // namespace

TEST(MemoryMappedFileTest, ConstructWithSizeDoesNotCrash) {
    TempPath tp("/tmp/__eqemu_mmf_test1__");
    EXPECT_NO_THROW({
        EQ::MemoryMappedFile mmf(tp.path, 64);
    });
}

TEST(MemoryMappedFileTest, SizeAfterZeroFileMatchesRequested) {
    TempPath tp("/tmp/__eqemu_mmf_test2__");
    EQ::MemoryMappedFile mmf(tp.path, 128);
    mmf.ZeroFile();
    EXPECT_EQ(mmf.Size(), 128u);
}

TEST(MemoryMappedFileTest, GetReturnsNonNull) {
    TempPath tp("/tmp/__eqemu_mmf_test3__");
    EQ::MemoryMappedFile mmf(tp.path, 32);
    EXPECT_NE(mmf.Get(), nullptr);
}

TEST(MemoryMappedFileTest, ArrowOperatorMatchesGet) {
    TempPath tp("/tmp/__eqemu_mmf_test4__");
    EQ::MemoryMappedFile mmf(tp.path, 32);
    EXPECT_EQ(mmf.operator->(), mmf.Get());
}

TEST(MemoryMappedFileTest, WriteAndReadBack) {
    TempPath tp("/tmp/__eqemu_mmf_test5__");
    {
        EQ::MemoryMappedFile mmf(tp.path, 64);
        char *data = reinterpret_cast<char*>(mmf.Get());
        std::memcpy(data, "hello", 6);
    }
    // Re-open and read
    EQ::MemoryMappedFile mmf2(tp.path);
    const char *data2 = reinterpret_cast<const char*>(mmf2.Get());
    EXPECT_EQ(std::string(data2), "hello");
}

TEST(MemoryMappedFileTest, ZeroFileZerosMemory) {
    TempPath tp("/tmp/__eqemu_mmf_test6__");
    EQ::MemoryMappedFile mmf(tp.path, 32);
    char *data = reinterpret_cast<char*>(mmf.Get());
    std::memset(data, 0xFF, 32);
    mmf.ZeroFile();
    // After ZeroFile the data should be zeroed
    for (int i = 0; i < 32; ++i) {
        EXPECT_EQ(data[i], 0) << "byte " << i << " not zeroed";
    }
}

TEST(MemoryMappedFileTest, SmallSizeWorks) {
    TempPath tp("/tmp/__eqemu_mmf_test7__");
    EQ::MemoryMappedFile mmf(tp.path, 1);
    mmf.ZeroFile();
    EXPECT_EQ(mmf.Size(), 1u);
    EXPECT_NE(mmf.Get(), nullptr);
}

TEST(MemoryMappedFileTest, LargeSizeWorks) {
    TempPath tp("/tmp/__eqemu_mmf_test8__");
    EQ::MemoryMappedFile mmf(tp.path, 1024 * 1024);
    mmf.ZeroFile();
    EXPECT_EQ(mmf.Size(), 1024u * 1024u);
    EXPECT_NE(mmf.Get(), nullptr);
}

#include <gtest/gtest.h>
#include "common/file.h"

#include <cstdio>
#include <fstream>
#include <string>

// ============================================================
// File::Exists — path existence checks
// ============================================================
TEST(FileExistsTest, RootTmpExists) {
    EXPECT_TRUE(File::Exists("/tmp"));
}

TEST(FileExistsTest, NonexistentPathReturnsFalse) {
    EXPECT_FALSE(File::Exists("/tmp/__eqemu_nonexistent_xyz_99887766__"));
}

TEST(FileExistsTest, CreatedFileThenDeleted) {
    const std::string path = "/tmp/__eqemu_file_test_exists__.txt";
    {
        std::ofstream f(path);
        f << "test";
    }
    EXPECT_TRUE(File::Exists(path));
    std::remove(path.c_str());
    EXPECT_FALSE(File::Exists(path));
}

TEST(FileExistsTest, EmptyPathReturnsFalse) {
    EXPECT_FALSE(File::Exists(""));
}

// ============================================================
// File::GetCwd — current working directory
// ============================================================
TEST(FileGetCwdTest, ReturnsNonEmptyString) {
    EXPECT_FALSE(File::GetCwd().empty());
}

TEST(FileGetCwdTest, ReturnsAbsolutePath) {
    std::string cwd = File::GetCwd();
    EXPECT_EQ(cwd[0], '/');
}

TEST(FileGetCwdTest, ConsistentAcrossCalls) {
    EXPECT_EQ(File::GetCwd(), File::GetCwd());
}

// ============================================================
// File::GetContents — read a real file
// ============================================================
TEST(FileGetContentsTest, NonexistentFileHasError) {
    auto result = File::GetContents("/tmp/__eqemu_no_such_file_xyz__.txt");
    EXPECT_FALSE(result.error.empty());
    EXPECT_TRUE(result.contents.empty());
}

TEST(FileGetContentsTest, ExistingFileHasNoError) {
    const std::string path = "/tmp/__eqemu_file_contents_test__.txt";
    const std::string content = "Hello, EQEmu!";
    {
        std::ofstream f(path);
        f << content;
    }
    auto result = File::GetContents(path);
    EXPECT_TRUE(result.error.empty());
    EXPECT_EQ(result.contents, content);
    std::remove(path.c_str());
}

TEST(FileGetContentsTest, EmptyFileHasNoErrorAndEmptyContents) {
    const std::string path = "/tmp/__eqemu_file_empty_test__.txt";
    {
        std::ofstream f(path);
    }
    auto result = File::GetContents(path);
    EXPECT_TRUE(result.error.empty());
    EXPECT_TRUE(result.contents.empty());
    std::remove(path.c_str());
}

TEST(FileGetContentsTest, BinaryDataPreserved) {
    const std::string path = "/tmp/__eqemu_file_binary_test__.bin";
    const std::string binary = "\x00\x01\x02\x03\xFF\xFE";
    {
        std::ofstream f(path, std::ios::binary);
        f.write(binary.data(), binary.size());
    }
    auto result = File::GetContents(path);
    EXPECT_TRUE(result.error.empty());
    EXPECT_EQ(result.contents.size(), binary.size());
    std::remove(path.c_str());
}

// ============================================================
// File::Makedir — create a directory
// ============================================================
TEST(FileMakedirTest, CreatesNewDirectory) {
    const std::string path = "/tmp/__eqemu_mkdir_test__";
    std::remove(path.c_str());
    File::Makedir(path);
    EXPECT_TRUE(File::Exists(path));
    rmdir(path.c_str());
}

TEST(FileMakedirTest, IdempotentOnExistingDirectory) {
    const std::string path = "/tmp/__eqemu_mkdir_exist__";
    File::Makedir(path);
    EXPECT_NO_THROW(File::Makedir(path));
    EXPECT_TRUE(File::Exists(path));
    rmdir(path.c_str());
}

// ============================================================
// FileContentsResult struct
// ============================================================
TEST(FileContentsResultTest, DefaultConstructHasEmptyFields) {
    FileContentsResult r;
    EXPECT_TRUE(r.contents.empty());
    EXPECT_TRUE(r.error.empty());
}

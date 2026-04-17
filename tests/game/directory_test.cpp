#include <gtest/gtest.h>
#include "common/util/directory.h"

#include <cstdio>
#include <string>
#include <vector>
#include <sys/stat.h>

// ============================================================
// EQ::Directory — filesystem directory utility
// ============================================================

TEST(EQDirectoryTest, ExistingDirExists) {
    EQ::Directory d("/tmp");
    EXPECT_TRUE(d.Exists());
}

TEST(EQDirectoryTest, NonexistentDirDoesNotExist) {
    EQ::Directory d("/tmp/__nonexistent_eqemu__");
    EXPECT_FALSE(d.Exists());
}

TEST(EQDirectoryTest, GetFilesFromNonexistentIsEmpty) {
    EQ::Directory d("/tmp/__nonexistent_eqemu__");
    std::vector<std::string> files;
    d.GetFiles(files);
    EXPECT_TRUE(files.empty());
}

TEST(EQDirectoryTest, GetFilesFromTmpDoesNotCrash) {
    EQ::Directory d("/tmp");
    std::vector<std::string> files;
    EXPECT_NO_THROW(d.GetFiles(files));
}

TEST(EQDirectoryTest, GetFilesFromKnownDirFindsKnownFile) {
    const char* dir  = "/tmp/__eqemu_dirtest__";
    const char* file = "/tmp/__eqemu_dirtest__/hello.txt";
    mkdir(dir, 0755);
    FILE* f = fopen(file, "w");
    if (f) { fputs("x", f); fclose(f); }

    EQ::Directory d(dir);
    ASSERT_TRUE(d.Exists());
    std::vector<std::string> files;
    d.GetFiles(files);
    EXPECT_FALSE(files.empty());

    bool found = false;
    for (const auto& name : files) {
        if (name == "hello.txt") { found = true; break; }
    }
    EXPECT_TRUE(found);

    remove(file);
    rmdir(dir);
}

TEST(EQDirectoryTest, MultipleInstancesIndependent) {
    EQ::Directory d1("/tmp");
    EQ::Directory d2("/tmp/__nonexistent_eqemu__");
    EXPECT_TRUE(d1.Exists());
    EXPECT_FALSE(d2.Exists());
}

#include <gtest/gtest.h>
#include <cstring>
#include <vector>
#include <string>
#include "common/compression.h"

namespace {

std::vector<char> MakeOutBuf(uint32 sz) { return std::vector<char>(sz, '\0'); }

std::string RoundTrip(const std::string& input) {
	uint32 maxOut = EQ::EstimateDeflateBuffer(static_cast<uint32>(input.size())) + 64;
	std::vector<char> compressed(maxOut);
	uint32 compSize = EQ::DeflateData(input.data(), static_cast<uint32>(input.size()),
	                                   compressed.data(), maxOut);
	if (compSize == 0) return "";

	std::vector<char> restored(input.size() + 1, '\0');
	uint32 decompSize = EQ::InflateData(compressed.data(), compSize,
	                                     restored.data(), static_cast<uint32>(restored.size()));
	return std::string(restored.data(), decompSize);
}

} // namespace

// ── EstimateDeflateBuffer ─────────────────────────────────────────────────────

TEST(CompressionTest, EstimateDeflateBufferNonZeroForNonEmpty) {
	EXPECT_GT(EQ::EstimateDeflateBuffer(100), 0u);
}

TEST(CompressionTest, EstimateDeflateBufferGrowsWithInput) {
	EXPECT_GE(EQ::EstimateDeflateBuffer(10000), EQ::EstimateDeflateBuffer(100));
}

// ── DeflateData / InflateData round-trips ─────────────────────────────────────

TEST(CompressionTest, RoundTripEmptyString) {
	EXPECT_EQ("", RoundTrip(""));
}

TEST(CompressionTest, RoundTripShortString) {
	EXPECT_EQ("hello world", RoundTrip("hello world"));
}

TEST(CompressionTest, RoundTripHighlyCompressible) {
	// 1000 repeated 'a' characters — deflate should shrink this significantly
	std::string input(1000, 'a');
	EXPECT_EQ(input, RoundTrip(input));
}

TEST(CompressionTest, RoundTripBinaryData) {
	// Data with all byte values
	std::string input;
	for (int i = 0; i < 256; ++i) input += static_cast<char>(i);
	EXPECT_EQ(input, RoundTrip(input));
}

TEST(CompressionTest, RoundTripLargeText) {
	std::string input;
	for (int i = 0; i < 500; ++i)
		input += "The quick brown fox jumps over the lazy dog. ";
	EXPECT_EQ(input, RoundTrip(input));
}

TEST(CompressionTest, HighlyCompressibleDataShrinks) {
	std::string input(4096, 'z');
	uint32 maxOut = EQ::EstimateDeflateBuffer(static_cast<uint32>(input.size())) + 64;
	std::vector<char> buf(maxOut);
	uint32 compSize = EQ::DeflateData(input.data(), static_cast<uint32>(input.size()),
	                                   buf.data(), maxOut);
	EXPECT_GT(compSize, 0u);
	EXPECT_LT(compSize, static_cast<uint32>(input.size())); // compressed < original
}

TEST(CompressionTest, DeflateReturnsBytesWritten) {
	std::string input = "EQEmu compression test";
	uint32 maxOut = 1024;
	std::vector<char> buf(maxOut);
	uint32 written = EQ::DeflateData(input.data(), static_cast<uint32>(input.size()),
	                                  buf.data(), maxOut);
	EXPECT_GT(written, 0u);
	EXPECT_LE(written, maxOut);
}

TEST(CompressionTest, InflateReturnsBytesWritten) {
	std::string input = "EQEmu compression test";
	uint32 maxOut = 1024;
	std::vector<char> compressed(maxOut);
	uint32 compSize = EQ::DeflateData(input.data(), static_cast<uint32>(input.size()),
	                                   compressed.data(), maxOut);

	std::vector<char> restored(input.size() + 1, '\0');
	uint32 decompSize = EQ::InflateData(compressed.data(), compSize,
	                                     restored.data(), static_cast<uint32>(restored.size()));
	EXPECT_EQ(decompSize, input.size());
}

TEST(CompressionTest, DifferentInputsDifferentCompressed) {
	auto compress = [](const std::string& s) {
		uint32 maxOut = EQ::EstimateDeflateBuffer(static_cast<uint32>(s.size())) + 64;
		std::vector<char> buf(maxOut);
		uint32 sz = EQ::DeflateData(s.data(), static_cast<uint32>(s.size()), buf.data(), maxOut);
		return std::string(buf.data(), sz);
	};
	EXPECT_NE(compress("hello"), compress("world"));
}

#include <gtest/gtest.h>
#include "common/net/reliable_stream_structs.h"

#include <cstddef>

// ============================================================
// EQ::Net::Reliable stream struct sizes
// These static size() functions define the wire-format byte counts.
// ============================================================

TEST(ReliableStreamHeaderTest, SizeIsTwo) {
    EXPECT_EQ(EQ::Net::ReliableStreamHeader::size(), 2u);
}

TEST(ReliableStreamHeaderTest, ZeroFieldPresent) {
    EQ::Net::ReliableStreamHeader h{};
    h.zero = 0;
    h.opcode = 0x07;
    EXPECT_EQ(h.zero, 0u);
    EXPECT_EQ(h.opcode, 0x07u);
}

TEST(ReliableStreamConnectTest, SizeIs14) {
    EXPECT_EQ(EQ::Net::ReliableStreamConnect::size(), 14u);
}

TEST(ReliableStreamConnectTest, FieldsAssignable) {
    EQ::Net::ReliableStreamConnect c{};
    c.protocol_version = 3;
    c.connect_code     = 0xDEADBEEF;
    c.max_packet_size  = 512;
    EXPECT_EQ(c.protocol_version, 3u);
    EXPECT_EQ(c.connect_code,     0xDEADBEEFu);
    EXPECT_EQ(c.max_packet_size,  512u);
}

TEST(ReliableStreamConnectReplyTest, SizeIs17) {
    EXPECT_EQ(EQ::Net::ReliableStreamConnectReply::size(), 17u);
}

TEST(ReliableStreamConnectReplyTest, FieldsAssignable) {
    EQ::Net::ReliableStreamConnectReply r{};
    r.connect_code  = 0x12345678;
    r.encode_key    = 0xABCDABCD;
    r.crc_bytes     = 2;
    r.encode_pass1  = 1;
    r.encode_pass2  = 0;
    r.max_packet_size = 1024;
    EXPECT_EQ(r.connect_code,     0x12345678u);
    EXPECT_EQ(r.encode_key,       0xABCDABCDu);
    EXPECT_EQ(r.crc_bytes,        2u);
    EXPECT_EQ(r.max_packet_size,  1024u);
}

TEST(ReliableStreamDisconnectTest, SizeIsEight) {
    EXPECT_EQ(EQ::Net::ReliableStreamDisconnect::size(), 8u);
}

TEST(ReliableStreamReliableHeaderTest, SizeIsFour) {
    EXPECT_EQ(EQ::Net::ReliableStreamReliableHeader::size(), 4u);
}

TEST(ReliableStreamReliableFragmentHeaderTest, SizeIsEight) {
    // Fragment header size = 4 + ReliableStreamReliableHeader::size() = 4 + 4 = 8
    size_t expected = 4 + EQ::Net::ReliableStreamReliableHeader::size();
    EXPECT_EQ(EQ::Net::ReliableStreamReliableFragmentHeader::size(), expected);
}

TEST(ReliableStreamReliableFragmentHeaderTest, SizeIsEightConcreteValue) {
    EXPECT_EQ(EQ::Net::ReliableStreamReliableFragmentHeader::size(), 8u);
}

TEST(ReliableStreamSessionStatRequestTest, SizeIs40) {
    EXPECT_EQ(EQ::Net::ReliableStreamSessionStatRequest::size(), 40u);
}

TEST(ReliableStreamSessionStatResponseTest, SizeIs40) {
    EXPECT_EQ(EQ::Net::ReliableStreamSessionStatResponse::size(), 40u);
}

TEST(ReliableStreamSessionStatTest, RequestAndResponseSameSize) {
    EXPECT_EQ(EQ::Net::ReliableStreamSessionStatRequest::size(),
              EQ::Net::ReliableStreamSessionStatResponse::size());
}

TEST(ReliableStreamSizesOrdered, HeaderSmallerThanConnect) {
    EXPECT_LT(EQ::Net::ReliableStreamHeader::size(),
              EQ::Net::ReliableStreamConnect::size());
}

TEST(ReliableStreamSizesOrdered, ConnectSmallerThanConnectReply) {
    EXPECT_LT(EQ::Net::ReliableStreamConnect::size(),
              EQ::Net::ReliableStreamConnectReply::size());
}

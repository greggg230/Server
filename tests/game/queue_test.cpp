#include <gtest/gtest.h>
#include "common/queue.h"

// ---- Construction ----

TEST(MyQueueTest, StartsEmpty) {
    MyQueue<int> q;
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.count(), 0);
}

TEST(MyQueueTest, TopOnEmptyReturnsNull) {
    MyQueue<int> q;
    EXPECT_EQ(q.top(), nullptr);
}

TEST(MyQueueTest, PopOnEmptyReturnsNull) {
    MyQueue<int> q;
    EXPECT_EQ(q.pop(), nullptr);
}

// ---- Push / top / pop ----

TEST(MyQueueTest, PushMakesNotEmpty) {
    MyQueue<int> q;
    int* v = new int(42);
    q.push(v);
    EXPECT_FALSE(q.empty());
    EXPECT_EQ(q.count(), 1);
    // queue owns it from here, pop to avoid leak
    delete q.pop();
}

TEST(MyQueueTest, TopReturnsHeadWithoutRemoving) {
    MyQueue<int> q;
    int* v = new int(7);
    q.push(v);
    EXPECT_EQ(q.top(), v);
    EXPECT_EQ(q.count(), 1);  // still there
    delete q.pop();
}

TEST(MyQueueTest, PopReturnsAndRemovesHead) {
    MyQueue<int> q;
    int* v = new int(99);
    q.push(v);
    int* popped = q.pop();
    EXPECT_EQ(popped, v);
    EXPECT_TRUE(q.empty());
    delete popped;
}

TEST(MyQueueTest, FIFOOrderPreserved) {
    MyQueue<int> q;
    int* a = new int(1);
    int* b = new int(2);
    int* c = new int(3);
    q.push(a);
    q.push(b);
    q.push(c);
    EXPECT_EQ(q.count(), 3);
    EXPECT_EQ(q.pop(), a);  // first in, first out
    EXPECT_EQ(q.pop(), b);
    EXPECT_EQ(q.pop(), c);
    EXPECT_TRUE(q.empty());
    delete a; delete b; delete c;
}

TEST(MyQueueTest, CountTracksCorrectly) {
    MyQueue<int> q;
    EXPECT_EQ(q.count(), 0);
    int* x = new int(0);
    q.push(x);
    EXPECT_EQ(q.count(), 1);
    q.push(new int(0));
    EXPECT_EQ(q.count(), 2);
    delete q.pop();
    EXPECT_EQ(q.count(), 1);
    delete q.pop();
    EXPECT_EQ(q.count(), 0);
}

// ---- clear ----

TEST(MyQueueTest, ClearEmptiesQueue) {
    MyQueue<int> q;
    q.push(new int(1));
    q.push(new int(2));
    q.push(new int(3));
    q.clear();
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.count(), 0);
    EXPECT_EQ(q.top(), nullptr);
}

// ---- works with struct ----

struct Item {
    int id;
    std::string name;
};

TEST(MyQueueTest, WorksWithStructValues) {
    MyQueue<Item> q;
    Item* it = new Item{42, "sword"};
    q.push(it);
    EXPECT_FALSE(q.empty());
    Item* out = q.pop();
    EXPECT_EQ(out->id, 42);
    EXPECT_EQ(out->name, "sword");
    delete out;
}

TEST(MyQueueTest, InterleavePopAndPush) {
    MyQueue<int> q;
    int* a = new int(10);
    int* b = new int(20);
    int* c = new int(30);
    q.push(a);
    q.push(b);
    EXPECT_EQ(q.pop(), a);
    q.push(c);
    EXPECT_EQ(q.pop(), b);
    EXPECT_EQ(q.pop(), c);
    EXPECT_TRUE(q.empty());
    delete a; delete b; delete c;
}

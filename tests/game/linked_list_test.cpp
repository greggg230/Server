#include <gtest/gtest.h>
#include "common/linked_list.h"

// LinkedList<TYPE> owns pointer data - destructor calls safe_delete on elements.
// Pop() transfers ownership back to caller.

// ---- Construction / empty state ----

TEST(LinkedListTest, StartsEmpty) {
    LinkedList<int*> list;
    EXPECT_EQ(list.Count(), 0u);
    EXPECT_EQ(list.GetFirst(), nullptr);
}

TEST(LinkedListTest, PeekTopOnEmptyReturnsZero) {
    LinkedList<int*> list;
    EXPECT_EQ(list.PeekTop(), nullptr);
}

TEST(LinkedListTest, PopOnEmptyReturnsZero) {
    LinkedList<int*> list;
    EXPECT_EQ(list.Pop(), nullptr);
}

// ---- Append ----

TEST(LinkedListTest, AppendIncreasesCount) {
    LinkedList<int*> list;
    list.Append(new int(1));
    EXPECT_EQ(list.Count(), 1u);
    // list owns, will clean up
}

TEST(LinkedListTest, AppendMultipleIncreasesCount) {
    LinkedList<int*> list;
    list.Append(new int(1));
    list.Append(new int(2));
    list.Append(new int(3));
    EXPECT_EQ(list.Count(), 3u);
}

TEST(LinkedListTest, AppendPreservesOrder) {
    LinkedList<int*> list;
    list.Append(new int(10));
    list.Append(new int(20));
    list.Append(new int(30));
    // Pop removes from head (FIFO when using Append only)
    int* a = list.Pop();
    int* b = list.Pop();
    int* c = list.Pop();
    EXPECT_EQ(*a, 10);
    EXPECT_EQ(*b, 20);
    EXPECT_EQ(*c, 30);
    delete a; delete b; delete c;
}

// ---- Insert ----

TEST(LinkedListTest, InsertAddsToFront) {
    LinkedList<int*> list;
    list.Insert(new int(1));
    list.Insert(new int(2));
    // Insert puts at front, so pop order is 2, 1
    int* a = list.Pop();
    int* b = list.Pop();
    EXPECT_EQ(*a, 2);
    EXPECT_EQ(*b, 1);
    delete a; delete b;
}

// ---- Pop ----

TEST(LinkedListTest, PopDecreasesCount) {
    LinkedList<int*> list;
    list.Append(new int(5));
    list.Append(new int(6));
    EXPECT_EQ(list.Count(), 2u);
    delete list.Pop();
    EXPECT_EQ(list.Count(), 1u);
    delete list.Pop();
    EXPECT_EQ(list.Count(), 0u);
}

TEST(LinkedListTest, PopOnEmptyAfterDrainReturnsNull) {
    LinkedList<int*> list;
    list.Append(new int(1));
    delete list.Pop();
    EXPECT_EQ(list.Pop(), nullptr);
}

// ---- PeekTop ----

TEST(LinkedListTest, PeekTopReturnsFirstWithoutRemoving) {
    LinkedList<int*> list;
    list.Append(new int(42));
    list.Append(new int(99));
    int* top = list.PeekTop();
    EXPECT_EQ(*top, 42);
    EXPECT_EQ(list.Count(), 2u);  // still there
}

// ---- Clear ----

TEST(LinkedListTest, ClearEmptiesAndFreesAll) {
    LinkedList<int*> list;
    list.Append(new int(1));
    list.Append(new int(2));
    list.Append(new int(3));
    list.Clear();
    EXPECT_EQ(list.Count(), 0u);
    EXPECT_EQ(list.GetFirst(), nullptr);
}

// ---- Forward iterator ----

TEST(LinkedListTest, ForwardIteratorTraversesAllElements) {
    LinkedList<int*> list;
    list.Append(new int(100));
    list.Append(new int(200));
    list.Append(new int(300));

    LinkedListIterator<int*> it(list, FORWARD);
    it.Reset();
    std::vector<int> seen;
    while (it.MoreElements()) {
        seen.push_back(*it.GetData());
        it.Advance();
    }
    ASSERT_EQ(seen.size(), 3u);
    EXPECT_EQ(seen[0], 100);
    EXPECT_EQ(seen[1], 200);
    EXPECT_EQ(seen[2], 300);
}

TEST(LinkedListTest, BackwardIteratorTraversesInReverse) {
    LinkedList<int*> list;
    list.Append(new int(10));
    list.Append(new int(20));
    list.Append(new int(30));

    LinkedListIterator<int*> it(list, BACKWARD);
    it.Reset();
    std::vector<int> seen;
    while (it.MoreElements()) {
        seen.push_back(*it.GetData());
        it.Advance();
    }
    ASSERT_EQ(seen.size(), 3u);
    EXPECT_EQ(seen[0], 30);
    EXPECT_EQ(seen[1], 20);
    EXPECT_EQ(seen[2], 10);
}

TEST(LinkedListTest, IteratorOnEmptyListHasNoElements) {
    LinkedList<int*> list;
    LinkedListIterator<int*> it(list, FORWARD);
    it.Reset();
    EXPECT_FALSE(it.MoreElements());
}

TEST(LinkedListTest, IteratorRemoveCurrentReducesCount) {
    LinkedList<int*> list;
    list.Append(new int(1));
    list.Append(new int(2));
    list.Append(new int(3));

    LinkedListIterator<int*> it(list, FORWARD);
    it.Reset();
    it.Advance();  // move to second element (value=2)
    it.RemoveCurrent(true);  // delete element + data
    EXPECT_EQ(list.Count(), 2u);

    // remaining should be 1 and 3
    it.Reset();
    std::vector<int> seen;
    while (it.MoreElements()) {
        seen.push_back(*it.GetData());
        it.Advance();
    }
    ASSERT_EQ(seen.size(), 2u);
    EXPECT_EQ(seen[0], 1);
    EXPECT_EQ(seen[1], 3);
}

TEST(LinkedListTest, IsFirstAndIsLastWork) {
    LinkedList<int*> list;
    list.Append(new int(1));
    list.Append(new int(2));

    LinkedListIterator<int*> it(list, FORWARD);
    it.Reset();
    EXPECT_TRUE(it.IsFirst());
    EXPECT_FALSE(it.IsLast());
    it.Advance();
    EXPECT_FALSE(it.IsFirst());
    EXPECT_TRUE(it.IsLast());
}

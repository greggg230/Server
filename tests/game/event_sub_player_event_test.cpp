#include <gtest/gtest.h>
#include "common/event_sub.h"
#include "common/events/player_events.h"

#include <string>

// ============================================================
// EventSubscriptionWatcher — singleton subscribe/unsubscribe
// Use unique event names per test to avoid cross-test state
// ============================================================
TEST(EventSubWatcherTest, InitiallyNotSubscribed) {
    auto* w = EventSubscriptionWatcher::Get();
    EXPECT_FALSE(w->IsSubscribed("__test_ev_initial_check"));
}

TEST(EventSubWatcherTest, SubscribeThenIsSubscribed) {
    auto* w = EventSubscriptionWatcher::Get();
    const std::string ev = "__test_ev_subscribe";
    w->Subscribe(ev);
    EXPECT_TRUE(w->IsSubscribed(ev));
    w->Unsubscribe(ev);
}

TEST(EventSubWatcherTest, UnsubscribeRemovesSubscription) {
    auto* w = EventSubscriptionWatcher::Get();
    const std::string ev = "__test_ev_unsub";
    w->Subscribe(ev);
    EXPECT_TRUE(w->IsSubscribed(ev));
    w->Unsubscribe(ev);
    EXPECT_FALSE(w->IsSubscribed(ev));
}

TEST(EventSubWatcherTest, MultipleDistinctEvents) {
    auto* w = EventSubscriptionWatcher::Get();
    const std::string ev1 = "__test_ev_multi1";
    const std::string ev2 = "__test_ev_multi2";
    w->Subscribe(ev1);
    EXPECT_TRUE(w->IsSubscribed(ev1));
    EXPECT_FALSE(w->IsSubscribed(ev2));
    w->Subscribe(ev2);
    EXPECT_TRUE(w->IsSubscribed(ev1));
    EXPECT_TRUE(w->IsSubscribed(ev2));
    w->Unsubscribe(ev1);
    w->Unsubscribe(ev2);
}

TEST(EventSubWatcherTest, UnsubscribeUnknownEventNoCrash) {
    auto* w = EventSubscriptionWatcher::Get();
    EXPECT_NO_THROW(w->Unsubscribe("__test_ev_never_subscribed"));
}

TEST(EventSubWatcherTest, IsSingletonSamePointer) {
    EXPECT_EQ(EventSubscriptionWatcher::Get(), EventSubscriptionWatcher::Get());
}

// ============================================================
// PlayerEvent::EventType enum values
// ============================================================
TEST(PlayerEventTypeTest, GmCommandIsOne) {
    EXPECT_EQ(PlayerEvent::EventType::GM_COMMAND, 1);
}

TEST(PlayerEventTypeTest, EarlySequential) {
    EXPECT_EQ(PlayerEvent::EventType::ZONING,          2);
    EXPECT_EQ(PlayerEvent::EventType::AA_GAIN,         3);
    EXPECT_EQ(PlayerEvent::EventType::AA_PURCHASE,     4);
    EXPECT_EQ(PlayerEvent::EventType::FORAGE_SUCCESS,  5);
    EXPECT_EQ(PlayerEvent::EventType::FORAGE_FAILURE,  6);
}

TEST(PlayerEventTypeTest, ItemAndCharEvents) {
    EXPECT_EQ(PlayerEvent::EventType::ITEM_DESTROY,    9);
    EXPECT_EQ(PlayerEvent::EventType::WENT_ONLINE,    10);
    EXPECT_EQ(PlayerEvent::EventType::WENT_OFFLINE,   11);
    EXPECT_EQ(PlayerEvent::EventType::LEVEL_GAIN,     12);
    EXPECT_EQ(PlayerEvent::EventType::LEVEL_LOSS,     13);
    EXPECT_EQ(PlayerEvent::EventType::LOOT_ITEM,      14);
}

TEST(PlayerEventTypeTest, MaxIsLast) {
    // MAX must be greater than all real events
    EXPECT_GT(PlayerEvent::EventType::MAX, PlayerEvent::EventType::GM_COMMAND);
    EXPECT_GT(PlayerEvent::EventType::MAX, PlayerEvent::EventType::LOOT_ITEM);
    EXPECT_GT(PlayerEvent::EventType::MAX, PlayerEvent::EventType::DEATH);
}

// ============================================================
// PlayerEvent::EventName static table
// ============================================================
TEST(PlayerEventNameTest, IndexZeroIsNone) {
    EXPECT_STREQ(PlayerEvent::EventName[0], "None");
}

TEST(PlayerEventNameTest, IndexOneIsGmCommand) {
    EXPECT_STREQ(PlayerEvent::EventName[1], "GM Command");
}

TEST(PlayerEventNameTest, AllEntriesNonNull) {
    for (int i = 0; i < PlayerEvent::EventType::MAX; ++i) {
        EXPECT_NE(PlayerEvent::EventName[i], nullptr)
            << "Null name at index " << i;
    }
}

TEST(PlayerEventNameTest, AllEntriesNonEmpty) {
    for (int i = 0; i < PlayerEvent::EventType::MAX; ++i) {
        EXPECT_GT(strlen(PlayerEvent::EventName[i]), 0u)
            << "Empty name at index " << i;
    }
}

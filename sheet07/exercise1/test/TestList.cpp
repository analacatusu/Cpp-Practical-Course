#include "lib/List.hpp"
#include "lib/MallocAllocator.hpp"
#include <optional>
#include <utility>
#include <gtest/gtest.h>
//---------------------------------------------------------------------------
using namespace pool;
using namespace std;
//---------------------------------------------------------------------------
TEST(TestList, InsertErase) {
    List<int, MallocAllocator<int>> l;
    EXPECT_EQ(l.size(), 0);
    for (unsigned i = 1; i <= 100; ++i) {
        l.insert(i);
        EXPECT_EQ(l.size(), i);
    }
    for (unsigned i = 1; i <= 100; ++i) {
        l.erase(i);
        EXPECT_EQ(l.size(), 100 - i);
    }
}
//---------------------------------------------------------------------------
TEST(TestList, InsertEraseReverse) {
    List<int, MallocAllocator<int>> l;
    EXPECT_EQ(l.size(), 0);
    for (unsigned i = 1; i <= 100; ++i) {
        l.insert(i);
        EXPECT_EQ(l.size(), i);
    }
    for (unsigned i = 1; i <= 100; ++i) {
        l.erase(100 - i + 1);
        EXPECT_EQ(l.size(), 100 - i);
    }
}
//---------------------------------------------------------------------------
TEST(TestList, Duplicates) {
    List<int, MallocAllocator<int>> l;
    EXPECT_EQ(l.size(), 0);
    for (unsigned i = 1; i <= 100; ++i) {
        l.insert(123);
        EXPECT_EQ(l.size(), i);
    }
    for (unsigned i = 1; i <= 100; ++i) {
        l.erase(123);
        EXPECT_EQ(l.size(), 100 - i);
    }
}
//---------------------------------------------------------------------------
TEST(TestList, EraseFromEmpty) {
    List<int, MallocAllocator<int>> l;
    EXPECT_EQ(l.size(), 0);
    l.erase(123);
    EXPECT_EQ(l.size(), 0);
}
//---------------------------------------------------------------------------
TEST(TestList, EraseNotExisting) {
    List<int, MallocAllocator<int>> l;
    EXPECT_EQ(l.size(), 0);
    l.insert(123);
    EXPECT_EQ(l.size(), 1);
    l.erase(456);
    EXPECT_EQ(l.size(), 1);
}
//---------------------------------------------------------------------------
TEST(TestList, Copy) {
    List<int, MallocAllocator<int>> l;
    EXPECT_EQ(l.size(), 0);
    l.insert(123);
    EXPECT_EQ(l.size(), 1);

    List<int, MallocAllocator<int>> l2(l);
    EXPECT_EQ(l.size(), 1);
    EXPECT_EQ(l2.size(), 1);

    List<int, MallocAllocator<int>> l3;
    l3 = l;
    EXPECT_EQ(l.size(), 1);
    EXPECT_EQ(l3.size(), 1);
}
//---------------------------------------------------------------------------
TEST(TestList, Move) {
    List<int, MallocAllocator<int>> l;
    EXPECT_EQ(l.size(), 0);
    l.insert(123);
    EXPECT_EQ(l.size(), 1);

    List<int, MallocAllocator<int>> l2(std::move(l));
    EXPECT_EQ(l.size(), 0);
    EXPECT_EQ(l2.size(), 1);

    List<int, MallocAllocator<int>> l3;
    l3 = std::move(l2);
    EXPECT_EQ(l2.size(), 0);
    EXPECT_EQ(l3.size(), 1);
}
//---------------------------------------------------------------------------
namespace {
//---------------------------------------------------------------------------
static unsigned allocateCalls = 0;
static unsigned deallocateCalls = 0;
static unsigned defaultConstructorCalls = 0;
static unsigned copyConstructorCalls = 0;
static unsigned destructorCalls = 0;
//---------------------------------------------------------------------------
void resetCounters() {
    allocateCalls = 0;
    deallocateCalls = 0;
    defaultConstructorCalls = 0;
    copyConstructorCalls = 0;
    destructorCalls = 0;
}
//---------------------------------------------------------------------------
template <typename T>
class TestAllocator {
    public:
    template <typename U>
    using rebind = TestAllocator<U>;

    MallocAllocator<T> allocator;

    T* allocate() {
        ++allocateCalls;
        return allocator.allocate();
    }

    void deallocate(T* ptr) {
        ++deallocateCalls;
        allocator.deallocate(ptr);
    }
};
//---------------------------------------------------------------------------
class TrackedStructors {
    public:
    TrackedStructors() { ++defaultConstructorCalls; }
    TrackedStructors(const TrackedStructors&) { ++copyConstructorCalls; }
    ~TrackedStructors() { ++destructorCalls; }
};
//---------------------------------------------------------------------------
bool operator==(const TrackedStructors&, const TrackedStructors&) {
    return true;
}
bool operator!=(const TrackedStructors&, const TrackedStructors&) {
    return false;
}
//---------------------------------------------------------------------------
} // namespace
//---------------------------------------------------------------------------
void testListAllocation_dummyEqualityOperators() {
    // This code exists only to remove warnings about the unused comparison
    // functions
    TrackedStructors t;
    static_cast<void>(t == t);
    static_cast<void>(t != t);
}
//---------------------------------------------------------------------------
TEST(TestList, Allocation) {
    resetCounters();
    optional<List<TrackedStructors, TestAllocator<TrackedStructors>>> l;
    l.emplace();

    EXPECT_EQ(allocateCalls, 0);
    EXPECT_EQ(deallocateCalls, 0);
    EXPECT_EQ(defaultConstructorCalls, 0);
    EXPECT_EQ(copyConstructorCalls, 0);
    EXPECT_EQ(destructorCalls, 0);

    TrackedStructors t;
    l->insert(t);

    EXPECT_EQ(allocateCalls, 1);
    EXPECT_EQ(deallocateCalls, 0);
    EXPECT_EQ(defaultConstructorCalls, 1);
    EXPECT_EQ(copyConstructorCalls, 1);
    EXPECT_EQ(destructorCalls, 0);

    l->erase(t);

    EXPECT_EQ(allocateCalls, 1);
    EXPECT_EQ(deallocateCalls, 1);
    EXPECT_EQ(defaultConstructorCalls, 1);
    EXPECT_EQ(copyConstructorCalls, 1);
    EXPECT_EQ(destructorCalls, 1);

    for (unsigned i = 0; i < 100; ++i) {
        l->insert(t);
    }

    EXPECT_EQ(allocateCalls, 101);
    EXPECT_EQ(deallocateCalls, 1);
    EXPECT_EQ(defaultConstructorCalls, 1);
    EXPECT_EQ(copyConstructorCalls, 101);
    EXPECT_EQ(destructorCalls, 1);

    l.reset();

    EXPECT_EQ(allocateCalls, 101);
    EXPECT_EQ(deallocateCalls, 101);
    EXPECT_EQ(defaultConstructorCalls, 1);
    EXPECT_EQ(copyConstructorCalls, 101);
    EXPECT_EQ(destructorCalls, 101);
}
//---------------------------------------------------------------------------
TEST(TestList, AllocationCopy) {
    resetCounters();
    optional<List<TrackedStructors, TestAllocator<TrackedStructors>>> l1, l2, l3;
    l1.emplace();
    l2.emplace();

    EXPECT_EQ(allocateCalls, 0);
    EXPECT_EQ(deallocateCalls, 0);
    EXPECT_EQ(defaultConstructorCalls, 0);
    EXPECT_EQ(copyConstructorCalls, 0);
    EXPECT_EQ(destructorCalls, 0);

    TrackedStructors t;
    for (unsigned i = 0; i < 10; ++i) {
        l1->insert(t);
    }

    EXPECT_EQ(allocateCalls, 10);
    EXPECT_EQ(deallocateCalls, 0);
    EXPECT_EQ(defaultConstructorCalls, 1);
    EXPECT_EQ(copyConstructorCalls, 10);
    EXPECT_EQ(destructorCalls, 0);

    for (unsigned i = 0; i < 10; ++i) {
        l2->insert(t);
    }

    EXPECT_EQ(allocateCalls, 20);
    EXPECT_EQ(deallocateCalls, 0);
    EXPECT_EQ(defaultConstructorCalls, 1);
    EXPECT_EQ(copyConstructorCalls, 20);
    EXPECT_EQ(destructorCalls, 0);

    // Use copy constructor
    l3.emplace(*l2);

    EXPECT_EQ(allocateCalls, 30);
    EXPECT_EQ(deallocateCalls, 0);
    EXPECT_EQ(defaultConstructorCalls, 1);
    EXPECT_EQ(copyConstructorCalls, 30);
    EXPECT_EQ(destructorCalls, 0);

    // Use copy assignment
    *l1 = *l2;

    EXPECT_EQ(allocateCalls, 40);
    EXPECT_EQ(deallocateCalls, 10);
    EXPECT_EQ(defaultConstructorCalls, 1);
    EXPECT_EQ(copyConstructorCalls, 40);
    EXPECT_EQ(destructorCalls, 10);

    l1.reset();
    l2.reset();
    l3.reset();

    EXPECT_EQ(allocateCalls, 40);
    EXPECT_EQ(deallocateCalls, 40);
    EXPECT_EQ(defaultConstructorCalls, 1);
    EXPECT_EQ(copyConstructorCalls, 40);
    EXPECT_EQ(destructorCalls, 40);
}
//---------------------------------------------------------------------------
TEST(TestList, AllocationMove) {
    resetCounters();
    optional<List<TrackedStructors, TestAllocator<TrackedStructors>>> l1, l2, l3;
    l1.emplace();
    l2.emplace();

    EXPECT_EQ(allocateCalls, 0);
    EXPECT_EQ(deallocateCalls, 0);
    EXPECT_EQ(defaultConstructorCalls, 0);
    EXPECT_EQ(copyConstructorCalls, 0);
    EXPECT_EQ(destructorCalls, 0);

    TrackedStructors t;
    for (unsigned i = 0; i < 10; ++i) {
        l1->insert(t);
    }

    EXPECT_EQ(allocateCalls, 10);
    EXPECT_EQ(deallocateCalls, 0);
    EXPECT_EQ(defaultConstructorCalls, 1);
    EXPECT_EQ(copyConstructorCalls, 10);
    EXPECT_EQ(destructorCalls, 0);

    for (unsigned i = 0; i < 10; ++i) {
        l2->insert(t);
    }

    EXPECT_EQ(allocateCalls, 20);
    EXPECT_EQ(deallocateCalls, 0);
    EXPECT_EQ(defaultConstructorCalls, 1);
    EXPECT_EQ(copyConstructorCalls, 20);
    EXPECT_EQ(destructorCalls, 0);

    // Use move constructor
    l3.emplace(move(*l2));

    EXPECT_EQ(allocateCalls, 20);
    EXPECT_EQ(deallocateCalls, 0);
    EXPECT_EQ(defaultConstructorCalls, 1);
    EXPECT_EQ(copyConstructorCalls, 20);
    EXPECT_EQ(destructorCalls, 0);

    // Use move assignment
    *l2 = move(*l1);

    EXPECT_EQ(allocateCalls, 20);
    EXPECT_EQ(deallocateCalls, 0);
    EXPECT_EQ(defaultConstructorCalls, 1);
    EXPECT_EQ(copyConstructorCalls, 20);
    EXPECT_EQ(destructorCalls, 0);

    l1.reset();
    l2.reset();
    l3.reset();

    EXPECT_EQ(allocateCalls, 20);
    EXPECT_EQ(deallocateCalls, 20);
    EXPECT_EQ(defaultConstructorCalls, 1);
    EXPECT_EQ(copyConstructorCalls, 20);
    EXPECT_EQ(destructorCalls, 20);
}
//---------------------------------------------------------------------------

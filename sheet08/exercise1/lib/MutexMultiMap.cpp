#include "lib/MutexMultiMap.hpp"
#include <cassert>
#include <new>
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
namespace hashtable {
//---------------------------------------------------------------------------
MutexMultiMap::Node::Node(value_type&& value)
    : value(move(value))
// Constructor
{
}
//---------------------------------------------------------------------------
MutexMultiMap::Iterator::Iterator(Node** bucket, Node** end, Node* node)
    : bucket(bucket),
      end(end),
      node(node)
// Constructor
{
    advance();
}
//---------------------------------------------------------------------------
void MutexMultiMap::Iterator::advance()
// Advance to the next entry
{
    while (!node && (bucket != end)) {
        ++bucket;
        node = (bucket == end) ? nullptr : *bucket;
    }
}
//---------------------------------------------------------------------------
MutexMultiMap::Iterator::reference MutexMultiMap::Iterator::operator*()
// Dereference
{
    assert(bucket != end);
    return node->value;
}
//---------------------------------------------------------------------------
MutexMultiMap::Iterator::pointer MutexMultiMap::Iterator::operator->()
// Pointer to member
{
    assert(bucket != end);
    return &node->value;
}
//---------------------------------------------------------------------------
MutexMultiMap::Iterator& MutexMultiMap::Iterator::operator++()
// Pre-increment
{
    assert(bucket != end);
    node = node->next;

    advance();

    return *this;
}
//---------------------------------------------------------------------------
MutexMultiMap::Iterator MutexMultiMap::Iterator::operator++(int)
// Post-increment
{
    assert(bucket != end);

    Iterator it(*this);
    operator++();
    return it;
}
//---------------------------------------------------------------------------
bool MutexMultiMap::Iterator::operator==(const Iterator& other) const
// Equality comparison
{
    return (bucket == other.bucket) && (end == other.end) && (node == other.node);
}
//---------------------------------------------------------------------------
bool MutexMultiMap::Iterator::operator!=(const Iterator& other) const
// Inequality comparison
{
    return !operator==(other);
}
//---------------------------------------------------------------------------
MutexMultiMap::MutexMultiMap(uint32_t bucketCount)
    : hashTable(bucketCount)
// Constructor
{
}
//---------------------------------------------------------------------------
MutexMultiMap::~MutexMultiMap()
// Destructor
{
    for (auto* node : hashTable) {
        while (node) {
            auto* next = node->next;
            node->~Node();
            nodeAllocator.deallocate(node, 1);
            node = next;
        }
    }
}
//---------------------------------------------------------------------------
MutexMultiMap::Iterator MutexMultiMap::insert(value_type&& value)
// Insert a value
{
    auto hash = value.first;
    auto slot = hash % hashTable.size();

    auto* node = nodeAllocator.allocate(1);
    new (node) Node(move(value));

    std::unique_lock lock(mutex);
    node->next = hashTable[slot];
    hashTable[slot] = node;

    return {&hashTable[slot], &hashTable[hashTable.size()], node};
}
//---------------------------------------------------------------------------
MutexMultiMap::Iterator MutexMultiMap::findFirst(uint32_t key)
// Find the first value with the specified key
{
    auto hash = key;
    auto slot = hash % hashTable.size();

    std::shared_lock lock(mutex);
    auto* node = hashTable[slot];

    while (node && (node->value.first != key))
        node = node->next;

    return node ? Iterator{&hashTable[slot], &hashTable[hashTable.size()], node} : end();
}
//---------------------------------------------------------------------------
MutexMultiMap::Iterator MutexMultiMap::findNext(Iterator& it)
// Find the next value with the specified key
{
    assert(it != end());

    auto key = it.node->value.first;
    auto* node = it.node->next;

    while (node && (node->value.first != key))
        node = node->next;

    return node ? Iterator(it.bucket, it.end, node) : end();
}
//---------------------------------------------------------------------------
MutexMultiMap::Iterator MutexMultiMap::begin()
// Return an iterator pointing to the first element
{
    return {&hashTable[0], &hashTable[hashTable.size()], hashTable[0]};
}
//---------------------------------------------------------------------------
MutexMultiMap::Iterator MutexMultiMap::end()
// Return an iterator pointing to the first element
{
    return {&hashTable[hashTable.size()], &hashTable[hashTable.size()], nullptr};
}
//---------------------------------------------------------------------------
} // namespace hashtable
//---------------------------------------------------------------------------

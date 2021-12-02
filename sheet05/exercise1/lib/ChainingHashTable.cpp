#include "lib/ChainingHashTable.hpp"
#include <cassert>
#include <iostream>
//---------------------------------------------------------------------------
namespace hashtable {
//---------------------------------------------------------------------------
// Construct from key and value
ChainingHashTable::Entry::Entry(int64_t k, GenericValue val) : key(k) {
    value = std::move(val);
}
//---------------------------------------------------------------------------
// Default constructor
ChainingHashTable::Entry::Entry() : key(-1) {}
//---------------------------------------------------------------------------
// Construct from an entry and a chain pointer
ChainingHashTable::EntryChain::EntryChain(std::unique_ptr<Entry> entry, std::unique_ptr<EntryChain> n) {
    e = std::move(entry);
    next = std::move(n);
}
//---------------------------------------------------------------------------
// Construct iterator
ChainingHashTable::iterator::iterator(EntryChain* chain, EntryChain* prev, size_t index, size_t buckets) : chain(chain), prev(prev), index(index), buckets(buckets) {}
//---------------------------------------------------------------------------
// Equals
bool ChainingHashTable::iterator::operator==(const iterator& it1) const {
    return (it1.chain == chain && it1.prev == prev);
}
//---------------------------------------------------------------------------
// Not-Equals
bool ChainingHashTable::iterator::operator!=(const iterator& it1) const {
    return (it1.chain != chain || it1.prev != prev);
}
//---------------------------------------------------------------------------
// Dereference
ChainingHashTable::iterator::reference ChainingHashTable::iterator::operator*() const {
    return *(chain->e.get());
}
//---------------------------------------------------------------------------
// Pointer
ChainingHashTable::iterator::pointer ChainingHashTable::iterator::operator->() const {
    return chain->e.get();
}
//---------------------------------------------------------------------------
// Helper function to iterate through buckets and chains
bool ChainingHashTable::iterator::nextBucket() {
    prev++;
    chain = prev;
    index++;
    if (index == buckets)
        return false;
    return true;
}
//---------------------------------------------------------------------------
// Pre-Increment
ChainingHashTable::iterator& ChainingHashTable::iterator::operator++() {
    assert(chain != nullptr);

    if (!chain->next.get()) {
        if (!nextBucket())
            return *this;

        while (!chain->e.get())
            if (!nextBucket())
                return *this;
    } else {
        chain = chain->next.get();
    }
    return *this;
}
//---------------------------------------------------------------------------
// Post-Increment
ChainingHashTable::iterator ChainingHashTable::iterator::operator++(int) {
    assert(chain != nullptr);

    iterator copy = *this;

    if (!chain->next.get()) {
        if (!nextBucket())
            return copy;

        while (!chain->e.get())
            if (!nextBucket())
                return copy;
    } else {
        chain = chain->next.get();
    }
    return copy;
}
//---------------------------------------------------------------------------
// Move constructor
ChainingHashTable::ChainingHashTable(ChainingHashTable&& other) noexcept
    : htSize(other.htSize), buckets(other.buckets), loadFactor(other.loadFactor), hashTable(std::move(other.hashTable)) {
    other.htSize = 0;
    other.buckets = 0;
    other.loadFactor = 0.0;
    other.hashTable.clear();
}
//---------------------------------------------------------------------------
// Move assignment
ChainingHashTable& ChainingHashTable::operator=(ChainingHashTable&& other) noexcept {
    if (this == &other)
        return *this;

    this->buckets = other.buckets;
    this->htSize = other.htSize;
    this->loadFactor = other.loadFactor;
    this->hashTable = std::move(other.hashTable);
    other.htSize = 0;
    other.buckets = 0;
    other.loadFactor = 0.0;
    other.hashTable.clear();
    return *this;
}
//---------------------------------------------------------------------------
// Private constructor for rehashing
ChainingHashTable::ChainingHashTable(size_t size) : buckets(size) {
    hashTable.resize(size);
}
//---------------------------------------------------------------------------
// Destructor
ChainingHashTable::~ChainingHashTable() {
    for (size_t i = 0; i < buckets; i++) {
        while (hashTable[i].e.get()) {
            erase(hashTable[i].e->key);
        }
    }
}
//---------------------------------------------------------------------------
// Create a new chain
void ChainingHashTable::newEntryChain(unsigned hash, int64_t key, GenericValue&& value) {
    hashTable[hash] = EntryChain(std::make_unique<Entry>(key, std::move(value)), std::make_unique<EntryChain>(std::move(hashTable[hash])));
    return;
}
//---------------------------------------------------------------------------
// Create a new entry
void ChainingHashTable::newEntry(EntryChain& entry, int64_t key, GenericValue&& value) {
    entry.e = std::make_unique<Entry>(key, std::move(value));
    return;
}
//---------------------------------------------------------------------------
// Return whether there exists an entry or not
bool ChainingHashTable::hasEntry(unsigned hash) const {
    if (!hashTable[hash].e)
        return false;
    return true;
}
//---------------------------------------------------------------------------
// Return whether there exists a next entry or not
bool ChainingHashTable::hasNext(unsigned hash) const {
    if (!hashTable[hash].next)
        return false;
    return true;
}
//---------------------------------------------------------------------------
// Return whether the current entry has the key
bool ChainingHashTable::hasKey(unsigned hash, int64_t key) const {
    if (hashTable[hash].e->key == key)
        return true;
    return false;
}
//---------------------------------------------------------------------------
// A raw pointer to the next chain
ChainingHashTable::EntryChain* ChainingHashTable::getNext(unsigned pos) const {
    return hashTable[pos].next.get();
}
//---------------------------------------------------------------------------
// Hash function
unsigned ChainingHashTable::hashFunction(int64_t key) const {
    return key % buckets;
}
//---------------------------------------------------------------------------
// Initialize the table to a given size
void ChainingHashTable::initializeTable() {
    hashTable.resize(16);
    buckets = 16;
    for (size_t i = 0; i < 16; i++) {
        hashTable[i] = EntryChain();
    }
}
//---------------------------------------------------------------------------
// Get the last entry
ChainingHashTable::EntryChain& ChainingHashTable::getLastEntryIndex(int& i) {
    for (; i >= 0; i--) {
        if (hasEntry(i) && hasNext(i)) {
            EntryChain* ptr = getNext(i);
            EntryChain* prev = getNext(i);
            while (ptr) {
                prev = ptr;
                ptr = ptr->next.get();
            }
            return *prev;
        }
    }
    i = static_cast<int>(buckets - 1);
    return hashTable[buckets - 1];
}

//---------------------------------------------------------------------------
// Get the first entry
size_t ChainingHashTable::getFirstEntryIndex() const {
    size_t i{0};
    for (i = 0; i < buckets; i++) {
        if (hasEntry(i))
            break;
    }
    return i;
}
//---------------------------------------------------------------------------
// Rehash function
void ChainingHashTable::rehash(size_t size) {
    ChainingHashTable ht = ChainingHashTable(size);
    for (size_t i = 0; i < buckets; i++) {
        if (hasEntry(i)) {
            ht.insert(std::move(*(hashTable[i].e)));
        }
        EntryChain* ptr = getNext(i);
        while (ptr) {
            ht.insert(std::move(*ptr->e));
            ptr = ptr->next.get();
        }
    }
    *this = std::move(ht);
}
//---------------------------------------------------------------------------
// Iterate through a chain
ChainingHashTable::EntryChain* ChainingHashTable::move(unsigned hash, int64_t key) const {
    EntryChain* ptr = getNext(hash);
    while (ptr) {
        if (ptr->e->key == key) {
            break;
        }
        ptr = ptr->next.get();
    }
    return ptr;
}
//---------------------------------------------------------------------------
// Return the size
size_t ChainingHashTable::size() const {
    return htSize;
}
//---------------------------------------------------------------------------
// Retain whether a key is present
bool ChainingHashTable::contains(int64_t key) const {
    unsigned hash = hashFunction(key);
    if (hasEntry(hash) && hasKey(hash, key)) {
        return true;
    }
    if (hasNext(hash)) {
        EntryChain* ptr = move(hash, key);
        if (ptr != nullptr)
            return true;
    }
    return false;
}
//---------------------------------------------------------------------------
// Insert from key and value
GenericValue& ChainingHashTable::insert(int64_t key, GenericValue&& value) {
    if (hashTable.empty()) {
        initializeTable();
    }

    if (loadFactor >= 0.5) {
        rehash(buckets * 2);
    }
    unsigned hash = hashFunction(key);

    if (!hasEntry(hash)) {
        newEntry(hashTable[hash], key, std::move(value));
        htSize++;
        loadFactor = static_cast<float>(static_cast<float>(htSize) / static_cast<float>(buckets));
        return hashTable[hash].e->value;
    }

    if (!contains(key)) {
        newEntryChain(hash, key, std::move(value));
        htSize++;
        loadFactor = static_cast<float>(static_cast<float>(htSize) / static_cast<float>(buckets));
        return hashTable[hash].e->value;
    }

    if (!hasNext(hash)) {
        newEntry(hashTable[hash], key, std::move(value));
        return hashTable[hash].e->value;
    }

    EntryChain* ptr = move(hash, key);
    assert(ptr != nullptr);
    newEntry(*ptr, key, std::move(value));

    return ptr->e->value;
}
//---------------------------------------------------------------------------
// Overloaded insert
GenericValue& ChainingHashTable::insert(Entry entry) {
    std::unique_ptr<Entry> ptr = std::make_unique<Entry>(entry.key, std::move(entry.value));
    return insert(ptr->key, std::move(ptr->value));
}
//---------------------------------------------------------------------------
// Subscript
GenericValue& ChainingHashTable::operator[](int64_t key) {
    if (hashTable.empty()) {
        return insert(key, GenericValue());
    }

    if (!contains(key))
        return insert(key, GenericValue());

    unsigned hash = hashFunction(key);

    if (hasEntry(hash) && hasKey(hash, key)) {
        return hashTable[hash].e->value;
    }

    EntryChain* ptr = move(hash, key);
    assert(ptr != nullptr);
    return ptr->e->value;
}
//---------------------------------------------------------------------------
// Delete an entry
void ChainingHashTable::erase(int64_t key) {
    if (hashTable.empty()) {
        return;
    }

    if (!contains(key))
        return;

    unsigned hash = hashFunction(key);

    if (hasEntry(hash) && hashTable[hash].e->key == key) {
        if (hasNext(hash)) {
            hashTable[hash].e = std::move(hashTable[hash].next->e);

            if (hashTable[hash].next->next)
                hashTable[hash].next = std::move(hashTable[hash].next->next);
            else
                hashTable[hash].next = nullptr;

            htSize--;
            return;
        }
        hashTable[hash] = EntryChain();
        htSize--;
        return;
    }

    EntryChain* ptr = getNext(hash);
    EntryChain* prev = getNext(hash);
    while (ptr) {
        if (ptr->e->key == key)
            break;
        prev = ptr;
        ptr = ptr->next.get();
    }

    if (prev == ptr) {
        hashTable[hash].next = nullptr;
        htSize--;
        return;
    }

    assert(ptr != nullptr);

    if (ptr->next.get())
        prev->next = std::move(ptr->next);
    else
        prev->next = nullptr;

    htSize--;
}
//---------------------------------------------------------------------------
// Iterator functions
ChainingHashTable::iterator ChainingHashTable::begin() {
    if (hashTable.empty()) {
        initializeTable();
        return iterator(&hashTable[0], &hashTable[0], 0, buckets - 1);
    }

    if (htSize == 0)
        return iterator(&hashTable[0], &hashTable[0], 0, buckets - 1);

    size_t i = getFirstEntryIndex();
    return iterator(&hashTable[i], &hashTable[i], i, buckets - 1);
}
//---------------------------------------------------------------------------
ChainingHashTable::iterator ChainingHashTable::end() {
    if (hashTable.empty()) {
        initializeTable();
        return iterator(&hashTable[0], &hashTable[0], 0, buckets - 1);
    }

    if (htSize == 0)
        return iterator(&hashTable[0], &hashTable[0], 0, buckets - 1);

    int index = static_cast<int>(buckets - 1);
    EntryChain& i = getLastEntryIndex(index);
    return iterator(&i, &i, index, buckets - 1);
}
//---------------------------------------------------------------------------
ChainingHashTable::iterator ChainingHashTable::find(int64_t key) {
    if (hashTable.empty()) {
        initializeTable();
        return iterator(&hashTable[0], &hashTable[0], 0, buckets - 1);
    }

    if (htSize == 0)
        return iterator(&hashTable[0], &hashTable[0], 0, buckets - 1);

    if (contains(key)) {
        unsigned hash = hashFunction(key);
        if (hasEntry(hash) && hasKey(hash, key)) {
            return iterator(&hashTable[hash], &hashTable[hash], hash, buckets - 1);
        }

        if (hasNext(hash)) {
            EntryChain* ptr = move(hash, key);
            assert(ptr != nullptr);
            return iterator(ptr, ptr, hash, buckets - 1);
        }
    }
    int index = static_cast<int>(buckets - 1);
    EntryChain& i = getLastEntryIndex(index);
    return iterator(&i, &i, index, buckets - 1);
}
//---------------------------------------------------------------------------
} // namespace hashtable
//---------------------------------------------------------------------------

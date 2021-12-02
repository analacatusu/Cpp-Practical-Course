#ifndef H_lib_ChainingHashTable
#define H_lib_ChainingHashTable
//---------------------------------------------------------------------------
#include "lib/GenericValue.hpp"
#include <iterator>
#include <memory>
#include <vector>
//---------------------------------------------------------------------------
namespace hashtable {
//---------------------------------------------------------------------------

struct ChainingHashTable {
    /// an entry in the hashtable
    struct Entry {
        /// store the key
        const int64_t key;
        /// store the value
        GenericValue value;
        /// Contructors
        Entry(int64_t k, GenericValue val);
        Entry();
    };
    /// a chain in the hashtable
    struct EntryChain {
        /// pointer to the entry
        std::unique_ptr<Entry> e;
        /// pointer to the next entry
        std::unique_ptr<EntryChain> next;
        /// Constructors
        EntryChain() = default;
        EntryChain(std::unique_ptr<Entry> entry, std::unique_ptr<EntryChain> n);
    };
    /// an iterator through the hashtable
    struct iterator {
        public:
        /// Aliases
        using value_type = Entry;
        using difference_type = std::ptrdiff_t;
        using reference = Entry&;
        using pointer = Entry*;
        using iterator_category = std::forward_iterator_tag;

        /// Constructors
        iterator() = default;
        iterator(EntryChain* chain, EntryChain* prev, size_t index, size_t buckets);
        iterator(const iterator&) = default;
        iterator& operator=(const iterator&) = default;

        /// Operators
        bool operator==(const iterator& it1) const;
        bool operator!=(const iterator& it1) const;
        reference operator*() const;
        pointer operator->() const;
        iterator& operator++();
        iterator operator++(int);

        private:
        /// a chain in the hashtable
        EntryChain* chain;
        /// a previous chain in the hashtable
        EntryChain* prev;
        /// an index of the current bucket
        size_t index;
        /// nr of buckets
        size_t buckets;
        /// function to move through buckets whilst there still exists a next bucket to go to
        bool nextBucket();
    };

    /// Constructors
    ChainingHashTable() = default;
    ChainingHashTable(const ChainingHashTable&) = delete;
    ChainingHashTable& operator=(const ChainingHashTable&) = delete;
    ChainingHashTable(ChainingHashTable&&) noexcept;
    ChainingHashTable& operator=(ChainingHashTable&&) noexcept;
    ~ChainingHashTable();

    /// size of the table
    size_t size() const;
    /// returns if a key is in the table or not
    bool contains(int64_t key) const;
    /// insert into the table from a key and a value
    GenericValue& insert(int64_t key, GenericValue&& value);
    /// insert into the table from an entry
    GenericValue& insert(Entry entry);
    /// Subscript operator
    GenericValue& operator[](int64_t key);
    /// erase an entry from the table
    void erase(int64_t key);

    /// Iterator functions
    iterator begin();
    iterator end();
    iterator find(int64_t key);

    private:
    /// size of the table
    size_t htSize = 0;
    /// nr of buckets
    size_t buckets = 0;
    /// loadfactor of the table
    float loadFactor = 0.0;
    /// storage of the table
    std::vector<EntryChain> hashTable;
    /// private constructor
    ChainingHashTable(size_t size);
    /// create a new chain
    void newEntryChain(unsigned hash, int64_t key, GenericValue&& value);
    /// create a new entry
    void newEntry(EntryChain& entry, int64_t key, GenericValue&& value);
    /// return whether the entry is in the table or not
    bool hasEntry(unsigned hash) const;
    /// return wheter an entry has a next value or not
    bool hasNext(unsigned hash) const;
    /// return whether the current entry has the key
    bool hasKey(unsigned hash, int64_t key) const;
    /// get the next chain
    EntryChain* getNext(unsigned pos) const;
    /// hash function
    unsigned hashFunction(int64_t key) const;
    /// initialize the table
    void initializeTable();
    /// return the index of the last entry
    EntryChain& getLastEntryIndex(int& i);
    /// return index of the first entry
    size_t getFirstEntryIndex() const;
    /// rehash the table
    void rehash(size_t size);
    /// iterate through a chain
    EntryChain* move(unsigned hash, int64_t key) const;
};

//---------------------------------------------------------------------------
} // namespace hashtable
//---------------------------------------------------------------------------
#endif

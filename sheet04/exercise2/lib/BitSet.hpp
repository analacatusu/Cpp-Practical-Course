#ifndef H_lib_BitSet
#define H_lib_BitSet
#include <cstddef>
#include <vector>
//---------------------------------------------------------------------------
namespace bitset {
//---------------------------------------------------------------------------
class BitSet {
    private:
    /// storage of the bitset
    std::vector<std::byte> bitset;
    /// size of the bitset
    size_t bitsetSize;

    public:
    /// Class for referencing one bit in the bitset
    class BitReference {
        private:
        friend class BitSet;
        /// reference to byte
        std::byte* byteRef;
        /// offset within byte
        size_t bitOffset;

        /// Construct from byte reference and offset
        BitReference(std::byte* byteRef, size_t bitOffset);

        public:
        /// Implicit conversion to bool
        operator bool() const;
        /// Assignment
        BitReference& operator=(bool value);
        /// Assignment
        BitReference& operator=(const BitReference& other);
    };

    /// Class for iterating through a bitset
    class BitIterator {
        public:
        /// Aliases
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = bool;
        using reference = BitReference;

        /// Construct default
        BitIterator() = default;
        /// Construct from reference to byte and index
        BitIterator(std::byte* byte, size_t index);

        /// Equals
        bool operator==(const BitIterator& it1) const;
        /// Dereference
        reference operator*() const;
        /// Pre increment
        BitIterator& operator++();
        /// Post increment
        BitIterator operator++(int);
        /// Pre decrement
        BitIterator& operator--();
        /// Post decrement
        BitIterator operator--(int);

        private:
        /// Reference to a byte
        std::byte* byte;
        /// Offset within byte
        size_t index;
        /// Increment the iterator
        void increment();
        /// Decrement the iterator
        void decrement();
    };

    class ConstBitIterator {
        public:
        /// Aliases
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = bool;
        using reference = bool;

        /// Construct default
        ConstBitIterator() = default;
        /// Construct from byte reference and index
        ConstBitIterator(const std::byte* byte, size_t index);

        /// Equals
        bool operator==(const ConstBitIterator& it1) const;
        /// Dereference
        reference operator*() const;
        /// Pre increment
        ConstBitIterator& operator++();
        /// Post increment
        ConstBitIterator operator++(int);
        /// Pre decrement
        ConstBitIterator& operator--();
        /// Post decrement
        ConstBitIterator operator--(int);

        private:
        /// Pointer to a const byte
        const std::byte* byte;
        /// Offset within byte
        size_t index;
        /// Increment iterator
        void increment();
        /// Decrement iterator
        void decrement();
    };

    /// Default constructor
    BitSet();
    /// Explicit constructor from given size
    explicit BitSet(size_t size);

    /// Get size of bitset
    size_t size();
    /// Get cardinality of bitset
    size_t cardinality() const;
    /// Push back a value in the bitset
    void push_back(bool value);
    /// Get first bit
    bool front() const;
    /// Get first bit
    BitReference front();
    /// Get last bit
    bool back() const;
    /// Get last bit
    BitReference back();
    /// Subscript
    bool operator[](size_t pos) const;
    /// Subscript
    BitReference operator[](size_t pos);

    /// Iterator functions
    BitIterator begin();
    BitIterator end();
    ConstBitIterator begin() const;
    ConstBitIterator end() const;
};
//---------------------------------------------------------------------------
} // namespace bitset
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------

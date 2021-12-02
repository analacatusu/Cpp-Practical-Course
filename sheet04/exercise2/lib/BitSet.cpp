#include "lib/BitSet.hpp"
#include <cassert>
//---------------------------------------------------------------------------
namespace bitset {
//---------------------------------------------------------------------------
// Constructor BitReference
BitSet::BitReference::BitReference(std::byte* byteRef, size_t bitOffset)
    : byteRef(byteRef), bitOffset(bitOffset)
// Construct from byte reference and bit offset
{
}
//---------------------------------------------------------------------------
// Operators BitReference
BitSet::BitReference::operator bool() const
// Implicit conversion to bool
{
    const std::byte b{128};
    std::byte copy{*byteRef};
    copy <<= bitOffset;
    copy &= b;
    if (copy == b)
        return true;
    else
        return false;
}
//---------------------------------------------------------------------------
BitSet::BitReference& BitSet::BitReference::operator=(bool value)
// Assignment from bool
{
    std::byte b{128};
    const std::byte b2{0xFF};
    b >>= bitOffset;
    if (not value) {
        b ^= b2;
        *byteRef &= b;
    } else
        *byteRef |= b;
    return *this;
}
//---------------------------------------------------------------------------
BitSet::BitReference& BitSet::BitReference::operator=(const BitSet::BitReference& other)
// Assignment from BitReference
{
    if (this != &other) {
        std::byte otherBit{*(other.byteRef)};
        otherBit <<= other.bitOffset;
        otherBit >>= 7;
        if (std::to_integer<unsigned>(otherBit) == 0) {
            *byteRef &= ~(std::byte{128} >> bitOffset);
        } else {
            *byteRef |= std::byte{128} >> bitOffset;
        }
    }
    return *this;
}
//---------------------------------------------------------------------------
// Constructors BitIterator
BitSet::BitIterator::BitIterator(std::byte* byte, size_t index)
    : byte(byte), index(index)
// Construct from byte pointer and index
{
}
//---------------------------------------------------------------------------
// Helper-functions
void BitSet::BitIterator::increment()
// Increment iterator
{
    if ((index + 1) == 8) {
        index = 0;
        byte++;
    } else {
        index++;
    }
}
//---------------------------------------------------------------------------
void BitSet::BitIterator::decrement()
// Decrement iterator
{
    if (index == 0) {
        index = 7;
        byte--;
    } else {
        index--;
    }
}
//---------------------------------------------------------------------------
// Operators BitIterator
bool BitSet::BitIterator::operator==(const BitSet::BitIterator& it1) const
// Equals
{
    return (it1.byte == byte && it1.index == index);
}
//---------------------------------------------------------------------------
BitSet::BitIterator::reference BitSet::BitIterator::operator*() const
// Dereference
{
    return BitReference(byte, index);
}
//---------------------------------------------------------------------------
BitSet::BitIterator& BitSet::BitIterator::operator++()
// Pre-increment
{
    increment();
    return *this;
}
//---------------------------------------------------------------------------
BitSet::BitIterator BitSet::BitIterator::operator++(int)
// Post-increment
{
    BitSet::BitIterator copy = *this;
    increment();
    return copy;
}
//---------------------------------------------------------------------------
BitSet::BitIterator& BitSet::BitIterator::operator--()
// Pre-decrement
{
    decrement();
    return *this;
}
//---------------------------------------------------------------------------
BitSet::BitIterator BitSet::BitIterator::operator--(int)
// Post-decrement
{
    BitSet::BitIterator copy = *this;
    decrement();
    return copy;
}
//---------------------------------------------------------------------------
// Constructors ConstBitIterator
BitSet::ConstBitIterator::ConstBitIterator(const std::byte* byte, size_t index)
    : byte(byte), index(index)
// Construct from const byte pointer and index
{
}
//---------------------------------------------------------------------------
// Helper-functions
void BitSet::ConstBitIterator::increment()
// Increment iterator
{
    if ((index + 1) == 8) {
        index = 0;
        byte++;
    } else {
        index++;
    }
}
//---------------------------------------------------------------------------
void BitSet::ConstBitIterator::decrement()
// Decrement iterator
{
    if (index == 0) {
        index = 7;
        byte--;
    } else {
        index--;
    }
}
//---------------------------------------------------------------------------
// Operators ConstBitIterator
bool BitSet::ConstBitIterator::operator==(const BitSet::ConstBitIterator& it1) const
// Equals
{
    return (it1.byte == byte && it1.index == index);
}
//---------------------------------------------------------------------------
BitSet::ConstBitIterator::reference BitSet::ConstBitIterator::operator*() const
// Dereference
{
    const std::byte b{128};
    std::byte copy{*byte};
    copy <<= index;
    copy &= b;
    if (copy == b)
        return true;
    else
        return false;
}
//---------------------------------------------------------------------------
BitSet::ConstBitIterator& BitSet::ConstBitIterator::operator++()
// Pre-increment
{
    increment();
    return *this;
}
//---------------------------------------------------------------------------
BitSet::ConstBitIterator BitSet::ConstBitIterator::operator++(int)
// Post-increment
{
    ConstBitIterator copy = *this;
    increment();
    return copy;
}
//---------------------------------------------------------------------------
BitSet::ConstBitIterator& BitSet::ConstBitIterator::operator--()
// Pre-decrement
{
    decrement();
    return *this;
}
//---------------------------------------------------------------------------
BitSet::ConstBitIterator BitSet::ConstBitIterator::operator--(int)
// Post-decrement
{
    ConstBitIterator copy = *this;
    decrement();
    return copy;
}
//---------------------------------------------------------------------------
// Constructors BitSet
BitSet::BitSet()
    : bitset({}), bitsetSize(0)
// Construct empty bitset
{
}
//---------------------------------------------------------------------------
BitSet::BitSet(size_t size)
    : bitsetSize(size)
// Construct from given size
{
    const size_t nrBytes = size / 8;
    const size_t additionalByte = size % 8;

    for (size_t i{0}; i < nrBytes; i++)
        bitset.push_back(std::byte{0});

    if (additionalByte)
        bitset.push_back(std::byte{0});
}
//---------------------------------------------------------------------------
// Member functions BitSet
size_t BitSet::size()
// Return size of bitset
{
    return bitsetSize;
}
//---------------------------------------------------------------------------
size_t BitSet::cardinality() const
// Return nr of true elements in bitset
{
    assert(!bitset.empty());

    size_t cardinal{0};
    size_t nrBytes{0};
    const size_t additionalByte = bitsetSize % 8;

    if (additionalByte)
        nrBytes = bitsetSize / 8 + 1;
    else
        nrBytes = bitsetSize / 8;

    const std::byte b{128};
    std::byte res{0};

    for (size_t i{0}; i < nrBytes; i++) {
        std::byte byte{bitset[i]};
        for (size_t j{0}; j < 8; j++) {
            if ((i * 8 + j) == bitsetSize)
                break;
            res = byte & b;
            if (res == b)
                cardinal++;
            byte <<= 1;
        }
    }
    return cardinal;
}
//---------------------------------------------------------------------------
void BitSet::push_back(bool value)
// Push a value at the end of the bitset
{
    std::byte b{value};
    b <<= 7;
    const size_t additionalByte = bitsetSize % 8;
    if (not additionalByte) {
        bitset.push_back(b);
    } else {
        std::byte byte{bitset[bitset.size() - 1]};
        std::byte copy{byte};
        bitset.pop_back();
        copy <<= additionalByte;
        copy |= b;
        copy >>= additionalByte;
        byte |= copy;
        bitset.push_back(byte);
    }
    bitsetSize++;
}
//---------------------------------------------------------------------------
bool BitSet::front() const
// Value of first bit
{
    assert(!bitset.empty());
    std::byte byte{bitset[0]};
    byte >>= 7;
    const std::byte b{1};
    byte &= b;

    if (byte == b)
        return true;
    else
        return false;
}
//---------------------------------------------------------------------------
BitSet::BitReference BitSet::front()
// Reference to value of first bit
{
    assert(!bitset.empty());
    return BitSet::BitReference(&bitset[0], 0);
}
//---------------------------------------------------------------------------
bool BitSet::back() const
// Value of last bit
{
    assert(!bitset.empty());
    std::byte byte{bitset[bitset.size() - 1]};
    const std::byte b{1};
    const size_t offset = bitsetSize % 8;

    if (offset)
        byte >>= (8 - offset);

    byte &= b;

    if (byte == b)
        return true;
    else
        return false;
}
//---------------------------------------------------------------------------
BitSet::BitReference bitset::BitSet::back()
// Reference to value of last bit
{
    assert(!bitset.empty());
    return BitSet::BitReference(&bitset[bitset.size() - 1], (bitsetSize - 1) % 8);
}
//---------------------------------------------------------------------------
// Operators BitSet
bool BitSet::operator[](size_t pos) const
// Subscript
{
    assert(!bitset.empty());
    assert(pos < bitsetSize);
    const size_t nrBytes = pos / 8;
    const size_t offset = pos % 8;
    std::byte byte{bitset[nrBytes]};
    const std::byte b{128};
    byte <<= offset;
    byte &= b;

    if (byte == b)
        return true;

    return false;
}
//---------------------------------------------------------------------------
BitSet::BitReference BitSet::operator[](size_t pos)
// Subscript
{
    assert(!bitset.empty());
    assert(pos < bitsetSize);
    return BitSet::BitReference(&bitset[pos / 8], pos % 8);
}
//---------------------------------------------------------------------------
// Iterator functions
BitSet::BitIterator BitSet::begin() {
    return BitSet::BitIterator(&bitset[0], 0);
}
//---------------------------------------------------------------------------
BitSet::BitIterator BitSet::end() {
    return BitSet::BitIterator(&bitset[bitset.size() - 1], bitsetSize % 8);
}
//---------------------------------------------------------------------------
BitSet::ConstBitIterator BitSet::begin() const {
    return BitSet::ConstBitIterator(&bitset[0], 0);
}
//---------------------------------------------------------------------------
BitSet::ConstBitIterator BitSet::end() const {
    return BitSet::ConstBitIterator(&bitset[bitset.size() - 1], bitsetSize % 8);
}
//---------------------------------------------------------------------------
} // namespace bitset
//---------------------------------------------------------------------------

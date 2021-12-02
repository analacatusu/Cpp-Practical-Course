#include "lib/BinaryHeap.hpp"
#include <bitset>
#include <cassert>
#include <cmath>
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
namespace binary_heap {
//---------------------------------------------------------------------------
namespace {
//---------------------------------------------------------------------------
unsigned parent(unsigned pos)
// Return the position of the parent or -1 of we are at the root
{
    if (pos > 0)
        return static_cast<unsigned>(floor((pos - 1) / 2));
    else
        return -1;
}
//---------------------------------------------------------------------------
unsigned leftChild(unsigned heapSize, unsigned pos)
// Return the position of the left child or -1 if it doesn't exist.
{
    std::bitset<sizeof(unsigned)* 8> bitsPos = pos;
    assert(not bitsPos.all());
    assert(heapSize > 0);

    if (heapSize >= (2 * pos + 1))
        return 2 * pos + 1;
    else
        return -1;
}
//---------------------------------------------------------------------------
unsigned rightChild(unsigned heapSize, unsigned pos)
// Return the position of the right child or -1 if it doesn't exist.
{
    std::bitset<sizeof(unsigned)* 8> bitsPos = pos;
    assert(not bitsPos.all());
    assert(heapSize > 0);

    if (heapSize >= (2 * pos + 2))
        return 2 * pos + 2;
    else
        return -1;
}
//---------------------------------------------------------------------------
void inorder(ostream& out, unsigned size, unsigned currentPos)
// inorder transversion
{
    std::bitset<sizeof(unsigned)* 8> bitsCurrentPos = currentPos;
    assert(not bitsCurrentPos.all());
    assert(size > 0);

    unsigned left = leftChild(size, currentPos);
    unsigned right = rightChild(size, currentPos);
    std::bitset<sizeof(unsigned)* 8> bitsLeft = left;
    std::bitset<sizeof(unsigned)* 8> bitsRight = right;

    if (bitsLeft.all() and bitsRight.all()) {
        return;
    }

    if (not bitsLeft.all()) {
        out << "\t" << currentPos << " -> " << left << ";\n";
        out.flush();
        inorder(out, size, left);
    }

    if (not bitsRight.all()) {
        out << "\t" << currentPos << " -> " << right << ";\n";
        out.flush();
        inorder(out, size, right);
    }
    return;
}
//---------------------------------------------------------------------------
} // end namespace
//---------------------------------------------------------------------------
void insert(vector<unsigned>& heap, unsigned value)
// Insert a value into the heap
{
    heap.push_back(value);

    if (heap.size() > 1) {
        unsigned currentPos = heap.size() - 1;
        unsigned parentPos = parent(currentPos);
        std::bitset<sizeof(unsigned)* 8> bitsParentPos = parentPos;

        while ((not bitsParentPos.all()) and heap.at(currentPos) > heap.at(parentPos)) {
            std::swap(heap.at(currentPos), heap.at(parentPos));
            currentPos = parentPos;
            parentPos = parent(currentPos);
            bitsParentPos = parentPos;
        }
    }
}
//---------------------------------------------------------------------------
unsigned extract(vector<unsigned>& heap)
// Extract a value from the heap
{
    if (heap.size() == 1) {
        unsigned result = heap.at(0);
        heap.pop_back();
        return result;
    }

    unsigned currentPos = 0;
    std::swap(heap.at(currentPos), heap.at(heap.size() - 1));
    unsigned result = heap.at(heap.size() - 1);
    heap.pop_back();

    if (heap.size() == 1)
        return result;

    unsigned posMax = -1;

    while (posMax != currentPos) {
        std::bitset<sizeof(unsigned)* 8> bitsPosMax = posMax;

        if (not bitsPosMax.all())
            currentPos = posMax;

        unsigned heapSize = heap.size() - 1;
        unsigned left = leftChild(heapSize, currentPos);
        unsigned right = rightChild(heapSize, currentPos);
        std::bitset<sizeof(unsigned)* 8> bitsLeft = left;
        std::bitset<sizeof(unsigned)* 8> bitsRight = right;

        if ((not bitsLeft.all()) and heap.at(currentPos) < heap.at(left)) {
            posMax = left;
            bitsPosMax = posMax;
        }

        if ((not bitsRight.all()) and (not bitsPosMax.all()) and heap.at(right) > heap.at(posMax)) {
            posMax = right;
            bitsPosMax = posMax;
        }

        if (not bitsPosMax.all())
            std::swap(heap.at(currentPos), heap.at(posMax));

        if (bitsPosMax.all())
            break;
    }

    return result;
}
//---------------------------------------------------------------------------
void printDot(ostream& out, const vector<unsigned>& heap)
// Print a dotfile representing the heap
{
    assert(not heap.empty());
    out << "digraph {\n";
    out.flush();

    for (size_t i{0}; i < heap.size(); i++) {
        out << "\t" << i << " [label=\"" << heap.at(i) << "\"];\n";
        out.flush();
    }

    unsigned heapSize = heap.size() - 1;
    inorder(out, heapSize, 0);
    out << "}\n";
    out.flush();
}
//---------------------------------------------------------------------------
} // namespace binary_heap
//---------------------------------------------------------------------------

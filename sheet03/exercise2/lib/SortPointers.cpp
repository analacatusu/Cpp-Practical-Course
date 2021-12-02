#include "lib/SortPointers.hpp"
#include <cassert>
#include <vector>
// Quicksort implementation taken and updated from: https://www.geeksforgeeks.org/cpp-program-for-quicksort/
// Mergesort implementation taken and updated from: https://www.geeksforgeeks.org/merge-sort/
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
namespace sort_pointers {
//---------------------------------------------------------------------------
namespace {
//---------------------------------------------------------------------------
void swaping(const unsigned*** a, const unsigned*** b)
// Swap two numbers
{
    assert(a != nullptr);
    assert(b != nullptr);

    const unsigned* tmp = **a;
    **a = **b;
    **b = tmp;
}
//---------------------------------------------------------------------------
const unsigned** partition(const unsigned** begin, const unsigned** end)
// Partition the array based on last element pivot
{
    assert(begin != nullptr);
    assert((end - 1) != nullptr);
    assert(begin <= (end - 1));

    const unsigned** pivot = (end - 1);
    const unsigned** i = (begin - 1);

    for (const unsigned** j = begin; j <= (end - 2); j++) {
        if (**j <= **pivot) {
            i++;
            swaping(&i, &j);
        }
    }
    i++;
    swaping(&i, &pivot);
    return i;
}
//---------------------------------------------------------------------------
void createCopyArrays(std::vector<const unsigned*>& left, std::vector<const unsigned*>& right, const unsigned endLeft, const unsigned endRight, const unsigned** begin, const unsigned** middle)
// Create two copy arrays
{
    assert(begin != nullptr);
    assert(middle != nullptr);
    assert((begin + endLeft - 1) != nullptr);
    assert((middle + endRight) != nullptr);

    size_t i = 0;
    size_t j = 0;

    while (i < endLeft || j < endRight) {
        if (i < endLeft) {
            left.push_back(*(begin + i));
            i++;
        }
        if (j < endRight) {
            right.push_back(*(middle + 1 + j));
            j++;
        }
    }
}
//---------------------------------------------------------------------------
void copyPointer(const unsigned* value, const unsigned*** begin)
// Copy a pointer to a value
{
    assert(begin != nullptr);
    assert(value != nullptr);

    const unsigned**** k = &begin;
    ***k = value;
    (*begin)++;
}
//---------------------------------------------------------------------------
void copyFromArrays(std::vector<const unsigned*>& left, std::vector<const unsigned*>& right, const unsigned endLeft, const unsigned endRight, const unsigned** begin)
// Copy ordered pointers from the two helper arrays
{
    assert(begin != nullptr);

    size_t i = 0;
    size_t j = 0;

    //Copy from both arrays
    while (i < endLeft && j < endRight) {
        if (*left.at(i) <= *right.at(j)) {
            copyPointer(left.at(i), &begin);
            i++;
        } else {
            copyPointer(right.at(j), &begin);
            j++;
        }
    }

    //Copy if there is anything remaining in the left array
    while (i < endLeft) {
        copyPointer(left.at(i), &begin);
        i++;
    }

    //Copy if there is anything remaining in the right array
    while (j < endRight) {
        copyPointer(right.at(j), &begin);
        j++;
    }
}
//---------------------------------------------------------------------------
void merge(const unsigned** begin, const unsigned** middle, const unsigned** end)
// Merge ranges of pointers [begin; middle] and (middle; end)
{
    assert(begin != nullptr);
    assert((end - 1) != nullptr);
    assert(middle != nullptr);
    assert(middle >= begin);
    assert(middle <= (end - 1));

    const unsigned endLeft = middle - begin + 1;
    const unsigned endRight = end - 1 - middle;
    std::vector<const unsigned*> left;
    std::vector<const unsigned*> right;

    createCopyArrays(left, right, endLeft, endRight, begin, middle);
    copyFromArrays(left, right, endLeft, endRight, begin);
}
//---------------------------------------------------------------------------
} //end namespace
//---------------------------------------------------------------------------
void quicksort(const unsigned** begin, const unsigned** end)
// Sort the range of pointers [begin; end)
{
    assert(begin != nullptr);
    assert((end - 1) != nullptr);

    if (begin < (end - 1)) {
        const unsigned** p = partition(begin, end);

        quicksort(begin, p);
        quicksort((p + 1), end);
    }
}
//---------------------------------------------------------------------------
void mergesort(const unsigned** begin, const unsigned** end)
// Sort the range of pointers [begin; end)
{
    assert(begin != nullptr);
    assert((end - 1) != nullptr);

    if (begin >= (end - 1)) {
        return;
    }

    const unsigned** middle = begin + (end - 1 - begin) / 2;

    mergesort(begin, middle + 1);
    mergesort(middle + 1, end);
    merge(begin, middle, end);
}
//---------------------------------------------------------------------------
} // namespace sort_pointers
//---------------------------------------------------------------------------

#include "lib/BinaryHeap.hpp"
#include <bitset>
#include <fstream>
#include <iostream>
//---------------------------------------------------------------------------
using namespace std;
using namespace binary_heap;
//---------------------------------------------------------------------------
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "USAGE: " << argv[0] << " file" << endl;
        return 1;
    }

    ofstream out(argv[1]);

    unsigned value;
    vector<unsigned> heap;
    std::cout << "Please insert a number into the heap: ";
    std::cin >> value;
    std::bitset<sizeof(unsigned)* 8> valueBits = value;

    while (not valueBits.all()) {
        binary_heap::insert(heap, value);
        std::cout << "Please insert a number into the heap: ";
        std::cin >> value;
        valueBits = value;
    }

    binary_heap::printDot(out, heap);

    while (not heap.empty()) {
        unsigned result;
        result = binary_heap::extract(heap);
        std::cout << result << " ";
    }
    std::cout << std::endl;

    return 0;
}
//---------------------------------------------------------------------------

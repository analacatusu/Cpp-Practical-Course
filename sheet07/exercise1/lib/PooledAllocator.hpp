#ifndef H_lib_PooledAllocator
#define H_lib_PooledAllocator
#include <cstdlib>

using namespace std;
//---------------------------------------------------------------------------
namespace pool {
template <class T>
/// Class that allocates storage for objects of type T in chunks
class PooledAllocator {
    public:
    /// Constructor
    PooledAllocator() = default;
    /// Deleted copy constructor
    PooledAllocator(const PooledAllocator&) = delete;
    /// Deleted copy assignment
    PooledAllocator& operator=(const PooledAllocator&) = delete;
    /// Move constructor
    PooledAllocator(PooledAllocator&&) noexcept;
    /// Move assignment
    PooledAllocator& operator=(PooledAllocator&&) noexcept;
    /// Destructor
    ~PooledAllocator();
    /// Allocate storage
    T* allocate();
    /// Deallocate storage
    void deallocate(T*);
    /// Rebind the allocator to a type U
    template <class U>
    using rebind = PooledAllocator<U>;

    private:
    /// Struct to manage chunks of memory in a linked list
    struct Chunk {
        Chunk* next = nullptr;
    };
    /// Current size of a chunk
    size_t sizeChunk = 1;
    /// Storage of the current element
    T* currentElement = nullptr;
    /// Storage of the last element that can be allocated in the current chunk
    T* endElement = nullptr;
    /// Storage of the previous element in the current chunk
    T* prevElement = nullptr;
    /// Storage of the current chunk
    Chunk* currentChunk = nullptr;
    /// Storage of the head of the linked list of chunks
    Chunk* head = nullptr;
    /// Helper function to allocate a new chunk of memory
    bool allocateNewChunk();
    /// Helper function to insert a chunk in the chunk list
    void insertInChunkList();
    /// Helper function to deallocate all the chunks in the list
    void clear();
};
//---------------------------------------------------------------------------
// Helper function to deallocate all the chunks in the list
template <class T>
void PooledAllocator<T>::clear() {
    currentElement = nullptr;
    prevElement = nullptr;
    currentChunk = nullptr;
    endElement = nullptr;

    Chunk* del;
    while (head != nullptr) {
        del = head;
        head = head->next;
        del->next = nullptr;
        std::free(del);
    }
}
//---------------------------------------------------------------------------
// Helper function to allocate a new chunk of memory
template <class T>
bool PooledAllocator<T>::allocateNewChunk() {
    if (currentElement == endElement) {
        size_t allocSize = sizeChunk * sizeof(T) + sizeof(void*);
        void* ptr = std::malloc(allocSize);
        currentChunk = static_cast<Chunk*>(ptr);
        currentChunk->next = nullptr;
        currentElement = static_cast<T*>(ptr);
        endElement = currentElement + sizeChunk;
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
// Helper function that inserts a chunk at the beginning of the chunk list
template <class T>
void PooledAllocator<T>::insertInChunkList() {
    if (head != nullptr) {
        currentChunk->next = head;
        head = currentChunk;
    } else {
        head = currentChunk;
    }
}
//---------------------------------------------------------------------------
// Allocate memory
template <class T>
T* PooledAllocator<T>::allocate() {
    if (allocateNewChunk()) {
        sizeChunk = 2 * sizeChunk;
        insertInChunkList();
    }

    prevElement = currentElement;
    currentElement++;

    return prevElement;
}
//---------------------------------------------------------------------------
// Deallocate memory if the ptr argument points at the allocated storage of the last element
template <class T>
void PooledAllocator<T>::deallocate(T* ptr) {
    if (ptr == prevElement) {
        currentElement = prevElement;
    }
}
//---------------------------------------------------------------------------
// Destructor
template <class T>
PooledAllocator<T>::~PooledAllocator() {
    clear();
}
//---------------------------------------------------------------------------
// Move constructor
template <class T>
PooledAllocator<T>::PooledAllocator(PooledAllocator<T>&& other) noexcept
    : sizeChunk(other.sizeChunk), currentElement(other.currentElement), endElement(other.endElement), prevElement(other.prevElement), currentChunk(other.currentChunk), head(other.head) {
    other.sizeChunk = 0;
    other.currentElement = nullptr;
    other.endElement = nullptr;
    other.prevElement = nullptr;
    other.currentChunk = nullptr;
    other.head = nullptr;
}
//---------------------------------------------------------------------------
// Move assignment
template <class T>
PooledAllocator<T>& PooledAllocator<T>::operator=(PooledAllocator<T>&& other) noexcept {
    if (this == &other)
        return *this;

    clear();

    this->sizeChunk = other.sizeChunk;
    this->currentElement = other.currentElement;
    this->endElement = other.endElement;
    this->prevElement = other.prevElement;
    this->currentChunk = other.currentChunk;
    this->head = other.head;

    other.sizeChunk = 0;
    other.currentElement = nullptr;
    other.endElement = nullptr;
    other.prevElement = nullptr;
    other.currentChunk = nullptr;
    other.head = nullptr;

    return *this;
}
//---------------------------------------------------------------------------
} // namespace pool
//---------------------------------------------------------------------------
#endif

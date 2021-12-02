#ifndef H_lib_MallocAllocator
#define H_lib_MallocAllocator
#include <cstdlib>
//---------------------------------------------------------------------------
namespace pool {

template <class T>
/// Class that allocates storage for one object of type T
class MallocAllocator {
    public:
    /// Constructor
    MallocAllocator() = default;
    /// Destructor
    ~MallocAllocator() = default;
    /// Deleted copy constructor
    MallocAllocator(const MallocAllocator&) = delete;
    /// Deleted copy assignment
    MallocAllocator& operator=(const MallocAllocator&) = delete;
    /// Move constructor
    MallocAllocator(MallocAllocator&&) noexcept = default;
    /// Move assignment
    MallocAllocator& operator=(MallocAllocator&&) noexcept = default;
    /// Allocate storage
    T* allocate();
    /// Deallocate storage
    void deallocate(T*);
    /// Rebind the allocator to a type U
    template <class U>
    using rebind = MallocAllocator<U>;
};
//---------------------------------------------------------------------------
// Allocate storage
template <class T>
T* MallocAllocator<T>::allocate() {
    T* ret = static_cast<T*>(std::malloc(sizeof(T)));
    return ret;
}
//---------------------------------------------------------------------------
// Deallocate storage
template <class T>
void MallocAllocator<T>::deallocate(T* p) {
    std::free(p);
}
//---------------------------------------------------------------------------
} // namespace pool
//---------------------------------------------------------------------------
#endif

#ifndef H_lib_Find
#define H_lib_Find
#include "lib/List.hpp"
//---------------------------------------------------------------------------
namespace pool {
// Generic find function for containers from the standard library that support iteration
template <class C, class T>
typename C::value_type* find(C& container, const T& value) requires std::equality_comparable_with<typename C::value_type, T> {
    size_t i = 0;
    for (auto val : container) {
        if (val == value) {
            return &container[i];
        }
        i++;
    }
    return nullptr;
}

// Generic find function for the List class
template <class T, class Allocator, class R>
T* find(List<T, Allocator>& list, const R& value) requires std::equality_comparable_with<T, R>;

} // namespace pool
//---------------------------------------------------------------------------
#endif

#ifndef H_lib_List
#define H_lib_List
#include "lib/MallocAllocator.hpp"
#include <concepts>
#include <new>
//---------------------------------------------------------------------------
namespace pool {
template <class T, class Allocator>
/// A doubly-linked list
class List {
    public:
    /// Construct an empty list
    List() = default;
    /// Copy Constructor
    List(const List&) requires std::copy_constructible<T>;
    /// Copy Assignment
    List& operator=(const List&) requires std::copy_constructible<T>;
    /// Move constructor
    List(List&&) noexcept;
    /// Move assignment
    List& operator=(List&&) noexcept;
    /// Destructor
    ~List();
    /// Return the nr of elements in the list
    size_t size() const;
    /// Insert an element at the end of the list
    void insert(const T& value) requires std::copy_constructible<T>;
    /// Delete an element from the list
    void erase(const T& value) requires std::equality_comparable<T>;
    /// Friend template function find
    template <class T1, class Allocator1, class R>
    friend T1* find(List<T1, Allocator1>& list, const R& value) requires std::equality_comparable_with<T1, R>;
    /// Delete and deallocate storage for every element in the list
    void clear();

    private:
    /// A struct to create a doubly linked list with a pointer to the element and the storage
    struct Node {
        T* element;
        T* storage;
        Node* prev;
        Node* next;
    };
    /// Alias allocator for the nodes
    using NodeAllocator = typename MallocAllocator<T>::template rebind<Node>;
    /// Helper function to delete the head
    bool eraseHead(const T& value);
    /// Helper function to delete the tail
    bool eraseTail(const T& value);
    /// Helper function to copy from another list into this list
    void copyFromOtherList(const List<T, Allocator>& other);
    /// Storage of the head
    Node* head = nullptr;
    /// Storage of the tail
    Node* tail = nullptr;
    /// Number of elements
    size_t nrElements = 0;
    /// Allocator of the elements
    Allocator allocator;
    /// Allocator of the nodes
    NodeAllocator nodeAllocator;
};
//---------------------------------------------------------------------------
// Function to find an element in a list
template <class T1, class Allocator1, class R>
T1* find(List<T1, Allocator1>& list, const R& value) requires std::equality_comparable_with<T1, R> {
    typename List<T1, Allocator1>::Node* node = list.head;
    while (node != nullptr) {
        if (*node->element == value) {
            return node->element;
        }
        node = node->next;
    }
    return nullptr;
}
//---------------------------------------------------------------------------
// Delete and deallocate every element in the list
template <class T, class Allocator>
void List<T, Allocator>::clear() {
    Node* del;
    while (head != nullptr) {
        del = head;
        head = head->next;
        del->next = nullptr;
        del->element->~T();
        allocator.deallocate(del->storage);
        nodeAllocator.deallocate(del);
    }
    tail = nullptr;
    nrElements = 0;
}
//---------------------------------------------------------------------------
// Destructor
template <class T, class Allocator>
List<T, Allocator>::~List() {
    clear();
}
//---------------------------------------------------------------------------
// Copy from another list into this list
template <class T, class Allocator>
void List<T, Allocator>::copyFromOtherList(const List<T, Allocator>& other) {
    Node* otherNode = other.head;

    while (otherNode != nullptr) {
        insert(*otherNode->element);
        otherNode = otherNode->next;
    }
}
//---------------------------------------------------------------------------
// Copy constructor
template <class T, class Allocator>
List<T, Allocator>::List(const List<T, Allocator>& other) requires std::copy_constructible<T> {
    if (other.head == nullptr) {
        return;
    }

    copyFromOtherList(other);
}
//---------------------------------------------------------------------------
// Copy assignment
template <class T, class Allocator>
List<T, Allocator>& List<T, Allocator>::operator=(const List<T, Allocator>& other) requires std::copy_constructible<T> {
    if (this == &other) {
        return *this;
    }

    clear();

    if (other.head == nullptr) {
        return *this;
    }

    copyFromOtherList(other);

    return *this;
}
//---------------------------------------------------------------------------
// Move constructor
template <class T, class Allocator>
List<T, Allocator>::List(List<T, Allocator>&& other) noexcept : head(other.head), tail(other.tail), nrElements(other.nrElements), allocator(std::move(other.allocator)), nodeAllocator(std::move(other.nodeAllocator)) {
    other.head = nullptr;
    other.tail = nullptr;
    other.nrElements = 0;
}
//---------------------------------------------------------------------------
// Move assignment
template <class T, class Allocator>
List<T, Allocator>& List<T, Allocator>::operator=(List<T, Allocator>&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    clear();

    head = other.head;
    tail = other.tail;
    allocator = std::move(other.allocator);
    nodeAllocator = std::move(other.nodeAllocator);
    nrElements = other.nrElements;

    other.head = nullptr;
    other.tail = nullptr;
    other.nrElements = 0;

    return *this;
}
//---------------------------------------------------------------------------
// Return the nr of elements in the list
template <class T, class Allocator>
size_t List<T, Allocator>::size() const {
    return nrElements;
}
//---------------------------------------------------------------------------
// Insert an element at the end of the list
template <class T, class Allocator>
void List<T, Allocator>::insert(const T& value) requires std::copy_constructible<T> {
    Node* node = nodeAllocator.allocate();
    T* storage = allocator.allocate();
    T* element = new (storage) T(value);
    node->next = nullptr;
    node->element = element;
    node->storage = storage;

    if (!tail) {
        node->prev = nullptr;
        head = node;
        tail = node;
        nrElements++;
        return;
    }

    if (nrElements == 1) {
        node->prev = head;
        head->next = node;
    } else {
        node->prev = tail;
    }

    tail->next = node;
    tail = node;
    nrElements++;
}
//---------------------------------------------------------------------------
// Delete the head of the list
template <class T, class Allocator>
bool List<T, Allocator>::eraseHead(const T& value) {
    if (*head->element == value) {
        head->element->~T();
        allocator.deallocate(head->storage);
        Node* del = head;

        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }

        nodeAllocator.deallocate(del);
        nrElements--;
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
// Delete the tail of the list
template <class T, class Allocator>
bool List<T, Allocator>::eraseTail(const T& value) {
    if (*tail->element == value) {
        tail->element->~T();
        allocator.deallocate(tail->storage);
        Node* del = tail;
        tail = tail->prev;
        nodeAllocator.deallocate(del);
        nrElements--;
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
// Delete an element from the list
template <class T, class Allocator>
void List<T, Allocator>::erase(const T& value) requires std::equality_comparable<T> {
    if (nrElements == 0)
        return;

    if (eraseHead(value)) {
        return;
    }

    if (eraseTail(value)) {
        return;
    }

    Node* del = head;
    while (del->next != nullptr) {
        if (*del->element == value) {
            del->prev->next = del->next;
            del->next->prev = del->prev;
            del->element->~T();
            allocator.deallocate(del->storage);
            del->next = nullptr;
            del->prev = nullptr;
            nodeAllocator.deallocate(del);
            nrElements--;
            return;
        }
        del = del->next;
    }
}
//---------------------------------------------------------------------------
} // namespace pool
//---------------------------------------------------------------------------
#endif

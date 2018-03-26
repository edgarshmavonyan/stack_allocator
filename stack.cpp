#include "stack.h"
#include "cassert"

template<class T>
AllocationArea<T>::AllocationArea() : _cur(reinterpret_cast<pointer>(new char[MAX_ALLOCATION])), _available(MAX_ALLOCATION), _nextArea(nullptr) {}

template<class T>
bool AllocationArea<T>::_checkAvailability(size_t requiredMemory) {
    return MAX_ALLOCATION >= requiredMemory;
}

template<class T>
typename AllocationArea<T>::pointer AllocationArea<T>::_allocate(size_t requiredMemory) {
    assert(!_checkAvailability(requiredMemory));
    _cur += requiredMemory;
    return _cur - requiredMemory;
}

template<class T>
AllocationArea<T>::~AllocationArea() {
    delete[] (_cur + _available - MAX_ALLOCATION);

}

template<class T>
typename StackAllocator<T>::area_pointer StackAllocator<T>::_create_node() {
    return _cur->_nextArea = new area();
}

template <class T>
typename StackAllocator<T>::pointer StackAllocator<T>::allocate(size_t elementNumber) {
    size_t requiredMemory = elementNumber * sizeof(T);
    if (!_cur->_checkAvailability(requiredMemory))
        _create_node();
    return _cur->_allocate(requiredMemory);
}

template<class T>
StackAllocator<T>::StackAllocator(): _start(new AllocationArea<T>()), _cur(_start) {}

template<class T>
StackAllocator<T>::~StackAllocator() {
    area_pointer cur;
    area_pointer next = _start->_nextArea;
    delete _start;
    while (next != nullptr) {
        cur = next;
        next = next->_nextArea;
        delete cur;
    }
}
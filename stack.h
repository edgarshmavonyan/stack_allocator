#include <iostream>
#include <cassert>


class AllocationArea {
private:
    template<class>
    friend class StackAllocator;
//    friend class StackAllocator<T>;

//    typedef T value_type;
//    typedef T* pointer;
//    typedef const T* const_pointer;
//    typedef T& reference;
//    typedef const T& const_reference;

    static const size_t MAX_ALLOCATION = 1000000;

//    pointer _cur;
    char* _cur;
    size_t _available;
//    AllocationArea<T>* _nextArea;
    AllocationArea* _nextArea;

    bool _checkAvailability(size_t requiredMemory);

//    pointer _allocate(size_t requiredMemory);
    char* _allocate(size_t requiredMemory);

public:
    AllocationArea();

    ~AllocationArea();
};

template<class T>
class StackAllocator {
private:
//    typedef AllocationArea<T>* area_pointer;
//    typedef AllocationArea<T> area;
    typedef AllocationArea* area_pointer;
    typedef AllocationArea area;

    area_pointer _start;
    area_pointer _cur;

    area_pointer _createNode();

public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;

    StackAllocator();

    ~StackAllocator();

    template<typename T1>
    struct rebind {
        typedef StackAllocator<T1> other;
    };

    pointer allocate(size_t requiredMemory);

    void deallocate(pointer ptr, size_t size) {}

//    void construct(pointer ptr, const_reference value);
};

//template class StackAllocator<int>;


//template<class T>
//AllocationArea<T>::AllocationArea() : _cur((pointer) ::operator new(MAX_ALLOCATION)), _available(MAX_ALLOCATION), _nextArea(nullptr) {}

AllocationArea::AllocationArea() : _cur(new char[MAX_ALLOCATION]), _available(MAX_ALLOCATION), _nextArea(nullptr) {}

//template<class T>
//bool AllocationArea<T>::_checkAvailability(size_t requiredMemory) {
//    return _available >= requiredMemory;
//}

bool AllocationArea::_checkAvailability(size_t requiredMemory) {
    return _available >= requiredMemory;
}

/**
template<class T>
typename AllocationArea<T>::pointer AllocationArea<T>::_allocate(size_t requiredMemory) {
    assert(_checkAvailability(requiredMemory));
    _available -= requiredMemory;
    _cur += requiredMemory;
    return _cur - requiredMemory;
}
 **/

char* AllocationArea::_allocate(size_t requiredMemory) {
    assert(_checkAvailability(requiredMemory));
    _available -= requiredMemory;
    _cur += requiredMemory;
    return _cur - requiredMemory;
}


//template<class T>
//AllocationArea<T>::~AllocationArea() {
//    delete[] (_cur + _available - MAX_ALLOCATION);
//}

template<class T>
typename StackAllocator<T>::area_pointer StackAllocator<T>::_createNode() {
    return _cur = _cur->_nextArea = new area();
}

template <class T>
typename StackAllocator<T>::pointer StackAllocator<T>::allocate(size_t requiredMemory) {
    requiredMemory *= sizeof(T);
    if (!_cur->_checkAvailability(requiredMemory))
        _createNode();
//    return _cur->_allocate(requiredMemory);
    return reinterpret_cast<pointer>(_cur->_allocate(requiredMemory));
}


AllocationArea::~AllocationArea() {
    delete [] (_cur + _available - MAX_ALLOCATION);
}


//template<class T>
//void StackAllocator<T>::construct(pointer ptr, const_reference value) {
//    new((void*)ptr) value_type(value);
//}

//template<class T>
//StackAllocator<T>::StackAllocator(): _start(new AllocationArea<T>()), _cur(_start) {}

template<class T>
StackAllocator<T>::StackAllocator() : _start(new AllocationArea()), _cur(_start) {}

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
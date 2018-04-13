#include <iostream>
#include <cassert>
#include <list>

// Definition

class AllocationArea {
private:
    template<class>
    friend class StackAllocator;

    static const size_t MAX_ALLOCATION = 1048576;

    char* _cur;
    size_t _available;
    AllocationArea* _nextArea;

    bool _checkAvailability(size_t requiredMemory);

    char* _allocate(size_t requiredMemory);

public:
    AllocationArea();

    ~AllocationArea();
};

template<class T>
class StackAllocator {
private:

    typedef AllocationArea* area_pointer;
    typedef AllocationArea area;

    size_t _areaCount;
    area_pointer _start;
    area_pointer _cur;

    area_pointer _createNode();

public:
    typedef size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;

    StackAllocator();

    StackAllocator(const StackAllocator&) {}

    template<class U>
    StackAllocator(const StackAllocator<U>&);

    ~StackAllocator();

    template<class U>
    struct rebind {
        typedef StackAllocator<U> other;
    };

    pointer allocate(size_t requiredMemory);

    void deallocate(pointer ptr, size_t size) {}

    /*
    template<class U>
    void destroy(U* ptr);


    template<class U, class... Args>
    void construct(U* ptr, Args&&... args) {
        ::new((void *)ptr) U(std::forward<Args>(args)...);
    }
    */
};

//Implementation

AllocationArea::AllocationArea() : _cur(new char[MAX_ALLOCATION]), _available(MAX_ALLOCATION), _nextArea(nullptr) {}

bool AllocationArea::_checkAvailability(size_t requiredMemory) {
    return _available >= requiredMemory;
}

char* AllocationArea::_allocate(size_t requiredMemory) {
    assert(_checkAvailability(requiredMemory));
    _available -= requiredMemory;
    _cur += requiredMemory;
    return _cur - requiredMemory;
}

template<class T>
typename StackAllocator<T>::area_pointer StackAllocator<T>::_createNode() {
    _areaCount++;
    return _cur = _cur->_nextArea = new area();
}

template <class T>
typename StackAllocator<T>::pointer StackAllocator<T>::allocate(size_t requiredMemory) {
    requiredMemory *= sizeof(T);
    if (!_cur->_checkAvailability(requiredMemory))
        _createNode();
    return reinterpret_cast<pointer>(_cur->_allocate(requiredMemory));
}


AllocationArea::~AllocationArea() {
    delete [] (_cur + _available - MAX_ALLOCATION);
}

template<class T>
StackAllocator<T>::StackAllocator() : _areaCount(1), _start(new AllocationArea()), _cur(_start) {}


// may be we need to change it
template<class T, class U>
StackAllocator<T>::StackAllocator(const StackAllocator<U>& other) : 
        _areaCount(1), _start(StackAllocator<T>()), _cur(_start) {}

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

template<class T>
template<class U>
void StackAllocator<T>::destroy(U *ptr) {
    ptr->~U();
}
#include "stackAllocator.h"

template <class T>
StackAllocator<T>::pointer StackAllocator<T>::allocate(size_t elementsNumber) {
    return reinterpret_cast<pointer>(_chain->allocate(elementsNumber * sizeof(T)));
}

template<class T>
StackAllocator<T>::StackAllocator() : _chain(std::make_shared<StackChain>()) {}

template<class T, class U>
StackAllocator<T>::StackAllocator(const StackAllocator<U>& other) :
        _chain(other._chain) {}

template<typename T>
StackAllocator<T>::StackAllocator(StackChain &stackChain): _chain(){}
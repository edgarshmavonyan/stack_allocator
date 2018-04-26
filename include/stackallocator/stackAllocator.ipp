#include "stackAllocator.h"

template <class T>
typename StackAllocator<T>::pointer
StackAllocator<T>::allocate(size_t elementsNumber) {
    return reinterpret_cast<pointer>(_chain->allocate(elementsNumber * sizeof(T)));
}

template<class T>
StackAllocator<T>::StackAllocator() : _chain(std::make_shared<StackChain>()) {}

template<class T>
template<class U>
StackAllocator<T>::StackAllocator(const StackAllocator<U>& other) :
        _chain(other._chain) {}

template<class T>
StackAllocator<T>::StackAllocator(StackChain &stackChain): _chain() {}

template<class T1, class T2>
bool operator==(const StackAllocator<T1>& first, const StackAllocator<T2>& other) {
    return first._chain == other._chain;
}

template<class T1, class T2>
bool operator!=(const StackAllocator<T1>& first, const StackAllocator<T2>& other) {
    return first._chain != other._chain;
}
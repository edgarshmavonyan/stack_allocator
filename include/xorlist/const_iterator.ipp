#include "const_iterator.h"

template<typename T>
Const_XorListIterator<T>::Const_XorListIterator() : _current(0), _previous(0) {}

template<typename T>
typename Const_XorListIterator<T>::calc_type
Const_XorListIterator<T>::_cast(const node_pointer& ptr) const {
    return reinterpret_cast<calc_type>(ptr);
}

template<typename T>
typename Const_XorListIterator<T>::node_pointer
Const_XorListIterator<T>::_cast(const calc_type& calc_ptr) const {
    return reinterpret_cast<node_pointer>(calc_ptr);
}

template<typename T>
Const_XorListIterator<T>::Const_XorListIterator(node_pointer curr, node_pointer prev) :
        _current(_cast(curr)), _previous(_cast(prev)) {}

template<typename T>
Const_XorListIterator<T>::Const_XorListIterator(const iterator& other) :
        _current(other._current), _previous(other._previous) {}

template<typename T>
Const_XorListIterator<T>& Const_XorListIterator<T>::operator=(const iterator& other) {
    _current = other._current; _previous = other._previous;
    return *this;
}

template<typename T>
typename Const_XorListIterator<T>::self&
Const_XorListIterator<T>::operator++() {
    calc_type next = _cast(_current)->_neighboursXor ^ _previous;
    _previous = _current;
    _current = next;
}

template<typename T>
typename Const_XorListIterator<T>::self
Const_XorListIterator<T>::operator++(int) {
    self temp = *this;
    operator++();
    return temp;
}

template<typename T>
typename Const_XorListIterator<T>::self&
Const_XorListIterator<T>::operator--() {
    calc_type prev = _cast(_previous)->_neighboursXor ^ _current;
    _current = _previous;
    _previous = prev;
}

template<typename T>
typename Const_XorListIterator<T>::self
Const_XorListIterator<T>::operator--(int) {
    self temp = *this;
    operator--();
    return temp;
}

template<typename T>
typename Const_XorListIterator<T>::reference
Const_XorListIterator<T>::operator*() const {
    return _cast(_current)->_value;
}

template<typename T>
typename Const_XorListIterator<T>::pointer
Const_XorListIterator<T>::operator->() const {
    return &(operator*());
}

template<typename U>
bool operator==(const Const_XorListIterator<U>& first, const Const_XorListIterator<U>& other) {
    return first._current == other._current && first._previous == other._previous;
}

template<typename U>
bool operator!=(const Const_XorListIterator<U>& first, const Const_XorListIterator<U>& other) {
    return !(first == other);
}

template<typename T>
typename Const_XorListIterator<T>::node_pointer
inline Const_XorListIterator<T>::_getNode() const {
    return _cast(_current);
}

template<typename T>
typename Const_XorListIterator<T>::node_pointer
inline Const_XorListIterator<T>::_getPrevNode() const {
    return _cast(_previous);
}

template<typename T>
typename Const_XorListIterator<T>::node_pointer
inline Const_XorListIterator<T>::_getNextNode() const {
    return _cast(_cast(_current)->_neighboursXor ^ _previous);
}
#include "iterator.h"

template<typename T>
XorListIterator<T>::XorListIterator() : _current(0), _previous(0) {}

template<typename T>
typename XorListIterator<T>::calc_type
XorListIterator<T>::_cast(const node_pointer &ptr) {
    return reinterpret_cast<calc_type>(ptr);
}

template<typename T>
typename XorListIterator<T>::node_pointer
XorListIterator<T>::_cast(const calc_type &calc_ptr) {
    return reinterpret_cast<node_pointer>(calc_ptr);
}


template<typename T>
XorListIterator<T>::XorListIterator(node_pointer ptr):
        _current(_cast(ptr)), _previous(0) {}

template<typename T>
XorListIterator<T>::XorListIterator(node_pointer curr, node_pointer prev) :
        _current(_cast(curr)), _previous(_cast(prev)) {}

template<typename T>
typename XorListIterator<T>::self&
XorListIterator<T>::operator++() {
    calc_type next = _cast(_current)->_neighboursXor ^ _previous;
    _previous = _current;
    _current = next;
}

template<typename T>
typename XorListIterator<T>::self
XorListIterator<T>::operator++(int) {
    self temp = *this;
    operator++();
    return temp;
}

template<typename T>
typename XorListIterator<T>::self&
XorListIterator<T>::operator--() {
    calc_type prev = _cast(_previous)->_neighboursXor ^ _current;
    _current = _previous;
    _previous = prev;
}

template<typename T>
typename XorListIterator<T>::self
XorListIterator<T>::operator--(int) {
    self temp = *this;
    operator--();
    return temp;
}

template<typename T>
typename XorListIterator<T>::reference
XorListIterator<T>::operator*() {
    return _cast(_current)->_value;
}

template<typename T>
typename XorListIterator<T>::pointer
XorListIterator<T>::operator->() {
    return &(operator*());
}

template<typename U>
bool operator==(const XorListIterator<U>& first, const XorListIterator<U>& other) {
    return first._current == other._current && first._previous == other._previous;
}

template<typename U>
bool operator!=(const XorListIterator<U>& first, const XorListIterator<U>& other) {
    return !(first == other);
}
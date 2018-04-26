#include "xorlist.h"

template<typename T, class Allocator>
typename XorList<T, Allocator>::node_pointer
XorList<T, Allocator>::_createNode(rvalue_reference value, node_pointer before, node_pointer next) {
    node_pointer newNode = node_allocator_traits::allocate(_alloc, 1);
    node_allocator_traits::construct(_alloc, newNode, std::forward<value_type>(value), before, next);
    return newNode;
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::node_pointer
XorList<T, Allocator>::_createNode(const_reference value, node_pointer before, node_pointer next) {
    node_pointer newNode = node_allocator_traits::allocate(_alloc, 1);
    node_allocator_traits::construct(_alloc, newNode, value, before, next);
    return newNode;
}

template<typename T, class Allocator>
XorList<T, Allocator>::XorList(const allocator_type& alloc):
        _start(nullptr), _end(nullptr), _size(0), _alloc(node_allocator_type(alloc)) {}

template<typename T, class Allocator>
typename XorList<T, Allocator>::allocator_type
XorList<T, Allocator>::get_allocator() const {
    return allocator_type(_alloc);
}

template<typename T, class Allocator>
XorList<T, Allocator>::XorList(const XorList& other):
        _start(nullptr), _end(nullptr), _size(0),
        _alloc(node_allocator_traits::select_on_container_copy_construction(other._alloc)) {
    for (auto it = other.begin(); it != other.end(); ++it)
        push_back(*it);
//    for (const auto& element: other)
//        push_back(element);
}

template<typename T, class Allocator>
XorList<T, Allocator>::XorList(const XorList& other, const allocator_type& alloc):
        _start(nullptr), _end(nullptr), _size(0), _alloc(alloc) {
    for (const auto& element: other)
        push_back(element);
}

template<typename T, class Allocator>
XorList<T, Allocator>::XorList(XorList&& other):
        _start(std::move(other._start)), _end(std::move(other._end)),
        _size(std::move(other._size)), _alloc(std::move(other._alloc)) {}

template<typename T, class Allocator>
XorList<T, Allocator>::XorList(XorList&& other, const allocator_type& alloc):
        _start(std::move(other._start)), _end(std::move(other._end)),
        _size(std::move(other._size)), _alloc(alloc) {
    if (_alloc != other._alloc) {
        _start = nullptr; _end = nullptr; _size = 0;
        for (auto&& element: other)
            push_back(std::move(element));
    }
}
/*
template<typename T, class Allocator>
XorList<T, Allocator>&
XorList<T, Allocator>::operator=(const XorList& other) {

}
*/
template<typename T, class Allocator>
XorList<T, Allocator>::~XorList() {
    clear();
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::size_type
XorList<T, Allocator>::size() const {
    return _size;
}

template<typename T, class Allocator>
bool XorList<T, Allocator>::empty() const {
    return _size == 0;
};


template<typename T, class Allocator>
typename XorList<T, Allocator>::iterator
XorList<T, Allocator>::begin() {
    return iterator(_start);
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::iterator
XorList<T, Allocator>::end() {
    return iterator(nullptr, _end);
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::const_iterator
XorList<T, Allocator>::begin() const {
    return const_iterator(_start);
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::const_iterator
XorList<T, Allocator>::end() const {
    return const_iterator(nullptr, _end);
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::const_iterator
XorList<T, Allocator>::cbegin() const {
    return const_iterator(_start);
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::const_iterator
XorList<T, Allocator>::cend() const {
    return const_iterator(nullptr, _end);
}


template<typename T, class Allocator>
typename XorList<T, Allocator>::reverse_iterator
XorList<T, Allocator>::rbegin() {
    return reverse_iterator(end());
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::reverse_iterator
XorList<T, Allocator>::rend() {
    return reverse_iterator(begin());
}

template<typename T, class Allocator>
void XorList<T, Allocator>::_hook(node_pointer curNode, node_pointer nextNode, node_pointer newNode) {
    if (curNode)
        curNode->_changeNeighbour(nextNode, newNode);
    else
        _start = newNode;
    if (nextNode)
        nextNode->_changeNeighbour(curNode, newNode);
    else
        _end = newNode;
    ++_size;
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::iterator
XorList<T, Allocator>::insert_after(iterator pos, const_reference value) {
    auto leftNode = pos._getNode(), rightNode = pos._getNextNode();
    node_pointer newNode = _createNode(value, leftNode, rightNode);
    _hook(leftNode, rightNode, newNode);
    return iterator(newNode, leftNode);
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::iterator
XorList<T, Allocator>::insert_after(iterator pos, rvalue_reference value) {
    auto leftNode = pos._getNode(), rightNode = pos._getNextNode();
    node_pointer newNode = _createNode(std::move(value), leftNode, rightNode);
    _hook(leftNode, rightNode, newNode);
    return iterator(newNode, leftNode);
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::iterator
XorList<T, Allocator>::insert_before(iterator pos, const_reference value) {
    auto leftNode = pos._getPrevNode(), rightNode = pos._getNode();
    node_pointer newNode = _createNode(value, leftNode, rightNode);
    _hook(leftNode, rightNode, newNode);
    return iterator(newNode, leftNode);
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::iterator
XorList<T, Allocator>::insert_before(iterator pos, rvalue_reference value) {
    auto leftNode = pos._getPrevNode(), rightNode = pos._getNode();
    node_pointer newNode = _createNode(std::move(value), leftNode, rightNode);
    _hook(leftNode, rightNode, newNode);
    return iterator(newNode, leftNode);
}

template<typename T, class Allocator>
void XorList<T, Allocator>::push_back(const_reference element) {
    _hook(_end, nullptr, _createNode(element, _end, nullptr));
}

template<typename T, class Allocator>
void XorList<T, Allocator>::push_back(rvalue_reference element) {
    _hook(_end, nullptr, _createNode(std::move(element), _end, nullptr));
}

template<typename T, class Allocator>
void XorList<T, Allocator>::push_front(const_reference element) {
    _hook(nullptr, _start, _createNode(element, nullptr, _start));
}

template<typename T, class Allocator>
void XorList<T, Allocator>::push_front(rvalue_reference element) {
    _hook(nullptr, _start, _createNode(std::move(element), nullptr, _start));
}

template<typename T, class Allocator>
void XorList<T, Allocator>::pop_back() {
    node_pointer toDelete = _end;
    _end = reinterpret_cast<node_pointer>(_end->_neighboursXor);
    if (_size > 1)
        _end->_neighboursXor ^= reinterpret_cast<uintptr_t>(toDelete);
    else
        _start = nullptr;
    _free(toDelete);
}

template<typename T, class Allocator>
void XorList<T, Allocator>::pop_front() {
    node_pointer toDelete = _start;
    _start = reinterpret_cast<node_pointer>(_start->_neighboursXor);
    if (_size > 1)
        _start->_neighboursXor ^= reinterpret_cast<uintptr_t>(toDelete);
    else
        _end = nullptr;
    _free(toDelete);
}

template<typename T, class Allocator>
void XorList<T, Allocator>::clear() {
    while (_size > 0)
        pop_front();
}

template<typename T, class Allocator>
void XorList<T, Allocator>::_free(node_pointer toDelete) {
    node_allocator_traits::destroy(_alloc, toDelete);
    node_allocator_traits::deallocate(_alloc, toDelete, 1);
    _size--;
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::reference
XorList<T, Allocator>::back() {
    return *_end;
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::reference
XorList<T, Allocator>::front() {
    return *_start;
}

template<typename T, class Allocator>
void XorList<T, Allocator>::_hookOut(node_pointer left, node_pointer right, node_pointer toDelete) {
    left->_changeNeighbour(toDelete, right);
    right->_changeNeighbour(toDelete, left);
    _free(toDelete);
}

template<typename T, class Allocator>
void XorList<T, Allocator>::erase(iterator cur) {
    _hookOut(cur._getPrevNode(), cur._getNextNode(), cur._getNode());
}
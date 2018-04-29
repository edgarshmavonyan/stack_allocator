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
void XorList<T, Allocator>::_init() {
    _start = nullptr; _end = nullptr; _size = 0; _alloc = node_allocator_type(Allocator());
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

    for (const auto& element: other)
        push_back(element);
}

template<typename T, class Allocator>
XorList<T, Allocator>::XorList(const XorList& other, const allocator_type& alloc):
        _start(nullptr), _end(nullptr), _size(0), _alloc(alloc) {

    for (const auto& element: other)
        push_back(element);
}

template<typename T, class Allocator>
XorList<T, Allocator>::XorList(XorList&& other) noexcept:
        _start(other._start), _end(other._end),
        _size(other._size), _alloc(other._alloc) {
    other._init();
}

template<typename T, class Allocator>
XorList<T, Allocator>::XorList(XorList&& other, const allocator_type& alloc):
        _start(other._start), _end(other._end),
        _size(other._size), _alloc(alloc) {
    if (_alloc != other._alloc) {
        _start = nullptr; _end = nullptr; _size = 0;
        for (auto&& element: other)
            push_back(std::move(element));
    }
}

template<typename T, class Allocator>
XorList<T, Allocator>::XorList(std::initializer_list<value_type> init, const allocator_type& alloc):
        _start(nullptr), _end(nullptr), _size(0), _alloc(node_allocator_type(alloc)) {
    for (const auto& element: init)
        push_back(element);
}

template<typename T, class Allocator>
XorList<T, Allocator>&
XorList<T, Allocator>::operator=(const XorList& other) {
    if (this != &other) {
        clear();
        if (node_allocator_traits::propagate_on_container_copy_assignment::value)
            _alloc = other._alloc;
        for (const auto& element: other)
            push_back(element);
    }
    return *this;
}

template<typename T, class Allocator>
XorList<T, Allocator>&
XorList<T, Allocator>::operator=(XorList&& other) noexcept {
    if (this != &other) {
        clear();
        // if we propagate allocator, or they're equal, we only move pointers
        // else we move element by element
        if (node_allocator_traits::propagate_on_container_move_assignment::value
            || node_allocator_traits::is_always_equal::value
            || _alloc == other._alloc) {
            _start = other._start;
            _end = other._end;
            _size = other._size;
            _alloc = other._alloc;
            other._init();
        } else
            for (auto &&element: other)
                push_back(std::move(element));
    }
    return *this;
}

template<typename T, class Allocator>
XorList<T, Allocator>&
XorList<T, Allocator>::operator=(std::initializer_list<value_type> ilist) {
    clear();
    for (const auto& element: ilist)
        push_back(element);
    return *this;
}

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
typename XorList<T, Allocator>::const_reverse_iterator
XorList<T, Allocator>::rbegin() const {
    return const_reverse_iterator(cend());
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::const_reverse_iterator
XorList<T, Allocator>::rend() const {
    return const_reverse_iterator(cbegin());
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::const_reverse_iterator
XorList<T, Allocator>::crbegin() {
    return const_reverse_iterator(cend());
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::const_reverse_iterator
XorList<T, Allocator>::crend() {
    return const_reverse_iterator(cbegin());
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
    erase(--end());
}

template<typename T, class Allocator>
void XorList<T, Allocator>::pop_front() {
    erase(begin());
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
XorList<T, Allocator>::front() {
    return _start->_value;
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::const_reference
XorList<T, Allocator>::front() const {
    return _start->_value;
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::reference
XorList<T, Allocator>::back() {
    return _end->_value;
}

template<typename T, class Allocator>
typename XorList<T, Allocator>::const_reference
XorList<T, Allocator>::back() const {
    return _end->_value;
}

template<typename T, class Allocator>
void XorList<T, Allocator>::_unhook(node_pointer left, node_pointer right, node_pointer toDelete) {
    if (left != nullptr)
        left->_changeNeighbour(toDelete, right);
    else
        _start = right;
    if (right != nullptr)
        right->_changeNeighbour(toDelete, left);
    else
        _end = left;
    _free(toDelete);
}

template<typename T, class Allocator>
void XorList<T, Allocator>::erase(iterator cur) {
    _unhook(cur._getPrevNode(), cur._getNextNode(), cur._getNode());
}
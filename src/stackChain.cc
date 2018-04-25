#include "stackallocator/stackChain.h"

StackChain::area_pointer
StackChain::_createNode() {
    _areaCount++;
    return _cur = _cur->_nextArea = new area();
}


char* StackChain::allocate(size_t requiredMemory) {
    if (!_cur->_checkAvailability(requiredMemory))
        _createNode();
    return _cur->_allocate(requiredMemory);
}

StackChain::StackChain() : _areaCount(1), _start(new AllocationArea()), _cur(_start) {}

StackChain::~StackChain() {
    area_pointer cur;
    area_pointer next = _start->_nextArea;
    delete _start;
    while (next != nullptr) {
        cur = next;
        next = next->_nextArea;
        delete cur;
    }
}
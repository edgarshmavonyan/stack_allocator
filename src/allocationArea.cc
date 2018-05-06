#include "stackallocator/allocationArea.h"

AllocationArea::AllocationArea() : _cur((char*) ::operator new(MAX_ALLOCATION)), _available(MAX_ALLOCATION), _nextArea(nullptr) {}

bool AllocationArea::_checkAvailability(size_t requiredMemory) const {
    return _available >= requiredMemory;
}

char* AllocationArea::_allocate(size_t requiredMemory) {
    _available -= requiredMemory;
    _cur += requiredMemory;
    return _cur - requiredMemory;
}


AllocationArea::~AllocationArea() {
    ::operator delete((void*) (_cur + _available - MAX_ALLOCATION));
}

project(stackAllocator_src)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES allocationArea.cc stackChain.cc)

add_library(stackAllocator_src STATIC ${SOURCE_FILES})
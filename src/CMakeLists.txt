project(stackallocator_src)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES allocationArea.cc stackChain.cc)

add_library(stackallocator_src STATIC ${SOURCE_FILES})
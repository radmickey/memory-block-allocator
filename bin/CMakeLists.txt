add_executable(memory-block-allocator main.cpp)

target_link_libraries(memory-block-allocator MemoryBlockAllocator)
target_include_directories(memory-block-allocator PRIVATE ${PROJECT_SOURCE_DIR})

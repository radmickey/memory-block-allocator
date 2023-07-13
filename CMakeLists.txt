cmake_minimum_required(VERSION 3.12)

project(
        PoolMemoryAllocator
        VERSION 1.0
        DESCRIPTION "Pools memory allocator"
        LANGUAGES CXX
)


set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(examples)

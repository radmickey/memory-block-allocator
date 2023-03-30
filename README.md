# MemoryPoolsAllocator

## Project Description

MemoryPoolsAllocator is a memory allocator that works based on pre-allocated blocks of memory and meets the requirements for allocators.
The project aims to implement an allocator and compare its performance with the standard allocator when interacting with containers.
The obtained results will be presented on a graph and are part of the task that affects the final grade.

## Working Principle

The allocator uses pre-allocated blocks of memory that are divided into pools and pieces of the same size. 
Pools can only allocate and free memory in pieces and have information about free and occupied pieces. 
When allocating N-byte memory, the allocator searches for the most suitable pool to optimally allocate memory.
If this is not possible, the std::bad_alloc exception is thrown. 
When freed through the allocator, memory pieces become available for use again.

## Implementation

The sizes of pools, their number, and the sizes of pieces can be parameterized (at compile time or runtime).
The allocator does not necessarily have to own pools. The design is up to the developer's discretion.

## Installation and Running

Clone the repository using the ``git clone https://github.com/radmickey/memory-block-allocator`` command.

Build the project using any C++14-compatible compiler.

Run the project and perform the required tasks.

## Example of using
````
#include "lib/MemoryBlockAllocator.h"

#include <iostream>
#include <vector>

int main() {
    std::vector<std::pair<int, size_t>> groups;
    groups.resize(11);
    groups[0].second = 1; groups[0].first = 10000;
    groups[1].second = 2; groups[1].first = 10000;
    groups[2].second = 4; groups[2].first = 10000;
    groups[3].second = 8; groups[3].first = 10000;
    groups[4].second = 16; groups[4].first = 10000;
    groups[5].second = 32; groups[5].first = 10000;
    groups[6].second = 64; groups[6].first = 10000;
    groups[7].second = 128; groups[7].first = 10000;
    groups[8].second = 256; groups[8].first = 10000;
    groups[9].second = 512; groups[9].first = 10000;
    groups[10].second = 10000000; groups[10].first = 10;

    MemoryBlockAllocator<int> testAlloc(groups);
    std::vector<int, MemoryBlockAllocator<int>> v1(testAlloc);

    return 0;
}

````

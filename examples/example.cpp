#include "MemoryBlockAllocator.h"

#include <iostream>
#include <chrono>
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

    auto start1 = std::chrono::system_clock::now();

    for (int i = 0; i < 500000; i++) {
        v1.push_back(i);
    }

    auto end1 = std::chrono::system_clock::now();


    std::vector<int> v2;
    auto start2 = std::chrono::system_clock::now();

    for (int i = 0; i < 500000; i++) {
        v2.push_back(i);
    }
    auto end2 = std::chrono::system_clock::now();

    auto res1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count();
    auto res2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();

    std::cout << "\nThe time with MyAlloc: " << res1 << " ms\n";
    std::cout << "\nThe time without MyAlloc: " << res2 << " ms\n";

    return 0;
}

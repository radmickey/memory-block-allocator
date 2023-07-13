#include "utils.h"

#include <map>
#include <cstdlib>
#include <exception>
#include <vector>
#include <algorithm>

template <class T>
class MemoryBlockAllocator {
private:
    size_t groups_number_;

    size_t bin_search(std::vector<std::pair<size_t, Group>>& arr, size_t x) {
        size_t size = arr.size();
        size_t left = 0;
        size_t right = size;
        while (left < right) {
            size_t mid = left + (right - left) / 2;
            if (x <= arr[mid].first) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }

public:
    using value_type = T;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;

    std::vector<std::pair<size_type, Group>> all_groups_;
    std::map<pointer, int> position_to_allocate_pointer_;

    MemoryBlockAllocator() = default;

    template<typename T2>
    explicit MemoryBlockAllocator(const MemoryBlockAllocator<T2>& rhs) noexcept {
        all_groups_ = rhs.all_groups_;

        groups_number_ = rhs.GetGroupsNumber();
    }

    explicit MemoryBlockAllocator(std::vector<std::pair<int, size_type>>& memory_to_allocate) {
        groups_number_ = memory_to_allocate.size();
        for (size_t i = 0; i < groups_number_; ++i) {
            int count_chunks = memory_to_allocate[i].first;
            size_t size_chunk = memory_to_allocate[i].second;
            all_groups_.emplace_back(size_chunk, Group(count_chunks, size_chunk));
        }
        sort(all_groups_.begin(), all_groups_.end(), cmp);
    }

    ~MemoryBlockAllocator() {
        all_groups_.clear();
    }

    pointer allocate(size_type chunksNum) {
        size_t paste_position = bin_search(all_groups_, chunksNum * sizeof(value_type));

        if (paste_position < all_groups_.size()) {
            auto& group_to_paste = all_groups_[paste_position];
            if (group_to_paste.second.havePlace()) {
                auto ptr = (pointer)group_to_paste.second.allocateInGroup();
                position_to_allocate_pointer_[ptr] = paste_position;
                return ptr;
            } else {
                for (size_t i = paste_position; i < all_groups_.size(); i++)
                    if (all_groups_[i].second.havePlace()) {
                        auto *ptr = (pointer)all_groups_[i].second.allocateInGroup();
                        position_to_allocate_pointer_[ptr] = i;
                        return ptr;
                    }
                throw std::bad_alloc();
            }
        } else {
            throw std::bad_alloc();
        }
    }

    void deallocate(pointer ptr, size_type elementsCount) {
        int dealloc_pos = position_to_allocate_pointer_[ptr];
        auto& group_to_deallocate = all_groups_[dealloc_pos];
        group_to_deallocate.second.deallocateInGroup(ptr);
    }

    [[nodiscard]] size_type GetGroupsNumber() const {
        return groups_number_;
    }
};

template <class T, class T2>
bool operator==(const MemoryBlockAllocator<T>& lhs, const MemoryBlockAllocator<T2>& rhs) {
    return (lhs.allGroups_ == rhs.allGroups_ && lhs.GetGroupsNumber() == rhs.GetGroupsNumber());
}

template <class T, class T2>
bool operator!=(const MemoryBlockAllocator<T>& lhs, const MemoryBlockAllocator<T2>& rhs) {
    return (lhs.allGroups_ != rhs.allGroups_ || lhs.GetGroupsNumber() != rhs.GetGroupsNumber());
}

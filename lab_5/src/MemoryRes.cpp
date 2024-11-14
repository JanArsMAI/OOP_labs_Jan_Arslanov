#include "../include/MemoryRes.h"
#include <new>
#include <stdexcept>
#include <iostream>

CustomMemoryResource::CustomMemoryResource(size_t count_of_item, size_t size_of_item)
    : count_of_item(count_of_item), size_of_item(size_of_item), memory_res(nullptr) {
    if (size_of_item == 0 || count_of_item == 0) {
        throw std::invalid_argument("Size and count should be higher than 0");
    }

    std::pmr::polymorphic_allocator<std::byte> alloc{std::pmr::get_default_resource()};
    memory_res = alloc.allocate_bytes(size_of_item * count_of_item);

    for (size_t i = 0; i < count_of_item; ++i) {
        void* block = static_cast<std::byte*>(memory_res) + i * size_of_item;
        free_blocks.push_back(block);
    }
}

CustomMemoryResource::~CustomMemoryResource() {
    std::pmr::polymorphic_allocator<std::byte> alloc{std::pmr::get_default_resource()};
    alloc.deallocate_bytes(static_cast<std::byte*>(memory_res), size_of_item * count_of_item);

    free_blocks.clear();
    allocatedBlocks.clear();
}

void* CustomMemoryResource::do_allocate(size_t bytes, size_t alignment) {
    if (bytes > size_of_item) {
        throw std::bad_alloc();
    }

    if (free_blocks.empty()) {
        throw std::bad_alloc();
    }

    void* block = free_blocks.front();
    free_blocks.pop_front();

    uintptr_t blockAddress = reinterpret_cast<uintptr_t>(block);
    if (blockAddress % alignment != 0) {
        throw std::bad_alloc();
    }

    allocatedBlocks.push_back(block);
    return block;
}

void CustomMemoryResource::do_deallocate(void* ptr, size_t bytes, size_t alignment) {
    auto it = allocatedBlocks.begin();
    for (; it != allocatedBlocks.end(); ++it) {
        if (*it == ptr) {
            break;
        }
    }

    if (it == allocatedBlocks.end()) {
        throw std::invalid_argument("You are trying to deallocate an unallocated block");
    }

    allocatedBlocks.erase(it);
    free_blocks.push_back(ptr);
}

bool CustomMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    const auto* otherResource = dynamic_cast<const CustomMemoryResource*>(&other);
    return this == otherResource;
}

void* CustomMemoryResource::allocate(size_t bytes, size_t alignment) {
    return do_allocate(bytes, alignment);
}

void CustomMemoryResource::deallocate(void* ptr, size_t bytes, size_t alignment) {
    do_deallocate(ptr, bytes, alignment);
}
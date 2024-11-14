#pragma once

#include <memory_resource>
#include <list>
#include <cstddef>
#include <stdexcept>
#include <iostream>

class CustomMemoryResource : public std::pmr::memory_resource {
public:
    CustomMemoryResource(size_t count_of_item, size_t size_of_item);
    ~CustomMemoryResource();
    size_t available_blocks() const { return free_blocks.size(); }
    size_t allocated_blocks() const { return allocatedBlocks.size(); }

    void* allocate(size_t bytes, size_t alignment);
    void deallocate(void* ptr, size_t bytes, size_t alignment);

protected:
    void* do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void* ptr, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

private:
    size_t size_of_item;
    size_t count_of_item;
    void* memory_res;
    std::list<void*> free_blocks;
    std::list<void*> allocatedBlocks;
};
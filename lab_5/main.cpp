#include "../include/MemoryRes.h"
#include <iostream>

int main() {
    try {
        CustomMemoryResource memoryResource(10, 64);
        std::cout << "Initial available blocks: " << memoryResource.available_blocks() << std::endl;
        std::cout << "Initial allocated blocks: " << memoryResource.allocated_blocks() << std::endl;
        void* ptr1 = memoryResource.allocate(64, alignof(std::max_align_t));
        void* ptr2 = memoryResource.allocate(64, alignof(std::max_align_t));
        std::cout << "Available blocks after allocation: " << memoryResource.available_blocks() << std::endl;
        std::cout << "Allocated blocks after allocation: " << memoryResource.allocated_blocks() << std::endl;
        memoryResource.deallocate(ptr1, 64, alignof(std::max_align_t));
        memoryResource.deallocate(ptr2, 64, alignof(std::max_align_t));
        std::cout << "Available blocks after deallocation: " << memoryResource.available_blocks() << std::endl;
        std::cout << "Allocated blocks after deallocation: " << memoryResource.allocated_blocks() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
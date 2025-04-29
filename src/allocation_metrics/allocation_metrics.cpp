/*
 * Credit to The Cherno for the Allocation Metric idea
 * Video: Track MEMORY ALLOCATION the Easy Way in C++
 * Link: https://www.youtube.com/watch?v=sLlGEUO_EGE&list=LL&index=1&pp=gAQBiAQB
 */

/*
 * Links to docs: 
 * vscode: file:///./../../docs/allocation_metrics.md
 * path: 3d-renderer/docs/allocation_metrics.md
 */


#include <iostream>

#include "..\..\include\allocation_metrics\allocaion_metrics.h"

AllocatioMetrics s_allocation_metrics;

// Override raw memory block allocation
// new keyword used operator new under the hood
void* operator new(size_t size) {
    std::cout << "Allocating " << size << " bytes" << std::endl;
    s_allocation_metrics.bytes_allocated += size;
    return malloc(size);
}
void* operator new[](size_t size) {
    std::cout << "Allocating " << size << " bytes" << std::endl;
    s_allocation_metrics.bytes_allocated += size;
    return malloc(size);
}

// Override operator delete with size meta-data
// delete keyword used operator delete under the hood
void operator delete(void* memory, size_t size) {
    std::cout << "Deallocating " << size << " bytes" << std::endl;
    s_allocation_metrics.bytes_deallocated += size;
    free(memory);
}
void operator delete[](void* memory, size_t size) {
    std::cout << "Deallocating " << size << " bytes" << std::endl;
    s_allocation_metrics.bytes_deallocated += size;
    free(memory);
}

// Override operator delete with no size meta-data
// delete keyword used operator delete under the hood
void operator delete(void* memory) {
    size_t size = _msize(memory);
    std::cout << "Deallocating " << size << " bytes" << std::endl;
    s_allocation_metrics.bytes_deallocated += size;
    free(memory);
}
void operator delete[](void* memory) {
    size_t size = _msize(memory);
    std::cout << "Deallocating " << size << " bytes" << std::endl;
    s_allocation_metrics.bytes_deallocated += size;
    free(memory);
}

// Display data about current memory state
void memInfo() {
    std::cout << "\n";
    std::cout << "Total bytes allocated: " << s_allocation_metrics.bytes_allocated << "\n";
    std::cout << "Total bytes deallocated: " << s_allocation_metrics.bytes_deallocated << "\n";
    std::cout << "Bytes still allocated: " << s_allocation_metrics.getCurrentMemory() << "\n";
    std::cout << std::endl;
}

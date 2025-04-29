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

#ifndef ALLOCATION_METRICS_H_
#define ALLOCATION_METRICS_H_

#include <cstdint>

struct AllocatioMetrics {

    uint32_t bytes_allocated = 0;
    uint32_t bytes_deallocated = 0;
    uint32_t getCurrentMemory() {return bytes_allocated - bytes_deallocated;}

};

extern AllocatioMetrics s_allocation_metrics;

// Override raw memory block allocation
// new keyword used operator new under the hood
void* operator new(size_t size);
void* operator new[](size_t size);

// Override operator delete with size meta-data
// delete keyword used operator delete under the hood
void operator delete(void* memory, size_t size);
void operator delete[](void* memory, size_t size);

// Override operator delete with no size meta-data
// delete keyword used operator delete under the hood
void operator delete(void* memory);
void operator delete[](void* memory);

// Display data about current memory state
void memInfo();

#endif
// Standard library imports
#include <iostream>
#include <cstdint>

// 3rd party imports

// Local imports
#include "..\include\allocation_metrics\allocaion_metrics.h"
#include "..\include\framebuffer\framebuffer.h"

// Check the allocation metrics to find signs of a memory leak
void detect_mem_leak() {
    size_t size = s_allocation_metrics.getCurrentMemory();
    std::cout << "\n\n";
    if (size) {
        std::cout << "!!!MEMORY LEAK DETECTED!!!\n";
        std::cout << size << " bytes still allocated at program termination!\n";
    } else {
        std::cout << "No memory leak detected.\n";
        std::cout << "All memory seems to be deallocated at program termination\n";
    }
    std::cout << std::endl;
}

int main() {

    // Run memory leak detection before program termination
    std::atexit(detect_mem_leak);

    Framebuffer fb(800, 600);

    const char* filename = "../../images/test.ppm";
    const char* depth = "../../images/test_depth.ppm";

    for (uint32_t y = 0; y < fb.height; y++) {
        for (uint32_t x = 0; x < fb.width; x++) {
            fb.setPixel(x, y, (float)x, (float)y, ((float)x+y)/2.0f);
            fb.setDepth(x, y, (float)x);
        }
    }

    fb.plotImage(filename, depth);

    return 0;

}
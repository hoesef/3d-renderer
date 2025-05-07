// Standard library imports
#include <iostream>
#include <cstdint>
#include <math.h>

// 3rd party imports

// Local imports
#include "..\include\allocation_metrics\allocaion_metrics.h"
#include "..\include\framebuffer\framebuffer.h"
#include "..\include\framebuffer\linedrawer.h"
#include "..\include\maths\vector.h"
#include "..\include\maths\matrix.h"

#define M_PI 3.14159265395f
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

    for (uint32_t y = 0; y < fb.m_height; y++) {
        for (uint32_t x = 0; x < fb.m_width; x++) {
            fb.setPixel(x, y, (float)x/fb.m_width, (float)y/fb.m_height, 0.0f);//((float)x+y)/(fb.m_width+fb.m_height));
            fb.setDepth(x, y, (float)x);
        }
    }

    drawline(fb, 400, 300, 400, 300);
    
    for (float i = 0; i < M_PI * 2; i += M_PI /64.0f)
    {
        // Generate a simple 2D vector
        float x = cos(i);
        float y = sin(i);

        // draw a line
        drawline(fb, 400 + (int)(48.0f*x), 300 + (int)(48.0f*y), 400 + (int)(240.0f*x), 300 + (int)(240.0f*y));
    }

    fb.plotImage(filename, depth);

    Vector v0(1,2,3);
    Vector v1(4,5,6);
    Vector v2;

    std::cout << "v0: " << v0 << "\n";
    std::cout << "v1: " << v1 << "\n";
    std::cout << "v2: " << v2 << "\n";

    Matrix4x4 m;
    std::cout << "m: \n" << m << "\n";

    std::cout << "m + 5:\n" << (m+5) << "\n";
    std::cout << "m + m:\n" << (m+m) << "\n";

    m = m + 5;
    m = m - 5;
    std::cout << "(m + 5) - 5: \n" << ((m+5) - 5) << "\n";

    Matrix4x4 m2 = m + m;
    m2 = m2 - m;
    std::cout << "m2 = (m + m) - m:\n" << m2 << "\n";
    
    std::cout << "m * 2:\n" << m*2 << "\n";

    v2 = m * v0;
    std::cout << "v2 = m * v0: " << v2 << "\n";

    Vertex vert(6,7,8,9);
    vert = m * vert;
    std::cout << "m * vert: (" << vert.m_x << ", " << vert.m_y << ", " << vert.m_z << ", " << vert.m_w << ")\n";

    m2 = m2 * 8;
    std::cout << "(m2*8) * m:\n" << m2 << "\n";

    m2 = m2.transpose();
    std::cout << "m2.T()\n" << m2 << "\n";

    bool s = m2.inverse(m2);
    if (s) { std::cout << "m2.inverse() successfull: \n" << m2 << "\n"; }
    
    return 0;

}
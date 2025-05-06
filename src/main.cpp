// Standard library imports
#include <iostream>
#include <cstdint>
#include <math.h>

// 3rd party imports

// Local imports
#include "..\include\allocation_metrics\allocaion_metrics.h"
#include "..\include\framebuffer\framebuffer.h"
#include "..\include\framebuffer\linedrawer.h"
#include "..\include\objects\polymesh.h"
#include "..\include\parser\object-parser.h"
#include "..\include\parser\obj-parser.h"

#include <string>

#define M_PI 3.14159265395f
// Check the allocation metrics to find signs of a memory leak
void detect_mem_leak() {
    size_t size = s_allocation_metrics.getCurrentMemory();
    std::cout << "\n\n------------------------------------------------------\n";
    if (size) {
        std::cout << "!!!MEMORY LEAK DETECTED!!!\n";
        std::cout << size << " bytes still allocated at program termination!\n";
    } else {
        std::cout << "No memory leak detected.\n";
        std::cout << "All memory seems to be deallocated at program termination\n";
    }
    std::cout << "------------------------------------------------------" << std::endl;
}

void radial_lines(Framebuffer* fb, float inc = 64.0f) {
    for (uint32_t y = 0; y < fb->m_height; y++) {
        for (uint32_t x = 0; x < fb->m_width; x++) {
            fb->setPixel(x, y, (float)x/fb->m_width, (float)y/fb->m_height, 0.0f);//((float)x+y)/(fb->m_width+fb->m_height));
            fb->setDepth(x, y, (float)x);
        }
    }

    drawline(*fb, 400, 300, 400, 300);
    
    for (float i = 0; i < M_PI * 2; i += M_PI /inc)
    {
        // Generate a simple 2D vector
        float x = cos(i);
        float y = sin(i);

        // draw a line
        drawline(*fb, 400 + (int)(48.0f*x), 300 + (int)(48.0f*y), 400 + (int)(240.0f*x), 300 + (int)(240.0f*y));
    }
}

int main() {

    // Run memory leak detection before program termination
    std::atexit(detect_mem_leak);

    // Names of images to create
    const char* filename = "../../images/test.ppm";
    const char* depth = "../../images/test_depth.ppm";

    // Framebuffer instanciation
    Framebuffer fb(800, 600);
    radial_lines(&fb);

    bool success = true;
    const char* file = "../../assets/objects/test.obj";
    // Polymesh obj(file, success);

    std::cout << "Success: " << (success?"true":"false") << "\n";

    if (!success) { 
        return -1; }

    fb.plotImage(filename, depth);

    // obj.print();
    ObjectParser* parser = new OBJParser();
    
    Polymesh* mesh =  parser->parse(file);

    if (!mesh) {
        delete parser;
        return -1;
    }
    
    mesh->print();
    
    delete mesh;
    delete parser;  
    
    return 0;

}
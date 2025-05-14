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
#include "..\include\maths\vector.h"
#include "..\include\maths\matrix.h"

#include "..\include\renderer\perspective.h"

#ifndef M_PI
#define M_PI 3.1415926535f
#endif

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

int main() {

    // Run memory leak detection before program termination
    std::atexit(detect_mem_leak);

    int width = 800;
    int height = 600;

    // Names of images to create
    const char* filename = "../../images/test.ppm";
    const char* depth = "../../images/test_depth.ppm";

    // Framebuffer instanciation
    Framebuffer fb(width, height);
    Colour bgc = {0.02f, 0.3f, 0.1432f};
    fb.setBGC(bgc);

    const char* file = "../../assets/objects/cube_ccw.obj";

    ObjectParser* parser = new OBJParser();
    Polymesh* mesh =  parser->parse(file);

    Colour obj_col = {1, 1, 1};
    mesh->setColour(obj_col);

    mesh->transform.rotate(-45, 45, 45);
    mesh->transform.scale(5, 0.5, 2);
    mesh->transform.translate(0, 0, -5);

    if (!mesh) {
        delete parser;
        return -1;
    }
    
    Renderer* renderer = new Perspective(width, height, 90);
    
    renderer->render(*mesh, fb);
    
    delete renderer;
    delete mesh;
    delete parser;  

    int s = fb.plotImage(filename, depth);
    std::cout << (s==0?"success":"fail") << "\n";   
    
    return 0;

}
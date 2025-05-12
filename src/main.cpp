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

#include "..\include\camera\perspective.h"

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

void radial_lines(Framebuffer& fb, float inc = 64.0f) {
    for (uint32_t y = 0; y < fb.m_height; y++) {
        for (uint32_t x = 0; x < fb.m_width; x++) {
            fb.setPixel(x, y, (float)x/fb.m_width, (float)y/fb.m_height, 0.0f);//((float)x+y)/(fb->m_width+fb->m_height));
            fb.setDepth(x, y, (float)x);
        }
    }

    drawline(fb, 400, 300, 400, 300);
    
    for (float i = 0; i < M_PI * 2; i += M_PI /inc)
    {
        // Generate a simple 2D vector
        float x = cos(i);
        float y = sin(i);

        // draw a line
        drawline(fb, 400 + (int)(48.0f*x), 300 + (int)(48.0f*y), 400 + (int)(240.0f*x), 300 + (int)(240.0f*y));
    }
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

    const char* file = "../../assets/objects/cube_ccw.obj";

    // obj.print();
    ObjectParser* parser = new OBJParser();
    
    Polymesh* mesh =  parser->parse(file);

    mesh->scale(4, 3, 1);
    mesh->rotate(231, 231, 50);
    mesh->translate(-2, 1, 5);
    std::cout << mesh->getTransform();
    // mesh->translate(-2.5, 5, 10);
    // mesh->rotate(90, 0, 0);

    // std::cout << "Offset: " << mesh->m_transform_data.offset << "\n"
    //           << "rotation: x(" << mesh->m_transform_data.rotate_x << ") y(" << mesh->m_transform_data.rotate_y << ") z("
    //           << mesh->m_transform_data.rotate_z << ")\n"
    //           << "scale: x(" << mesh->m_transform_data.scale_x << ") y(" << mesh->m_transform_data.scale_y << ") z("
    //           << mesh->m_transform_data.scale_z << ")\n";

    if (!mesh) {
        delete parser;
        return -1;
    }
    
    // mesh->print();

    Camera* camera = new Perspective(width, height, 90);
    
    camera->render(*mesh, fb);
    
    delete camera;
    delete mesh;
    delete parser;  

    int s = fb.plotImage(filename, depth);
    std::cout << (s==0?"success":"fail") << "\n";

    // Matrix4x4 A(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
    // Matrix4x4 B(1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4);

    // std::cout << "A:\n" << A << "\n";
    // std::cout << "B:\n" << B << "\n";

    // std::cout << "A*B:\n" << A*A*B << "\n";

    
    
    return 0;

}
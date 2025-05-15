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
#include "..\include\camera\camera.h"
#include "..\include\data-structures\linked-list.h"

#include "..\include\scene\scene.h"

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

    const char* file = "../../assets/objects/teapot.obj";
    // const char* file = "../../assets/objects/cube_ccw.obj";

    ObjectParser* parser = new OBJParser();
    Polymesh* mesh =  parser->parse(file);

    const char* file2 = "../../assets/objects/cube_ccw.obj";
    Polymesh* mesh2 = parser->parse(file2);
    Colour obj_col2 = {1,1,1};
    mesh2->setColour(obj_col2);

    mesh2->transform.rotate(45, 45,  0);
    mesh2->transform.scale(1, 1, 10);
    mesh2->transform.translate(0, 0, -10);

    if (!mesh2) {
        delete parser;
        return -1;
    }

    Colour obj_col = {0.7f, 0.32f, 0.53f};
    mesh->setColour(obj_col);

    mesh->transform.rotate(-90, 0,  0);
    mesh->transform.scale(1, 1, 1);
    mesh->transform.translate(0, 0, -50);

    if (!mesh) {
        delete mesh2;
        delete parser;
        return -1;
    }
    
    Camera camera({-30, 30, 10}, {0, -10, -30}, {0, 1, 0});
    Camera camera2({-30, 30, 10}, {0, 1, 0}, 30.0f, 140.0f);
    Renderer* renderer = new Perspective(width, height, 90);
    
    std::cout << "Mesh 1\n";
    renderer->render(camera2, *mesh, fb);
    std::cout << "Mesh 2\n";
    renderer->render(camera2, *mesh2, fb);

    {
    Scene scene;
    scene.addObject(mesh);
    scene.addObject(mesh2);
    }
    delete renderer;
    delete parser;  

    int s = fb.plotImage(filename, depth);
    std::cout << (s==0?"success":"fail") << "\n";  
    
    return 0;

}
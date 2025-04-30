#include <fstream>

#include "../../include/framebuffer/framebuffer.h"

// Constructor
Framebuffer::Framebuffer(uint32_t w, uint32_t h) {
    width = w;
    height = h;
    fb = new Pixel[w * h];
}

// Set pixel value at position (x, y)
int Framebuffer::setPixel(uint32_t x, uint32_t y, float r, float g, float b) {
    // Chech that position is within image bounds
    if ((x >= width) || y >= height) {
        return -1;
    }

    // Get index
    uint32_t i = y * width + x;

    // Set pixel
    fb[i].red = r;
    fb[i].green= g;
    fb[i].blue= b;

    return 0;
}

// Get pixel value at position (x, y)
int Framebuffer::getPixel(uint32_t x, uint32_t y, float& r, float& g, float& b) {
    // Check that position is within image bounds
    if ((x >= width) || (y >= height)) {
        return -1;
    }
    
    // Get index
    uint32_t i = y * width + x;

    // Get r,g,b values
    r = fb[i].red;
    g = fb[i].green;
    b = fb[i].blue;

    return 0;
}

// Set depth at position (x, y)
int Framebuffer::setDepth(uint32_t x, uint32_t y, float d) {
    // Check that position is within image bounds
    if ((x >= width) || (y >= height)) {
        return -1;
    }

    // Set depth
    fb[y * width + x].depth = d;
    
    return 0;
}

// Get depth at position (x, y)
int Framebuffer::getDepth(uint32_t x, uint32_t y, float& d) {
    // Check that position is within image bounds
    if ((x >= width) || (y >= height)) {
        return -1;
    }

    // Get depth
    d = fb[y * width + x].depth;

    return 0;
}

int Framebuffer::plotImage(const char* filename, const char* depthName) {
    std::ofstream image(filename, std::ios::binary);
    std::ofstream depth(depthName, std::ios::binary);

    // Check files opened
    if (image.fail() || depth.fail()) {
        return -1;
    }

    // Max/min rgb trackers
    float i_max = 0.0f;
    float i_min = 0.0f;

    // Max/min depth trackers
    float d_max = 0.0f;
    float d_min = 0.0f;

    for (uint32_t i = 0; i < width * height; i++) {
        // Get max/min r,b,g value
        if (fb[i].red > i_max) { i_max = fb[i].red; }
        if (fb[i].red < i_min) { i_min = fb[i].red; }
        if (fb[i].red > i_max) { i_max = fb[i].green; }
        if (fb[i].red < i_min) { i_min = fb[i].green; }
        if (fb[i].red > i_max) { i_max = fb[i].blue; }
        if (fb[i].red < i_min) { i_min = fb[i].blue; }
        // Get max/min depth value
        if (fb[i].depth > d_max) { d_max = fb[i].depth; }
        if (fb[i].depth < d_min) { d_min = fb[i].depth; }
    }

    float i_diff = i_max - i_min;
    float d_diff = d_max - d_min;

    if (i_diff == 0.0f) { i_diff = 1.0f; }
    if (d_diff == 0.0f) { d_diff = 1.0f; }

    // Write out data
    image << "P6\n"; // PPM type
    depth << "P5\n"; // PPM type

    image << width << " " << height << "\n255\n"; // width, height, max colour value
    depth << width << " " << height << "\n255\n"; // width, height, max colour value

    // Write pixel data
    // Pixels are normalized (possible loss of realism)
    for (uint32_t i = 0; i < width * height; i++) {
        image << (unsigned char)((fb[i].red - i_min) / i_diff * 255.00f);   // r
        image << (unsigned char)((fb[i].green - i_min) / i_diff * 255.00f); // g
        image << (unsigned char)((fb[i].blue - i_min) / i_diff * 255.00f);  // b
        depth << (unsigned char)((fb[i].depth - d_min) / d_diff * 255.0f);  // d
    }

    // Close image files
    image.close();
    depth.close();

    return 0;
}

// Destructor
Framebuffer::~Framebuffer() {
    // Free framebuffer
    delete[] fb;
}
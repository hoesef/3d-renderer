#include <fstream>
#include <iostream>

#include "../../include/framebuffer/framebuffer.h"

// Constructor
Framebuffer::Framebuffer(uint32_t w, uint32_t h) {
    m_width = w;
    m_height = h;
    m_fb = new Colour[w * h];
    m_db = new float[w * h];

    for (uint32_t i = 0; i < w*h; i++) {
        m_fb[i] = m_BGC;
        m_db[i] = INFINITY;
    }
}

Framebuffer::Framebuffer(uint32_t w, uint32_t h, Colour c) {
    m_width = w;
    m_height = h;
    m_BGC = c;
    m_fb = new Colour[w * h];
    m_db = new float[w * h];

    for (uint32_t i = 0; i < w*h; i++) {
        m_fb[i] = m_BGC;
        m_db[i] = INFINITY;
    }
}

void Framebuffer::setBGC(Colour c) {
    m_BGC = c;

    for (uint32_t i = 0; i < m_width * m_height; i++) {
        m_fb[i].red = std::max(m_BGC.red, 0.0f);
        m_fb[i].green = std::max(m_BGC.green, 0.0f);
        m_fb[i].blue = std::max(m_BGC.blue, 0.0f);
        m_db[i] = INFINITY;
    }
}

// Set pixel value at position (x, y)
int Framebuffer::setPixel(uint32_t x, uint32_t y, float r, float g, float b) {
    // Chech that position is within image bounds
    if ((x >= m_width) || y >= m_height) {
        return -1;
    }

    // Get index
    uint32_t i = y * m_width + x;

    // Set pixel
    m_fb[i].red = std::max(0.0f, r);
    m_fb[i].green= std::max(0.0f, g);
    m_fb[i].blue= std::max(0.0f, b);

    return 0;
}

int Framebuffer::setPixel(uint32_t x, uint32_t y, Colour c) {
    // Chech that position is within image bounds
    if ((x >= m_width) || y >= m_height) {
        return -1;
    }

    // Get index
    uint32_t i = y * m_width + x;

    // Set pixel
    m_fb[i].red = std::max(0.0f, c.red);
    m_fb[i].green= std::max(0.0f, c.green);
    m_fb[i].blue= std::max(0.0f, c.blue);

    return 0;
}

// Get pixel value at position (x, y)
int Framebuffer::getPixel(uint32_t x, uint32_t y, float& r, float& g, float& b) {
    // Check that position is within image bounds
    if ((x >= m_width) || (y >= m_height)) {
        return -1;
    }
    
    // Get index
    uint32_t i = y * m_width + x;

    // Get r,g,b values
    r = m_fb[i].red;
    g = m_fb[i].green;
    b = m_fb[i].blue;

    return 0;
}

// Set depth at position (x, y)
int Framebuffer::setDepth(uint32_t x, uint32_t y, float d) {
    // Check that position is within image bounds
    if ((x >= m_width) || (y >= m_height)) {
        return -1;
    }

    // Set depth
    m_db[y * m_width + x] = d;
    
    return 0;
}

// Get depth at position (x, y)
int Framebuffer::getDepth(uint32_t x, uint32_t y, float& d) {
    // Check that position is within image bounds
    if ((x >= m_width) || (y >= m_height)) {
        return -1;
    }

    // Get depth
    d = m_db[y * m_width + x];

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

    for (uint32_t i = 0; i < m_width * m_height; i++) {
        // Get max/min r,b,g value
        if (m_fb[i].red > i_max) { i_max = m_fb[i].red; }
        if (m_fb[i].red < i_min) { i_min = m_fb[i].red; }
        if (m_fb[i].red > i_max) { i_max = m_fb[i].green; }
        if (m_fb[i].red < i_min) { i_min = m_fb[i].green; }
        if (m_fb[i].red > i_max) { i_max = m_fb[i].blue; }
        if (m_fb[i].red < i_min) { i_min = m_fb[i].blue; }
        // Get max/min depth value
        if (m_db[i] > d_max && m_db[i] < INFINITY) { d_max = m_db[i]; }
        if (m_db[i] < d_min) { d_min = m_db[i]; }
    }

    float i_diff = i_max - i_min;
    float d_diff = d_max - d_min;

    if (i_diff == 0.0f) { i_diff = 1.0f; }
    if (d_diff == 0.0f) { d_diff = 1.0f; }

    // Write out data
    image << "P6\n"; // PPM type
    depth << "P5\n"; // PPM type

    image << m_width << " " << m_height << "\n255\n"; // width, height, max colour value
    depth << m_width << " " << m_height << "\n255\n"; // width, height, max colour value

    // Write pixel data
    // Pixels are normalized (possible loss of realism)
    for (uint32_t i = 0; i < m_width * m_height; i++) {
        image << (unsigned char)((m_fb[i].red - i_min) / i_diff * 255.00f);   // r
        image << (unsigned char)((m_fb[i].green - i_min) / i_diff * 255.00f); // g
        image << (unsigned char)((m_fb[i].blue - i_min) / i_diff * 255.00f);  // b
        depth << (unsigned char)((m_db[i] - d_min) / d_diff * 255.0f);  // d
    }

    // Close image files
    image.close();
    depth.close();

    return 0;
}

// Destructor
Framebuffer::~Framebuffer() {
    // Free framebuffer
    delete[] m_fb;
    delete[] m_db;
}
#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_

#include <cstdint>

struct Pixel {
    float red = 0.0f;
    float green = 0.0f;
    float blue = 0.0f;
    float depth = 0.0f;
};

class Framebuffer {

    private:
        Pixel* fb = nullptr;

    public:
        uint32_t width = 0;
        uint32_t height = 0;

    public:
        Framebuffer(uint32_t w, uint32_t h);
        int setPixel(uint32_t x, uint32_t y, float r, float g, float b);
        int getPixel(uint32_t x, uint32_t y, float& r, float& g, float& b);
        int setDepth(uint32_t x, uint32_t y, float d);
        int getDepth(uint32_t x, uint32_t y, float& d);
        int plotImage(const char* filename, const char* depthName);  
        ~Framebuffer();
};

#endif
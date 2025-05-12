#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_

#include <cstdint>

#include <math.h>

struct Colour {
    float red = 0.0f;
    float green = 0.0f;
    float blue = 0.0f;
};

class Framebuffer {

    private:
        Colour m_BGC;
        Colour* m_fb = nullptr;
        float* m_db = nullptr;

    public:
        uint32_t m_width = 0;
        uint32_t m_height = 0;

    public:
        Framebuffer(uint32_t w, uint32_t h);
        Framebuffer(uint32_t w, uint32_t h, Colour c);
        void setBGC(Colour c);
        int setPixel(uint32_t x, uint32_t y, float r, float g, float b);
        int setPixel(uint32_t x, uint32_t y, Colour c = {1,1,1});
        int getPixel(uint32_t x, uint32_t y, float& r, float& g, float& b);
        int setDepth(uint32_t x, uint32_t y, float d);
        int getDepth(uint32_t x, uint32_t y, float& d);
        int plotImage(const char* filename, const char* depthName);  
        ~Framebuffer();
};

#endif
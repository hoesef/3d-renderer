#include <cstdint>

#include "../../include/framebuffer/framebuffer.h"
#include "../../include/framebuffer/linedrawer.h"
#include "../../include/maths/vertex.h"
#include "../../include/maths/vector.h"

// Return the absolute value of a number
uint32_t absi(int num) {
    return -num * (num < 0) + num * (num > 0);
}

void drawline(Framebuffer& fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour c) {
    if (absi(x1-x0) > absi(y1-y0)) {
        // Horizontal
        drawlineH(fb, x0, y0, x1, y1, c);
    } else {
        // Vertical
        drawlineV(fb, x0, y0, x1, y1, c);
    }
}

void drawlineH(Framebuffer& fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour c) {
    if (x0 > x1) {
        uint32_t temp = x0;
        x0 = x1;
        x1 = temp;
        temp = y0;
        y0 = y1;
        y1 = temp;
    }

    int dx = x1 - x0;
    int dy = y1 - y0;

    short dir = (1 * (dy > 0)) + (-1 * (dy < 0));

    dy *= dir;

    uint32_t y = y0;
    int p = 2*dy - dx;

    for (int i = 0; i < dx+1; i++) {
        fb.setPixel(x0+i, y, c);
        if (p >= 0) {
            y += dir;
            p -= 2*dx;
        }
        p += 2*dy;
    }
}

void drawlineV(Framebuffer& fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour c) {
    if (y0 > y1) {
        uint32_t temp = x0;
        x0 = x1;
        x1 = temp;
        temp = y0;
        y0 = y1;
        y1 = temp;
    }

    int dx = x1 - x0;
    int dy = y1 - y0;

    short dir = (1 * (dx > 0)) + (-1 * (dx < 0));

    dx *= dir;

    uint32_t x = x0;
    int p = 2*dx - dy;

    for (int i = 0; i < dy+1; i++) {
        fb.setPixel(x, y0+i, c);
        if (p >= 0) {
            x += dir;
            p -= 2*dy;
        }
        p += 2*dx;
    }
}

void drawTriangle(Framebuffer& fb, Vertex& v0, Vertex& v1, Vertex& v2, Colour c) {
    drawline(fb, (uint32_t)v0.m_x, (uint32_t)v0.m_y, (uint32_t)v1.m_x, (uint32_t)v1.m_y, c);
    drawline(fb, (uint32_t)v0.m_x, (uint32_t)v0.m_y, (uint32_t)v2.m_x, (uint32_t)v2.m_y, c);
    drawline(fb, (uint32_t)v1.m_x, (uint32_t)v1.m_y, (uint32_t)v2.m_x, (uint32_t)v2.m_y, c);
}

void fillTriangle(Framebuffer& fb, Vertex& v0, Vertex& v1, Vertex& v2, Colour c){
    uint32_t x_max = (uint32_t)std::max(std::max(v0.m_x, v1.m_x), v2.m_x);
    uint32_t y_max = (uint32_t)std::max(std::max(v0.m_y, v1.m_y), v2.m_y);

    uint32_t x_min = (uint32_t)std::min(std::min(v0.m_x, v1.m_x), v2.m_x);
    uint32_t y_min = (uint32_t)std::min(std::min(v0.m_y, v1.m_y), v2.m_y);

    float depth;

    Vertex p;
    for (uint32_t y = y_min; y <= y_max; y++) {
        for (uint32_t x = x_min; x  <= x_max; x++) {
            p.m_x = (float)x; p.m_y = (float)y;
            float u, v, w;
            if (barycentricCoords(v0, v1, v2, p, u, v, w)) {
                float z = u * v0.m_z + v * v1.m_z + w * v2.m_z;
                if (fb.getDepth(x, y, depth); depth >= z) {
                    continue;
                }
                fb.setPixel(x, y, c);
                fb.setDepth(x, y, z);
            }
        }
    }
}

bool barycentricCoords(const Vertex& A, const Vertex& B, const Vertex& C, const Vertex& P, float& u, float& v, float& w) {
    float denom = ((B.m_y - C.m_y) * (A.m_x - C.m_x) + (C.m_x - B.m_x) * (A.m_y - C.m_y));
    if (denom == 0) { return false; }

    u = ((B.m_y - C.m_y) * (P.m_x - C.m_x) + (C.m_x - B.m_x) * (P.m_y - C.m_y)) / denom;
    v = ((C.m_y - A.m_y) * (P.m_x - C.m_x) + (A.m_x - C.m_x) * (P.m_y - C.m_y)) / denom;
    w = 1.0f - u - v;

    return (u >= 0) && (v >= 0) && (w >= 0);
}
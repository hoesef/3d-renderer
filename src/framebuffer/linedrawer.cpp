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

    float z = (v0.m_z + v1.m_z + v2.m_z) / 3;

    Vertex p;
    for (uint32_t y = y_min; y <= y_max; y++) {
        for (uint32_t x = x_min; x  <= x_max; x++) {
            p.m_x = (float)x; p.m_y = (float)y;
            float depth;
            if (fb.getDepth(x, y, depth); z >= depth) {
                continue;
            }
            if (pointInTriangle(v0, v1, v2, p)) {
                fb.setPixel(x, y, c);
                fb.setDepth(x, y, z);
            }
        }
    }
}

bool pointInTriangle(Vertex& A, Vertex& B, Vertex& C, Vertex& P) {
    Vector v0 = C - A;
    Vector v1 = B - A;
    Vector v2 = P - A;

    float dot00 = v0.dot(v0);
    float dot01 = v0.dot(v1);
    float dot02 = v0.dot(v2);
    float dot11 = v1.dot(v1);
    float dot12 = v1.dot(v2);

    float denom = dot00 * dot11 - dot01 * dot01;
    float u = (dot11 * dot02 - dot01 * dot12) / denom;
    float v = (dot00 * dot12 - dot01 * dot02) / denom;

    return ((u >= 0) && (v >= 0) && (u+v<=1));

}
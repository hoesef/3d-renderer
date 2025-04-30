#include <cstdint>

#include "../../include/framebuffer/framebuffer.h"
#include "../../include/framebuffer/linedrawer.h"

// Return the absolute value of a number
uint32_t abs(int num) {
    return -num * (num < 0) + num * (num > 0);
}

void drawline(Framebuffer& fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) {
    if (abs(x1-x0) > abs(y1-y0)) {
        // Horizontal
        drawlineH(fb, x0, y0, x1, y1);
    } else {
        // Vertical
        drawlineV(fb, x0, y0, x1, y1);
    }
}

void drawlineH(Framebuffer& fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) {
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
        fb.setPixel(x0+i, y, 1.0f, 1.0f, 1.0f);
        if (p >= 0) {
            y += dir;
            p -= 2*dx;
        }
        p += 2*dy;
    }
}

void drawlineV(Framebuffer& fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) {
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
        fb.setPixel(x, y0+i, 1.0f, 1.0f, 1.0f);
        if (p >= 0) {
            x += dir;
            p -= 2*dy;
        }
        p += 2*dx;
    }
}
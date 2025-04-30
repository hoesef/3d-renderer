#ifndef LINEDRAWER_H_
#define LINEDRAWER_H_

#include <cstdint>
#include "../../include/framebuffer/framebuffer.h"

void drawline(Framebuffer& fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);
void drawlineH(Framebuffer& fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);
void drawlineV(Framebuffer& fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);

#endif
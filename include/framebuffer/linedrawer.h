#ifndef LINEDRAWER_H_
#define LINEDRAWER_H_

#include <cstdint>
#include "../../include/framebuffer/framebuffer.h"

class Vertex;

void drawline(Framebuffer& fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);
void drawlineH(Framebuffer& fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);
void drawlineV(Framebuffer& fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);

// Draw Triangle
// void drawTriangle(Framebuffer& fb, float x0, float y0, float x1, float y1, float x2, float y2);
void drawTriangle(Framebuffer& fb, Vertex& v0, Vertex& v1, Vertex& v2);
void fillTriangle(Framebuffer& fb, Vertex& v0, Vertex& v1, Vertex& v2);
bool pointInTriangle(Vertex& A, Vertex& B, Vertex& C, Vertex& P);

#endif
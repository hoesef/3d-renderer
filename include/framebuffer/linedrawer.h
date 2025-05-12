#ifndef LINEDRAWER_H_
#define LINEDRAWER_H_

typedef unsigned int uint32_t;
class Framebuffer;
class Vertex;
struct Colour;


void drawline(Framebuffer& fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour c = {1,1,1});
void drawlineH(Framebuffer& fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour c = {1,1,1});
void drawlineV(Framebuffer& fb, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour c = {1,1,1});

// Draw Triangle
void drawTriangle(Framebuffer& fb, Vertex& v0, Vertex& v1, Vertex& v2, Colour c = {1,1,1});
void fillTriangle(Framebuffer& fb, Vertex& v0, Vertex& v1, Vertex& v2, Colour c = {1,1,1});
bool pointInTriangle(Vertex& A, Vertex& B, Vertex& C, Vertex& P);

#endif
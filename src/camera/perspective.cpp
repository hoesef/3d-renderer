#include "..\..\include\camera\perspective.h"
#include <math.h>
#include "..\..\include\framebuffer\linedrawer.h"

// Check if math variables have been defined
#ifndef M_PI
#define M_PI 3.1415926535f
#endif

void homogenize(Vertex& v) {
    if (v.m_w != 1 && v.m_w != 0) {
        v.m_x = v.m_x / v.m_w;
        v.m_y = v.m_y / v.m_w;
        v.m_z = v.m_z / v.m_w;
        v.m_w = v.m_w / v.m_w;
    }
}

float max(float a, float b) {
    return a*(a > b) + b*(b > a);
}
float min(float a, float b) {
    return a*(a < b) + b*(b < a);
}

Perspective::Perspective() { makeProjMatrix(); }
Perspective::Perspective(int width, int height, float fov) {
    m_width = width;
    m_height = height;
    m_a = (float)width / (float)height;
    m_fov = fov;
    makeProjMatrix();
}
void Perspective::render(Polymesh& mesh, Framebuffer& fb) {

    float r_x = 231 * M_PI / 180;
    Matrix4x4 rotate_x(1.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, cos(r_x), -sin(r_x), 0,
                        0.0f, sin(r_x), cos(r_x), 0, 
                        0.0f, 0.0f, 0.0f, 1.0f);

    float r_y = 231 * M_PI / 180;
    Matrix4x4 rotate_y(cos(r_y), 0.0f, sin(r_y), 0.0f,
                        0.0f, 1.0f, 0.0f, 0.0f,
                        -sin(r_y), 0.0f, cos(r_y), 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f);

    for (unsigned int i = 0; i < mesh.m_tri_count; i++) {
        // Get vertex data
        Vertex v0 = mesh.m_vertices[mesh.m_tris[i].v0];
        Vertex v1 = mesh.m_vertices[mesh.m_tris[i].v1];
        Vertex v2 = mesh.m_vertices[mesh.m_tris[i].v2];

        // Position vertex (temporary, will be moved to object.applyTransform)
        v0 = rotate_x * v0;
        v1 = rotate_x * v1;
        v2 = rotate_x * v2;

        v0 = rotate_y * v0;
        v1 = rotate_y * v1;
        v2 = rotate_y * v2;

        float offset = 2.0f;
        v0.m_z += offset;
        v1.m_z += offset;
        v2.m_z += offset;

        // Get surface normal
        Vector normal, line1, line2;
        line1 = v1 - v0;
        line2 = v2 - v0;

        normal = line1.cross(line2);
        normal.normalize();
        
        // Check if face is towards camera
        if (normal.dot(v0.toVector() - pos) >= 0) { continue; }

        // Project face to canvas
        v0 = m_proj * v0;
        v1 = m_proj * v1;
        v2 = m_proj * v2;

        // w=z, so divide by w (perspective divide)
        homogenize(v0);
        homogenize(v1);
        homogenize(v2);        

        // Convert to NCD, then scale to actual image
        float scaleX = 0.5f * m_width;
        float scaleY = 0.5f * m_height;
        v0.m_x = (v0.m_x + 1.0f) * scaleX; v0.m_y = (1.0f - v0.m_y) * scaleY;
        v1.m_x = (v1.m_x + 1.0f) * scaleX; v1.m_y = (1.0f - v1.m_y) * scaleY;
        v2.m_x = (v2.m_x + 1.0f) * scaleX; v2.m_y = (1.0f - v2.m_y) * scaleY;

        // Clamping
        v0.m_x = min(max(0.0f, v0.m_x), (float)m_width); v0.m_y = min(max(0.0f, v0.m_y), (float)m_height);
        v1.m_x = min(max(0.0f, v1.m_x), (float)m_width); v1.m_y = min(max(0.0f, v1.m_y), (float)m_height);
        v2.m_x = min(max(0.0f, v2.m_x), (float)m_width); v2.m_y = min(max(0.0f, v2.m_y), (float)m_height);

        // Drawline
        drawline(fb, (uint32_t)v0.m_x, (uint32_t)v0.m_y, (uint32_t)v1.m_x, (uint32_t)v1.m_y);
        drawline(fb, (uint32_t)v0.m_x, (uint32_t)v0.m_y, (uint32_t)v2.m_x, (uint32_t)v2.m_y);
        drawline(fb, (uint32_t)v1.m_x, (uint32_t)v1.m_y, (uint32_t)v2.m_x, (uint32_t)v2.m_y);
    }
}
void Perspective::makeProjMatrix() {
    float f = 1 / tanf(m_fov * 0.5f * M_PI / 180);

    m_proj = Matrix4x4(
        f / m_a, 0, 0, 0,
              0, f, 0, 0,
              0, 0, (m_zFar + m_zNear)/(m_zNear - m_zFar), (2 * m_zFar * m_zNear)/(m_zNear-m_zFar),
              0, 0, -1, 0);
}
Perspective::~Perspective() {}
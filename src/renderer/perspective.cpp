#include "..\..\include\renderer\perspective.h"
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

Perspective::Perspective() {
    m_proj = Matrix4x4::projectionMatrix(m_fov, m_a, m_zNear, m_zFar);
}
Perspective::Perspective(int width, int height, float fov) {
    m_width = width;
    m_height = height;
    m_a = (float)height / (float)width;
    m_fov = fov;
    m_proj = Matrix4x4::projectionMatrix(m_fov, m_a, m_zNear, m_zFar);
}
void Perspective::render(Camera& camera, Polymesh& mesh, Framebuffer& fb) {

    // Check framebuffer and camera are using the same dimensions
    // Probably just temporary, there may be a reason why you'd want them to be different?
    if (m_width != fb.m_width || m_height != m_height) {
        std::cout << "Framebuffer is not the same size as camera screen. Using framebuffer values\n";
        m_width = fb.m_width;
        m_height = fb.m_height;
        m_a = (float)m_height / (float)m_width;
        m_proj = Matrix4x4::projectionMatrix(m_fov, m_a, m_zNear, m_zFar);
    }

    // Get object's normal matrix
    Matrix4x4 normalMatrix = mesh.transform.getNormalMatrix();

    for (unsigned int i = 0; i < mesh.m_tri_count; i++) {
        // Get vertex data
        Vertex v0 = mesh.m_vertices[mesh.m_tris[i].v0];
        Vertex v1 = mesh.m_vertices[mesh.m_tris[i].v1];
        Vertex v2 = mesh.m_vertices[mesh.m_tris[i].v2];

        // Get surface normal
        Vector normal, line1, line2;
        line1 = v1 - v0;
        line2 = v2 - v0;
        normal = line1.cross(line2);
        normal = normalMatrix * normal;
        normal.normalize();

        // Position vertex (temporary, will be moved to object.applyTransform)
        Matrix4x4 transform = mesh.transform.get();
        v0 = transform * v0;
        v1 = transform * v1;
        v2 = transform * v2;

        // Check if face is towards camera
        if (normal.dot(v0.toVector() - camera.pos) >= 0) { continue; }

        v0 = camera.worldToCamera * v0;
        v1 = camera.worldToCamera * v1;
        v2 = camera.worldToCamera * v2;

        // Project face to canvas
        v0 = m_proj * v0;
        v1 = m_proj * v1;
        v2 = m_proj * v2;

        if (v0.m_w <= 0 || v1.m_w <= 0 || v2.m_w <= 0) {continue;}

        // w=z, so divide by w (perspective divide)
        homogenize(v0);
        homogenize(v1);
        homogenize(v2);

        // Convert NCD to clip space
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
        // Very basic temporary lighting
        Vector lDir(0,0,1);
        float x = normal.dot(lDir);
        Colour c = mesh.getColour();
        c.red *= x; c.green *= x; c.blue *= x;
        // c.red += c.red*x; c.green += c.green*x; c.blue += c.blue*x;
        fillTriangle(fb, v0, v1, v2, c);
    }
}
Perspective::~Perspective() {}
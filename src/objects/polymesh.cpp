#include <fstream>
#include <string>

#include <iostream>

#include "../../include/objects/polymesh.h"

void Polymesh::print() {
    std::cout << "\nVertex data\n";
    for (unsigned int i = 0; i < m_vertex_count; i++) {
        std::cout << "(" << m_vertices[i].m_x << ", " << m_vertices[i].m_y << ", " << m_vertices[i].m_z << ", " << m_vertices[i].m_w << ")\n";
    }
    std::cout << "\nVertex normals\n";
    for (unsigned int i = 0; i < m_normal_count; i++) {
        std::cout << "(" << m_normals[i].m_x << ", " << m_normals[i].m_y << ", " << m_normals[i].m_z << ")\n";
    }

    std::cout << "\nTexture Cords\n";
    for (unsigned int i = 0; i < m_texture_count; i++) {
        std::cout << "(" << m_text_cords[i].m_x << ", " << m_text_cords[i].m_y << ", " << m_text_cords[i].m_z << ")\n";
    }
    
    std::cout << "\nTriangles\n";
    for (unsigned int i = 0; i < m_tri_count; i++) {
        std::cout << "(" << m_tris[i].v0 << ", " << m_tris[i].v1 << ", " << m_tris[i].v2 << ")\n";
    }
}

// Rotation
void Polymesh::rotate(float x, float y, float z) {
    m_transform_data.rotate_x += x;
    m_transform_data.rotate_y += y;
    m_transform_data.rotate_z += z;
    m_dirty_transform = true;
}
void Polymesh::rotate_x(float x) {
    m_transform_data.rotate_x += x;
    m_dirty_transform = true;
}
void Polymesh::rotate_y(float y) {
    m_transform_data.rotate_y += y;
    m_dirty_transform = true;
}
void Polymesh::rotate_z(float z) {
    m_transform_data.rotate_z += z;
    m_dirty_transform = true;
}
// Offset
void Polymesh::translate(const Vector& v) {
    m_transform_data.offset = m_transform_data.offset + v;
    m_dirty_transform = true;
}
void Polymesh::translate(float x, float y, float z) {
    m_transform_data.offset.m_x = x;
    m_transform_data.offset.m_y = y;
    m_transform_data.offset.m_z = z;
    m_dirty_transform = true;
}
// Scale
void Polymesh::scale(float x, float y, float z) {
    m_transform_data.scale_x = x;
    m_transform_data.scale_y = y;
    m_transform_data.scale_z = z;
    m_dirty_transform = true;
}
void Polymesh::scale_x(float x) {
    m_transform_data.scale_x = x;
    m_dirty_transform = true;
}
void Polymesh::scale_y(float y) {
    m_transform_data.scale_y = y;
    m_dirty_transform = true;
}
void Polymesh::scale_z(float z) {
    m_transform_data.scale_z = z;
    m_dirty_transform = true;
}
// Get transform
Matrix4x4& Polymesh::getTransform() {
    if (m_dirty_transform) {
        Matrix4x4 T = translationMatrix(m_transform_data.offset);
        Matrix4x4 R = rotationMatrixX(m_transform_data.rotate_x) * rotationMatrixY(m_transform_data.rotate_y) * rotationMatrixZ(m_transform_data.rotate_z);
        Matrix4x4 S = scaleMatrix(m_transform_data.scale_x, m_transform_data.scale_y, m_transform_data.scale_z);
        m_transform = T * R * S;
        m_dirty_transform = false;
    }
    return m_transform;
}

void Polymesh::resetTransform() {
    m_transform = Matrix4x4();
}
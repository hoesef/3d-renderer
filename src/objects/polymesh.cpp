#include <fstream>
#include <string>

#include <iostream>

#include "../../include/objects/polymesh.h"

void Polymesh::setColour(Colour c) {
    m_col = c;
}

Colour Polymesh::getColour() {
    return m_col;
}

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

// // Rotation
// void Polymesh::rotate(float x, float y, float z) {
//     transform.rotate(x,y,z);
// }
// void Polymesh::rotate_x(float x) {
//     transform.rotateX(x);
// }
// void Polymesh::rotate_y(float y) {
//     transform.rotateY(y);
// }
// void Polymesh::rotate_z(float z) {
//     transform.rotateZ(z);
// }
// // Offset
// void Polymesh::translate(const Vector& v) {
//     transform.translate(v);
// }
// void Polymesh::translate(float x, float y, float z) {
//     transform.translate(x,y,z);
// }
// // Scale
// void Polymesh::scale(float x, float y, float z) {
//     transform.scale(x,y,z);
// }
// void Polymesh::scale_x(float x) {
//     transform.scaleX(x);
// }
// void Polymesh::scale_y(float y) {
//     transform.scaleY(y);
// }
// void Polymesh::scale_z(float z) {
//     transform.scaleZ(z);
// }
// // Get transform
// const Matrix4x4 Polymesh::getTransform() {
//     return transform.get();
// }

// void Polymesh::resetTransform() {
//     transform.reset();
// }
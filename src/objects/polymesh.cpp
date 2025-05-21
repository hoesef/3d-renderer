#include <iostream>

#include "..\..\include\objects\polymesh.h"

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
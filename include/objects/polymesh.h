#ifndef POLYMESH_H_
#define POLYMESH_H_

#include <vector>

#include "..\maths\vertex.h"
#include "..\maths\vector.h"

struct Triangle {
    unsigned int v0 = 0;
    unsigned int v1 = 0;
    unsigned int v2 = 0;
};


class Polymesh {

    public:
        // Vertex
        unsigned int m_vertex_count = 0;
        std::vector<Vertex> m_vertices;
        // Normals
        unsigned int m_normal_count = 0;
        std::vector<Vector> m_normals;
        // Textcords
        unsigned int m_texture_count = 0;
        std::vector<Vector> m_text_cords;
        // Triangles
        unsigned int m_tri_count = 0;
        std::vector<Triangle> m_tris;

    public:
        Polymesh() {};
        void print();
        ~Polymesh() {};

};

#endif
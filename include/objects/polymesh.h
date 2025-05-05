#ifndef POLYMESH_H_
#define POLYMESH_H_

#include <vector>

#include "..\maths\vertex.h"
#include "..\maths\vector.h"

class Polymesh {

    private:
    // Vertex
    unsigned int m_vertex_count = 0;
    std::vector<Vertex> m_vertices;
    // Normals
    // int m_normal_count = 0;
    std::vector<Vector> m_normals;
    // Textcords
    // Triangles

    public:
        Polymesh(const char* filename, bool &sucess);
        void print();
        ~Polymesh();

};

#endif
#ifndef POLYMESH_H_
#define POLYMESH_H_

#include <vector>

#include "..\maths\vertex.h"
#include "..\maths\vector.h"
#include "..\maths\matrix.h"
#include "..\maths\transform.h"

#include "..\framebuffer\framebuffer.h"

struct Triangle {
    unsigned int v0 = 0;
    unsigned int v1 = 0;
    unsigned int v2 = 0;
};

// TODO:
// material
// center
class Polymesh {

    private:
        Colour m_col;
        // Material material

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
        // Transform
        Transform transform;

    public:
        Polymesh() {};
        void setColour(Colour c);
        Colour getColour();
        void print();
        ~Polymesh() {};

};

#endif
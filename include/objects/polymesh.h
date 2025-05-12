#ifndef POLYMESH_H_
#define POLYMESH_H_

#include <vector>

#include "..\maths\vertex.h"
#include "..\maths\vector.h"
#include "..\maths\matrix.h"

#include "..\framebuffer\framebuffer.h"

struct Triangle {
    unsigned int v0 = 0;
    unsigned int v1 = 0;
    unsigned int v2 = 0;
};

struct TransformData {
    // Rotation
    float rotate_x = 0.0f;
    float rotate_y = 0.0f;
    float rotate_z = 0.0f;
    // Offset
    Vector offset;
    // Scale
    float scale_x = 1.0f;
    float scale_y = 1.0f;
    float scale_z = 1.0f;
};

// TODO:
// material
// transform
// transform_data (offset, rotation, scale)
// dirty bit
// center
class Polymesh {

    private:
        Colour m_col;
        Matrix4x4 m_transform;
        bool m_dirty_transform = false;
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

        TransformData m_transform_data;

    public:
        Polymesh() {};
        void setColour(Colour c);
        Colour getColour();
        void print();
        // Rotation
        void rotate(float x, float y, float z);
        void rotate_x(float x);
        void rotate_y(float y);
        void rotate_z(float z);
        // Offset
        void translate(const Vector& v);
        void translate(float x, float y, float z);
        // Scale
        void scale(float x, float y, float z);
        void scale_x(float x);
        void scale_y(float y);
        void scale_z(float z);
        // Get transform
        Matrix4x4& getTransform();
        void resetTransform();

        ~Polymesh() {};

};

#endif
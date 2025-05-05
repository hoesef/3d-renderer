#ifndef VERTEX_H_
#define VERTEX_H_

class Vertex {

    public:
        float m_x = 0.0f;
        float m_y = 0.0f;
        float m_z = 0.0f;
        float m_w = 1.0f;

    public:
        // Constructor
        Vertex();
        Vertex(float x, float y, float z);
        Vertex(float x, float y, float z, float w);
        // Copy constructor
        Vertex(const Vertex& other);
        // Move constructor
        Vertex(Vertex&& other);
        // Assignment operator
        Vertex& operator=(const Vertex& other);
        // Move operator
        Vertex& operator=(Vertex&&other);
        // Apply transform
        // Destructor
        ~Vertex();

};

#endif
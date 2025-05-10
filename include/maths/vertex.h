#ifndef VERTEX_H_
#define VERTEX_H_

// Forward decloration of vector
class Vector;

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
        // Addition
        Vertex operator+(Vertex& other);
        // Subtraction (distance from one to the other)
        Vector operator-(Vertex& other);
        // Convert to a vector
        Vector toVector();
        // Destructor
        ~Vertex();

};

#endif
#ifndef VECTOR_H_
#define VECTOR_H_

// Forward decloration of vertex
class Vertex;

class Vector {

    public:
        float m_x = 0.0f;
        float m_y = 0.0f;
        float m_z = 0.0f;

    public:
        // Constructor
        Vector();
        Vector(float x, float y, float z);
        // Copy constuctor
        Vector(const Vector& other);
        // Move constructor
        Vector(Vector&& other);
        // Assignment operator
        Vector& operator=(const Vector& other);
        // Move operator
        Vector& operator=(Vector&& other);
        // Addition
        // Subtraction
        // Multiplication
        // Division
        // Magnitude
        // To unit vector
        // Dot product
        // Cross product
        // Destructor
        ~Vector();

};

#endif
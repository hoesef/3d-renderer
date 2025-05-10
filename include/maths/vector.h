#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>

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
        Vector operator+(float n);
        Vector operator+(const Vector& other);
        // Subtraction
        Vector operator-(float n);
        Vector operator-(const Vector& other);
        // Multiplication
        Vector operator*(float n);
        // Division
        Vector operator/(float n);
        // Magnitude
        float magnitude();
        // To unit vector
        Vector normalize();
        // Distance
        float distance(const Vector& other);
        // Dot product
        float dot(const Vector& other);
        // Cross product
        Vector cross(const Vector& other);
        // Convert to Vertex
        Vertex toVertex();
        friend std::ostream& operator<<(std::ostream& os, const Vector& v);
        // Destructor
        ~Vector();

};

#endif
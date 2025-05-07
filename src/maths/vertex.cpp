#include "../../include/maths/vertex.h"

#include <iostream>

// Constructor
Vertex::Vertex() {
    std::cout << "Default contstructor\n";
}
Vertex::Vertex(float x, float y, float z) {
    m_x=x, m_y=y, m_z=z;
    std::cout << "xyz contstructor\n";
}
Vertex::Vertex(float x, float y, float z, float w) {
    std::cout << "xyzw contstructor\n";
    m_x=x, m_y=y, m_z=z, m_w=w;
}

// Copy Constructor
Vertex::Vertex(const Vertex& other) {
    std::cout << "copy constructor\n";
    m_x = other.m_x;
    m_y = other.m_y;
    m_z = other.m_z;
    m_w = other.m_w;
}

// Move constructor
Vertex::Vertex(Vertex&& other) {
    std::cout << "move constructor\n";
    m_x = other.m_x;
    m_y = other.m_y;
    m_z = other.m_z;
    m_w = other.m_w;

    other.m_x = 0.0f;
    other.m_y = 0.0f;
    other.m_z = 0.0f;
    other.m_w = 1.0f;
}

// Assignment operator
Vertex& Vertex::operator=(const Vertex& other) {
    std::cout << "assignment operator\n";
    if (this != &other) {
        m_x = other.m_x;
        m_y = other.m_y;
        m_z = other.m_z;
        m_w = other.m_w;
    }

    return *this;
}

// Move operator
Vertex& Vertex::operator=(Vertex&& other) {
    std::cout << "move operator\n";
    if (this != &other) {
        m_x = other.m_x;
        m_y = other.m_y;
        m_z = other.m_z;
        m_w = other.m_w;

        other.m_x = 0.0f;
        other.m_y = 0.0f;
        other.m_z = 0.0f;
        other.m_w = 1.0f;
    }   

    return *this;
}

// Destructor
Vertex::~Vertex() {}
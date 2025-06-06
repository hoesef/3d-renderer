#include "..\..\include\maths\vertex.h"
#include "..\..\include\maths\vector.h"

// Constructor
Vertex::Vertex() {}
Vertex::Vertex(float x, float y, float z) {
    m_x=x, m_y=y, m_z=z;
}
Vertex::Vertex(float x, float y, float z, float w) {
    m_x=x, m_y=y, m_z=z, m_w=w;
}

// Copy Constructor
Vertex::Vertex(const Vertex& other) {
    m_x = other.m_x;
    m_y = other.m_y;
    m_z = other.m_z;
    m_w = other.m_w;
}

// Move constructor
Vertex::Vertex(Vertex&& other) {
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

// Addition
Vertex Vertex::operator+(Vertex& other) {
    return Vertex(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
}

// Subtraction (distance from one to another)
Vector Vertex::operator-(Vertex& other) {
    return Vector(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
}

// Convert to a Vector
Vector Vertex::toVector() {
    return Vector(m_x, m_y, m_z);
}

std::ostream& operator<<(std::ostream& os, const Vertex& v) {
    os << "(" << v.m_x << ", " << v.m_y << ", " << v.m_z <<  ", " << v.m_w << ")";
    return os;
}

// Destructor
Vertex::~Vertex() {}
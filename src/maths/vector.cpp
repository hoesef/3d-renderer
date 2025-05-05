#include "../../include/maths/vector.h"

Vector::Vector() {}
Vector::Vector(float x, float y, float z) {m_x=x, m_y=y, m_z=z;}
// Copy constuctor
Vector::Vector(const Vector& other) {
    m_x = other.m_x;
    m_y = other.m_y;
    m_z = other.m_z;
}
// Move constructor
Vector::Vector(Vector&& other) {
    m_x = other.m_x;
    m_y = other.m_y;
    m_z = other.m_z;

    other.m_x = 0.0f;
    other.m_y = 0.0f;
    other.m_z = 0.0f;
}
// Assignment operator
Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        m_x = other.m_x;
        m_y = other.m_y;
        m_z = other.m_z;
    }

    return *this;
}
// Move operator
Vector& Vector::operator=(Vector&& other) {
    if (this != &other) {
        m_x = other.m_x;
        m_y = other.m_y;
        m_z = other.m_z;

        other.m_x = 0.0f;
        other.m_y = 0.0f;
        other.m_z = 0.0f;
    }

    return *this;
}
// Addition
// Subtraction
// Multiplication
// Division
// Dot product
// Cross product
// Destructor
Vector::~Vector() {}
#include <math.h>

#include "..\..\include\maths\vector.h"
#include "..\..\include\maths\vertex.h"

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
Vector Vector::operator+(float n) {
    return Vector(m_x + n, m_y + n, m_z + n);
}
Vector Vector::operator+(const Vector& other) {
    return Vector(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
}
Vector& Vector::operator+=(float n) {
    m_x += n;
    m_y += n;
    m_z += n;
    return *this;
}
Vector& Vector::operator+=(const Vector& other) {
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;
    return *this;
}
// Subtraction
Vector Vector::operator-(float n) {
    return Vector(m_x - n, m_y - n, m_z - n);
}
Vector Vector::operator-(const Vector& other) {
    return Vector(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
}
Vector& Vector::operator-=(float n) {
    m_x -= n;
    m_y -= n;
    m_z -= n;
    return *this;
}
// Multiplication
Vector Vector::operator*(float n) {
    return Vector(m_x * n, m_y * n, m_z * n);
}
Vector& Vector::operator*=(float n) {
    m_x *= n;
    m_y *= n;
    m_z *= n;
    return *this;
}
// Division
Vector Vector::operator/(float n) {
    if (n == 0) {
        return Vector(0, 0, 0);
    }
    return Vector(m_x / n, m_y / n, m_z / n);
}
Vector& Vector::operator/=(float n) {
    if (n != 0) {
        m_x /= n;
        m_y /= n;
        m_z /= n;
    }
    return *this;
}
// Magnitude
float Vector::magnitude() {
    return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}
// Normalize
void Vector::normalize() {
    float mag = magnitude();
    if (mag == 0) {
        m_x = 0; m_y = 0; m_z = 0;
    }
    m_x /= mag; m_y /= mag; m_z /= mag;
}
void Vector::normalize(Vector& norm) {
    float mag = magnitude();
    if (mag == 0) {
        norm.m_x = 0; norm.m_y = 0; norm.m_z = 0;
    }
    norm.m_x /= mag; norm.m_y /= mag; norm.m_z /= mag;
}
float Vector::distance(const Vector& other) {
    return (*this - other).magnitude();
}
// Dot product
float Vector::dot(const Vector& other) {
    return (m_x * other.m_x + 
            m_y * other.m_y +
            m_z * other.m_z);
}
// Cross product
Vector Vector::cross(const Vector& other) {
    return Vector(m_y * other.m_z - m_z * other.m_y,
                  m_z * other.m_x - m_x * other.m_z,
                  m_x * other.m_y - m_y * other.m_x);
}
// Convert to Vertex
Vertex Vector::toVertex() {
    return Vertex(m_x, m_y, m_z, 0);
}
std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "(" << v.m_x << ", " << v.m_y << ", " << v.m_z << ")";
    return os;
}
// Destructor
Vector::~Vector() {}
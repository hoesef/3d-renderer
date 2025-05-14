#include <math.h>

#include "..\..\include\maths\matrix.h"

#ifndef M_PI
#define M_PI 3.1415926535f
#endif

#define RADIAN(x) (x * M_PI / 180) 

// Constructor
Matrix4x4::Matrix4x4() {
    // Set diag to 1 (identity matrix)
    m_mat[0]  = 1.0f;
    m_mat[5]  = 1.0f;
    m_mat[10] = 1.0f;
    m_mat[15] = 1.0f;
}
Matrix4x4::Matrix4x4(
    float x0, float y0, float z0, float w0,
    float x1, float y1, float z1, float w1,
    float x2, float y2, float z2, float w2,
    float x3, float y3, float z3, float w3
) {
    // Row 1
    m_mat[0] = x0;
    m_mat[1] = y0;
    m_mat[2] = z0;
    m_mat[3] = w0;
    // Row 2
    m_mat[4] = x1;
    m_mat[5] = y1;
    m_mat[6] = z1;
    m_mat[7] = w1;
    // Row 3
    m_mat[8]  = x2;
    m_mat[9]  = y2;
    m_mat[10] = z2;
    m_mat[11] = w2;
    // Row 4
    m_mat[12] = x3;
    m_mat[13] = y3;
    m_mat[14] = z3;
    m_mat[15] = w3;
}
// Assignment operator
Matrix4x4& Matrix4x4::operator=(const Matrix4x4& other) {
    if (this != &other) {
        for (int i = 0; i < 16; i++) {
            m_mat[i] = other.m_mat[i];
        }
    }
    return *this;
}
// Addition
Matrix4x4 Matrix4x4::operator+(float n) {
    return Matrix4x4(
        m_mat[0]  + n, m_mat[1]  + n, m_mat[2]  + n, m_mat[3]  + n,
        m_mat[4]  + n, m_mat[5]  + n, m_mat[6]  + n, m_mat[7]  + n,
        m_mat[8]  + n, m_mat[9]  + n, m_mat[10] + n, m_mat[11] + n,
        m_mat[12] + n, m_mat[13] + n, m_mat[14] + n, m_mat[15] + n);
}
Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) {
    return Matrix4x4(
        m_mat[0]  + other.m_mat[0],  m_mat[1]  + other.m_mat[1],  m_mat[2]  + other.m_mat[2],  m_mat[3]  + other.m_mat[3],
        m_mat[4]  + other.m_mat[4],  m_mat[5]  + other.m_mat[5],  m_mat[6]  + other.m_mat[6],  m_mat[7]  + other.m_mat[7],
        m_mat[8]  + other.m_mat[8],  m_mat[9]  + other.m_mat[9],  m_mat[10] + other.m_mat[10], m_mat[11] + other.m_mat[11],
        m_mat[12] + other.m_mat[12], m_mat[13] + other.m_mat[13], m_mat[14] + other.m_mat[14], m_mat[15] + other.m_mat[15]);
}
// Subtraction
Matrix4x4 Matrix4x4::operator-(float n) {
    return Matrix4x4(
        m_mat[0]  - n, m_mat[1]  - n, m_mat[2]  - n, m_mat[3]  - n,
        m_mat[4]  - n, m_mat[5]  - n, m_mat[6]  - n, m_mat[7]  - n,
        m_mat[8]  - n, m_mat[9]  - n, m_mat[10] - n, m_mat[11] - n,
        m_mat[12] - n, m_mat[13] - n, m_mat[14] - n, m_mat[15] - n);
}
Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) {
    return Matrix4x4(
        m_mat[0]  - other.m_mat[0],  m_mat[1]  - other.m_mat[1],  m_mat[2]  - other.m_mat[2],  m_mat[3]  - other.m_mat[3],
        m_mat[4]  - other.m_mat[4],  m_mat[5]  - other.m_mat[5],  m_mat[6]  - other.m_mat[6],  m_mat[7]  - other.m_mat[7],
        m_mat[8]  - other.m_mat[8],  m_mat[9]  - other.m_mat[9],  m_mat[10] - other.m_mat[10], m_mat[11] - other.m_mat[11],
        m_mat[12] - other.m_mat[12], m_mat[13] - other.m_mat[13], m_mat[14] - other.m_mat[14], m_mat[15] - other.m_mat[15]);
}
// Multiplication
Matrix4x4 Matrix4x4::operator*(float n) {
    return Matrix4x4(
        m_mat[0]  * n, m_mat[1]  * n, m_mat[2]  * n, m_mat[3]  * n,
        m_mat[4]  * n, m_mat[5]  * n, m_mat[6]  * n, m_mat[7]  * n,
        m_mat[8]  * n, m_mat[9]  * n, m_mat[10] * n, m_mat[11] * n,
        m_mat[12] * n, m_mat[13] * n, m_mat[14] * n, m_mat[15] * n);
}
Vector Matrix4x4::operator*(const Vector& v) {
    float x, y, z = 0.0f;

    x = v.m_x * m_mat[0] + 
        v.m_y * m_mat[1] +
        v.m_z * m_mat[2];

    y = v.m_x * m_mat[4] + 
        v.m_y * m_mat[5] +
        v.m_z * m_mat[6];

    z = v.m_x * m_mat[8] + 
        v.m_y * m_mat[9] +
        v.m_z * m_mat[10];

    return Vector(x, y, z);
}
Vertex Matrix4x4::operator*(const Vertex& v) {
    float x, y, z, w = 0.0f;

    x = v.m_x * m_mat[0] + 
        v.m_y * m_mat[1] +
        v.m_z * m_mat[2] +
        v.m_w * m_mat[3];

    y = v.m_x * m_mat[4] + 
        v.m_y * m_mat[5] +
        v.m_z * m_mat[6] +
        v.m_w * m_mat[7];

    z = v.m_x * m_mat[8]  + 
        v.m_y * m_mat[9]  +
        v.m_z * m_mat[10] +
        v.m_w * m_mat[11];

    w = v.m_x * m_mat[12] +
        v.m_y * m_mat[13] +
        v.m_z * m_mat[14] + 
        v.m_w * m_mat[15];

    return Vertex(x, y, z, w);
}
Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) {
    Matrix4x4 result;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            result.m_mat[row*4+col] = 0.0f;
            for (int k = 0; k < 4; k++) {
                result.m_mat[row*4+col] += m_mat[row*4+k] * other.m_mat[k*4+col];
            }
        }
    }
    return result;
}
// Transpose
Matrix4x4 Matrix4x4::transpose() {
     return Matrix4x4(
        m_mat[0], m_mat[4], m_mat[8],  m_mat[12],
        m_mat[1], m_mat[5], m_mat[9],  m_mat[13],
        m_mat[2], m_mat[6], m_mat[10], m_mat[14],
        m_mat[3], m_mat[7], m_mat[11], m_mat[15]);
}
void Matrix4x4::T() {
    Matrix4x4 T;
    for (int row = 0; row < 4; row++) {
        for (int col =0; col < 4; col++) {
            T.m_mat[col * 4 + row] = m_mat[row * 4 + col];
        }
    }
    *this = T;
}
// Inverse
bool Matrix4x4::inverse(Matrix4x4& out) {
    Matrix4x4 inv;
    float det;
    inv.m_mat[0] =  m_mat[5]  *  m_mat[10] *  m_mat[15] - 
                    m_mat[5]  *  m_mat[11] *  m_mat[14] - 
                    m_mat[9]  *  m_mat[6]  *  m_mat[15] + 
                    m_mat[9]  *  m_mat[7]  *  m_mat[14] +
                    m_mat[13] *  m_mat[6]  *  m_mat[11] - 
                    m_mat[13] *  m_mat[7]  *  m_mat[10];

    inv.m_mat[4] = - m_mat[4]  *  m_mat[10] *  m_mat[15] + 
                     m_mat[4]  *  m_mat[11] *  m_mat[14] + 
                     m_mat[8]  *  m_mat[6]  *  m_mat[15] - 
                     m_mat[8]  *  m_mat[7]  *  m_mat[14] - 
                     m_mat[12] *  m_mat[6]  *  m_mat[11] + 
                     m_mat[12] *  m_mat[7]  *  m_mat[10];

    inv.m_mat[8] =  m_mat[4]  *  m_mat[9] *  m_mat[15] - 
                    m_mat[4]  *  m_mat[11] *  m_mat[13] - 
                    m_mat[8]  *  m_mat[5] *  m_mat[15] + 
                    m_mat[8]  *  m_mat[7] *  m_mat[13] + 
                    m_mat[12] *  m_mat[5] *  m_mat[11] - 
                    m_mat[12] *  m_mat[7] *  m_mat[9];

    inv.m_mat[12] = - m_mat[4]  *  m_mat[9] *  m_mat[14] + 
                      m_mat[4]  *  m_mat[10] *  m_mat[13] +
                      m_mat[8]  *  m_mat[5] *  m_mat[14] - 
                      m_mat[8]  *  m_mat[6] *  m_mat[13] - 
                      m_mat[12] *  m_mat[5] *  m_mat[10] + 
                      m_mat[12] *  m_mat[6] *  m_mat[9];
       
    inv.m_mat[1] = - m_mat[1]  *  m_mat[10] *  m_mat[15] + 
                     m_mat[1]  *  m_mat[11] *  m_mat[14] + 
                     m_mat[9]  *  m_mat[2] *  m_mat[15] - 
                     m_mat[9]  *  m_mat[3] *  m_mat[14] - 
                     m_mat[13] *  m_mat[2] *  m_mat[11] + 
                     m_mat[13] *  m_mat[3] *  m_mat[10];

    inv.m_mat[5] =  m_mat[0]  *  m_mat[10] *  m_mat[15] - 
                    m_mat[0]  *  m_mat[11] *  m_mat[14] - 
                    m_mat[8]  *  m_mat[2] *  m_mat[15] + 
                    m_mat[8]  *  m_mat[3] *  m_mat[14] + 
                    m_mat[12] *  m_mat[2] *  m_mat[11] - 
                    m_mat[12] *  m_mat[3] *  m_mat[10];

    inv.m_mat[9] = - m_mat[0]  *  m_mat[9] *  m_mat[15] + 
                     m_mat[0]  *  m_mat[11] *  m_mat[13] + 
                     m_mat[8]  *  m_mat[1] *  m_mat[15] - 
                     m_mat[8]  *  m_mat[3] *  m_mat[13] - 
                     m_mat[12] *  m_mat[1] *  m_mat[11] + 
                     m_mat[12] *  m_mat[3] *  m_mat[9];

    inv.m_mat[13] =  m_mat[0]  *  m_mat[9] *  m_mat[14] - 
                     m_mat[0]  *  m_mat[10] *  m_mat[13] - 
                     m_mat[8]  *  m_mat[1] *  m_mat[14] + 
                     m_mat[8]  *  m_mat[2] *  m_mat[13] + 
                     m_mat[12] *  m_mat[1] *  m_mat[10] - 
                     m_mat[12] *  m_mat[2] *  m_mat[9];

    inv.m_mat[2] =  m_mat[1]  *  m_mat[6] *  m_mat[15] - 
                    m_mat[1]  *  m_mat[7] *  m_mat[14] - 
                    m_mat[5]  *  m_mat[2] *  m_mat[15] + 
                    m_mat[5]  *  m_mat[3] *  m_mat[14] + 
                    m_mat[13] *  m_mat[2] *  m_mat[7] - 
                    m_mat[13] *  m_mat[3] *  m_mat[6];

    inv.m_mat[6] = - m_mat[0]  *  m_mat[6] *  m_mat[15] + 
                     m_mat[0]  *  m_mat[7] *  m_mat[14] + 
                     m_mat[4]  *  m_mat[2] *  m_mat[15] - 
                     m_mat[4]  *  m_mat[3] *  m_mat[14] - 
                     m_mat[12] *  m_mat[2] *  m_mat[7] + 
                     m_mat[12] *  m_mat[3] *  m_mat[6];

    inv.m_mat[10] =  m_mat[0]  *  m_mat[5] *  m_mat[15] - 
                     m_mat[0]  *  m_mat[7] *  m_mat[13] - 
                     m_mat[4]  *  m_mat[1] *  m_mat[15] + 
                     m_mat[4]  *  m_mat[3] *  m_mat[13] + 
                     m_mat[12] *  m_mat[1] *  m_mat[7] - 
                     m_mat[12] *  m_mat[3] *  m_mat[5];

    inv.m_mat[14] = - m_mat[0]  *  m_mat[5] *  m_mat[14] + 
                      m_mat[0]  *  m_mat[6] *  m_mat[13] + 
                      m_mat[4]  *  m_mat[1] *  m_mat[14] - 
                      m_mat[4]  *  m_mat[2] *  m_mat[13] - 
                      m_mat[12] *  m_mat[1] *  m_mat[6] + 
                      m_mat[12] *  m_mat[2] *  m_mat[5];
       
    inv.m_mat[3] = - m_mat[1] *  m_mat[6] *  m_mat[11] + 
                     m_mat[1] *  m_mat[7] *  m_mat[10] + 
                     m_mat[5] *  m_mat[2] *  m_mat[11] - 
                     m_mat[5] *  m_mat[3] *  m_mat[10] - 
                     m_mat[9] *  m_mat[2] *  m_mat[7] + 
                     m_mat[9] *  m_mat[3] *  m_mat[6];

    inv.m_mat[7] =  m_mat[0] *  m_mat[6] *  m_mat[11] - 
                    m_mat[0] *  m_mat[7] *  m_mat[10] - 
                    m_mat[4] *  m_mat[2] *  m_mat[11] + 
                    m_mat[4] *  m_mat[3] *  m_mat[10] + 
                    m_mat[8] *  m_mat[2] *  m_mat[7] - 
                    m_mat[8] *  m_mat[3] *  m_mat[6];
       
    inv.m_mat[11] = - m_mat[0] *  m_mat[5] *  m_mat[11] + 
                      m_mat[0] *  m_mat[7] *  m_mat[9] + 
                      m_mat[4] *  m_mat[1] *  m_mat[11] - 
                      m_mat[4] *  m_mat[3] *  m_mat[9] - 
                      m_mat[8] *  m_mat[1] *  m_mat[7] + 
                      m_mat[8] *  m_mat[3] *  m_mat[5];

    inv.m_mat[15] =  m_mat[0] *  m_mat[5] *  m_mat[10] - 
                     m_mat[0] *  m_mat[6] *  m_mat[9] - 
                     m_mat[4] *  m_mat[1] *  m_mat[10] + 
                     m_mat[4] *  m_mat[2] *  m_mat[9] + 
                     m_mat[8] *  m_mat[1] *  m_mat[6] - 
                     m_mat[8] *  m_mat[2] *  m_mat[5];

    det =  m_mat[0] *  inv.m_mat[0] +  m_mat[1] *  inv.m_mat[4] +  m_mat[2] *  inv.m_mat[8] +  m_mat[3] *  inv.m_mat[12];

    if (det == 0) {
        std::cerr << "Cannot invert matrix: \n" << *this;
        return false;
    }

    det = 1.0f / det;

    out = (inv * det);

    return true;
        
}
// std out
std::ostream& operator<<(std::ostream& os, const Matrix4x4& m) {
    for (int i = 0; i < 4; i++) {
        os << "| ";
        for (int j = 0; j < 4; j++) {
            os << m.m_mat[i * 4 + j] << " ";
        }
        os << " |\n";
    }
    return os;
}
// Destructor
Matrix4x4::~Matrix4x4() {}


Matrix4x4 Matrix4x4::translationMatrix(const Vector& offset) {
    return Matrix4x4(1, 0, 0, offset.m_x,
                     0, 1, 0, offset.m_y,
                     0, 0, 1, offset.m_z,
                     0, 0, 0, 1);
}

Matrix4x4 Matrix4x4::rotationMatrixX(float x) {
    float cosX = cosf(RADIAN(x));
    float sinX = sinf(RADIAN(x));
    return Matrix4x4(1, 0, 0, 0,
                     0, cosX, -sinX, 0,
                     0, sinX, cosX, 0,
                     0, 0, 0, 1);
}
Matrix4x4 Matrix4x4::rotationMatrixY(float y) {
    float cosY = cosf(RADIAN(y));
    float sinY = sinf(RADIAN(y));
    return Matrix4x4(cosY, 0, sinY, 0,
                        0, 1, 0, 0,
                     -sinY, 0, cosY, 0,
                        0, 0, 0, 1);
}
Matrix4x4 Matrix4x4::rotationMatrixZ(float z) {
    float cosZ = cosf(RADIAN(z));
    float sinZ = sinf(RADIAN(z));
    return Matrix4x4(cosZ, -sinZ, 0, 0,
                     sinZ, cosZ, 0, 0,
                     0, 0, 1, 0,
                    0, 0, 0, 1);
}
Matrix4x4 Matrix4x4::scaleMatrix(float x, float y, float z) {
    return Matrix4x4(x, 0, 0, 0,
                     0, y, 0, 0,
                     0, 0, z, 0,
                     0, 0, 0, 1);
}
Matrix4x4 Matrix4x4::projectionMatrix(float fov, float a, float z_near, float z_far) {
    float f = 1 / tanf(fov * 0.5f * M_PI / 180);
    return Matrix4x4(
        f * a, 0, 0, 0,
              0, f, 0, 0,
              0, 0, (z_far + z_near) / (z_far - z_near), (2 * z_far * z_near) / (z_far - z_near),
              0, 0, -1, 0);
}
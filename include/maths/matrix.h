#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>

#include "vector.h"
#include "vertex.h"

class Matrix4x4 {

    public:
        float m_mat[16] = {0.0f};

    public:
        // Constructor
        Matrix4x4();
        Matrix4x4(
            float x0, float y0, float z0, float w0,
            float x1, float y1, float z1, float w1,
            float x2, float y2, float z2, float w2,
            float x3, float y3, float z3, float w3
        );
        // Assignment operator
        Matrix4x4& operator=(const Matrix4x4& other);
        // Addition
        Matrix4x4 operator+(float n);
        Matrix4x4 operator+(const Matrix4x4& other);
        // Subtraction
        Matrix4x4 operator-(float n);
        Matrix4x4 operator-(const Matrix4x4& other);
        // Multiplication
        Matrix4x4 operator*(float n);
        Vector operator*(const Vector& v);
        Vertex operator*(const Vertex& v);
        Matrix4x4 operator*(const Matrix4x4& other);
        // Transpose
        Matrix4x4 transpose();
        void T();
        // Inverse
        bool inverse(Matrix4x4& out);
        // std out
        friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& m);
        static Matrix4x4 translationMatrix(const Vector& offset);
        static Matrix4x4 rotationMatrixX(float alpha);
        static Matrix4x4 rotationMatrixY(float alpha);
        static Matrix4x4 rotationMatrixZ(float alpha);
        static Matrix4x4 scaleMatrix(float x, float y, float z);
        static Matrix4x4 projectionMatrix(float fov, float a, float z_near, float z_far);

        ~Matrix4x4();

};
#endif
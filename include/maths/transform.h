#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "vector.h"
#include "matrix.h"

class Transform {

    private:
        // Rotation
        float rotate_x = 0.0f;
        float rotate_y = 0.0f;
        float rotate_z = 0.0f;
        bool dirty_rotate = true;
        // Offser
        Vector offset;
        bool dirty_offset = true;
        // Scale
        float scale_x = 1.0f;
        float scale_y = 1.0f;
        float scale_z = 1.0f;
        bool dirty_scale = true;
        // Transform matrix
        Matrix4x4 m_rotation;
        Matrix4x4 m_translation;
        Matrix4x4 m_scale;
        Matrix4x4 transform;
        Matrix4x4 inverse;
        Matrix4x4 normalMatrix;
    public:
        // Dirty transform flag
        bool dirty_transform = true;

    public:
        // Constructor
        Transform() {}
        // Rotation
        void rotate(float x, float y, float z);
        void rotateX(float x);
        void rotateY(float y);
        void rotateZ(float z);
        // Offset
        void translate(const Vector& v);
        void translate(float x, float y, float z);
        // Scale
        void scale(float x, float y, float z);
        void scaleX(float x);
        void scaleY(float y);
        void scaleZ(float z);
        // Get transform
        Matrix4x4 get();
        Matrix4x4 getInverse();
        Matrix4x4 getNormalMatrix();
        Matrix4x4 getRotation();
        Matrix4x4 getOffset();
        Matrix4x4 getScale();
        // Reset transform
        void reset();
        // Destructor
        ~Transform() {}
    
    private:
        void makeMatrices();

};

#endif
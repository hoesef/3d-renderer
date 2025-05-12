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
        const Matrix4x4 get();
        // Reset transform
        void reset();
        // Destructor
        ~Transform() {}
    
    private:
        const Matrix4x4 getRotation();
        const Matrix4x4 getOffset();
        const Matrix4x4 getScale();

};

#endif
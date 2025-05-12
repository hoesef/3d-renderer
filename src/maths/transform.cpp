#include "../../include/maths/transform.h"

// Rotation
void Transform::rotate(float x, float y, float z) {
    rotate_x += x;
    rotate_y += y;
    rotate_z += z;
    dirty = true;
}
void Transform::rotateX(float x) {
    rotate_x += x;
    dirty = true;
}
void Transform::rotateY(float y) {
    rotate_y += y;
    dirty = true;
}
void Transform::rotateZ(float z) {
    rotate_z += z;
    dirty = true;
}
// Offset
void Transform::translate(const Vector& v) {
    offset += v;
    dirty = true;
}
void Transform::translate(float x, float y, float z) {
    offset.m_x += x;
    offset.m_y += y;
    offset.m_z += z;
    dirty = true;
}
// Scale
void Transform::scale(float x, float y, float z) {
    scale_x *= x;
    scale_y *= y;
    scale_z *= z;
    dirty = true;
}
void Transform::scaleX(float x) {
    scale_x *= x;
    dirty = true;
}
void Transform::scaleY(float y) {
    scale_y *= y;
    dirty = true;
}
void Transform::scaleZ(float z) {
    scale_z *= z;
    dirty = true;
}
// Get transform
const Matrix4x4 Transform::get() {
    if (dirty) {
        Matrix4x4 T = translationMatrix(offset);
        Matrix4x4 R = rotationMatrixX(rotate_x) * rotationMatrixY(rotate_y) * rotationMatrixZ(rotate_z);
        Matrix4x4 S = scaleMatrix(scale_x, scale_y, scale_z);
        transform = T * R * S;
        dirty = false;
    }
    return transform;
}
// Reset transform
void Transform::reset() {
    rotate_x = 0.0f;
    rotate_y = 0.0f;
    rotate_z = 0.0f;
    offset = Vector{0,0,0};
    scale_x = 1.0f;
    scale_y = 1.0f;
    scale_z = 1.0f;
    dirty = true;
}
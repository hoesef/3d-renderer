#include "../../include/maths/transform.h"

// Rotation
void Transform::rotate(float x, float y, float z) {
    rotate_x += x;
    rotate_y += y;
    rotate_z += z;
    dirty_rotate = true;
    dirty_transform = true;
}
void Transform::rotateX(float x) {
    rotate_x += x;
    dirty_rotate = true;
    dirty_transform = true;
}
void Transform::rotateY(float y) {
    rotate_y += y;
    dirty_rotate = true;
    dirty_transform = true;
}
void Transform::rotateZ(float z) {
    rotate_z += z;
    dirty_rotate = true;
    dirty_transform = true;
}
// Offset
void Transform::translate(const Vector& v) {
    offset += v;
    dirty_offset = true;
    dirty_transform = true;
}
void Transform::translate(float x, float y, float z) {
    offset.m_x += x;
    offset.m_y += y;
    offset.m_z += z;
    dirty_offset = true;
    dirty_transform = true;
}
// Scale
void Transform::scale(float x, float y, float z) {
    scale_x *= x;
    scale_y *= y;
    scale_z *= z;
    dirty_scale = true;
    dirty_transform = true;
}
void Transform::scaleX(float x) {
    scale_x *= x;
    dirty_scale = true;
    dirty_transform = true;
}
void Transform::scaleY(float y) {
    scale_y *= y;
    dirty_scale = true;
    dirty_transform = true;
}
void Transform::scaleZ(float z) {
    scale_z *= z;
    dirty_scale = true;
    dirty_transform = true;
}
// Get transform
Matrix4x4 Transform::getRotation() {
    if (dirty_rotate) {
        m_rotation = Matrix4x4::rotationMatrixX(rotate_x) * Matrix4x4::rotationMatrixY(rotate_y) * Matrix4x4::rotationMatrixZ(rotate_z);
        // m_rotation = rotationMatrixZ(rotate_z) * rotationMatrixY(rotate_y) * rotationMatrixX(rotate_x);
        dirty_rotate = false;
    }
    return m_rotation;
}
Matrix4x4 Transform::getOffset() {
    if (dirty_offset) {
        m_translation = Matrix4x4::translationMatrix(offset);
        dirty_offset = false;
    }
    return m_translation;
}
Matrix4x4 Transform::getScale() {
    if (dirty_scale) {
        m_scale = Matrix4x4::scaleMatrix(scale_x, scale_y, scale_z);
        dirty_scale = false;
    }
    return m_scale;
}
Matrix4x4 Transform::get() {
    makeMatrices();
    return transform;
}
Matrix4x4 Transform::getInverse() {
    makeMatrices();
    return inverse;
}
Matrix4x4 Transform::getNormalMatrix() {
    makeMatrices();
    return normalMatrix;
}
void Transform::makeMatrices() {
    // Check if we need to recalc matrixes
    if (!dirty_transform) { return; }
    // Temp matrix for normals
    Matrix4x4 temp;
    // Get Rotation, translation, sclae
    Matrix4x4 T = getOffset();
    Matrix4x4 R = getRotation();
    Matrix4x4 S = getScale();
    // Calc temp matrix
    temp = R * S;
    // Calc full object-to-world transform
    transform = T * temp;
    // Calc inverse matrix (world-to-object)
    transform.inverse(inverse);
    // Calc normal matrix
    temp.inverse(normalMatrix);
    normalMatrix.T();
    // Reset flag
    dirty_transform = false;   
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
    dirty_transform = true;
}
#include "../../include/camera/camera.h"

#include <iostream>

Camera::Camera() {}

Camera::Camera(Vector v_pos, Vector v_look, Vector v_up) {
    pos = v_pos;
    lookat = v_look;
    forward = pos - lookat;
    forward.normalize();
    right = up.cross(forward);
    right.normalize();
    up = forward.cross(right);
    up.normalize();
    
    Matrix4x4 rotation(right.m_x, right.m_y, right.m_z, 0,
                       up.m_x, up.m_y, up.m_z, 0,
                       forward.m_x, forward.m_y, forward.m_z, 0,
                       0, 0, 0, 1);
    Matrix4x4 translation(1, 0, 0, -(pos.m_x),
                          0, 1, 0, -(pos.m_y),
                          0, 0, 1, -(pos.m_z),
                          0, 0, 0, 1);
    worldToCamera = rotation * translation;
    cameraToWorld = Matrix4x4 (right.m_x, up.m_x, forward.m_x, pos.m_x,
                               right.m_y, up.m_y, forward.m_y, pos.m_y,
                               right.m_z, up.m_z, forward.m_z, pos.m_z,
                               0, 0, 0, 1);
}

Camera::~Camera() {}
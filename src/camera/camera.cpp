#include "../../include/camera/camera.h"

#include <iostream>
#include <math.h>

#ifndef M_PI
#define M_PI 3.1415926535f
#endif

#define RADIAN(x) (x * M_PI / 180) 

Camera::Camera() {}

Camera::Camera(Vector v_pos, Vector v_look, Vector v_up) {
    pos = v_pos;
    lookat = v_look;
    forward = pos - lookat;
    forward.normalize();
    right = v_up.cross(forward);
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

    std::cout << "Forward: " << forward << "\n";
    std::cout << "Right: " << right << "\n";
    std::cout << "Up: " << up << "\n";
    std::cout << "Pos: " << pos << "\n";
    // std::cout << "Forward: " << forward << "\n";

}

Camera::Camera(Vector v_pos, Vector v_up, float f_pitch, float f_yaw) { // Vector v_look,
    pos = v_pos;
    pitch = f_pitch;
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }
    yaw = f_yaw;
    forward.m_x = std::cos(RADIAN(yaw)) * std::cos(RADIAN(pitch));
    forward.m_y = std::sin(RADIAN(pitch));
    forward.m_z = std::sin(RADIAN(yaw)) * std::cos(RADIAN(pitch));
    forward.normalize();
    right = v_up.cross(forward);
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

    std::cout << "\n\nCamera 2: \n";
    std::cout << "Forward: " << forward << "\n";
    std::cout << "Right: " << right << "\n";
    std::cout << "Up: " << up << "\n";
    std::cout << "Pos: " << pos << "\n";
}

Camera::~Camera() {}
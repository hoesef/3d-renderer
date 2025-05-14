#ifndef CAMERA_H_
#define CAMERA_H_

#include "../maths/vector.h"
#include "../maths/matrix.h"

class Camera {

    public:
        float yaw = -90;
        float pitch = 0;
        Vector forward;
        Vector up = {0, 1, 0};
        Vector right;
        Vector lookat = {0, 0, 0};
        Vector pos = {0, 0, 0};
        Matrix4x4 cameraToWorld;
        Matrix4x4 worldToCamera;
        bool dirty_transform = false;        

    public:
        Camera();
        Camera(Vector loopat, Vector up, float yaw, float pitch);
        Camera(Vector v_pos, Vector v_look, Vector v_up); // Vector v_look, 
        ~Camera();

};

#endif
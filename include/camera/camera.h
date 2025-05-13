#ifndef CAMERA_H_
#define CAMERA_H_

#include "../maths/transform.h"

class Camera {

    public:
        Transform camera_to_world;
        Matrix4x4 world_to_camera;

    public:
        Camera();
        ~Camera();

};

#endif
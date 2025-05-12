#ifndef BASE_CAMERA_H_
#define BASE_CAMERA_H_

#include "..\objects\polymesh.h"
#include "..\framebuffer\framebuffer.h"
#include "..\maths\matrix.h"

class Camera {

    protected:
        unsigned m_width, m_height = 400;

    public:
        Camera() = default;
        virtual void render(Polymesh& mesh, Framebuffer& fb) = 0;
        virtual ~Camera() {};

};

#endif
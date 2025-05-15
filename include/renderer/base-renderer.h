#ifndef BASE_RENDERER_H_
#define BASE_RENDERER_H_

#include "..\objects\polymesh.h"
#include "..\framebuffer\framebuffer.h"
#include "..\maths\matrix.h"
#include "..\camera\camera.h"


class Renderer {

    protected:
        unsigned m_width, m_height = 400;

    public:
        Renderer() = default;
        virtual void render(Camera& camera, Polymesh& mesh, Framebuffer& fb) = 0;
        virtual ~Renderer() {};

};

#endif
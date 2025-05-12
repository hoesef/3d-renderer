#ifndef PERSPECTIVE_H_
#define PERSPECTIVE_H_

#include "base-renderer.h"
#include "..\maths\vector.h"

class Perspective : public Renderer {

    private:
        float m_zNear = 0.1f;           // Near plane
        float m_zFar = 1000.0f;         // Far plane
        float m_a = 1.0f;               // Aspect ratio
        float m_fov = 60;               // Field of view
        Vector pos;
    
    public:
        Matrix4x4 m_proj;               // Perspective Projectio Matrix

    public:
        Perspective();
        Perspective(int width, int height, float fov);
        void render(Polymesh& mesh, Framebuffer& fb) override;
        void makeProjMatrix();
        ~Perspective() override;

};

#endif
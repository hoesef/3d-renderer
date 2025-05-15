#ifndef SCENE_H_
#define SCENE_H_

#include "..\data-structures\linked-list.h"

class Polymesh;
class Light;

class Scene {

    public:
        Stack<Polymesh*> objects;
        Stack<Light*> lights;

    public:
        Scene() = default;
        void addObject(Polymesh* obj) { objects.add(obj); }
        void addLight(Light* light) { lights.add(light); }
        ~Scene() {}

};

#endif
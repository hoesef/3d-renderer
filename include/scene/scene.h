#ifndef SCENE_H_
#define SCENE_H_

#include <iostream>

#include "..\data-structures\linked-list.h"

class Polymesh;
// class Light;


/*
 * The scene class steals ownership of the object / light pointer.
 */
class Scene {

    public:
        Stack<Polymesh*> objects;
        // Stack<Light*> lights;

    public:
        Scene() = default;
        void addObject(Polymesh* obj) { objects.add(obj); }
        // void addLight(Light* light) { lights.add(light); }
        ~Scene() {
            while (!objects.isEmpty()) {
                Polymesh* mesh = objects.pop();
                delete mesh;
            }
            
            // while (!lights.isEmpty()) {
            //     Light* light = lights.pop();
            //     delete light;
            // }
        }

};

#endif
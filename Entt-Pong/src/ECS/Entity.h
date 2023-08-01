#pragma once
#include <entt/entt.hpp>
#include <print.h>
#include "Scene/Scene.h"

class Entity{
    public:
        Entity(entt::entity e, Scene* s){
            print("Entity created")

            handle = e;
            scene = s;
        }
        ~Entity(){
            print("Entity destroyed")
        }

        template<typename T, typename>
        T& addComponent(){

        }

        template<typename T>
        void removeComponent(){
            scene->r.remove<T>(handle)
        }

    private:
        entt::entity handle;
        Scene* scene;
}
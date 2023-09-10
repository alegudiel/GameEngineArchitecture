#pragma once

#include <entt/entt.hpp>
#include "print.h"
#include "Scene/Scene.h"

class Entity
{
    public:
        Entity(entt::entity e, Scene* s) {
            print("Entity Created");

            handle = e;
            scene = s;
        }
        ~Entity() {
            print("Entity Destroyed");
        }

        template<typename T>
        auto& addComponent(auto&&... args) {
            return scene->r.emplace<T>(handle, std::forward<decltype(args)>(args)...);
        }

        template<typename T>
        void removeComponent() {
            scene->r.remove<T>(handle);
        }

    private:
        entt::entity handle;
        Scene* scene;
};
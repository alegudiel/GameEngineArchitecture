#pragma once

#include <print.h>
#include "Scene/Scene.h"


class Entity {
  public:
    Entity(entt::entity e, Scene* s) {

      handle = e;
      scene = s;
    }

    ~Entity() {
    }

    template<typename T>
    auto& addComponent(auto&&... args) {
      return scene->r.emplace<T>(handle, std::forward<decltype(args)>(args)...);
    }

    template<typename T>
    void removeComponent() {
      scene->r.remove<T>(handle);
    }

    template<typename T>
    auto& get(auto&&... args) {
      return scene->r.get_or_emplace<T>(handle, std::forward<decltype(args)>(args)...);
    }

  private:
    entt::entity handle;
    Scene* scene;
};


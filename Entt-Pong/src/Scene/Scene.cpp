#include "Scene.h"
#include <print.h>

Scene::Scene(const std::string& name)
    : name(name) {
        print("Scene Created");
}

Scene::~Scene() {
    print("Scene Destroyed");
}


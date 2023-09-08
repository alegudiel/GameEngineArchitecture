#include <string>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include "print.h"

#include "Scene.h"

#include "ECS/Entity.h"
#include "ECS/Components.h"
#include "ECS/System.h"


Scene::Scene(const std::string& name)
    : name(name)
{}

Scene::~Scene()
{}

Entity Scene::createEntity(const std::string& name, int x, int y)
{
    Entity entity = { r.create(), this };
    entity.addComponent<NameComponent>(name);
    entity.addComponent<TransformComponent>(
    glm::vec2(x, y)
    );

    return entity;
}

void Scene::setup()
{   
    for (auto sys: setupSystems)
    {
        sys->run();
    }
}

void Scene::update(double dT)
{   
    for (auto sys: updateSystems)
    {
        sys->run(dT);
    }
}

void Scene::render(SDL_Renderer* renderer)
{
    for (auto sys: renderSystems)
    {
        sys->run(renderer);
    }
}

void Scene::processEvents(SDL_Event event)
{
    for (auto sys: eventSystems)
    {
        sys->run(event);
    }
}
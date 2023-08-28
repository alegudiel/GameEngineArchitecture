#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <entt/entt.hpp>

class Entity;
class SetupSystem;
class EventSystem;
class UpdateSystem;
class RenderSystem;

class Scene {
    private:
        std::vector<std::shared_ptr<SetupSystem>> setupSystems;
        std::vector<std::shared_ptr<EventSystem>> eventSystems;
        std::vector<std::shared_ptr<UpdateSystem>> updateSystems;
        std::vector<std::shared_ptr<RenderSystem>> renderSystems;
        std::string name;

    public:
        Scene(const std::string&);
        ~Scene();

    entt::registry r;

    Entity createEntity(
        const std::string& name = "NO NAME",
        int x = 0,
        int y = 0
    );
    
    template<typename T>
    void addSetupSystem(auto&&... args) {
        auto system = std::make_shared<T>(std::forward<decltype(args)>(args)...);
        system->setScene(this);
        setupSystems.push_back(system);
    }

    template<typename T>
    void addEventSystem(auto&&... args) {
        auto system = std::make_shared<T>(std::forward<decltype(args)>(args)...);
        system->setScene(this);
        eventSystems.push_back(system);
    }

    template<typename T>
    void addUpdateSystem(auto&&... args) {
        auto system = std::make_shared<T>(std::forward<decltype(args)>(args)...);
        system->setScene(this);
        updateSystems.push_back(system);
    }

    template<typename T>
    void addRenderSystem(auto&&... args) {
        auto system = std::make_shared<T>(std::forward<decltype(args)>(args)...);
        system->setScene(this);
        renderSystems.push_back(system);
    }

    void setup();
    void update(double dT);
    void render(SDL_Renderer* renderer);
    void processEvents(SDL_Event event);
};
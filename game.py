from ECS.systems import RenderSystem, PlayerControlSystem

class Game:
    def __init__(self, entities, screen):
        self.entities = entities
        self.screen = screen
        self.systems = [RenderSystem(), PlayerControlSystem()]  

    def update(self, dt, keys):
        for system in self.systems:
            if isinstance(system, PlayerControlSystem):
                system.update(self.entities, dt, keys)
            else:
                system.update(self.entities, self.screen, dt, keys)

    def render(self):
        pass
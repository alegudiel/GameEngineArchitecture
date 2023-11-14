
class Entity:
    def __init__(self):
        self.components = []

    def add_component(self, component):
        self.components.append(component)

    def get_component(self, component_type):
        for component in self.components:
            if isinstance(component, component_type):
                return component
        return None

    def update(self, dt):
        for component in self.components:
            if hasattr(component, 'update'):
                component.update(self, dt)
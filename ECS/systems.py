
import pygame
from ECS.components import Position, Velocity, Sprite, Player, Coin, Enemy

class MovementSystem:
    @staticmethod
    def update(entity):
        position = entity.get_component(Position)
        velocity = entity.get_component(Velocity)

        if position and velocity:
            position.x += velocity.dx
            position.y += velocity.dy

class GravitySystem:
    @staticmethod
    def update(entity):
        velocity = entity.get_component(Velocity)

        if velocity:
            velocity.dy = 0  

class RenderSystem:
    @staticmethod
    def update(entity, screen):
        position = entity.get_component(Position)
        sprite = entity.get_component(Sprite)

        if position and sprite:
            image = pygame.image.load(sprite.image_path)
            screen.blit(image, (position.x, position.y))

class PlayerControlSystem:
    @staticmethod
    def update(entity, keys):
        velocity = entity.get_component(Velocity)

        if keys[pygame.K_LEFT]:
            velocity.dx = -5
        elif keys[pygame.K_RIGHT]:
            velocity.dx = 5
        else:
            velocity.dx = 0

        if keys[pygame.K_SPACE]:
            velocity.dy = -15  
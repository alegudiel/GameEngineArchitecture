# systems.py
import pygame
from ECS.components import *

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
    def update(entities, screen, dt, keys):
        for entity in entities:
            position = entity.get_component(Position)
            animation = entity.get_component(Animation)

            if position and animation:
                current_frame = animation.get_current_frame()
                screen.blit(current_frame, (position.x, position.y))

class PlayerControlSystem:
    @staticmethod
    def update(entities, dt, keys):
        for entity in entities:
            velocity = entity.get_component(Velocity)
            animation = entity.get_component(Animation)

            if velocity:
                print(f"Left: {keys[pygame.K_LEFT]}, Right: {keys[pygame.K_RIGHT]}, A: {keys[pygame.K_a]}, D: {keys[pygame.K_d]}")
                print(f"velocity.dx: {velocity.dx}")
                if keys[pygame.K_LEFT] or keys[pygame.K_a]:
                    velocity.dx = -5
                    print("izquierda")
                    print(keys[pygame.K_LEFT])
                    if animation:
                        animation.frames = [pygame.image.load("assets/animations/silia-walking.png")]
                elif keys[pygame.K_RIGHT] or keys[pygame.K_d]:
                    velocity.dx = 5
                    print("derecha")
                    if animation:
                        animation.frames = [pygame.image.load("assets/animations/silia-walking.png")]
                else:
                    velocity.dx = 0
                    if animation:
                        animation.frames = [pygame.image.load("assets/animations/silia-idle.png")]

                if keys[pygame.K_SPACE]:
                    velocity.dy = -15  
                    if animation:
                        animation.frames = [pygame.image.load("assets/animations/silia-jumping.png")]
                else:
                    if animation:
                        animation.frames = [pygame.image.load("assets/animations/silia-idle.png")]

class CollisionSystem:
    @staticmethod
    def update(player, coins, enemies):
        player_position = player.get_component(Position)

        for coin in coins:
            coin_position = coin.get_component(Position)
            if pygame.Rect(player_position.x, player_position.y, 32, 32).colliderect(
                    pygame.Rect(coin_position.x, coin_position.y, 32, 32)):
                coins.remove(coin)
                player.get_component(Player).coins_collected += 1

        for enemy in enemies:
            enemy_position = enemy.get_component(Position)
            if pygame.Rect(player_position.x, player_position.y, 32, 32).colliderect(
                    pygame.Rect(enemy_position.x, enemy_position.y, 32, 32)):
                print("Game Over")  

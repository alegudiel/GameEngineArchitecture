# systems.py
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
            velocity.dy = 0  # Simulating gravity

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
            velocity.dy = -15  # Jump

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
                print("Game Over")  # You can add more game-over logic here

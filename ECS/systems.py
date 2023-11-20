
import pygame
from ECS.components import *

###### BOX2D lo reemplaza ######
# class MovementSystem:
#     @staticmethod
#     def update(entity):
#         position = entity.get_component(Position)
#         velocity = entity.get_component(Velocity)

#         if position and velocity:
#             position.x += velocity.dx
#             position.y += velocity.dy

# class GravitySystem:
#     @staticmethod
#     def update(entity):
#         velocity = entity.get_component(Velocity)

#         if velocity:
#             velocity.dy = 0  

class RenderSystem:
    @staticmethod
    def update(entities, screen, dt, keys):
        for entity in entities:
            position = entity.get_component(Position)
            player = entity.get_component(Player)
            animation = entity.get_component(Animation)
            sprite = entity.get_component(Sprite)

            # Update animations of player
            if player and animation:
                pos_x = player.body.position.x
                pos_y = player.body.position.y
                index = animation.get_current_frame()

                if index > (animation.frame_count):
                    index = 0
                current_frame = animation.sprite_sheet.subsurface(pygame.Rect(index * animation.frame_width, 0, animation.frame_width, animation.frame_height))
                screen.blit(current_frame, (pos_x, pos_y))

            # provisional para la plataforma
            if position and sprite:
                pos_x = position.body.position.x
                pos_y = position.body.position.y
                screen.blit(pygame.image.load(sprite.image_path), (pos_x, pos_y))

            # Update animations of coins
            if position and animation:
                pos_x = position.body.position.x
                pos_y = position.body.position.y
                index = animation.get_current_frame()

                if index > (animation.frame_count):
                    index = 0
                current_frame = animation.sprite_sheet.subsurface(pygame.Rect(index * animation.frame_width, 0, animation.frame_width, animation.frame_height))
                screen.blit(current_frame, (pos_x, pos_y))

class PlayerControlSystem:
    @staticmethod
    def update(entities, dt, keys):
        for entity in entities:
            player = entity.get_component(Player)
            animation = entity.get_component(Animation)

            if player and animation:
                # Left
                if keys[pygame.K_LEFT] or keys[pygame.K_a]:
                    player.body.linearVelocity = (-5, player.body.linearVelocity.y)
                    animation.sprite_sheet = pygame.image.load("assets/animations/silia-walking.png")

                # Right
                elif keys[pygame.K_RIGHT] or keys[pygame.K_d]:
                    player.body.linearVelocity = (5, player.body.linearVelocity.y)
                    animation.sprite_sheet = pygame.image.load("assets/animations/silia-walking.png")

                # Idle
                else:
                    player.body.linearVelocity = (0, player.body.linearVelocity.y)
                    animation.sprite_sheet = pygame.image.load("assets/animations/silia-idle.png")
                    player.is_in_air = False

                # Jump
                if keys[pygame.K_SPACE] and not player.is_in_air:
                    player.body.linearVelocity = (player.body.linearVelocity.x, -5)
                    animation.sprite_sheet = pygame.image.load("assets/animations/silia-jumping.png")
                    player.is_in_air = True

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

class ScoreSystem:
    @staticmethod
    def update(player):
        print("Coins collected: " + str(player.get_component(Player).coins_collected))

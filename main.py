# main.py
import pygame
import sys
from ECS.entity import Entity
from ECS.components import Position, Velocity, Player, Coin, Animation
from ECS.systems import MovementSystem, GravitySystem, RenderSystem, PlayerControlSystem, CollisionSystem

# Initialize Pygame
pygame.init()

# Set up the game window
width, height = 800, 600
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Silia against the world")

# Load animations
player_idle_animation = Animation("assets/animations/silia.png", 32, 32, 8)
coin_animation = Animation("assets/animations/coin.png", 32, 32, 8)

# Create entities
player = Entity()
player.add_component(Position(100, 100))
player.add_component(Velocity(0, 0))
player.add_component(Player())
player.add_component(player_idle_animation)  

coin1 = Entity()
coin1.add_component(Position(200, 200))
coin1.add_component(Coin())
coin1.add_component(coin_animation)  

coin2 = Entity()
coin2.add_component(Position(200, 300))
coin2.add_component(Coin())
coin2.add_component(coin_animation)  

entities = [player, coin1, coin2]

# Game loop
clock = pygame.time.Clock()

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    keys = pygame.key.get_pressed()

    # Update systems
    for entity in entities:
        MovementSystem.update(entity)
        GravitySystem.update(entity)
        PlayerControlSystem.update(player, keys)

    CollisionSystem.update(player, [coin1, coin2], [])  

    screen.fill((0, 0, 0))

    # Render systems
    for entity in entities:
        RenderSystem.update(entity, screen)

    # Update display
    pygame.display.flip()

    # Cap the frame rate
    clock.tick(15) 

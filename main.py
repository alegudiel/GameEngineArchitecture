# main.py
import pygame
import sys
from ECS.entity import Entity
from ECS.components import Position, Velocity, Sprite, Player, Coin, Enemy
from ECS.systems import MovementSystem, GravitySystem, RenderSystem, PlayerControlSystem, CollisionSystem

# Initialize Pygame
pygame.init()

# Set up the game window
width, height = 800, 600
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Silia against her world")

# Create entities
player = Entity()
player.add_component(Position(100, 100))
player.add_component(Velocity(0, 0))
player.add_component(Sprite("./assets/silia.png"))
player.add_component(Player())

coin1 = Entity()
coin1.add_component(Position(200, 200))
coin1.add_component(Sprite("./assets/coin.png"))
coin1.add_component(Coin())

enemy = Entity()
enemy.add_component(Position(300, 300))
enemy.add_component(Sprite("./assets/enemy.png"))
enemy.add_component(Enemy())

entities = [player, coin1, enemy]

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

    CollisionSystem.update(player, [coin1], [enemy])

    screen.fill((0, 0, 0))

    # Render systems
    for entity in entities:
        RenderSystem.update(entity, screen)

    # Update display
    pygame.display.flip()

    # Cap the frame rate
    clock.tick(60)

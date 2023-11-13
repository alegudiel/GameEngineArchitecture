
import pygame
import sys
from ECS.entity import *
from ECS.components import *
from ECS.systems import *

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
player.add_component(Sprite("./assets/silia.png", Color(8, 146, 215)))
player.add_component(Player())

# Changes to Silia
playerChanged1 = Entity()
playerChanged1.add_component(Position(200,100))
playerChanged1.add_component(Sprite("./assets/silia.png", Color(240, 202, 50)))
player.add_component(Player())

playerChanged2 = Entity()
playerChanged2.add_component(Position(300,100))
playerChanged2.add_component(Sprite("./assets/silia.png", Color(215, 36, 8)))
player.add_component(Player())

entities = [player, playerChanged1, playerChanged2]

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

    screen.fill((0, 0, 0))

    # Render systems
    for entity in entities:
        RenderSystem.update(entity, screen)

    # Update display
    pygame.display.flip()

    # Cap the frame rate
    clock.tick(60)

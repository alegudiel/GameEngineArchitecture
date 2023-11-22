import pygame
import sys
from ECS.entity import Entity
from ECS.components import *
from ECS.systems import *
from game import Game 
from Box2D import *

# Initialize Pygame
pygame.init()

# Initialize Box2D
world = b2World(gravity=(0, 9.8), doSleep=True)

# Set up the game window
width, height = 800, 575
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Silia against the world")

################### Animations
player_idle_animation = Animation("assets/animations/silia-idle.png", 14, 24, 8)
coin_animation = Animation("assets/animations/coin.png", 10, 12, 8)

################### Entities
player = Entity()
player.add_component(Player(world, 10, 485, 14, 24))
player.add_component(player_idle_animation)

coin1 = Entity()
coin1.add_component(Position(world, 200, 485))
# coin1.add_component(Coin(world, 200, 100))
coin1.add_component(Coin())
coin1.add_component(coin_animation)

coin2 = Entity()
coin2.add_component(Position(world, 555, 465))
# coin2.add_component(Coin(world, 150, 100))
coin2.add_component(Coin())
coin2.add_component(coin_animation)

# Lo reemplazamos por un tilemap
# platform = Entity()
# platform.add_component(Position(world, 100, 120))  
# platform.add_component(Sprite("assets/tilemaps/platform.png")) 
# platform.add_component(Platform(world, 100, 120, 112, 32))

tilemap = Entity()
tilemap.add_component(Tilemap(world, "assets/tilemaps/tiles.txt", "assets/tilemaps/tilemap-set.png"))
entities = [player, coin1, coin2, tilemap]

################### Game loop
clock = pygame.time.Clock()
game = Game(entities, screen)

while True:
    dt = clock.tick(60) / 1000.0
    world.Step(dt, 100, 100)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    keys = pygame.key.get_pressed()

    # Update entities
    for entity in entities:
        entity.update(dt)

    # Update systems for player velocity control
    for entity in entities:
        player = entity.get_component(Player)
        if player:
            PlayerControlSystem.update([entity], dt, keys)

    # Render
    screen.fill((0, 0, 0))
    game.update(dt, keys)

    pygame.display.flip()
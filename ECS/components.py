from Box2D import *
import pygame

class Position:
    def __init__(self, world, x, y):
        self.body = world.CreateBody(position=b2Vec2(x, y))

class Velocity:
    def __init__(self, world, dx, dy):
        self.body = world.CreateDynamicBody(position=b2Vec2(0, 0), linearVelocity=b2Vec2(dx, dy))

    def update(self, entity, dt):
        pass

class Sprite:
    def __init__(self, image_path):
        self.image_path = image_path

class Player:
    def __init__(self, world, x, y, width, height):
        self.body = world.CreateDynamicBody(position=b2Vec2(x, y))
        self.body.CreatePolygonFixture(box=(width/2, height/2), density=1, friction=0.3)
        self.coins_collected = 0
        self.is_in_air = False

class Coin:
    # def __init__(self, world, x, y):
    #     self.body = world.CreateDynamicBody(position=b2Vec2(x, y))
    #     self.body.CreateCircleFixture(radius=0.5, density=1, friction=0.3)

    # def on_collision(self, player, world):
    #     player.coins_collected += 1
    #     world.DestroyBody(self.body)
    pass

class Enemy:
    pass

class Animation:
    def __init__(self, sprite_sheet_path, frame_width, frame_height, frame_count):
        self.sprite_sheet = pygame.image.load(sprite_sheet_path)
        self.frame_width = frame_width
        self.frame_height = frame_height
        self.frame_count = frame_count
        self.current_frame = 0
        self.animation_speed = 5

    def get_frame_count(self):
        return self.frame_count

    def update(self, entity, dt):
        self.current_frame += self.animation_speed * dt
        if int(self.current_frame) >= self.frame_count:
            self.current_frame = 0

    def get_current_frame(self):
        return int(self.current_frame)

class Platform:
    def __init__(self, world, x, y, width, height):
        self.body = world.CreateStaticBody(position=b2Vec2(x,y))
        self.body.CreatePolygonFixture(box=(width, height/2), density=1, friction=0.3)

class Tilemap:
    def __init__(self, world, tilemap_path, tileset_path):
        self.world = world
        self.tilemap_path = tilemap_path
        self.tileset_path = tileset_path
        self.tiles = self.load_tiles()
        self.create_tile_bodies()

    def load_tiles(self):
        with open(self.tilemap_path, 'r') as file:
            lines = file.readlines()
        return [list(map(int, line.strip().split())) for line in lines]
    
    def create_tile_bodies(self):
        tile_size = 32
        for y, row in enumerate(self.tiles):
            for x, tile in enumerate(row):
                if tile != 0:  # 0 representa un tile vacío
                    self.world.CreateStaticBody(
                        position=(x * tile_size, y * tile_size),
                        shapes=b2PolygonShape(box=(tile_size / 2, tile_size / 2))
                    )
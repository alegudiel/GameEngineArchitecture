import pygame

class Position:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class Velocity:
    def __init__(self, dx, dy):
        self.dx = dx
        self.dy = dy

    def update(self, entity, dt):
        entity.get_component(Position).x += self.dx * dt
        entity.get_component(Position).y += self.dy * dt

class Sprite:
    def __init__(self, image_path):
        self.image_path = image_path

class Player:
    def __init__(self):
        self.coins_collected = 0

class Coin:
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

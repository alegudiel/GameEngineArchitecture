import pygame

class Position:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class Velocity:
    def __init__(self, dx, dy):
        self.dx = dx
        self.dy = dy

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
        self.frames = self.extract_frames()

    def extract_frames(self):
        frames = []
        sheet_width, sheet_height = self.sprite_sheet.get_size()
        for i in range(self.frame_count):

            i = min(i, self.frame_count - 1)

            self.frame_width = min(self.frame_width, sheet_width)
            self.frame_height = min(self.frame_height, sheet_height)

            frame_rect = pygame.Rect(i * self.frame_width, 0, self.frame_width, self.frame_height)
            if frame_rect.right <= sheet_width:
                frame = self.sprite_sheet.subsurface(frame_rect)
                frames.append(frame)
        return frames

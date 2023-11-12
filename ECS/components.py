# components.py
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

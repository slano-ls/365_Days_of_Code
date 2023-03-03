#!/usr/bin/env python3

import pygame

# INIT COLOURS

BLACK = (0, 0, 0)

# PADDLE CLASS
class Paddle(pygame.sprite.Sprite):

  def __init__(self, colour, width, height):
    # Sprite Constructor
    super().__init__()

    # Pass in Parameters to create paddle
    self.image = pygame.Surface([width, height])
    self.image.fill(BLACK)
    self.image.set_colorkey(BLACK)

    # Draw Paddle Rectangle
    pygame.draw.rect(self.image, colour, [0, 0, width, height])
    self.rect = self.image.get_rect()

  def move_left(self, pixels): # move left by pixel amount
    self.rect.x -= pixels

    if self.rect.x < 0:
      self.rect.x = 0
  def move_right(self, pixels): # move right by pixel amount
    self.rect.x += pixels

    if self.rect.x > 700:
      self.rect.x = 700

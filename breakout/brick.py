#!/usr/bin/env python3

import pygame
BLACK = (0,0,0)

class Brick(pygame.sprite.Sprite):

  def __init__(self, colour, width, height):
#Allows for us to call on any class in all files
    super().__init__()

#Sets colour, x,y position of the bricks, and its width and height
    self.image = pygame.Surface([width, height])
    self.image.fill(BLACK)
    self.image.set_colorkey(BLACK)

#Sets brick shape as rectangle
    pygame.draw.rect(self.image, colour, [0,0, width, height])

#Calling rectangle object to have identical dimensions as image
    self.rect = self.image.get_rect()

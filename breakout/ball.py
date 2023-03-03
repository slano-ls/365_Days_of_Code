#!/usr/bin/env python3

import pygame
from random import randint  # to randomize velocity
BLACK = (0,0,0)

class Ball(pygame.sprite.Sprite):

  def __init__(self, colour, width, height):
    super().__init__()

  # Ball colour and bkgrnd

    self.image = pygame.Surface([width, height])
    self.image.fill(BLACK)
    self.image.set_colorkey(BLACK)

    pygame.draw.rect(self.image, colour, [0, 0, width, height])
    self.velocity = [randint(4, 8), randint(-8, -8)]

    # Get Rectangle Object
    self.rect = self.image.get_rect()

  def update(self):
    self.rect.x += self.velocity[0]
    self.rect.y += self.velocity[1]

  def bounce(self):
    self.velocity[0] = -self.velocity[0]
    self.velocity[1] = randint(-8, 8)

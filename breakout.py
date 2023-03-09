
import pygame
from pygame.locals import *
import random
pygame.init()


screen_width = 600
screen_height = 600

screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption('Breakout')

# define font
font = pygame.font.SysFont('Constantia', 30)

# define colours
bg = (0, 0, 0)
# # block colours
# block_darkcyan = (242, 85, 96)
# block_keppel = (86, 174, 87)
# block_tiffany = (69, 177, 232)
# # paddle colours
# block_mayablue = (142, 135, 123)
# block_indigo= (100, 100, 100)
# text colour
block_darkcyan = (33, 137, 126)
block_keppel = (59, 169, 156)
block_tiffany = (105, 209, 197)
block_mayablue = (126, 188, 230)
block_indigo = (137, 128, 245)
text_col = (255, 255, 255)

# theme 1 bright 
# block_brightred = (255, 55, 48)
# block_brightyellow = (245, 247, 87)
# block_brightgreen = (87, 247, 87)
# block_brightblue = (87, 167, 247)

# theme 2 sea blues 
 # block_darkcyan = (30, 37, 250)
 # block_keppel = (44, 136, 242)
 # block_tiffany = (194, 232, 255)
 # block_mayablue = (126, 188, 230)
 # block_indigo = (137, 128, 245)

# theme 3 forest greens
# block_darkgreen = (11, 61, 1)
# block_pigment = (67, 250, 30)
# block_highlighter = (180, 250, 30)
# block_dartmouth = (4, 181, 107)
# block_grass = (5, 59, 6)

# theme 4 pastel
# block_pink = (225, 193, 207)
# block_yellow = (232, 255, 183)
# block_mauve = (226, 160, 255)
# block_lightcyan = (196, 245, 252)
# block_aquamarine = (183, 255, 216)

# define game variables
cols = 6
rows = 6
clock = pygame.time.Clock()
fps = 80
live_ball = False
game_over = 0
global score
score = 0
lives = 3

# function for outputting text onto the screen
def draw_text(text, font, text_col, x, y):
    img = font.render(text, True, text_col)
    screen.blit(img, (x, y))
  
# display score
def display_score(score):
    score_surf = font.render(f"Score: {score}", True, text_col)
    screen.blit(score_surf, (10, 550))
  
# display lives
def display_lives(lives):
   display_lives = font.render(f"Lives: {lives}", True, text_col)
   screen.blit(display_lives, (440, 550))


# brick wall class
class wall():
    def __init__(self):
        self.width = screen_width // cols
        self.height = 50

    def create_wall(self):
        block_number = 0
        self.blocks = []
        # define an empty list for an individual block
        block_individual = []
        for row in range(rows):
            # reset the block row list
            block_row = []
            # iterate through each column in that row
            for col in range(cols):
                # generate x and y positions for each block and create a rectangle from that
                block_x = col * self.width
                block_y = row * self.height
                rect = pygame.Rect(block_x, block_y, self.width, self.height)
                # assign block strength based on row
                if row < 2:
                    strength = 3
                elif row < 4:
                    strength = 2
                elif row < 6:
                    strength = 1
                # create a list at this point to store the rect and colour data
                block_individual = [rect, strength]
                # append that individual block to the block row
                block_row.append(block_individual)
                block_number += 1
            # append the row to the full list of blocks
            self.blocks.append(block_row)

    def draw_wall(self):
        for row in self.blocks:
            for block in row:
                # assign a colour based on block strength
                if block[1] == 3:
                    block_col = block_tiffany
                elif block[1] == 2:
                    block_col = block_keppel
                elif block[1] == 1:
                    block_col = block_darkcyan
                pygame.draw.rect(screen, block_col, block[0])
                pygame.draw.rect(screen, bg, (block[0]), 2)
        
# paddle class
class paddle():
    def __init__(self):
        self.reset()

    def move(self):
        # reset movement direction
        self.direction = 0
        key = pygame.key.get_pressed()
        if key[pygame.K_LEFT] and self.rect.left > 0:
            self.rect.x -= self.speed
            self.direction = -1
        if key[pygame.K_RIGHT] and self.rect.right < screen_width:
            self.rect.x += self.speed
            self.direction = 1

    def draw(self):
        pygame.draw.rect(screen, block_mayablue, self.rect)
        pygame.draw.rect(screen, block_indigo, self.rect, 3)

    def reset(self):
        # define paddle variables
        self.height = 20
        self.width = int(screen_width / cols)
        self.x = int((screen_width / 2) - (self.width / 2))
        self.y = screen_height - (self.height * 2)
        self.speed = 9
        self.rect = pygame.Rect(self.x, self.y, self.width, self.height)
        self.direction = 0


# ball class
class game_ball():
    def __init__(self, x, y):
        self.reset(x, y)


    def move(self):
        global score
        global lives
        # collision threshold
        collision_thresh = 5

        # start off with the assumption that the wall has been destroyed completely
        wall_destroyed = 1
        row_count = 0
        for row in wall.blocks:
            item_count = 0
            for item in row:
                # check collision
                if self.rect.colliderect(item[0]):
                    # check if collision was from above
                    if abs(self.rect.bottom - item[0].top) < collision_thresh and self.speed_y > 0:
                        self.speed_y *= -1
                        score += 1 
                        display_score(score)
                    # check if collision was from below
                    if abs(self.rect.top - item[0].bottom) < collision_thresh and self.speed_y < 0:
                        self.speed_y *= -1
                        score += 1 
                        display_score(score)
                    # check if collision was from left
                    if abs(self.rect.right - item[0].left) < collision_thresh and self.speed_x > 0:
                        self.speed_x *= -1
                        score += 1 
                        display_score(score)
                    # check if collision was from right
                    if abs(self.rect.left - item[0].right) < collision_thresh and self.speed_x < 0:
                        self.speed_x *= -1
                        score += 1 
                        display_score(score)
                    # reduce the block's strength by doing damage to it
                    if wall.blocks[row_count][item_count][1] > 1:
                        wall.blocks[row_count][item_count][1] -= 1
                    else:
                        wall.blocks[row_count][item_count][0] = (0, 0, 0, 0)

                # check if block still exists, in whcih case the wall is not destroyed
                if wall.blocks[row_count][item_count][0] != (0, 0, 0, 0):
                    wall_destroyed = 0
                # increase item counter
                item_count += 1
            # increase row counter
            row_count += 1
        # after iterating through all the blocks, check if the wall is destroyed
        if wall_destroyed == 1:
            self.game_over = 1

        # check for collision with walls
        if self.rect.left < 0 or self.rect.right > screen_width:
            self.speed_x *= -1

        # check for collision with top and bottom of the screen
        if self.rect.top < 0:
            self.speed_y *= -1
        if self.rect.bottom > screen_height:
          
        # lives
          if self.rect.bottom > screen_height:

            # subtract a life
            lives -= 1 
            ball.reset(screen_width // 2, screen_height //2)
            paddle.reset(self)
            display_lives = font.render("Lives:" + str(lives), True, text_col)
            screen.blit(display_lives, (10, 10))
            pygame.display.update()
            if lives == 0:
              pygame.quit()
            # else:
              # # reset the paddle and display remaining lives
              # ball.reset(screen_width // 2, screen_height //2)
              # paddle.reset(self)
              # display_lives = font.render("Lives:" + str(lives), True, text_col)
              # screen.blit(display_lives, (10, 10))
              # pygame.display.update()

        # look for collission with paddle
        if self.rect.colliderect(player_paddle):
            # check if colliding from the top
            if abs(self.rect.bottom - player_paddle.rect.top) < collision_thresh and self.speed_y > 0:
                self.speed_y *= -1
                self.speed_x += player_paddle.direction
                if self.speed_x > self.speed_max:
                    self.speed_x = self.speed_max
                elif self.speed_x < 0 and self.speed_x < -self.speed_max:
                    self.speed_x = -self.speed_max
            else:
                self.speed_x *= -1

        self.rect.x += self.speed_x
        self.rect.y += self.speed_y

        return self.game_over

    def draw(self):
        pygame.draw.circle(screen, block_mayablue, (self.rect.x + self.ball_rad, self.rect.y + self.ball_rad),
                           self.ball_rad)
        pygame.draw.circle(screen, block_indigo, (self.rect.x + self.ball_rad, self.rect.y + self.ball_rad),
                           self.ball_rad, 3)

    def reset(self, x, y):
        self.ball_rad = 10
        self.x = x - self.ball_rad
        self.y = y
        self.rect = pygame.Rect(self.x, self.y, self.ball_rad * 2, self.ball_rad * 2)
        self.speed_x = 4
        self.speed_y = -4
        self.speed_max = 5
        self.game_over = 0


# create a wall
wall = wall()
wall.create_wall()

# create paddle
player_paddle = paddle()

# create ball
ball = game_ball(player_paddle.x + (player_paddle.width // 2), player_paddle.y - player_paddle.height)

run = True
while run:

    clock.tick(fps)

    screen.fill(bg)

    # draw all objects
    wall.draw_wall()
    player_paddle.draw()
    ball.draw()

    if live_ball:
        # draw paddle
        player_paddle.move()
        # draw ball
        game_over = ball.move()
        if game_over != 0:
            live_ball = False

    # print player instructions
    if not live_ball:
        if game_over == 0:
            draw_text('CLICK ANYWHERE TO START', font, text_col, 100, screen_height // 2 + 100)
        elif game_over == 1:
            draw_text('YOU WON!', font, text_col, 240, screen_height // 2 + 50)
            draw_text('CLICK ANYWHERE TO START', font, text_col, 100, screen_height // 2 + 100)
        elif game_over == -1:
            draw_text('YOU LOST!', font, text_col, 240, screen_height // 2 + 50)
            draw_text('CLICK ANYWHERE TO START', font, text_col, 100, screen_height // 2 + 100)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False
        if event.type == pygame.MOUSEBUTTONDOWN and live_ball == False:
            live_ball = True
            ball.reset(player_paddle.x + (player_paddle.width // 2), player_paddle.y - player_paddle.height)
            player_paddle.reset()
            wall.create_wall()

    wall.draw_wall()
    display_lives(lives)
    display_score(score)
    pygame.display.update()


    
pygame.quit()


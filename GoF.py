import pygame
import numpy as np
import sys

WIDTH = 500
HEIGHT = 300
BLACK_COLOR = "#33333D"
WHITE_COLOR = "#FFFFFF"
GREY_COLOR = "#808080"

DIE = 0
ALIVE = 1

CELL_SIZE = 10
FPS = 60

pygame.init()
Main_Screen = pygame.display.set_mode((WIDTH, HEIGHT))
Main_Screen.fill(GREY_COLOR)
pygame.display.set_caption("Game of Life")
fps = pygame.time.Clock()

def DrawCell(surface, cell):
    for i, j in np.ndindex(cell.shape):
        if cell[i][j] == DIE:
            pygame.draw.rect(surface, BLACK_COLOR, (i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE-1, CELL_SIZE-1))
        elif cell[i][j] == ALIVE:
            pygame.draw.rect(surface, WHITE_COLOR, (i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE-1, CELL_SIZE-1))

def update(cell, update_cell):
    nrows, ncols = cell.shape
    for i in range(nrows):
        for j in range(ncols):
            # 使用模运算符(%)来实现周期性边界条件
            alive_neighbors = (
                cell[i, (j-1) % ncols] + cell[i, (j+1) % ncols] +             # 左右
                cell[(i-1) % nrows, j] + cell[(i+1) % nrows, j] +             # 上下
                cell[(i-1) % nrows, (j-1) % ncols] + cell[(i-1) % nrows, (j+1) % ncols] + # 上左右
                cell[(i+1) % nrows, (j-1) % ncols] + cell[(i+1) % nrows, (j+1) % ncols]   # 下左右
            )

            if cell[i][j] == ALIVE:
                if alive_neighbors < 2 or alive_neighbors > 3:
                    update_cell[i][j] = DIE
                else:
                    update_cell[i][j] = ALIVE
            else:
                if alive_neighbors == 3:
                    update_cell[i][j] = ALIVE

    cell[:, :] = update_cell[:, :]



def handle_mouse_click(cell, pos):
    i, j = pos[0] // CELL_SIZE, pos[1] // CELL_SIZE
    cell[i, j] = 1 - cell[i, j]

Cell = np.zeros((int(WIDTH / CELL_SIZE), int(HEIGHT / CELL_SIZE)))
update_Cell = np.zeros((int(WIDTH / CELL_SIZE), int(HEIGHT / CELL_SIZE)))

while True:
    fps.tick(FPS)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        elif event.type == pygame.MOUSEBUTTONDOWN:
            pos = pygame.mouse.get_pos()
            handle_mouse_click(Cell, pos)
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                update_Cell.fill(DIE)
                update(Cell, update_Cell)

    DrawCell(Main_Screen, Cell)
    pygame.display.flip()

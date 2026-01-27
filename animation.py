import pygame
import sys

# ----- Grid -----
grid_str = [
"R O O O O O O O X G",
"O O O O O O O O X O",
"O O O O O O O O X O",
"O O O O O O O O X O",
"O O O O O O O O X O",
"O O O O O O O O X O",
"O O O O O O O O X O",
"O O O O O O O O X O",
"O O O O O O O O X O",
"O O O O O O O O O O",
]
ROWS = len(grid_str)
COLS = len(grid_str[0].split())
CELL_SIZE = 60

# ----- Colors -----
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BLUE = (0, 0, 255)
GREEN = (0, 255, 0)
GRAY = (200, 200, 200)
RED = (255, 0, 0)

# ----- Parse grid -----
grid = [row.split() for row in grid_str]

# Find start and goal
for y in range(ROWS):
    for x in range(COLS):
        if grid[y][x] == 'R':
            robot_pos = [x, y]
        if grid[y][x] == 'G':
            goal_pos = [x, y]

# ----- Robot state -----
# 0 = UP, 1 = RIGHT, 2 = DOWN, 3 = LEFT
robot_dir = 0
dirs = [(0, -1), (1, 0), (0, 1), (-1, 0)]

# ----- Commands -----
commands = list("RFFFFFFFRFFFFFFFFFLFFLFFFFFFFFF") 
current_command_index = 0

# ----- Initialize Pygame -----
pygame.init()
screen = pygame.display.set_mode((COLS*CELL_SIZE, ROWS*CELL_SIZE + 40))  # extra space for text
pygame.display.set_caption("Grid Robot Auto Player")
clock = pygame.time.Clock()
font = pygame.font.SysFont(None, 30)

# ----- Draw function -----
def draw_grid():
    for y in range(ROWS):
        for x in range(COLS):
            rect = pygame.Rect(x*CELL_SIZE, y*CELL_SIZE, CELL_SIZE, CELL_SIZE)
            if grid[y][x] == 'X':
                pygame.draw.rect(screen, BLACK, rect)
            elif grid[y][x] == 'G':
                pygame.draw.rect(screen, GREEN, rect)
            else:
                pygame.draw.rect(screen, WHITE, rect)
            pygame.draw.rect(screen, GRAY, rect, 1)

    # Draw robot as arrow
    cx = robot_pos[0]*CELL_SIZE + CELL_SIZE//2
    cy = robot_pos[1]*CELL_SIZE + CELL_SIZE//2
    size = CELL_SIZE//2 - 5
    if robot_dir == 0:  # UP
        points = [(cx, cy - size), (cx - size//2, cy + size//2), (cx + size//2, cy + size//2)]
    elif robot_dir == 1:  # RIGHT
        points = [(cx + size, cy), (cx - size//2, cy - size//2), (cx - size//2, cy + size//2)]
    elif robot_dir == 2:  # DOWN
        points = [(cx, cy + size), (cx - size//2, cy - size//2), (cx + size//2, cy - size//2)]
    else:  # LEFT
        points = [(cx - size, cy), (cx + size//2, cy - size//2), (cx + size//2, cy + size//2)]

    pygame.draw.polygon(screen, BLUE, points)

    # Draw current command text
    if current_command_index < len(commands):
        text_surface = font.render(f"Command: {commands[current_command_index]}", True, RED)
    else:
        text_surface = font.render("Finished!", True, RED)
    screen.blit(text_surface, (10, ROWS*CELL_SIZE + 5))

# ----- Game loop -----
running = True
STEP_DELAY = 500  # milliseconds per command
last_step_time = pygame.time.get_ticks()

while running:
    screen.fill(WHITE)
    draw_grid()
    pygame.display.flip()

    current_time = pygame.time.get_ticks()
    if current_command_index < len(commands) and current_time - last_step_time >= STEP_DELAY:
        cmd = commands[current_command_index]
        if cmd == 'L':
            robot_dir = (robot_dir - 1) % 4
        elif cmd == 'R':
            robot_dir = (robot_dir + 1) % 4
        elif cmd == 'F':
            dx, dy = dirs[robot_dir]
            new_x = robot_pos[0] + dx
            new_y = robot_pos[1] + dy
            # Check bounds and obstacles
            if 0 <= new_x < COLS and 0 <= new_y < ROWS and grid[new_y][new_x] != 'X':
                robot_pos = [new_x, new_y]
            # Check goal
            if robot_pos == goal_pos:
                print("Robot reached the goal! 🎉")
        current_command_index += 1
        last_step_time = current_time

    # Handle quit
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    clock.tick(60)

pygame.quit()
sys.exit()
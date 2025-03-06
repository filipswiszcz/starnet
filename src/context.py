import pygame

from OpenGL.GL import *
from OpenGL.GLU import *

pygame.init()
pygame.display.set_mode((800, 600), pygame.DOUBLEBUF | pygame.OPENGL)

gluPerspective(45, (800 / 600), 0.1, 50.0)
glTranslatef(0.0, 0.0, -5.0)

verticies = (
    (1, -1, -1),
    (1, 1, -1),
    (-1, 1, -1),
    (-1, -1, -1),
    (1, -1, 1),
    (1, 1, 1),
    (-1, -1, 1),
    (-1, 1, 1)
)
edges = (
    (0,1),
    (0,3),
    (0,4),
    (2,1),
    (2,3),
    (2,7),
    (6,3),
    (6,4),
    (6,7),
    (5,1),
    (5,4),
    (5,7)
)

is_running = True

while is_running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT: is_running = False

    glRotatef(1, 3, 1, 1)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

    glBegin(GL_LINES)
    for e in edges:
        for v in e:
            glVertex3fv(verticies[v])
    glEnd()

    pygame.display.flip()
    pygame.time.wait(10)
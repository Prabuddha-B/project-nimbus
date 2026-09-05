#include <windows.h>
#include <glut.h>
#include "Camera.h"

// Camera position coordinates.
float camX = 0.0f;
float camY = 60.0f;
float camZ = 180.0f;

// Handles keyboard camera movement.
void keyboard(unsigned char key, int x, int y)
{
    switch (key){
    case 'w':
        camZ -= 1.0f;
        break;

    case 's':
        camZ += 1.0f;
        break;

    case 'a':
        camX -= 1.0f;
        break;

    case 'd':
        camX += 1.0f;
        break;

    case 'q':
        camY += 1.0f;
        break;

    case 'e':
        camY -= 1.0f;
        break;
    }

    glutPostRedisplay();
}
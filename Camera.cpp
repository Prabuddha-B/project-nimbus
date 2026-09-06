#include <windows.h>
#include <glut.h>
#include<stdio.h>
#include "Camera.h"
#include "Controls.h"

// Camera position coordinates.
float camX = 0.0f;
float camY = 60.0f;
float camZ = 180.0f;

// Show / Hide Sun sphere
bool showSun = true;

// Sun light position
float sunX = 50.0f;
float sunY = 80.0f;
float sunZ = 50.0f;

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

    case 'i':
        sunY += 5.0f;
        break;

    case 'k':
        sunY -= 5.0f;
        break;

    case 'j':
        sunX -= 5.0f;
        break;

    case 'l':
        sunX += 5.0f;
        break;

    case 'u':
        sunZ -= 5.0f;
        break;

    case 'o':
        sunZ += 5.0f;
        break;

    case 'p':
        showSun = !showSun;
        break;

    case 'g':
        showGrid = !showGrid;
        glutPostRedisplay();
        break;

    case 'x':
        showAxes = !showAxes;
        glutPostRedisplay();
        break;

    case 'z':
        lightingEnabled = !lightingEnabled;
        glutPostRedisplay();
        break;
    }


    printf(
        "Sun Position: %.1f %.1f %.1f\n", sunX, sunY, sunZ);


    glutPostRedisplay();
}
#include <windows.h>
#include <glut.h>
#include<stdio.h>
#include <cmath>

#include "Camera.h"
#include "Controls.h"
#include "Tower.h"
#include "Game.h"


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


// Tower light state
bool isTowerLightOn = false;


// Handles keyboard camera movement.
void keyboard(unsigned char key, int x, int y){

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

    case 't':
        isTowerLightOn = !isTowerLightOn;
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

    case 'r':
        towerRotation += 5.0f;
        break;

    case '1':
        cameraMode = 1; 
        break;

    case '2':
        cameraMode = 2; 
        break;

    case '3':
        cameraMode = 3; 
        break;

    case 13:                                        // 13 is the ASCII code for the 'Enter' key
        if (gameState == 0) {
            gameState = 1; 
        }
        break;
    }

    if (key == 'r' || key == 'R') {
        resetGame();
    }
    
    glutPostRedisplay();
}


// Triggers when an arrow key is pressed DOWN
void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:    keyUp = true;    break;
    case GLUT_KEY_DOWN:  keyDown = true;  break;
    case GLUT_KEY_LEFT:  keyLeft = true;  break;
    case GLUT_KEY_RIGHT: keyRight = true; break;
    }
}


// Triggers when an arrow key is RELEASED
void specialKeysUp(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:    keyUp = false;    break;
    case GLUT_KEY_DOWN:  keyDown = false;  break;
    case GLUT_KEY_LEFT:  keyLeft = false;  break;
    case GLUT_KEY_RIGHT: keyRight = false; break;
    }
}
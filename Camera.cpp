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


    


    glutPostRedisplay();
}


// Handles arrow key movement for the player
void specialKeys(int key, int x, int y) {
    // Only allow the player to fly if the game has officially started (State 1)
    if (gameState != 1) return;

    float speed = 2.0f;
    float turnSpeed = 5.0f;

    // Convert angle to radians for math
    float rad = playerAngle * 3.14159f / 180.0f;

    switch (key) {
    case GLUT_KEY_UP:
        // Push forward in the exact direction the player is facing
        playerX -= speed * sin(rad);
        playerZ -= speed * cos(rad);
        break;

    case GLUT_KEY_DOWN:
        // Reverse
        playerX += speed * sin(rad);
        playerZ += speed * cos(rad);
        break;

    case GLUT_KEY_LEFT:
        // Turn left
        playerAngle += turnSpeed;
        break;

    case GLUT_KEY_RIGHT:
        // Turn right
        playerAngle -= turnSpeed;
        break;
    }

    glutPostRedisplay();
}
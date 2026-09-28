#include "Game.h"
#include <cmath>

int gameState = 0;
int cameraMode = 1;

// Spawn player at the bottom of the pitch
float playerX = 0.0f;
float playerZ = 40.0f;
float playerAngle = 0.0f;

// Spawn the snitch on the other side of the pitch
float snitchX = 0.0f;
float snitchZ = -40.0f;

// Smooth Physical Variables for Player Movement
bool keyUp = false;
bool keyDown = false;
bool keyLeft = false;
bool keyRight = false;
float currentSpeed = 0.0f;


// Camera Variables
bool isInsidePitch(float targetX, float targetZ) {

    float a = 28.0f;
    float b = 58.0f;

    // The Ellipse Equation
    float value = (targetX * targetX) / (a * a) + (targetZ * targetZ) / (b * b);

    // If the value is less than or equal to 1, the coordinate is safely inside the grass
    return (value <= 1.0f);
}


// Update Player Movement based on Keyboard Input
void updatePlayerMovement() {
    if (gameState != 1) return;

    if (keyLeft) playerAngle += 2.5f;
    if (keyRight) playerAngle -= 2.5f;

    // Acceleration
    if (keyUp) {
        currentSpeed += 0.02f;
    }
    else if (keyDown) {
        currentSpeed -= 0.02f;
    }

    //  More Gliding (Friction)
    currentSpeed *= 0.95f;

    //  reduced max speeds 
    if (currentSpeed > 0.6f) currentSpeed = 0.6f;
    if (currentSpeed < -0.3f) currentSpeed = -0.3f;

    //  Calculate next position
    float rad = playerAngle * 3.14159f / 180.0f;
    float nextX = playerX - currentSpeed * sin(rad);
    float nextZ = playerZ - currentSpeed * cos(rad);

    // Boundary Collision
    if (isInsidePitch(nextX, nextZ)) {
        playerX = nextX;
        playerZ = nextZ;
    }
    else {
        currentSpeed = 0.0f;
    }

    // Snitch Collision Detection 
    float dx = playerX - snitchX;
    float dz = playerZ - snitchZ;

    // Calculate the straight-line distance between player and snitch
    float distance = sqrt(dx * dx + dz * dz);

    // If the player gets within 2.5 units of the Snitch, they catch it!
    if (distance < 2.5f) {
        gameState = 2;  // Trigger the Victory State
    }
}


// Rest Game Function to Reset All Variables and States
void resetGame() {
    
    gameState = 0;

    //  Reset Player Position and Angle
    playerX = 0.0f;
    playerZ = 40.0f;
    playerAngle = 0.0f;

    //  Kill all physics momentum and clear keyboard flags
    currentSpeed = 0.0f;
    keyUp = false;
    keyDown = false;
    keyLeft = false;
    keyRight = false;

    // Reset Snitch Position to the opposite side of the pitch
    snitchX = 0.0f;
    snitchZ = -40.0f;

    // Reset Camera back to Free Roam (Optional, but good for a fresh start)
    cameraMode = 1;
}
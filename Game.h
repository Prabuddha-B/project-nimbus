#pragma once

// Game States: 
// 0 = Ready (Waiting for Enter)
// 1 = Playing (In progress)
// 2 = Victory (Snitch Caught)
extern int gameState;

// Camera Modes:
// 1 = Free Roam (Standard)
// 2 = Chase Cam (Behind Player)
// 3 = Tactical Top-Down
extern int cameraMode;

// Player positional data (Camera needs this to follow the player)
extern float playerX;
extern float playerZ;
extern float playerAngle; // Which way the player is facing

// Snitch positional data
extern float snitchX;
extern float snitchZ;

// Smooth Physical Variables for Player Movement
extern bool keyUp;
extern bool keyDown;
extern bool keyLeft;
extern bool keyRight;
extern float currentSpeed;

// Checks if a given X and Z coordinate is inside the elliptical pitch
bool isInsidePitch(float targetX, float targetZ);

// Physics update loop
void updatePlayerMovement();

// Resets all game variables for a new round
void resetGame();
#pragma once

// Camera position coordinates
extern float camX;
extern float camY;
extern float camZ;

// Sun light position
extern float sunX;
extern float sunY;
extern float sunZ;

// Sun Visibility
extern bool showSun;

// Handles keyboard camera movement
void keyboard(unsigned char key, int x, int y);

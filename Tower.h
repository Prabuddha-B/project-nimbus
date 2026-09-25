#pragma once

extern float towerRotation;

// Draws the textured shaft of the tower
void drawTexturedShaft(GLuint tex);

// Draws hourglass viewing deck with open front
void drawHourglassDeck(GLuint deckTex, GLenum lightID);

// Draws Quidditch tent roof
void drawPyramidRoof(float width, float height, GLuint roofTex);

// Flag animation function
void drawAnimatedFlag(GLuint flagTex);

// Draw the tower
void drawTower(float angleDegrees, float baseR, float baseG, float baseB, GLuint shaftTex, GLuint deckTex, GLuint roofTex, GLuint flagTex, GLenum lightID);
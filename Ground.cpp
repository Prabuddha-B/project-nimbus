#include<windows.h>
#include <glut.h>
#include <cmath>
#include "Ground.h"
#include "Texture.h"

// Quidditch pitch dimensions
const float PITCH_LENGTH = 120.0f;
const float PITCH_WIDTH = 60.0f;


// Draws the main grass field.
void drawGround(){

    glBindTexture(GL_TEXTURE_2D, grassTexture);

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POLYGON);

    for (int angle = 0; angle < 360; angle++)
    {
        float theta = angle * 3.14159f / 180.0f;

        float x = (PITCH_WIDTH / 2) * cos(theta);
        float z = (PITCH_LENGTH / 2) * sin(theta);

        float u = ((x + PITCH_WIDTH / 2) / PITCH_WIDTH);
        float v = ((z + PITCH_LENGTH / 2) / PITCH_LENGTH);

        glTexCoord2f(u, v);
        glVertex3f(x, 0.0f, z);
    }

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
}


// Draws the boundary of the Quidditch pitch
void drawPitchBoundary() {
    glColor3f(1.0f, 1.0f, 1.0f);

    glLineWidth(3.0f);

	glBegin(GL_LINE_LOOP);

    for (int angle = 0; angle < 360; angle++) {
		float theta = angle * 3.14159f / 180.0f;

        float x = (PITCH_WIDTH / 2) * cos(theta);
        float z = (PITCH_LENGTH / 2) * sin(theta);

		glVertex3f(x, 0.05f, z);
    }

    glEnd();
}


// Draws the center line.
void drawCenterLine(){
    glColor3f(1.0f, 1.0f, 1.0f);

    glLineWidth(2.0f);

    glBegin(GL_LINES);

    glVertex3f(-30.0f, 0.05f, 0.0f);
    glVertex3f(30.0f, 0.05f, 0.0f);

    glEnd();
}


// Draws the center circle.
void drawCenterCircle()
{
    const float radius = 8.0f;

    glColor3f(1.0f, 1.0f, 1.0f);

    glLineWidth(2.0f);

    glBegin(GL_LINE_LOOP);

    for (int angle = 0; angle < 360; angle++){
        float theta = angle * 3.1415926f / 180.0f;

        float x = radius * cos(theta);
        float z = radius * sin(theta);

        glVertex3f(x, 0.05f, z);
    }

    glEnd();
}
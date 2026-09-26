#include<windows.h>
#include <glut.h>
#include <cmath>

#include "Ground.h"
#include "Texture.h"

// Quidditch pitch dimensions
const float PITCH_LENGTH = 120.0f;
const float PITCH_WIDTH = 60.0f;

// World Dimensions
const float WORLD_SIZE = 2000.0f;
const float WORLD_Y = -0.5f;


// Draw the ground plane for the world
void drawWorldGround(){

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, dirtTexture);

    glColor3f(0.8f, 0.8f, 0.8f);    // Slightly darkens texture.

    const float SIZE = WORLD_SIZE;

    glBegin(GL_QUADS);

    glNormal3f(0.0f, 1.0f, 0.0f);

    glTexCoord2f(0, 0);
    glVertex3f(-SIZE, WORLD_Y, -SIZE);

    glTexCoord2f(100, 0);
    glVertex3f(SIZE, WORLD_Y, -SIZE);

    glTexCoord2f(100, 100);
    glVertex3f(SIZE, WORLD_Y, SIZE);

    glTexCoord2f(0, 100);
    glVertex3f(-SIZE, WORLD_Y, SIZE);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);
}


// Draws the embankment around the pitch
void drawEmbankment(){

    const float INNER_X = 55.0f;
    const float INNER_Z = 95.0f;

    const float OUTER_X = 80.0f;
    const float OUTER_Z = 120.0f;

    const float HEIGHT = 1.5f;

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, dirtTexture);

    glColor3f(0.9f, 0.9f, 0.9f);

    glBegin(GL_QUAD_STRIP);

    for (int angle = 0; angle <= 360; angle++){

        float theta = angle * 3.1415926f / 180.0f;

        float innerX = INNER_X * cos(theta);
        float innerZ = INNER_Z * sin(theta);

        float outerX = OUTER_X * cos(theta);
        float outerZ = OUTER_Z * sin(theta);

        glNormal3f(0.0f, 1.0f, 0.0f);

        glTexCoord2f(0.0f, angle / 20.0f);
        glVertex3f(innerX, HEIGHT, innerZ);

        glTexCoord2f(1.0f, angle / 20.0f);
        glVertex3f(outerX, HEIGHT, outerZ);
    }

    glEnd();

    glBegin(GL_QUAD_STRIP);

    for (int angle = 0; angle <= 360; angle++){
        float theta = angle * 3.1415926f / 180.0f;

        float outerX = OUTER_X * cos(theta);
        float outerZ = OUTER_Z * sin(theta);

		// Normals for the outer slope wall 
        glNormal3f(
            cos(theta),
            0.4f,
            sin(theta)
        );

        glTexCoord2f(0.0f, angle / 20.0f);
        glVertex3f(outerX, HEIGHT, outerZ);

        glTexCoord2f(1.0f, angle / 20.0f);
        glVertex3f(outerX, -0.2f, outerZ);
    }

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);
}


// Draws the main grass field.
void drawGround(){

	glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, grassTexture);

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POLYGON);

    glNormal3f(0.0f, 1.0f, 0.0f);

    for (int angle = 0; angle < 360; angle++){

        float theta = angle * 3.14159f / 180.0f;

        float x = (PITCH_WIDTH / 2) * cos(theta);
        float z = (PITCH_LENGTH / 2) * sin(theta);

        // Texture Coordinates
        float u = ((x + PITCH_WIDTH / 2) / PITCH_WIDTH);
        float v = ((z + PITCH_LENGTH / 2) / PITCH_LENGTH);

        glTexCoord2f(u, v);
        glVertex3f(x, 0.0f, z);
    }

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
}


// Draws the white boundary of the Quidditch pitch
void drawPitchBoundary() {

    glColor3f(1.0f, 1.0f, 1.0f);

    glLineWidth(3.0f);

    // Automatically connects the final vertex back to the first, creating a closed boundary
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
void drawCenterCircle(){

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


// Draws ring of mountains 
void drawPerimeterMountains() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mountainTexture);

    glColor3f(0.8f, 0.8f, 0.8f);

    int slices = 100;
    int rings = 6;

    float innerRadius = 800.0f;
    float outerRadius = 1700.0f;
    float ringWidth = (outerRadius - innerRadius) / (rings - 1);

    for (int i = 0; i < rings - 1; i++) {
        float r1 = innerRadius + i * ringWidth;
        float r2 = innerRadius + (i + 1) * ringWidth;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; j++) {
            float theta = (float)j * (2.0f * 3.14159f / slices);

            float noise = sin(theta * 5.0f) * 80.0f + cos(theta * 11.0f) * 50.0f + sin(theta * 3.0f) * 140.0f;

            // --- INNER VERTEX ---
            float x1 = r1 * cos(theta);
            float z1 = r1 * sin(theta);
            float blend1 = sin((r1 - innerRadius) / (outerRadius - innerRadius) * 3.14159f);
            float y1 = (WORLD_Y - 5.0f) + (150.0f + noise) * blend1;

            // --- OUTER VERTEX ---
            float x2 = r2 * cos(theta);
            float z2 = r2 * sin(theta);
            float blend2 = sin((r2 - innerRadius) / (outerRadius - innerRadius) * 3.14159f);
            float y2 = (WORLD_Y - 5.0f) + (150.0f + noise) * blend2;

            // FLIPPED NORMALS: Pointing outward and upward to perfectly match the ground lighting
            float nx = cos(theta);
            float nz = sin(theta);
            float ny = 1.5f;
            float len = sqrt(nx * nx + ny * ny + nz * nz);

            glNormal3f(nx / len, ny / len, nz / len);

            glTexCoord2f((x1 + WORLD_SIZE) / 40.0f, (z1 + WORLD_SIZE) / 40.0f);
            glVertex3f(x1, y1, z1);

            glNormal3f(nx / len, ny / len, nz / len);

            glTexCoord2f((x2 + WORLD_SIZE) / 40.0f, (z2 + WORLD_SIZE) / 40.0f);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0f, 1.0f, 1.0f);
}
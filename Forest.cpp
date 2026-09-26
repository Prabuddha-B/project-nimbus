#include <windows.h>
#include <glut.h>
#include <cmath>
#include <cstdlib>

#include "Forest.h"
#include "Texture.h"


const int NUM_TREES = 1500;
Tree forest[NUM_TREES];


float getTerrainHeight(float x, float z) {
    float r = sqrt(x * x + z * z);

    // The mountain technically starts blending at 800.0f
    if (r < 800.0f || r > 1700.0f) {
        return -0.5f;
    }

    float theta = atan2(z, x);
    if (theta < 0.0f) theta += 2.0f * 3.14159f;

    float noise = sin(theta * 5.0f) * 80.0f + cos(theta * 11.0f) * 50.0f + sin(theta * 3.0f) * 140.0f;
    float blend = sin((r - 800.0f) / 900.0f * 3.14159f);

    return (-5.5f) + (150.0f + noise) * blend;
}

void initForest() {
    for (int i = 0; i < NUM_TREES; i++) {
        float x, z;

        if (i < 900) {
            float r = 650.0f + (rand() % 155);
            float theta = (rand() % 360) * 3.14159f / 180.0f;
            x = r * cos(theta);
            z = r * sin(theta);
        }
        else if (i < 1300) {
            x = (rand() % 900) - 450.0f;       // X: -450 to 450
            z = -400.0f - (rand() % 400);      // Z: -400 to -800
        }
        else {
            float r = 300.0f + (rand() % 350);
            float theta = (rand() % 360) * 3.14159f / 180.0f;
            x = r * cos(theta);
            z = r * sin(theta);
        }

        // BOUNDARY ENFORCEMENT
        float r_check = sqrt(x * x + z * z);

        // Keep trees off the Quidditch pitch
        if (r_check < 280.0f) {
            x = (x / r_check) * 280.0f;
            z = (z / r_check) * 280.0f;
            r_check = 280.0f;
        }

        if (r_check > 805.0f) {
            x = (x / r_check) * 805.0f;
            z = (z / r_check) * 805.0f;
        }

        forest[i].x = x;
        forest[i].z = z;
        forest[i].y = getTerrainHeight(x, z);

        forest[i].scale = 0.8f + ((rand() % 50) / 100.0f);
        forest[i].rotationY = (float)(rand() % 360);
        forest[i].type = (rand() % 3) + 1;
        forest[i].colorOffset = ((rand() % 20) - 10) / 100.0f;
    }
}

void drawSingle3DTree(int type, float colorOffset) {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluQuadricTexture(quad, GL_TRUE);

    glEnable(GL_TEXTURE_2D);

    // Draw Trunk
    glBindTexture(GL_TEXTURE_2D, seatTexture);
    glColor3f(0.6f, 0.45f, 0.35f);
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad, 1.5f, 1.5f, 10.0f, 6, 1);
    glPopMatrix();

    // Draw Leaves
    glBindTexture(GL_TEXTURE_2D, treeTexture);
   
    glColor3f(0.7f + (colorOffset * 0.5f), 0.95f + colorOffset, 0.7f + (colorOffset * 0.5f));

    if (type >= 1) {
        glPushMatrix();
        glTranslatef(0.0f, 5.0f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(quad, 8.0f, 0.0f, 12.0f, 6, 1);
        glPopMatrix();
    }

    if (type >= 2) {
        glPushMatrix();
        glTranslatef(0.0f, 12.0f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(quad, 6.0f, 0.0f, 10.0f, 6, 1);
        glPopMatrix();
    }

    if (type >= 3) {
        glPushMatrix();
        glTranslatef(0.0f, 18.0f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(quad, 4.0f, 0.0f, 9.0f, 6, 1);
        glPopMatrix();
    }

    gluDeleteQuadric(quad);
    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);
}

void drawForest() {
    for (int i = 0; i < NUM_TREES; i++) {
        glPushMatrix();
        glTranslatef(forest[i].x, forest[i].y, forest[i].z);
        glRotatef(forest[i].rotationY, 0.0f, 1.0f, 0.0f);
        glScalef(forest[i].scale, forest[i].scale, forest[i].scale);
        drawSingle3DTree(forest[i].type, forest[i].colorOffset);
        glPopMatrix();
    }
}
#include<windows.h>
#include<glut.h>
#include <cmath>
#include "GoalPost.h"

// Draws one goal hoop
void drawGoalPost(float x, float z, float height, float radius)
{
    glPushMatrix();

    
    glTranslatef(x, 0.0f, z);

    GLUquadric* quad = gluNewQuadric();

  
    // Pole
    glColor3f(0.95f, 0.95f, 0.95f);

    glPushMatrix();

    glRotatef(-90.0f, 1, 0, 0);
    gluCylinder(quad, 0.25, 0.25, height, 20, 20);

    glPopMatrix();

    
    // Base
    glColor3f(0.6f, 0.6f, 0.6f);

    glPushMatrix();

    glRotatef(-90.0f, 1, 0, 0);
    gluDisk(quad, 0.0, 0.5, 20, 1);

    glPopMatrix();

    
    // Hoop
    glPushMatrix();

 
    glTranslatef(0.0f, height + radius, 0.0f);
    glColor3f( 1.0f, 0.85f, 0.0f);
    glutWireTorus(0.08, radius, 30, 60);

    glPopMatrix();

    gluDeleteQuadric(quad);

    glPopMatrix();
}


// Draws all six Quidditch goal posts
void drawAllGoalPosts()
{
    // Left side
    drawGoalPost(-10.0f, -50.0f, 12.0f, 1.4f); // medium
    drawGoalPost(0.0f, -50.0f, 16.0f, 1.8f); // large
    drawGoalPost(10.0f, -50.0f, 8.0f, 1.0f); // small

    // Right side (mirrored)
    drawGoalPost(-10.0f, 50.0f, 8.0f, 1.0f); // small
    drawGoalPost(0.0f, 50.0f, 16.0f, 1.8f); // large
    drawGoalPost(10.0f, 50.0f, 12.0f, 1.4f); // medium
}


// Draws sand goal area
void drawGoalArea(float zLimit, bool topSide)
{
    const float a = 30.0f; // pitch half width
    const float b = 60.0f; // pitch half length

    
    const float curveDepth = 7.0f;

    glColor3f(0.90f, 0.88f, 0.78f);

    glBegin(GL_POLYGON);

    float x_edge = a * sqrt(1.0f - (zLimit * zLimit) / (b * b));

    if (topSide)
    {
        for (float z = zLimit; z <= b; z += 0.5f){
            float x = a * sqrt(1.0f - (z * z) / (b * b));
            glVertex3f(x, 0.01f, z);
        }

        for (float z = b; z >= zLimit; z -= 0.5f){
            float x = a * sqrt(1.0f - (z * z) / (b * b));
            glVertex3f(-x, 0.01f, z);
        }

        int segments = 30;
        for (int i = 0; i <= segments; ++i){
            float theta = 3.14159f * i / segments;
            float x = -x_edge * cos(theta);
            float z = zLimit - curveDepth * sin(theta);
            glVertex3f(x, 0.01f, z);
        }
    }
    else
    {
        for (float z = -b; z <= zLimit; z += 0.5f){
            float x = a * sqrt(1.0f - (z * z) / (b * b));
            glVertex3f(x, 0.01f, z);
        }

        for (float z = zLimit; z >= -b; z -= 0.5f){
            float x = a * sqrt(1.0f - (z * z) / (b * b));
            glVertex3f(-x, 0.01f, z);
        }

        int segments = 30;
        for (int i = 0; i <= segments; ++i){
            float theta = 3.14159f * i / segments;
            float x = -x_edge * cos(theta);
            float z = zLimit + curveDepth * sin(theta);
            glVertex3f(x, 0.01f, z);
        }
    }

    glEnd();
}
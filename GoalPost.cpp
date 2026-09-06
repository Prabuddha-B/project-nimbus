#include<windows.h>
#include<glut.h>
#include <cmath>
#include "GoalPost.h"
#include "Texture.h"

// Draws one goal hoop
void drawGoalPost(float x, float z, float height, float radius){
    glPushMatrix();

	glEnable(GL_TEXTURE_2D);

    
    glTranslatef(x, 0.0f, z);

    GLUquadric* quad = gluNewQuadric();

    gluQuadricTexture(quad, GL_TRUE);
    gluQuadricNormals(quad, GLU_SMOOTH);

    GLfloat specular[] =
    {
        1.0f,1.0f,1.0f,1.0f
    };

    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf( GL_FRONT, GL_SHININESS, 80.0f);

  
    // Pole
    glBindTexture(GL_TEXTURE_2D, metalTexture);

    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();

    glRotatef(-90.0f, 1, 0, 0);
    gluCylinder(quad, 0.25, 0.25, height, 20, 20);

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);

    
    // Base
    glBindTexture(GL_TEXTURE_2D, metalTexture);

    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();

    glRotatef(-90.0f, 1, 0, 0);
    gluDisk(quad, 0.0, 0.5, 20, 1);

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);

    
    // Hoop
    glPushMatrix();

 
    glTranslatef(0.0f, height + radius, 0.0f);
    glColor3f( 1.0f, 0.85f, 0.0f);
    glutWireTorus(0.08, radius, 30, 60);

    glPopMatrix();

    gluDeleteQuadric(quad);

	glDisable(GL_TEXTURE_2D);

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

    // Adjust this to make the sand grains larger or smaller
    const float texScale = 5.0f;

	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, sandTexture);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POLYGON);

    glNormal3f(0.0f, 1.0f, 0.0f);

    float x_edge = a * sqrt(1.0f - (zLimit * zLimit) / (b * b));

    if (topSide)
    {
        for (float z = zLimit; z <= b; z += 0.5f) {
            float x = a * sqrt(1.0f - (z * z) / (b * b));
            glTexCoord2f(x / texScale, z / texScale);
            glVertex3f(x, 0.01f, z);
        }

        for (float z = b; z >= zLimit; z -= 0.5f) {
            float x = a * sqrt(1.0f - (z * z) / (b * b));
            glTexCoord2f(-x / texScale, z / texScale);
            glVertex3f(-x, 0.01f, z);
        }

        int segments = 30;
        for (int i = 0; i <= segments; ++i) {
            float theta = 3.14159f * i / segments;
            float x = -x_edge * cos(theta);
            float z = zLimit - curveDepth * sin(theta);

            glTexCoord2f(x / texScale, z / texScale);
            glVertex3f(x, 0.01f, z);
        }
    }
    else
    {
        for (float z = -b; z <= zLimit; z += 0.5f) {
            float x = a * sqrt(1.0f - (z * z) / (b * b));
            glTexCoord2f(x / texScale, z / texScale);
            glVertex3f(x, 0.01f, z);
        }

        for (float z = zLimit; z >= -b; z -= 0.5f) {
            float x = a * sqrt(1.0f - (z * z) / (b * b));
            glTexCoord2f(-x / texScale, z / texScale);
            glVertex3f(-x, 0.01f, z);
        }

        int segments = 30;
        for (int i = 0; i <= segments; ++i) {
            float theta = 3.14159f * i / segments;
            float x = -x_edge * cos(theta);
            float z = zLimit + curveDepth * sin(theta);

            glTexCoord2f(x / texScale, z / texScale);
            glVertex3f(x, 0.01f, z);
        }
    }

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}
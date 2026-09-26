#include <windows.h>
#include <glut.h>

#include "Sky.h"
#include "Texture.h"
#include "Camera.h"
#include "Controls.h"

void drawSkydome() {
    glPushMatrix();

    // Center the sphere 
    glTranslatef(camX, camY, camZ);

    // Stand the sphere upright
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);

    glDepthMask(GL_FALSE);
    glDisable(GL_LIGHTING);

    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);

    if (lightingEnabled) {
        glBindTexture(GL_TEXTURE_2D, nightSkyTexture);
    }
    else {
        glBindTexture(GL_TEXTURE_2D, daySkyTexture);
    }

    // Switch to the Texture Matrix to manipulate image coordinates
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();

    glTranslatef(0.0f, -0.35f, 0.0f);

    glMatrixMode(GL_MODELVIEW);
    

    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluQuadricOrientation(quad, GLU_INSIDE);

    gluSphere(quad, 900.0f, 120, 120);

    gluDeleteQuadric(quad);

    // Clean up the Texture Matrix shift 
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    if (lightingEnabled) {
        glEnable(GL_LIGHTING);
    }

    glDepthMask(GL_TRUE);

    glPopMatrix();
}
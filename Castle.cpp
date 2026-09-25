#include <windows.h>
#include <glut.h>
#include <cmath>

#include "Castle.h"
#include "Texture.h"
#include "Camera.h"
#include "Controls.h"

void drawCastle() {

    // Position the castle far off in the background
    float castleX = -300.0f;
    float castleY = -20.0f;
    float castleZ = -400.0f;

    // BILLBOARDING MATH: Calculate the angle to the camera
    float dx = camX - castleX;
    float dz = camZ - castleZ;

    // atan2 returns radians, multiply by 180/PI to get degrees for glRotatef
    float angle = atan2(dx, dz) * 180.0f / 3.14159265f;

    glPushMatrix();

    glTranslatef(castleX, castleY, castleZ);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    // TRANSPARENCY: Enable alpha blending for the image cutout
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, castleTexture);

    // Disable lighting temporarily so the castle renders like a crisp painted backdrop
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);

    float width = 350.0f;
    float height = 200.0f;

    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);

    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width / 2.0f, 0.0f, 0.0f); // Bottom-Left
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width / 2.0f, 0.0f, 0.0f);  // Bottom-Right
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width / 2.0f, height, 0.0f); // Top-Right
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2.0f, height, 0.0f); // Top-Left

    glEnd();

    // Cleanup states
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    if (lightingEnabled) {
        glEnable(GL_LIGHTING);
    }

    glPopMatrix();
}
#include <windows.h>
#include <glut.h>
#include <cmath>
#include <cstdlib> 

#include "Snitch.h"
#include "Game.h"

extern bool lightingEnabled;

// The current target waypoint the Snitch is flying towards
float targetX = 0.0f;
float targetZ = 0.0f;

// Remember the angle 
static float currentSnitchAngle = 0.0f;


// Update the Snitch's AI behavior
void updateSnitchAI() {
    if (gameState != 1) return;

    float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

    float dx = targetX - snitchX;
    float dz = targetZ - snitchZ;
    float distToTarget = sqrt(dx * dx + dz * dz);

    
    if (distToTarget < 5.0f || (rand() % 1000) < 3) {
        do {
            targetX = ((rand() % 600) / 10.0f) - 30.0f;
            targetZ = ((rand() % 1200) / 10.0f) - 60.0f;
        } while (!isInsidePitch(targetX, targetZ));
    }

    //  Normalized forward direction
    float dirX = dx / distToTarget;
    float dirZ = dz / distToTarget;

    //  Perpendicular direction for weaving
    float perpX = -dirZ;
    float perpZ = dirX;

    //  BALANCED Player Evasion
    float evadeX = 0.0f;
    float evadeZ = 0.0f;

    float pdx = snitchX - playerX;
    float pdz = snitchZ - playerZ;
    float distToPlayer = sqrt(pdx * pdx + pdz * pdz);

    // Only evade if player is within 15 units (was 25)
    if (distToPlayer < 15.0f && distToPlayer > 0.1f) {
        float evadeStrength = (15.0f - distToPlayer) / 15.0f;

        // Pushes away gently (0.6f) instead of aggressively (1.5f)
        evadeX = (pdx / distToPlayer) * evadeStrength * 0.6f;
        evadeZ = (pdz / distToPlayer) * evadeStrength * 0.6f;
    }

    // BALANCED Speed & Weaving
    float speed = 0.25f + (sin(time * 5.0f) * 0.1f) + (cos(time * 3.1f) * 0.05f);

    // softer weaving 
    float weave = sin(time * 8.0f) * 0.15f + cos(time * 4.3f) * 0.08f;

    // Combine Target Seeking + Weaving + Player Evasion
    float moveX = (dirX * speed) + (perpX * weave) + evadeX;
    float moveZ = (dirZ * speed) + (perpZ * weave) + evadeZ;

    // Boundary Protection
    float nextX = snitchX + moveX;
    float nextZ = snitchZ + moveZ;

    if (isInsidePitch(nextX, nextZ)) {
        snitchX = nextX;
        snitchZ = nextZ;
    }
    else {
        targetX = ((rand() % 600) / 10.0f) - 30.0f;
        targetZ = ((rand() % 1200) / 10.0f) - 60.0f;
    }
}


// Draw the Golden Snitch with its AI behavior
void drawGoldenSnitch() {
    float oldX = snitchX;
    float oldZ = snitchZ;

    // Run the AI to update its position
    updateSnitchAI();

    float moveX = snitchX - oldX;
    float moveZ = snitchZ - oldZ;

    if (abs(moveX) > 0.0001f || abs(moveZ) > 0.0001f) {
        currentSnitchAngle = atan2(moveX, moveZ) * 180.0f / 3.14159f;
    }

    glPushMatrix();

    glTranslatef(snitchX, 3.5f, snitchZ);
    glRotatef(currentSnitchAngle, 0.0f, 1.0f, 0.0f);

    float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    glRotatef(sin(time * 15.0f) * 15.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(cos(time * 20.0f) * 15.0f, 0.0f, 0.0f, 1.0f);

    glDisable(GL_TEXTURE_2D);

    //  THE GOLD BODY
    if (lightingEnabled) {
        GLfloat goldAmbient[] = { 0.24725f, 0.1995f, 0.0745f, 1.0f };
        GLfloat goldDiffuse[] = { 0.75164f, 0.60648f, 0.22648f, 1.0f };
        GLfloat goldSpecular[] = { 0.62828f, 0.5558f, 0.366065f, 1.0f };
        glMaterialfv(GL_FRONT, GL_AMBIENT, goldAmbient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, goldDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, goldSpecular);
        glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);
    }
    glColor3f(1.0f, 0.84f, 0.0f);
    glutSolidSphere(0.4f, 16, 16);

    //  THE SILVER WINGS
    float wingAngle = sin(time * 100.0f) * 45.0f;

    if (lightingEnabled) {
        GLfloat silver[] = { 0.8f, 0.8f, 0.8f, 1.0f };
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, silver);
        GLfloat lowSpecular[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        glMaterialfv(GL_FRONT, GL_SPECULAR, lowSpecular);
    }
    glColor3f(0.9f, 0.9f, 0.9f);

    // Left Wing
    glPushMatrix();
    glTranslatef(-0.3f, 0.0f, 0.0f);
    glRotatef(-wingAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.8f, 0.0f, 0.0f);
    glScalef(1.5f, 0.05f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Right Wing
    glPushMatrix();
    glTranslatef(0.3f, 0.0f, 0.0f);
    glRotatef(wingAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.8f, 0.0f, 0.0f);
    glScalef(1.5f, 0.05f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();

    //  CLEANUP MATERIALS
    if (lightingEnabled) {
        GLfloat defaultAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        GLfloat defaultDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
        GLfloat defaultSpecular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_AMBIENT, defaultAmbient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, defaultDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, defaultSpecular);
        glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    glPopMatrix();
}
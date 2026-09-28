#include <windows.h>
#include <glut.h>
#include <cmath>

#include "Player.h"
#include "Game.h"
#include "Texture.h"

extern bool lightingEnabled;

void drawPlayer() {
    glPushMatrix();

    // Position the player in the world
    glTranslatef(playerX, 3.5f, playerZ);

    // Rotate to face the driving direction
    glRotatef(playerAngle, 0.0f, 1.0f, 0.0f);

    GLUquadric* quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluQuadricTexture(quad, GL_TRUE);

    // -----------------------------------------------------
    //  THE BROOMSTICK 
    // -----------------------------------------------------
    glEnable(GL_TEXTURE_2D);
    glColor3f(0.8f, 0.8f, 0.8f);

    glPushMatrix();
 
    glTranslatef(0.0f, -1.0f, -3.0f);

    // Main Handle (Wood)
    glBindTexture(GL_TEXTURE_2D, woodTexture);
    gluCylinder(quad, 0.15f, 0.15f, 6.0f, 12, 1);

    // Tail Bristles 
    glBindTexture(GL_TEXTURE_2D, bristlesTexture);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 6.0f); 

   
    gluCylinder(quad, 0.15f, 0.7f, 3.5f, 16, 1);

    // Cap the back of the twigs 
    glTranslatef(0.0f, 0.0f, 3.5f);
    gluDisk(quad, 0.0f, 0.7f, 16, 1);
    glPopMatrix();

    glPopMatrix();


    // -----------------------------------------------------
    // THE BODY 
    // -----------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, bodyTexture);

    if (lightingEnabled) {
        GLfloat matte[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_SPECULAR, matte);
        glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);
    }

    glColor3f(0.9f, 0.9f, 0.9f);

    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f); 
    glScalef(1.4f, 2.5f, 1.0f);     

    
    glBegin(GL_QUADS);

    // Front Face
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // Back Face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);

    // Top Face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);

    // Bottom Face
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);

    // Right Face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);

    // Left Face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    glEnd();
    glPopMatrix();


    // -----------------------------------------------------
    //  THE CAPE 
    // -----------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, capeTexture);

    glPushMatrix();
    glTranslatef(0.0f, 2.0f, 0.5f); 

    float time = glutGet(GLUT_ELAPSED_TIME) * 0.005f;
    int segments = 100;
    float capeLength = 2.5f;

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; i++) {
        float t = (float)i / segments;
        float y = -t * capeLength; 

        // Math for the wave
        float wave =
            sin(time * 3.0f + t * 4.0f) * 0.15f +
            sin(time * 5.5f + t * 9.0f) * 0.06f +
            sin(time * 8.0f + t * 15.0f) * 0.03f;

        wave *= t;

       
        float slant = t * 4.5f;

        float z = slant + wave;
        float width = 1.0f + (t * 0.8f); 

        glNormal3f(0.0f, 0.5f, 1.0f);
        glTexCoord2f(1.0f, t); glVertex3f(width, y, z); 
        glTexCoord2f(0.0f, t); glVertex3f(-width, y, z); 
    }
    glEnd();
    glPopMatrix();


    // -----------------------------------------------------
    //  THE ARMS 
    // -----------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, handsTexture);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Left Arm
    glPushMatrix();
    glTranslatef(-0.8f, 1.8f, 0.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad, 0.25f, 0.2f, 3.2f, 10, 1);
    glPopMatrix();

    // Right Arm
    glPushMatrix();
    glTranslatef(0.8f, 1.8f, 0.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(15.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad, 0.25f, 0.2f, 3.2f, 10, 1);
    glPopMatrix();


    // -----------------------------------------------------
    //  THE LEGS 
    // -----------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, legsTexture);

    // Left Leg
    glPushMatrix();
    glTranslatef(-0.4f, 0.0f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad, 0.25f, 0.2f, 2.0f, 10, 1);
    glPopMatrix();

    // Right Leg
    glPushMatrix();
    glTranslatef(0.4f, 0.0f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(15.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quad, 0.25f, 0.2f, 2.0f, 10, 1);
    glPopMatrix();


    // -----------------------------------------------------
    //  THE HEAD 
    // -----------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, headTexture);

    glPushMatrix();
    glTranslatef(0.0f, 2.8f, 0.2f);

    // Rotate
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);

    gluSphere(quad, 0.7f, 16, 16);
    glPopMatrix();


    // -----------------------------------------------------
    // CLEANUP
    // -----------------------------------------------------
    gluDeleteQuadric(quad);

    if (lightingEnabled) {
        // THE FIX: Turn off the massive specular glare and reset shininess
        GLfloat defaultSpecular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_SPECULAR, defaultSpecular);
        glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    glPopMatrix();
}
 
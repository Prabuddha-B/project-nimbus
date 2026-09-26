#include <windows.h>
#include <glut.h>
#include <cmath>

#include "FlyingCar.h"
#include "Texture.h"

extern bool lightingEnabled;

// Helper function to draw a 3D box 
void drawTexturedBox(float w, float h, float d) {
    glBegin(GL_QUADS);

    // Front Face
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-w / 2, -h / 2, d / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(w / 2, -h / 2, d / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(w / 2, h / 2, d / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-w / 2, h / 2, d / 2);

    // Back Face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-w / 2, -h / 2, -d / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-w / 2, h / 2, -d / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(w / 2, h / 2, -d / 2);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(w / 2, -h / 2, -d / 2);

    // Top Face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-w / 2, h / 2, -d / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-w / 2, h / 2, d / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(w / 2, h / 2, d / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(w / 2, h / 2, -d / 2);

    // Bottom Face
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-w / 2, -h / 2, -d / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(w / 2, -h / 2, -d / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(w / 2, -h / 2, d / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-w / 2, -h / 2, d / 2);

    // Right Face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(w / 2, -h / 2, -d / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(w / 2, h / 2, -d / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(w / 2, h / 2, d / 2);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(w / 2, -h / 2, d / 2);

    // Left Face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-w / 2, -h / 2, -d / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-w / 2, -h / 2, d / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-w / 2, h / 2, d / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-w / 2, h / 2, -d / 2);
    glEnd();
}

void buildCarModel() {

    // Lower Chassis
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, carBodyTexture);
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    drawTexturedBox(4.0f, 1.5f, 9.0f);
    glPopMatrix();

    // Upper Cabin 
    glBindTexture(GL_TEXTURE_2D, carWindowTexture);
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, -0.5f);
    drawTexturedBox(3.5f, 1.5f, 4.5f);
    glPopMatrix();

    // Four Textured Wheels with Hubcaps
    glEnable(GL_TEXTURE_2D);
    GLUquadric* quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluQuadricTexture(quad, GL_TRUE); 

    float wheelX = 2.2f;
    float wheelZ = 2.5f;
    float wheelY = -0.5f;

    float positions[4][2] = { {wheelX, wheelZ}, {-wheelX, wheelZ}, {wheelX, -wheelZ}, {-wheelX, -wheelZ} };

    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(positions[i][0], wheelY, positions[i][1]);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f); 
        glTranslatef(0.0f, 0.0f, -0.4f);    

        // Draw the Tread 
        glBindTexture(GL_TEXTURE_2D, metalTexture);
        glColor3f(0.15f, 0.15f, 0.15f); // Dark rubber color
        gluCylinder(quad, 1.0f, 1.0f, 0.8f, 16, 1);

        // Draw the Hubcap Faces 
        glBindTexture(GL_TEXTURE_2D, carTireTexture);
        glColor3f(1.0f, 1.0f, 1.0f); // Reset to pure white so the chrome shines

        // Outer Face
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.8f); 
        gluDisk(quad, 0.0f, 1.0f, 16, 1);
        glPopMatrix();

        // Inner Face
        glPushMatrix();
        glRotatef(180.0f, 1.0f, 0.0f, 0.0f); 
        gluDisk(quad, 0.0f, 1.0f, 16, 1);
        glPopMatrix();

        glPopMatrix();
    }

    // Glowing Headlights & Flipped Beams
    glDisable(GL_TEXTURE_2D); 

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 4.6f);

    if (lightingEnabled) {
        GLfloat emission[] = { 1.0f, 1.0f, 0.8f, 1.0f };
        glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    }

    glColor3f(1.0f, 1.0f, 0.9f);

    glPushMatrix(); glTranslatef(-1.2f, 0.0f, 0.0f); glutSolidSphere(0.4, 12, 12); glPopMatrix();
    glPushMatrix(); glTranslatef(1.2f, 0.0f, 0.0f); glutSolidSphere(0.4, 12, 12); glPopMatrix();

    if (lightingEnabled) {
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glColor4f(1.0f, 1.0f, 0.7f, 0.25f);

        // Left Beam 
        glPushMatrix();
        glTranslatef(-1.2f, 0.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, 18.0f);     
        glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
        glutSolidCone(3.5, 18.0, 16, 4);     
        glPopMatrix();

        // Right Beam 
        glPushMatrix();
        glTranslatef(1.2f, 0.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, 18.0f);
        glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
        glutSolidCone(3.5, 18.0, 16, 4);
        glPopMatrix();

        glDisable(GL_BLEND);
        glEnable(GL_LIGHTING);

        GLfloat no_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
    }

    glPopMatrix();
    gluDeleteQuadric(quad);
    glColor3f(1.0f, 1.0f, 1.0f);
}

void drawFlyingCar() {

    // Only appear in Night Mode
    if (!lightingEnabled) {
        return;
    }

    float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float speed = 0.25f; 
    float t = time * speed;

    // Elliptical Orbit parameters
    float radiusX = 250.0f;
    float radiusZ = 160.0f;

    float x = radiusX * cos(t);
    float z = radiusZ * sin(t);
    float y = 38.0f + sin(time * 1.5f) * 7.0f; // Bouncy flight path

    float dx = -radiusX * sin(t);
    float dz = radiusZ * cos(t);
    float angle = atan2(dx, dz) * 180.0f / 3.14159f;

    glPushMatrix();
    glTranslatef(x, y, z);

   
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glRotatef(sin(time * 3.0f) * 10.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(cos(time * 2.0f) * 15.0f, 0.0f, 0.0f, 1.0f);

    // Massive scale multiplier
    glScalef(2.5f, 2.5f, 2.5f);

    buildCarModel();

    glPopMatrix();
}
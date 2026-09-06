#include <windows.h>
#include <glut.h>
#include <cmath>

#include "SpectatorStand.h"
#include "Texture.h"


const float STAND_INNER_X = 36.0f;
const float STAND_INNER_Z = 66.0f;

const float STAND_OUTER_X = 42.0f;
const float STAND_OUTER_Z = 72.0f;

const float STAND_HEIGHT = 10.0f;

const float PITCH_LENGTH = 120.0f;
const float PITCH_WIDTH = 60.0f;

// Draw Outer Wooden Wall
void drawOuterWall()
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, woodTexture);

    glColor3f(1.0f, 1.0f, 1.0f);

    int segments = 120;

    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i <= segments; i++){
        float theta = 2.0f * 3.14159f * i / segments;

        float x = STAND_OUTER_X * cos(theta);

        float z = STAND_OUTER_Z * sin(theta);

        float u = (float)i / segments * 8.0f;

        glNormal3f(cos(theta), 0, sin(theta));

        glTexCoord2f(u, 0.0f);
        glVertex3f(x, 0, z);

        glTexCoord2f(u, 1.0f);
        glVertex3f( x, STAND_HEIGHT, z);
    }

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);
}


// Draw Inner Banner Wall
void drawInnerWall(){
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, bannerTexture);

    glColor3f(1.0f, 1.0f, 1.0f);

    float bannerRepeats = 20.0f;

    glBegin(GL_QUAD_STRIP);

    for (float deg = 0.0f; deg <= 360.0f; deg += 2.0f){

        float theta = deg * 3.14159f / 180.0f;

        float x = STAND_INNER_X * cos(theta);

        float z = STAND_INNER_Z * sin(theta);

        float u = (deg / 360.0f) * bannerRepeats;

        glNormal3f(-cos(theta), 0.0f, -sin(theta));

        glTexCoord2f(u, 1.0f);
        glVertex3f(x, 0.0f, z);

        glTexCoord2f(u, 0.0f);
        glVertex3f(x, 3.0f, z);
    }

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);
}


// Draw Wooden Support Stakes
void drawWoodenDeck(){

    int planks = 160;

    for (int i = 0; i < planks; i++){
        float theta = 2.0f * 3.14159f * i / planks;

        float innerX = (PITCH_WIDTH / 2.0f + 1.0f) * cos(theta);

        float innerZ = (PITCH_LENGTH / 2.0f + 1.0f) * sin(theta);

        float outerX = STAND_INNER_X * cos(theta);

        float outerZ = STAND_INNER_Z * sin(theta);

        float dx = outerX - innerX;
        float dz = outerZ - innerZ;

        float length = sqrt(dx * dx + dz * dz);

        float angle = atan2(dz, dx) * 180.0f / 3.14159f;

        glPushMatrix();

        glTranslatef( (innerX + outerX) * 0.5f, 0.2f, (innerZ + outerZ) * 0.5f );

        glRotatef(-angle, 0,  1, 0);

        glColor3f( 0.45f, 0.28f, 0.12f);

        glScalef(length, 0.2f, 0.5f);

        glutSolidCube(1);

        glPopMatrix();
    }
}


// Draw stepped seating tiers
void drawSeatingTiers(){

    const int tiers = 8;

    float innerWallHeight = 3.0f;

    float seatDepthX = (STAND_OUTER_X - STAND_INNER_X) / tiers;

    float seatDepthZ = (STAND_OUTER_Z - STAND_INNER_Z) / tiers;

    float heightStep = 0.5f;

    for (int tier = 0; tier < tiers; tier++){

        float innerRadiusX = STAND_INNER_X + tier * seatDepthX;

        float innerRadiusZ = STAND_INNER_Z + tier * seatDepthZ;

        float outerRadiusX = innerRadiusX + seatDepthX;

        float outerRadiusZ = innerRadiusZ + seatDepthZ;

        float y = innerWallHeight + tier * heightStep;

        
        //  Textured Seat Platform
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, seatTexture);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

        glColor3f(1.0f, 1.0f, 1.0f);

        glBegin(GL_QUAD_STRIP);

        glNormal3f(0.0f, 1.0f, 0.0f);

        for (float deg = 0.0f; deg <= 360.0f; deg += 2.0f){

            float theta = deg * 3.14159f / 180.0f;

            float u = deg / 20.0f;

            float v0 = (float)tier;

            float v1 = (float)tier + 1.0f;

            glTexCoord2f(u, v0);

            glVertex3f(innerRadiusX * cos(theta), y, innerRadiusZ * sin(theta));

            glTexCoord2f(u, v1);

            glVertex3f( outerRadiusX * cos(theta), y, outerRadiusZ * sin(theta));
        }

        glEnd();

        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);

        
        // Untextuerd Vertical Riser
        

        glColor3f(0.35f, 0.22f, 0.10f);

        glBegin(GL_QUAD_STRIP);

        for (float deg = 0.0f; deg <= 360.0f; deg += 2.0f){

            float theta = deg * 3.14159f / 180.0f;

            float x = outerRadiusX * cos(theta);

            float z = outerRadiusZ * sin(theta);

            glNormal3f(cos(theta), 0.0f, sin(theta));

            glVertex3f(x, y, z);

            glVertex3f(x, y + heightStep, z);
        }

        glEnd();
    }
}


// Draw Main Stand 
void drawSpectatorStand()
{
    drawWoodenDeck();

    drawInnerWall();

    drawSeatingTiers();

    drawOuterWall();
}
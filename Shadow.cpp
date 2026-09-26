#include <windows.h>
#include <glut.h>
#include <cmath>

#include "Shadow.h"
#include "Camera.h"


// Draws a complete goal post shadow (pole + hoop)
void drawShadowGoalPost(float x, float z, float height){

    // Calculate hoop shadow position
    float hoopHeight = height + (height / 8.0f);

    float shadowScale = 0.4f;

    float hoopShadowX = x - (sunX * hoopHeight / sunY) * shadowScale;

    float hoopShadowZ = z - (sunZ * hoopHeight / sunY) * shadowScale;

    // Hoop radius
    float hoopRadius = height / 8.0f;

    // Direction from pole base to hoop shadow
    float dx = hoopShadowX - x;
    float dz = hoopShadowZ - z;

    // Length : Distance Formula
    float len = sqrt(dx * dx + dz * dz);

	// Normalize direction vector
    if (len > 0.0f){
        dx /= len;
        dz /= len;
    }

    // Connect line to edge of hoop shadow instead of center
    float connectionX = hoopShadowX - dx * hoopRadius;

    float connectionZ = hoopShadowZ - dz * hoopRadius;

    // Pole Shadow
   
    glLineWidth(4.0f);

    glBegin(GL_LINES);

    glVertex3f( x, 0.05f, z);

    glVertex3f( connectionX, 0.05f, connectionZ);

    glEnd();

    
    // Hoop Shadow
    glPushMatrix();

    glTranslatef(hoopShadowX, 0.05f, hoopShadowZ);

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 40; i++){

        float theta = 2.0f * 3.14159f * i / 40;

        glVertex3f( hoopRadius * cos(theta), 0.0f, hoopRadius * sin(theta));
    }

    glEnd();

    glPopMatrix();
}


// Draws all projected goal post shadows
void drawGoalPostShadows(){

    // No shadows when the sun is below the ground
    if (sunY <= 0.0f){
        return;
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);  // Enable Transparency

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f( 0.0f, 0.0f, 0.0f, 0.35f); // Black 35% Opacity Shadow

    drawShadowGoalPost(-10.0f, -50.0f, 12.0f);
    drawShadowGoalPost(0.0f, -50.0f, 16.0f);
    drawShadowGoalPost(10.0f, -50.0f, 8.0f);

    drawShadowGoalPost(-10.0f, 50.0f, 8.0f);
    drawShadowGoalPost(0.0f, 50.0f, 16.0f);
    drawShadowGoalPost(10.0f, 50.0f, 12.0f);

    glDisable(GL_BLEND);

    glEnable(GL_LIGHTING);
}


// Draws the shadow of the inner wall
void drawOuterWallShadow(){

    if (sunY <= 0.0f)
        return;

    // Wall Shape Dimensions
    const float OUTER_X = 42.0f;
    const float OUTER_Z = 72.0f;
    const float HEIGHT = 10.0f;

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_BLEND);

    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f( 0.0f, 0.0f, 0.0f, 0.25f);

    glBegin(GL_QUAD_STRIP);

    for (int angle = 0; angle <= 360; angle++){

        float theta = angle * 3.1415926f / 180.0f;

        float x = OUTER_X * cos(theta);
        float z = OUTER_Z * sin(theta);

        float shadowX = x - (sunX * HEIGHT / sunY);

        float shadowZ = z - (sunZ * HEIGHT / sunY);

        glVertex3f(x, 0.02f, z);

        glVertex3f( shadowX, 0.02f, shadowZ);
    }

    glEnd();

    glDisable(GL_BLEND);

    glEnable(GL_LIGHTING);
}


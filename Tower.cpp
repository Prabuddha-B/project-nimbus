#include <windows.h>
#include <glut.h>
#include <cmath>
#include "Tower.h"
#include "Texture.h"
#include "Controls.h"

float towerRotation = 0.0f;

// Draws the textured shaft of the tower
void drawTexturedShaft() {

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, gryffindorTexture);

    float w = 4.0f;
    float h = 16.0f;
    float d = 4.0f;

    glBegin(GL_QUADS);

    // FRONT
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-w, -h, d);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(w, -h, d);
    glTexCoord2f(1.0f, 4.0f); glVertex3f(w, h, d);
    glTexCoord2f(0.0f, 4.0f); glVertex3f(-w, h, d);

    // BACK
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(w, -h, -d);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-w, -h, -d);
    glTexCoord2f(1.0f, 4.0f); glVertex3f(-w, h, -d);
    glTexCoord2f(0.0f, 4.0f); glVertex3f(w, h, -d);

    // LEFT
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-w, -h, -d);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-w, -h, d);
    glTexCoord2f(1.0f, 4.0f); glVertex3f(-w, h, d);
    glTexCoord2f(0.0f, 4.0f); glVertex3f(-w, h, -d);

    // RIGHT
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(w, -h, d);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(w, -h, -d);
    glTexCoord2f(1.0f, 4.0f); glVertex3f(w, h, -d);
    glTexCoord2f(0.0f, 4.0f); glVertex3f(w, h, d);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);
}


// Draws hourglass viewing deck with open front
void drawHourglassDeck() {

    float w1 = 4.0f;        // Bottom Width
	float w2 = 2.0f;        // Middle Width
	float w3 = 5.2f;        // Top Width
    float h1 = 6.0f;        // Lower Height
	float h2 = 8.0f;        // Upper Height

    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gryffindorDeckTexture);

    glColor3f(1.0f, 1.0f, 1.0f); // Pure White Wash

    glBegin(GL_QUADS);


    // ---------------------- LOWER SECTION ------------------------
    
    // Back Face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); 
    glVertex3f(w1, 0.0f, -w1);
    glTexCoord2f(1.0f, 0.0f); 
    glVertex3f(-w1, 0.0f, -w1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-w2, h1, -w2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(w2, h1, -w2);

    // Left Face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-w1, 0.0f, -w1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-w1, 0.0f, w1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-w2, h1, w2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-w2, h1, -w2);

    // Right Face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); 
    glVertex3f(w1, 0.0f, w1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(w1, 0.0f, -w1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(w2, h1, -w2);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(w2, h1, w2);

    glEnd();

    glBegin(GL_QUADS);
    // ------------------------ UPPER SECTION ---------------------------------
    
    // Back Face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(w2, h1, -w2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-w2, h1, -w2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-w3, h1 + h2, -w3);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(w3, h1 + h2, -w3);

    // Left Face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-w2, h1, -w2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-w2, h1, w2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-w3, h1 + h2, w3);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-w3, h1 + h2, -w3);

    // Right Face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(w2, h1, w2);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(w2, h1, -w2);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(w3, h1 + h2, -w3);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(w3, h1 + h2, w3);
    glEnd();

    // Disable Texturing before drawing the wood
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    // ------------------------- DRAW WOODEN SUPPORT FRAME -----------------------------
    glColor3f(0.35f, 0.25f, 0.10f);
    glLineWidth(4.0f);

    glBegin(GL_LINES);

    // Lower angled corner posts
    glVertex3f(-w1, 0.0f, w1);  
    glVertex3f(-w2, h1, w2);
    glVertex3f(w1, 0.0f, w1);  
    glVertex3f(w2, h1, w2);
    glVertex3f(-w1, 0.0f, -w1);
    glVertex3f(-w2, h1, -w2);
    glVertex3f(w1, 0.0f, -w1); 
    glVertex3f(w2, h1, -w2);

    // Upper angled corner posts
    glVertex3f(-w2, h1, w2);  
    glVertex3f(-w3, h1 + h2, w3);
    glVertex3f(w2, h1, w2);    
    glVertex3f(w3, h1 + h2, w3);
    glVertex3f(-w2, h1, -w2);  
    glVertex3f(-w3, h1 + h2, -w3);
    glVertex3f(w2, h1, -w2);  
    glVertex3f(w3, h1 + h2, -w3);

    // Waist horizontal frame
    glVertex3f(-w2, h1, w2); 
    glVertex3f(w2, h1, w2);
    glVertex3f(w2, h1, w2);  
    glVertex3f(w2, h1, -w2);
    glVertex3f(w2, h1, -w2); 
    glVertex3f(-w2, h1, -w2);
    glVertex3f(-w2, h1, -w2);
    glVertex3f(-w2, h1, w2);

    // Top horizontal frame
    glVertex3f(-w3, h1 + h2, w3); 
    glVertex3f(w3, h1 + h2, w3);
    glVertex3f(w3, h1 + h2, w3); 
    glVertex3f(w3, h1 + h2, -w3);
    glVertex3f(w3, h1 + h2, -w3); 
    glVertex3f(-w3, h1 + h2, -w3);
    glVertex3f(-w3, h1 + h2, -w3);
    glVertex3f(-w3, h1 + h2, w3);
    glEnd();

    glLineWidth(1.0f);

    // ---------------------------  DRAW SOLID WOODEN FLOOR ----------------------
    
    glColor3f(0.25f, 0.15f, 0.05f); 

    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-w1, 0.02f, w1);
    glVertex3f(w1, 0.02f, w1);
    glVertex3f(w1, 0.02f, -w1);
    glVertex3f(-w1, 0.02f, -w1);
    glEnd();

    
    // ---------------------------  TOWER LIGHT SYSTEM ----------------------
  

    if (isTowerLightOn) {
        glEnable(GL_LIGHT1);

        GLfloat lightPos[] = { 0.0f, h1 + (h2 * 0.5f), w3 + 3.0f, 1.0f };
        GLfloat diffuse[] = { 1.0f, 0.8f, 0.3f, 1.0f };   // Warm Yellow Light
        GLfloat specular[] = { 1.0f, 0.9f, 0.5f, 1.0f };

        GLfloat ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };

        glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
        glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);

        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.5f);
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.01f);
        glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.001f);

        glDisable(GL_LIGHTING);

        // --- Core Bright Panel ---
        glColor3f(1.0f, 0.95f, 0.8f);
        glBegin(GL_QUADS);
        glVertex3f(-w2, h1, w2);
        glVertex3f(w2, h1, w2);
        glVertex3f(w3, h1 + h2, w3);
        glVertex3f(-w3, h1 + h2, w3);
        glEnd();

        // --- Front Halo Layer ---
		glEnable(GL_BLEND);                 // Enable blending for transparency
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        glColor4f(1.0f, 0.6f, 0.1f, 0.6f);
        glBegin(GL_QUADS);
        float g1 = 0.6f;
        glVertex3f(-w2 - g1, h1 - g1, w2 + 0.1f);
        glVertex3f(w2 + g1, h1 - g1, w2 + 0.1f);
        glVertex3f(w3 + g1, h1 + h2 + g1, w3 + 0.1f);
        glVertex3f(-w3 - g1, h1 + h2 + g1, w3 + 0.1f);
        glEnd();

        glColor4f(1.0f, 0.4f, 0.0f, 0.25f);
        glBegin(GL_QUADS);
        float g2 = 1.8f;
        glVertex3f(-w2 - g2, h1 - g2, w2 + 0.2f);
        glVertex3f(w2 + g2, h1 - g2, w2 + 0.2f);
        glVertex3f(w3 + g2, h1 + h2 + g2, w3 + 0.2f);
        glVertex3f(-w3 - g2, h1 + h2 + g2, w3 + 0.2f);
        glEnd();

        glDisable(GL_BLEND);

		// Global lighting Switch
        if (lightingEnabled) {
            glEnable(GL_LIGHTING);
        }
    }
    else {
        glDisable(GL_LIGHT1);
    }

    glColor3f(1.0f, 1.0f, 1.0f);    // Pure white wash
}


// Draws Quidditch tent roof
void drawPyramidRoof(float width, float height){

    float w = width * 0.5f;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gryffindorRoofTexture);

    // Exact color tint of the shaft 
    glColor3f(0.55f, 0.45f, 0.20f);

    glBegin(GL_TRIANGLES);

    // FRONT FACE
    glNormal3f(0.0f, 0.7f, 0.7f);
    glTexCoord2f(0.0f, 1.0f); 
    glVertex3f(-w, 0.0f, w);
    glTexCoord2f(1.0f, 1.0f); 
    glVertex3f(w, 0.0f, w);
    glTexCoord2f(0.5f, 0.5f); 
    glVertex3f(0.0f, height, 0.0f);

    // BACK FACE
    glNormal3f(0.0f, 0.7f, -0.7f);
    glTexCoord2f(0.0f, 1.0f); 
    glVertex3f(w, 0.0f, -w);
    glTexCoord2f(1.0f, 1.0f); 
    glVertex3f(-w, 0.0f, -w);
    glTexCoord2f(0.5f, 0.5f); 
    glVertex3f(0.0f, height, 0.0f);

    // LEFT FACE
    glNormal3f(-0.7f, 0.7f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-w, 0.0f, -w);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-w, 0.0f, w);
    glTexCoord2f(0.5f, 0.5f); 
    glVertex3f(0.0f, height, 0.0f);

    // RIGHT FACE
    glNormal3f(0.7f, 0.7f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(w, 0.0f, w);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(w, 0.0f, -w);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3f(0.0f, height, 0.0f);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);                // Pure White Wash to prevent color bleed onto other objects
}


// Draws an animated flag that waves in the wind
void drawAnimatedFlag(){

    float time = glutGet(GLUT_ELAPSED_TIME) * 0.005f;

    float flagWidth = 3.0f;
    float flagHeight = 1.5f;

    // Segmented for the Waving of the flag
    int segments = 50;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gryffindorFlagTexture);

    glColor3f(1.0f, 1.0f, 1.0f);

    // ---------- FRONT SIDE ----------
    glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; i++){

        float x = (flagWidth * i) / segments;

        float wave = sin(time + x * 2.5f) * 0.15f * (x / flagWidth);

        float u = (float)i / segments;

        // Bottom Vertex
        glTexCoord2f(u, 1.0f);
        glVertex3f(x, 0.0f, wave);

		// Top Vertex
        glTexCoord2f(u, 0.0f);
        glVertex3f(x, flagHeight, wave);
    }

    glEnd();


    // ---------- BACK SIDE ----------
    glNormal3f(0.0f, 0.0f, -1.0f);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; i++){
        float x = (flagWidth * i) / segments;

        float wave = sin(time + x * 2.5f) * 0.15f * (x / flagWidth);

        float u = (float)i / segments;

        glTexCoord2f(1.0f -u, 1.0f);
        glVertex3f(x, 0.0f, wave);

        glTexCoord2f(1.0f - u, 0.0f);
        glVertex3f(x, flagHeight, wave);
    }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}


// Draws the entire Quidditch tower
void drawTower() {

    glPushMatrix();

    // Tower position on the pitch
    float theta = 45.0f * 3.14159f / 180.0f;
    float towerX = 50.0f * cos(theta);
    float towerZ = 80.0f * sin(theta);
    glTranslatef(towerX, 0.0f, towerZ);   // Move Tower

    glRotatef(towerRotation, 0.0f, 1.0f, 0.0f); // Rotate around Y 


    // ----- BASE ----- 
    glPushMatrix();
    glColor3f(0.70f, 0.15f, 0.15f);
    glTranslatef(0.0f, 4.0f, 0.0f);
    glScalef(12.0f, 8.0f, 12.0f);
    glutSolidCube(1.0f);
    glPopMatrix();


    // ----- SHAFT ----- 
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, 24.0f, 0.0f);
    drawTexturedShaft();
    glPopMatrix();



    // ----- HOURGLASS VIEWING DECK -----
    glPushMatrix();
    glTranslatef(0.0f, 40.0f, 0.0f);
    drawHourglassDeck();
    glPopMatrix();


    // ----- ROOF -----
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, 54.0f, 0.0f);
    drawPyramidRoof(10.4f, 14.0f);
    glPopMatrix();


    // ----- FLAG POLE & FLAG -----

    glPushMatrix();
    glTranslatef(0.0f, 68.0f, 0.0f);

    // Pole
    glPushMatrix();
    glColor3f(0.8f, 0.8f, 0.8f);      // Metal Color
    glTranslatef(0.0f, 3.0f, 0.0f);
    glScalef(0.25f, 6.0f, 0.25f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Flag
    glPushMatrix();
    glTranslatef(0.0f, 4.5f, 0.0f);
    drawAnimatedFlag();
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();

  
    glColor3f(1.0f, 1.0f, 1.0f);    // Pure White Wash
}
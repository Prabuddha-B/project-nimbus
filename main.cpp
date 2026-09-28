#include<windows.h>
#include <glut.h>
#include <cmath>

#include "Ground.h"
#include "Camera.h"
#include "GoalPost.h"
#include "Texture.h"
#include "SpectatorStand.h"
#include "Shadow.h"
#include "Controls.h"
#include "Tower.h"
#include "Castle.h"
#include "Sky.h"
#include "Forest.h"
#include "FlyingCar.h"
#include "Game.h"
#include "Player.h"
#include "Snitch.h"


bool showAxes = false;
bool showGrid = false;
bool lightingEnabled = true;

// For Axes 
void drawAxes() {

    glDisable(GL_TEXTURE_2D);

    glLineWidth(3);

    glBegin(GL_LINES);

    // X axis - Red
    glColor3f(1, 0, 0);
    glVertex3f(-300, 0, 0);
    glVertex3f(300, 0, 0);

    // Y axis - Green
    glColor3f(0, 1, 0);
    glVertex3f(0, -300, 0);
    glVertex3f(0, 300, 0);

    // Z axis - Blue
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -300);
    glVertex3f(0, 0, 300);

    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);

    glEnable(GL_TEXTURE_2D);
}


// For Grid
void drawGrid() {
    glColor3f(0.5f, 0.5f, 0.5f);

    glBegin(GL_LINES);

    for (int i = -300; i <= 300; i += 5) {
        glVertex3f((float)i, 0.0f, -300);
        glVertex3f((float)i, 0, 300);

        glVertex3f(-300, 0.01f, (float)i);
        glVertex3f(300, 0, (float)i);
    }

    glEnd();
}


// For Lighting Functions
void setupLighting() {
    GLfloat lightPosition[] = { sunX, sunY, sunZ, 1.0f };     // Light Position

    GLfloat ambientLight[] =
    {
        0.3f, 0.3f, 0.3f, 1.0f                               // Indirect light that exists everywhere
    };

    GLfloat diffuseLight[] =
    {
        0.9f, 0.9f, 0.9f, 1.0f                              // Main illumination component
    };

    GLfloat specularLight[] =
    {
        1.0f, 1.0f, 1.0f, 1.0f                              // Shiny highlights on reflective surfaces
    };

    // Assign Light Properties
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
}


// For Sun 
void drawSun() {

    glPushMatrix();

    glTranslatef(sunX, sunY, sunZ);

    // Core Sun
    glColor3f(1.0f, 1.0f, 0.0f);
    glutSolidSphere(3.0f, 30, 30);

    // Glow Layer
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glColor4f(1.0f, 0.9f, 0.2f, 0.25f);
    glutSolidSphere(4.5f, 30, 30);

    glDisable(GL_BLEND);

    // Change color with height
    if (sunY > 80) {
        glColor3f(1.0f, 1.0f, 0.8f);
    }
    else if (sunY > 40) {
        glColor3f(1.0f, 0.9f, 0.3f);
    }
    else {
        glColor3f(1.0f, 0.5f, 0.2f);
    }

    glPopMatrix();

    //Reset color 
    glColor3f(1.0f, 1.0f, 1.0f);
}


// Helper function to draw text over the screen
void drawVictoryText() {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Set text color to Golden Yellow and make the lines bold
    glColor3f(1.0f, 0.84f, 0.0f);
    glLineWidth(6.0f);

    // --- Line 1: "150 POINTS!" ---
    glPushMatrix();
    glTranslatef(120.0f, 350.0f, 0.0f); 
    glScalef(0.5f, 0.5f, 1.0f);          
    const char* msg1 = "150 POINTS!";
    for (int i = 0; msg1[i] != '\0'; i++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, msg1[i]);
    }
    glPopMatrix();

    // --- Line 2: "YOU CAUGHT THE SNITCH!" ---
    glPushMatrix();
    glTranslatef(50.0f, 250.0f, 0.0f);  
    glScalef(0.3f, 0.3f, 1.0f);         
    const char* msg2 = "YOU CAUGHT THE SNITCH!";
    for (int i = 0; msg2[i] != '\0'; i++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, msg2[i]);
    }
    glPopMatrix();

    // Restore standard settings
    glLineWidth(1.0f);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_TEXTURE_2D);
    if (lightingEnabled) glEnable(GL_LIGHTING);
}


// Helper function to draw strings of text to the screen
void renderBitmapString(float x, float y, void* font, const char* string) {
    const char* c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}


// Function to draw the starting instructions
void drawStartScreenText() {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    // Switch to a flat 2D projection
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600); 

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Set text color to bright white 
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw the instructions in the top-left corner
    renderBitmapString(20, 560, GLUT_BITMAP_HELVETICA_18, "CONTROLS & INSTRUCTIONS:");
    renderBitmapString(20, 530, GLUT_BITMAP_HELVETICA_18, "[ ENTER ] - Start the Match");
    renderBitmapString(20, 500, GLUT_BITMAP_HELVETICA_18, "[ Z ] - Toggle Day/Night Mode");
    renderBitmapString(20, 470, GLUT_BITMAP_HELVETICA_18, "[ 1, 2, 3 ] - Change Camera Views");
    renderBitmapString(20, 440, GLUT_BITMAP_HELVETICA_18, "[ ARROWS ] - Steer / Accelerate / Brake");
    renderBitmapString(20, 410, GLUT_BITMAP_HELVETICA_18, "[ R ] - Restart Game");

    // Restore the 3D perspective camera
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_TEXTURE_2D);
    if (lightingEnabled) glEnable(GL_LIGHTING);
}


// Display Method
void display() {

    updatePlayerMovement();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // --- VICTORY CAMERA OVERRIDE ---
    if (gameState == 2) {
        float rad = playerAngle * 3.14159f / 180.0f;

       
        float frontCamX = playerX - 18.0f * sin(rad);
        float frontCamZ = playerZ - 18.0f * cos(rad);
        float frontCamY = 6.0f; 

        gluLookAt(
            frontCamX, frontCamY, frontCamZ,  // Camera positioned in front
            playerX, 3.5f, playerZ,           // Looking back at the player and Snitch
            0, 1, 0
        );
    }


    // ---------------- CAMERA LOGIC ----------------
    else if (cameraMode == 1) {

        // Prevent  going underground
        if (camY < 2.0f) {
            camY = 2.0f; 
        }

        // Mode 1: Free Roam 
        gluLookAt(
            camX, camY, camZ,
            0, 0, 0,
            0, 1, 0
        );
    }

    else if (cameraMode == 2) {

        // Mode 2: Chase Cam 
        float rad = playerAngle * 3.14159f / 180.0f;

        float chaseCamX = playerX + 30.0f * sin(rad);
        float chaseCamZ = playerZ + 30.0f * cos(rad);
        float chaseCamY = 15.0f;

        gluLookAt(
            chaseCamX, chaseCamY, chaseCamZ,  // Camera position
            playerX, 5.0f, playerZ,           // Looking exactly at the player
            0, 1, 0
        );
    }
    else if (cameraMode == 3) {
        // Mode 3: Tactical Top-Down
        gluLookAt(
            0.0f, 200.0f, 1.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f
        );
    }
   

    // Reset the global color state to pure white 
    glColor3f(1.0f, 1.0f, 1.0f);

	drawSkydome();

    if (lightingEnabled) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        setupLighting();

        // ENABLE NIGHT FOG
        glEnable(GL_FOG);
        GLfloat fogColor[] = { 0.05f, 0.1f, 0.15f, 1.0f };   // Deep midnight blue
        glFogfv(GL_FOG_COLOR, fogColor);
        glFogi(GL_FOG_MODE, GL_LINEAR);
        glFogf(GL_FOG_START, 50.0f); 
        glFogf(GL_FOG_END, 2000.0f);

    }
    else {
        glDisable(GL_LIGHTING);
        glDisable(GL_FOG);
    }

    if (showGrid) {
        drawGrid();
    }

    if (showAxes) {
        drawAxes();
    }

    glEnable(GL_TEXTURE_2D);

    if (showSun) {
        drawSun();
    }

    drawWorldGround();
    drawPerimeterMountains();
    drawPathLights();
	drawForest();
    drawFlyingCar();
	drawPlayer();
	drawGoldenSnitch();
    drawEmbankment();
    drawGround();
    drawSpectatorStand();

    // Gryffindor at 45 degrees
    drawTower(45.0f, 0.70f, 0.15f, 0.15f, gryffindorTexture, gryffindorDeckTexture, gryffindorRoofTexture, gryffindorFlagTexture, GL_LIGHT1);

    // Slytherin at 135 degrees
    drawTower(135.0f, 0.10f, 0.40f, 0.20f, slytherinTexture, slytherinDeckTexture, slytherinRoofTexture, slytherinFlagTexture, GL_LIGHT2);

    // Ravenclaw at 225 degrees
    drawTower(225.0f, 0.15f, 0.30f, 0.60f, ravenclawTexture, ravenclawDeckTexture, ravenclawRoofTexture, ravenclawFlagTexture, GL_LIGHT3);

    // Hufflepuff at 315 degrees
    drawTower(315.0f, 0.80f, 0.65f, 0.15f, hufflepuffTexture, hufflepuffDeckTexture, hufflepuffRoofTexture, hufflepuffFlagTexture, GL_LIGHT4);

    drawGoalArea(-42.0f, false);
    drawGoalArea(42.0f, true);

    drawPitchBoundary();
    drawCenterLine();
    drawCenterCircle();

    drawOuterWallShadow();
    drawGoalPostShadows();

    drawAllGoalPosts();

    glDisable(GL_TEXTURE_2D);

    // Turn off ALL tower lights 
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    glDisable(GL_LIGHT3);
    glDisable(GL_LIGHT4);

    
    drawCastle();

    // Show instructions if the game hasn't started yet
    if (gameState == 0) {
        drawStartScreenText();
    }
    // Show victory text if the Snitch is caught
    else if (gameState == 2) {
        drawVictoryText();
    }

    glutSwapBuffers();
}


void idle() {
    glutPostRedisplay();
}


void reshape(int w, int h) {
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(
        60.0,
        (float)w / (float)h,
        1.0,
        4000.0
    );

    glMatrixMode(GL_MODELVIEW);
}


void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_NORMALIZE);

    glShadeModel(GL_SMOOTH);

    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    loadTextures();
}

int main(int argc, char** argv){

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(1200, 800);

    glutCreateWindow("Project Nimbus");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);
    glutSpecialUpFunc(specialKeysUp);
    glutIdleFunc(display);
	glutIdleFunc(idle);

	initForest();
    

    glutMainLoop();

    return 0;
}
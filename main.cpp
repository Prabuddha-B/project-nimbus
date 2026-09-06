#include<windows.h>
#include <glut.h>
#include "Ground.h"
#include "Camera.h"
#include "GoalPost.h"
#include "Texture.h"
#include "SpectatorStand.h"
#include "Shadow.h"


// For Axes 
void drawAxes(){

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
void drawGrid(){
    glColor3f(0.5f, 0.5f, 0.5f);

    glBegin(GL_LINES);

    for (int i = -300; i <= 300; i+=5){
        glVertex3f((float)i, 0.0f, -300);
        glVertex3f((float)i, 0, 300);

        glVertex3f(-300, 0.01f, (float)i);
        glVertex3f(300, 0, (float)i);
    }

    glEnd();
}

// For Lighting Functions
void setupLighting()
{
    GLfloat lightPosition[] = { sunX, sunY, sunZ, 1.0f };

    GLfloat ambientLight[] =
    {
        0.3f, 0.3f, 0.3f, 1.0f
    };

    GLfloat diffuseLight[] =
    {
        0.9f, 0.9f, 0.9f, 1.0f
    };

    GLfloat specularLight[] =
    {
        1.0f, 1.0f, 1.0f, 1.0f
    };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
}

// For Sun 
void drawSun(){
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
    if (sunY > 80)
    {
        glColor3f(1.0f, 1.0f, 0.8f);
    }
    else if (sunY > 40)
    {
        glColor3f(1.0f, 0.9f, 0.3f);
    }
    else
    {
        glColor3f(1.0f, 0.5f, 0.2f);
    }

    glPopMatrix();
}

// Display Method
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(
        camX, camY, camZ,
        0, 0, 0,
        0, 1, 0
    );

    setupLighting();

    //drawGrid();
    //drawAxes();

	glEnable(GL_TEXTURE_2D);

    if (showSun) {
        drawSun();
    }

    drawWorldGround();
    drawEmbankment();
    drawGround();
    drawSpectatorStand();

    drawGoalArea(-42.0f, false);
    drawGoalArea(42.0f, true);

    drawPitchBoundary();
    drawCenterLine();
    drawCenterCircle();
    drawGoalPostShadows();
    drawAllGoalPosts();


	glDisable(GL_TEXTURE_2D);
    

   

    glutSwapBuffers();
}


void reshape(int w, int h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(
        60.0,
        (float)w / (float)h,
        1.0,
        1000.0
    );

    glMatrixMode(GL_MODELVIEW);
}

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_NORMALIZE);

    glShadeModel(GL_SMOOTH);

    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(
        GL_FRONT_AND_BACK,
        GL_AMBIENT_AND_DIFFUSE
    );

    loadTextures();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(1200, 800);

    glutCreateWindow("Project Nimbus");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
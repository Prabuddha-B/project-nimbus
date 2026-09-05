#include<windows.h>
#include <glut.h>
#include "Ground.h"
#include "Camera.h"
#include "GoalPost.h"
#include "Texture.h"


// For Axes 
void drawAxes(){
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

    drawGround();

    drawGoalArea(-42.0f, false);
    drawGoalArea(42.0f, true);

    drawPitchBoundary();
    drawCenterLine();
    drawCenterCircle();

    drawAllGoalPosts();
    

    drawGrid();
    drawAxes();

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
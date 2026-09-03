#include <glut.h>

// Camera position
float camX = 0.0f;
float camY = 10.0f;
float camZ = 25.0f;

void drawAxes()
{
    glLineWidth(3);

    glBegin(GL_LINES);

    // X axis - Red
    glColor3f(1, 0, 0);
    glVertex3f(-50, 0, 0);
    glVertex3f(50, 0, 0);

    // Y axis - Green
    glColor3f(0, 1, 0);
    glVertex3f(0, -50, 0);
    glVertex3f(0, 50, 0);

    // Z axis - Blue
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -50);
    glVertex3f(0, 0, 50);

    glEnd();
}

void drawGrid()
{
    glColor3f(0.5f, 0.5f, 0.5f);

    glBegin(GL_LINES);

    for (int i = -50; i <= 50; i++)
    {
        glVertex3f((float)i, 0, -50);
        glVertex3f((float)i, 0, 50);

        glVertex3f(-50, 0, (float)i);
        glVertex3f(50, 0, (float)i);
    }

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(
        camX, camY, camZ,
        0, 0, 0,
        0, 1, 0
    );

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
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGB |
        GLUT_DEPTH
    );

    glutInitWindowSize(1200, 800);

    glutCreateWindow("Project Nimbus");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
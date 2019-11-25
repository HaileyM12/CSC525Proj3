/*==================================================================================================
 PROGRAMMERS:           Hailey Martinelli, Quy Pham, Nathan Pasley, Evan Politte
 TRACE FOLDEER:         Hailey555, quy123, Pollitt96, pasley3
 ASSIGNMENT:            Proj3
 COURSE:                CSC 525
 MODIFIED BY:            N/A
 LAST MODIFIED DATE:    12/08/2019
 DESCRIPTION:           Creating a 3D advertisement for snowman sales
 NOTE:                  Pollitt96 -
                        Hailey555 -
                        quy123 -
                        pasley3 -
 FILES:                 proj3.cpp, (projProject.sln, ...)
 IDE/COMPILER:            MicroSoft Visual Studio 2019
 INSTRUCTION FOR COMPILATION AND EXECUTION:
    1.        Double click on projProject folder
    2.        Double click on    projProject.sln  to OPEN the project
    3.        Press Ctrl+F7                    to COMPILE
    4.        Press Ctrl+F5                    to EXECUTE
==================================================================================================*/
#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <math.h>
#include <GLUT/GLUT.h>                // include GLUT library
using namespace std;
//***********************************************************************************
//text font for billboard
void* font = GLUT_BITMAP_TIMES_ROMAN_24;

// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=5.0f;


void drawPresents() {
    glColor3f(0.0f, 1.0f, 0.0f);
    glTranslatef(1.1f, -2.0f, 0.0f);
    glutSolidCube(0.5);
}

void drawSnowMan() {

    glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
    glTranslatef(0.0f ,0.75f, 0.0f);
    glutSolidSphere(0.75f,20,20);
    
//Draw Middle
    glTranslatef(0.0f, 0.90f, 0.0f);
    glutSolidSphere(0.5f, 20, 20);

// Draw Head
    glTranslatef(0.0f, 0.7f, 0.0f);
    glutSolidSphere(0.25f,20,20);

// Draw Eyes
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f,10,10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f,10,10);
    glPopMatrix();

// Draw Nose
    glColor3f(1.0f, 0.5f , 0.5f);
    glutSolidCone(0.08f,0.5f,10,2);
}

void drawBitmapText(float x, float y, float z, void* font, const char* string)
{
    const char* c;
    glRasterPos3f(x, y, z);

    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void renderScene(void) {

    // Clear Color and Depth Buffers

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();
    // Set the camera
    gluLookAt(    x, 1.0f, z,
            x+lx, 1.0f,  z+lz,
            0.0f, 1.0f,  0.0f);

        // Draw ground
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();
    
        // Draw 36 SnowMen
    for(int i = -3; i < 3; i++)
        for(int j=-3; j < 3; j++) {
            glPushMatrix();
            glTranslatef(i*10.0,0,j * 10.0);
            drawSnowMan();
            drawPresents();
            glPopMatrix();
        }
    
    //Draw banner
    /*glColor3f(0.1f, 1.0f, 0.1f);
    glTranslatef(-8.0, 10.0, -50.0);
    glBegin(GL_QUADS);
        glVertex3f(-20.0f, -3.0f, 0.0f);
        glVertex3f(-20.0f, 3.0f, 0.0f);
        glVertex3f(20.0f, 3.0f, 0.0f);
        glVertex3f(20.0f, -3.0f, 0.0f);
    glEnd();*/
    
    //Write banner text
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBitmapText(-10, 10, -25, font, "Welcome to Snowman Fields Forever!");
    drawBitmapText(-5, 8, -25, font, "All snowmen $10");

    glutSwapBuffers();
}

void changeSize(int w, int h)
{

// Prevent a divide by zero, when window is too short
// (you cant make a window of zero width).
if (h == 0)
h = 1;
float ratio = w * 1.0 / h;

// Use the Projection Matrix
glMatrixMode(GL_PROJECTION);

// Reset Matrix
glLoadIdentity();

// Set the viewport to be the entire window
glViewport(0, 0, w, h);

// Set the correct perspective.
gluPerspective(45.0f, ratio, 0.1f, 100.0f);

// Get Back to the Modelview
glMatrixMode(GL_MODELVIEW);
}

void processNormalKeys(unsigned char key, int x, int y)
{

if (key == 27)
exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {

    float fraction = 0.3f;

    switch (key) {
        case GLUT_KEY_LEFT :
            angle -= 0.03f;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_RIGHT :
            angle += 0.03f;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_UP :
            x += lx * fraction;
            z += lz * fraction;
            break;
        case GLUT_KEY_DOWN :
            x -= lx * fraction;
            z -= lz * fraction;
            break;
    }
}

int main(int argc, char **argv) {

    // init GLUT and create window

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Snowmen For Sale!");

    // register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    // OpenGL init
    glEnable(GL_DEPTH_TEST);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 1;
}

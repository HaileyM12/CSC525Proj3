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
//void* font2 = GLUT_BITMAP_ARIAL_18;

// angle of rotation for the camera direction
float camera_angle = 0.0;
// actual vector representing the camera's direction
float camera_x_direction = 0.0f, camera_z_direction = -1.0f;
// XZ position of the camera
float camera_x_position = 0.0f, camera_z_position = 5.0f;


void drawPresents() {
    glColor3f(0.0f, 1.0f, 0.0f);
    glTranslatef(1.1f, -1.0f, 0.0f);
    glutSolidCube(0.5);
}

void drawSnowman() {

    glColor3f(1.0f, 1.0f, 1.0f);

// Draw snowman's bottom circle
    glTranslatef(0.0f ,0.75f, 0.0f);
    glutSolidSphere(0.75f,20,20);
    
//Draw snowman's middle circle
    glTranslatef(0.0f, 0.90f, 0.0f);
    glutSolidSphere(0.5f, 20, 20);

// Draw snowmans's top circle
    glTranslatef(0.0f, 0.7f, 0.0f);
    glutSolidSphere(0.25f,20,20);

// Draw snowman's eyes
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f,10,10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f,10,10);
    glPopMatrix();

// Draw snowman's nose
    glColor3f(1.0f, 0.5f , 0.5f);
    glutSolidCone(0.08f,0.5f,10,2);
    
//Draw snowman's buttons
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -0.50f, 0.5f);
    glutSolidSphere(0.04f,10,10);
    glTranslatef(0.0f, -0.15f, 0.0f);
    glutSolidSphere(0.04f,10,10);
    glTranslatef(0.0f, -0.17f, 0.0f);
    glutSolidSphere(0.04f,10,10);
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

void displayScene(void) {

    // Clear Color and Depth Buffers

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();
    
    // Set camera position
    gluLookAt(    camera_x_position, 1.0f, camera_z_position,
            camera_x_position+camera_x_direction, 1.0f,  camera_z_position+camera_z_direction,
            0.0f, 1.0f,  0.0f);

    // Draw ground
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();
    
    // Draw 36 snowmen and presents
    for(int x = -3; x < 3; x++)
        for(int z = -3; z < 3; z++) {
            glPushMatrix();
            glTranslatef(x * 10.0, 0 , z * 10.0);
            drawSnowman();
            drawPresents();
            glPopMatrix();
        }
    
    // Draw snow
    for(int x = -10; x < 10; x++)
        for(int y = -10; y < 10; y++)
            for(int z = -10; z < 10; z++) {
                glPushMatrix();
                glTranslatef(x * 10.0, y * 10.0, z * 10.0);
                glColor3f(1.0f, 1.0f, 1.0f);
                glutSolidSphere(0.04f,10,10);
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
    
    // Write banner text
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBitmapText(-10, 10, -25, font, "Welcome to Snowman Fields Forever!");
    drawBitmapText(-5, 8, -25, font, "All snowmen $10");

    glutSwapBuffers();
}

void reshapeScene(int w, int h)
{

float ratio = w * 1.0 / h;

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
// Make viewport the entire window
glViewport(0, 0, w, h);
// Update perspective with ratio
gluPerspective(45.0f, ratio, 0.1f, 100.0f);
glMatrixMode(GL_MODELVIEW);
}


void processArrowKeys(int key, int x, int y) {

    float multiplier = 0.3f;
    
    if(key == GLUT_KEY_LEFT) {
        camera_angle -= 0.03f;
        camera_x_direction = sin(camera_angle);
        camera_z_direction = -cos(camera_angle);
    }
    else if(key == GLUT_KEY_RIGHT) {
        camera_angle += 0.03f;
        camera_x_direction = sin(camera_angle);
        camera_z_direction = -cos(camera_angle);
    }
    else if(key == GLUT_KEY_UP) {
        camera_x_position += camera_x_direction * multiplier;
        camera_z_position += camera_z_direction * multiplier;
    }
    else if(key == GLUT_KEY_DOWN) {
        camera_x_position -= camera_x_direction * multiplier;
        camera_z_position -= camera_z_direction * multiplier;
    }

}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Snowmen For Sale!");

    // register callbacks
    glutDisplayFunc(displayScene);
    glutReshapeFunc(reshapeScene);
    glutIdleFunc(displayScene);
    glutSpecialFunc(processArrowKeys);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}

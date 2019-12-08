/*==================================================================================================
 PROGRAMMERS:           Hailey Martinelli, Quy Pham, Nathan Pasley, Evan Politte
 TRACE FOLDEER:         Hailey555, quy123, Pollitt96, pasley3
 ASSIGNMENT:            Proj3
 COURSE:                CSC 525
 MODIFIED BY:            N/A
 LAST MODIFIED DATE:    12/08/2019
 DESCRIPTION:           Creating a 3D advertisement for snowman sales
 NOTE:                  Pollitt96 (25%) - displaying everything in 3D space
                        Hailey555 (25%) - moving around 3D space with arrow keys
                        quy123 (25%) - drawing snowmen, text in sky
                        pasley3 (25%) - drawing presents, trees
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
#include <GLUT/GLUT.h>
//using namespace std;
//***********************************************************************************
//text font for billboard
void* font = GLUT_BITMAP_TIMES_ROMAN_24;

//angle of rotation for the camera direction, initally 0
float camera_angle = 0.0;

/*
   x and z direction of camera. This is used for
   the left and right arrow keys to "turn" the
   camera
 */
float camera_x_direction = 0.0f, camera_z_direction = -1.0f;

/*
   x and z position of the camera. This is used
   for the up and down arrow keys to move the
   camera's position forward or backward
 */
float camera_x_position = 0.0f, camera_z_position = 5.0f;


/*
   This function draws a Christmas present. It
   utilizes glutSolidCube() and glutWireCube()
   functions appear more like presents. It will
   later be used by the displayScene() function to
   draw multiple presents within our 3D world.
 */
void drawPresents() {
        
    //draw main cube of present
    glColor3f(0.0f, 0.5f, 0.05f);
    glTranslatef(1.1f, -1.0f, 0.0f);
    glutSolidCube(0.5);

    //draw "ribbon" around present
    glColor3f(0.0f, 0.0f, 0.0f);
    glutWireCube(0.501);
    
    glColor3f(.55, .09, .09);
    glScalef(1.0, .25, 1.0);
    glTranslatef(0.0f, 0.75f, 0.0f);
    glutSolidCube(0.53);

    glColor3f(0.0f, 0.0f, 0.0f);
    glutWireCube(0.5301);

    glTranslatef(0.0f, -0.75f, 0.0f);

    glColor3f(0.83, 0.69, 0.22);

    glScalef(0.25, 4.0, 1.0);
    glutSolidCube(0.531);
    glColor3f(0.0f, 0.0f, 0.0f);
    glutWireCube(0.53105);

    glScalef(4.0, 1.0, .25);
    glColor3f(0.83, 0.69, 0.22);
    glutSolidCube(0.531);
    glColor3f(0.0f, 0.0f, 0.0f);
    glutWireCube(0.53105);
}

/*
   This function draws a tree. It utilizes
   glutSolidCone() function to draw the tree and
   the star on top. It will also be referenced
   in the displayScene() function to draw multiple
   trees around the 3D world.
 */

void drawTree() {
    
    glColor3f(0, 0.39, 0);

    //draw each layer of tree
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(1.0, 1.0, 500, 500);

    glTranslatef(0.0, 0.0, 0.5);
    glutSolidCone(0.75, 1.0, 500, 500);

    glTranslatef(0.0, 0.0, 0.5);
    glutSolidCone(0.5, 0.75, 500, 500);
    
    glTranslatef(0.0, 0.0, 0.5);
    glutSolidCone(0.25, 0.5, 500, 500);
    
    //draw star on top of trees
    glColor3f(1.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 0.52f);
    glutSolidCone(0.05, 0.15, 500, 500);
    glRotatef(80, 0, 1, 0);
    glutSolidCone(0.05, 0.15, 500, 500);
    glRotatef(80, 0, 1, 0);
    glutSolidCone(0.05, 0.15, 500, 500);
    glRotatef(80, 0, 1, 0);
    glutSolidCone(0.05, 0.15, 500, 500);
    glRotatef(70, 0, 1, 0);
    glutSolidCone(0.05, 0.15, 500, 500);
    
}

/*
   This function draws a snowman. It utilizes
   multiple Glut 3D shape functions. It will be
   used in the displayScene() function to draw
   many snowmen in the 3D world.
 */

void drawSnowman() {

    glColor3f(1.0f, 1.0f, 1.0f);

    //draw snowman's bottom circle
    glTranslatef(0.0f ,0.75f, 0.0f);
    glutSolidSphere(0.75f,20,20);
    
    //draw snowman's middle circle
    glTranslatef(0.0f, 0.90f, 0.0f);
    glutSolidSphere(0.5f, 20, 20);

    //draw snowmans's top circle
    glTranslatef(0.0f, 0.7f, 0.0f);
    glutSolidSphere(0.25f,20,20);

    //draw snowman's eyes
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f,10,10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f,10,10);
    glPopMatrix();

    //draw snowman's nose
    glColor3f(1.0f, 0.5f , 0.5f);
    glutSolidCone(0.08f,0.5f,10,2);
    
    //draw snowman's buttons
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -0.50f, 0.5f);
    glutSolidSphere(0.04f,10,10);
    glTranslatef(0.0f, -0.15f, 0.0f);
    glutSolidSphere(0.04f,10,10);
    glTranslatef(0.0f, -0.17f, 0.0f);
    glutSolidSphere(0.04f,10,10);
}

/*
   This function writes text in the 3D world. When using
   this function specify x, y, and z coordinates of the
   starting position of the text. Give the font of the
   text and the actual string message to display.
 */

void drawBitmapText(float x, float y, float z, void* font, const char* string)
{
    const char* c;
    glRasterPos3f(x, y, z);

    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

/*
   This function is our display callback. This is where
   all the 3D objects are displayed and the camera is
   updated. If an arrow key is pressed, this will change
   either the direction/angle or position of camera, and then
   gluLookAt() is updated here in the callback.
 */

void displayScene(void) {

    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    //put identity matrix on top of stack to reset transformations
    glLoadIdentity();
    
    /*
       Set camera position: The camera's eye position should be updated to the current camera
       position depending on if arrow keys were pressed. So, camera's x and z coordinates are used
       along with a constant for y coordinate because the camera's y position doesn't change.
       The camera's look at position should also be updated if the arrow keys are used. The x and z
       coordinate of the look at position will take into consideration where the camera is and the
       direction it is pointing. A constant is used for the y coordinate again because the camera only
       looks at the same y coordinate. 0.0, 1.0, 0.0 is used for the up-vector so that it points in the
       position y direction. Constants are used because this will never change, the camera will never
       be able to spin.
     */
    
    gluLookAt(camera_x_position, 1.0f, camera_z_position, camera_x_position + camera_x_direction, 1.0f,  camera_z_position + camera_z_direction, 0.0f, 1.0f,  0.0f);

    //draw ground
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();
    
    //draw a few trees
    for(int x = -2; x < 2; x++)
        for(int z = -2; z < 2; z++) {
            glPushMatrix();
            glTranslatef(x * 20.0 + 5.0, 0 , z * 20.0 + 5.0);
            drawTree();
            glPopMatrix();
    }
    
    //draw snowmen and presents
    for(int x = -3; x < 3; x++)
        for(int z = -3; z < 3; z++) {
            glPushMatrix();
            glTranslatef(x * 10.0, 0 , z * 10.0);
            drawSnowman();
            drawPresents();
            glPopMatrix();
        }
    
    //draw stars in sky
    for(int x = -10; x < 10; x++)
        for(int y = -10; y < 10; y++)
            for(int z = -10; z < 10; z++) {
                glPushMatrix();
                glTranslatef(x * 10.0, y * 10.0, z * 10.0);
                glColor3f(1.0f, 1.0f, 1.0f);
                glutSolidSphere(0.04f,10,10);
                glPopMatrix();
    }
    
    //write banner text
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBitmapText(-10, 10, -25, font, "Welcome to Snowman Fields Forever!");
    drawBitmapText(-5, 8, -25, font, "All snowmen $10");

    glutSwapBuffers();
}


/*
   This function is the special key callback. It controls what
   happens when we press the arrow keys. The left and right arrow
   keys set the camera's direction by using the sin and cos
   functions with the camera's current angle. The current angle
   must first be decremented/incremented before taking the sin/cos
   of it. Using direction instead of position turns
   the camera without actually moving where the camera is placed.
   The up and down arrow keys use both the camera direction and
   position. This is because in order to move the camera's position,
   you need to add/subtract to it's position. We do this by
   adding/subtracting a scaled portion (0.3 in this case) of the
   direction of the camera to the position. This will either move
   the camera forward or backward. We only deal with x and z
   coordinates so that the camera cannot move up off the
   ground or stay positioned on the ground but "look up".
 */

void processArrowKeys(int key, int x, int y) {

    float movementMultiplier = 0.3f;
    
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
        camera_x_position += camera_x_direction * movementMultiplier;
        camera_z_position += camera_z_direction * movementMultiplier;
    }
    else if(key == GLUT_KEY_DOWN) {
        camera_x_position -= camera_x_direction * movementMultiplier;
        camera_z_position -= camera_z_direction * movementMultiplier;
    }

}

void myInit()
{
    //specify a background color for sky: dark blue
    glClearColor(0.05, 0.05, 0.25, 0);
}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    
    //create window
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Snowmen For Sale!");
    
    myInit();

    //register callbacks
    glutDisplayFunc(displayScene);
    glutIdleFunc(displayScene);
    glutSpecialFunc(processArrowKeys);

    glEnable(GL_DEPTH_TEST);
    

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //make viewport the entire window
    glViewport(0, 0, 500, 500);
    //update perspective with ratio
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    glutMainLoop();

    return 0;
}

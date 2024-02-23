//Usage:
//Hold down the number keys , 1-7, to select one or multiple circles.
//While circle(s) are selected, use the left mouse button to translate and use the right mouse button to rotate.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <math.h>
#include "Rig.h"
using namespace std;

#define NUM_PARTS 16

int win_width = 600, win_height = 600;
float canvas_width = 20.0f; float canvas_height = 20.0f;

Rig testRig;
bool keyStates[256];
int buttonState;

void init(void)
{
    for(int i = 0; i<256; i++) {
        keyStates[i] = false;
    }
    
    buttonState = -1;

    // Make root bone and add to rig
    testRig.ConstructRig();
}

void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    /* Draw all shapes that'll be part of the rig */
    testRig.m_pRoot->RenderBone();
    
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    win_width =  w;
    win_height = h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-canvas_width/2.0f, canvas_width/2.0f, -canvas_height/2.0f, canvas_height/2.0f);
    glViewport(0, 0, (GLsizei) win_width, (GLsizei) win_height);
    
    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) // 'esc' key
        exit(0);

    if (key == 'a') // A Key
        testRig.UpdateBoneRotations(1.0f);
    if (key == 'd') // D Key
        testRig.UpdateBoneRotations(-1.0f);
    
    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y)
{
    glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y)
{
    if (key == GLUT_KEY_UP) // Up Arrow
        testRig.SelectParent();
    if (key == GLUT_KEY_DOWN) // down arrow
        testRig.SelectFirstChild();
    if (key == GLUT_KEY_RIGHT) // right arrow
        testRig.SelectNextChild(-1);
    if (key == GLUT_KEY_LEFT) // left arrow
        testRig.SelectNextChild(1);
        
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(win_width, win_height);
    glutCreateWindow("2D transformation Tree");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialKeyboard);
    glutMainLoop();
    return 0;
    
}
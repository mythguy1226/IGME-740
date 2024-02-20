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
using namespace std;

#define MAX_NUM_CIRCLE 8
#define CIRCLE_RADIUM 2.0

int win_width = 600, win_height = 600;
float canvas_width = 20.0f; float canvas_height = 20.0f;


bool keyStates[256];
int buttonState;
float colors[3*MAX_NUM_CIRCLE];
float rotations[16];

float curMouse[2];
float preMouse[2];

int currentPart = 0;

void init(void)
{
    for(int i = 0; i<256; i++) {
        keyStates[i] = false;
    }
    for(int i=0; i<MAX_NUM_CIRCLE; i++) {
        colors[i*3+0] = 0.0f; // red
        colors[i*3+1] = 0.0f; // green
        colors[i*3+2] = 0.0f; // blue
        
        rotations[i] = 0.0f;
    }
    
    buttonState = -1;
}

void drawRect(float size, const float* c)
{
    glColor3fv(c);
    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-size, size); // vertex 1
    glVertex2f(-size, -size); // vertex 4
    glVertex2f(size, -size); // vertex 3
    glVertex2f(size, size); // vertex 2
    glVertex2f(-size, size); // vertex 1
    glEnd();
}

void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    /* Draw all shapes that'll be part of the rig */

    // Chest
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f);
    glRotatef(rotations[0], 0.0f, 0.0f, 1.0f);
    glScalef(2.0f, 1.0f, 1.0f);
    drawRect(1.0f, colors + 0 * 3);
    glPopMatrix();

    // Torso
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 0.0f);
    glRotatef(rotations[1], 0.0f, 0.0f, 1.0f);
    glScalef(1.25f, 1.0f, 1.0f);
    drawRect(1.0f, colors + 1 * 3);
    glPopMatrix();

    // Neck
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 0.0f);
    glScalef(0.25f, 0.5f, 1.0f);
    drawRect(1.0f, colors + 2 * 3);
    glPopMatrix();

    // Head
    glPushMatrix();
    glTranslatef(0.0f, 4.0f, 0.0f);
    glScalef(1.0f, 1.0f, 1.0f);
    drawRect(1.0f, colors + 3 * 3);
    glPopMatrix();

    // Left Arm 1
    glPushMatrix();
    glTranslatef(-3.0f, 1.0f, 0.0f);
    glScalef(1.0f, 0.5f, 1.0f);
    drawRect(1.0f, colors + 4 * 3);
    glPopMatrix();

    // Left Arm 2
    glPushMatrix();
    glTranslatef(-5.0f, 1.0f, 0.0f);
    glScalef(1.0f, 0.5f, 1.0f);
    drawRect(1.0f, colors + 5 * 3);
    glPopMatrix();

    // Left Hand
    glPushMatrix();
    glTranslatef(-7.0f, 1.0f, 0.0f);
    glScalef(1.0f, 1.0f, 1.0f);
    drawRect(1.0f, colors + 6 * 3);
    glPopMatrix();

    // Right Arm 1
    glPushMatrix();
    glTranslatef(3.0f, 1.0f, 0.0f);
    glScalef(1.0f, 0.5f, 1.0f);
    drawRect(1.0f, colors + 7 * 3);
    glPopMatrix();

    // Right Arm 2
    glPushMatrix();
    glTranslatef(5.0f, 1.0f, 0.0f);
    glScalef(1.0f, 0.5f, 1.0f);
    drawRect(1.0f, colors + 8 * 3);
    glPopMatrix();

    // Right Hand
    glPushMatrix();
    glTranslatef(7.0f, 1.0f, 0.0f);
    glScalef(1.0f, 1.0f, 1.0f);
    drawRect(1.0f, colors + 9 * 3);
    glPopMatrix();

    // Left Leg 1
    glPushMatrix();
    glTranslatef(-0.7f, -3.0f, 0.0f);
    glScalef(0.5f, 1.0f, 1.0f);
    drawRect(1.0f, colors + 10 * 3);
    glPopMatrix();

    // Left Leg 2
    glPushMatrix();
    glTranslatef(-0.7f, -5.0f, 0.0f);
    glScalef(0.5f, 1.0f, 1.0f);
    drawRect(1.0f, colors + 11 * 3);
    glPopMatrix();

    // Left Foot
    glPushMatrix();
    glTranslatef(-1.2f, -6.5f, 0.0f);
    glScalef(1.0f, 0.5f, 1.0f);
    drawRect(1.0f, colors + 12 * 3);
    glPopMatrix();

    // Right Leg 1
    glPushMatrix();
    glTranslatef(0.7f, -3.0f, 0.0f);
    glScalef(0.5f, 1.0f, 1.0f);
    drawRect(1.0f, colors + 13 * 3);
    glPopMatrix();

    // Right Leg 2
    glPushMatrix();
    glTranslatef(0.7f, -5.0f, 0.0f);
    glScalef(0.5f, 1.0f, 1.0f);
    drawRect(1.0f, colors + 14 * 3);
    glPopMatrix();

    // Right Foot
    glPushMatrix();
    glTranslatef(1.2f, -6.5f, 0.0f);
    glScalef(1.0f, 0.5f, 1.0f);
    drawRect(1.0f, colors + 15 * 3);
    glPopMatrix();

    // Update colors based on current part selection
    for (int i = 0; i < 16; i++)
    {
        if (i == currentPart)
        {
            colors[(i) * 3 + 0] = 1.0f;
            colors[(i) * 3 + 1] = 0.0f;
            colors[(i) * 3 + 2] = 0.0f;
        }
        else
        {
            colors[(i) * 3 + 0] = 0.0f;
            colors[(i) * 3 + 1] = 0.0f;
            colors[(i) * 3 + 2] = 0.0f;
        }
    }
    
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

    if (key == 'd') // A Key
    {
        rotations[currentPart] += 1.0f;
        std::cout << rotations[currentPart] << std::endl;
    }
    
    glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y)
{
    if (key == GLUT_KEY_UP) // Up Arrow
        currentPart++;

    if (key == GLUT_KEY_DOWN) // down arrow
        currentPart--;
    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y)
{
    unsigned char asciiOffset = 49; // see an ascii table
    for(unsigned char i = '1'; i<'8'; i++) {
        if(key == i) {
            keyStates[i] = false;
            colors[(i-asciiOffset)*3+0] = 0.0f;
            colors[(i-asciiOffset)*3+1] = 0.0f;
            colors[(i-asciiOffset)*3+2] = 0.0f;
        }
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN) {
        buttonState = button;
        curMouse[0] = ((float)x/win_width - 0.5f)*canvas_width;
        curMouse[1] = ((float)(win_height - y)-0.5f)/win_height*canvas_height;
        preMouse[0] = ((float)x/win_width - 0.5f)*canvas_width;
        preMouse[1] = ((float)(win_height - y)-0.5f)/win_height*canvas_height;
    }
    else if (state == GLUT_UP)
        button = -1;
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
    //glutSpecialFunc(specialKeyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
    
}
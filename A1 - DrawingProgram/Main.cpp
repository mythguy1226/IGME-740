
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <vector>
#include "ShapeManager.h"

using namespace std;

float canvasSize[] = { 10.0f, 10.0f };
int rasterSize[] = { 800, 600 };

// structure for storing 3 2D vertices of a triangle
float color[3];

float mousePos[2];

// Shape manager singleton
ShapeManager* pShapeMngr = ShapeManager::GetInstance();

void init(void)
{
    // Initialize mouse position and color
    mousePos[0] = mousePos[1] = 0.0f;
    color[0] = 1.0f;
    color[1] = color[2] = 0.0f;
}

void drawCursor()
{
    glColor3f(1.0f, 0.0f, 1.0f);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex2fv(mousePos);
    glEnd();
    glPointSize(1.0f);
}

void display(void)
{
    // Set background to white
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Set drawing color to current color
    glColor3fv(color);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Call shape manager to display all of its shapes
    pShapeMngr->DisplayAllShapes(mousePos);
    
    drawCursor();
    glutSwapBuffers();
}

// Method called upon to handle resize of window
void reshape(int w, int h)
{
    // Set raster size to new window values
    rasterSize[0] = w;
    rasterSize[1] = h;

    // Generate 2D orthographic projection
    // using new window size and canvas size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, canvasSize[0], 0.0, canvasSize[1]);
    glViewport(0, 0, rasterSize[0], rasterSize[1]);

    // Redisplay scene
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    // Detect left mouse button down
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        // Create shape if a type is chosen
        if(pShapeMngr->GetObjectType() != ShapeType::None)
            pShapeMngr->CreateShape();
        
        // Get mouse position in canvas space
        mousePos[0] = (float)x / rasterSize[0] * canvasSize[0];
        mousePos[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];

        // Add shape point
        pShapeMngr->AddShapePoint(mousePos, color);

        glutPostRedisplay();
    }
}

void motion(int x, int y)
{
    // mouse events are handled by OS, eventually. When using mouse in the raster window, it assumes top-left is the origin.
    // Note: the raster window created by GLUT assumes bottom-left is the origin.
    mousePos[0] = (float)x / rasterSize[0] * canvasSize[0];
    mousePos[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    }
}

void menu(int value)
{
    switch (value) {
    case 0: // clear
        pShapeMngr->Release();
        glutPostRedisplay();
        break;
    case 1: //exit
        exit(0);
    case 2: // red
        color[0] = 1.0f;
        color[1] = 0.0f;
        color[2] = 0.0f;
        glutPostRedisplay();
        break;
    case 3: // green
        color[0] = 0.0f;
        color[1] = 1.0f;
        color[2] = 0.0f;
        glutPostRedisplay();
        break;
    case 4: // blue
        color[0] = 0.0f;
        color[1] = 0.0f;
        color[2] = 1.0f;
        glutPostRedisplay();
        break;
    case 5: // black
        color[0] = 0.0f;
        color[1] = 0.0f;
        color[2] = 0.0f;
        glutPostRedisplay();
        break;
    case 6:
        pShapeMngr->SetObjectType(ShapeType::Point);
        break;
    case 7:
        pShapeMngr->SetObjectType(ShapeType::Line);
        break;
    case 8:
        pShapeMngr->SetObjectType(ShapeType::Triangle);
        break;
    case 9:
        pShapeMngr->SetObjectType(ShapeType::Quad);
        break;
    case 10:
        pShapeMngr->SetObjectType(ShapeType::Polygons);
        break;
    case 11:
        pShapeMngr->SetObjectSize(ShapeSize::Small);
        break;
    case 12:
        pShapeMngr->SetObjectSize(ShapeSize::Medium);
        break;
    case 13:
        pShapeMngr->SetObjectSize(ShapeSize::Large);
        break;
    default:
        break;
    }
}
void createMenu()
{
    int colorMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Red", 2);
    glutAddMenuEntry("Green", 3);
    glutAddMenuEntry("Blue", 4);
    glutAddMenuEntry("Black", 5);

    int objectsMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Point", 6);
    glutAddMenuEntry("Line", 7);
    glutAddMenuEntry("Triangle", 8);
    glutAddMenuEntry("Quad", 9);
    glutAddMenuEntry("Polygon", 10);

    int sizesMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Small", 11);
    glutAddMenuEntry("Medium", 12);
    glutAddMenuEntry("Large", 13);

    glutCreateMenu(menu);
    glutAddMenuEntry("Clear", 0);
    glutAddSubMenu("Objects", objectsMenu);
    glutAddSubMenu("Colors", colorMenu);
    glutAddSubMenu("Sizes", sizesMenu);
    glutAddMenuEntry("Exit", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char* argv[])
{
    // Initialize program variables
    // and GLUT display
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(rasterSize[0], rasterSize[1]);
    glutCreateWindow("Mouse Event - draw a triangle");

    // Attach callback functions to methods within class
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);
    createMenu();
    glutMainLoop();
    return 0;


}
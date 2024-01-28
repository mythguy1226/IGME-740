
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <vector>
#include "ShapeManager.h"

// Size values for vector and raster spaces
float fCanvasSize[] = { 10.0f, 10.0f };
int iRasterSize[] = { 800, 600 };

// Color and mouse position
float v3Color[3];
float v2MousePos[2];

// Shape manager singleton
ShapeManager* pShapeMngr = ShapeManager::GetInstance();

void init(void)
{
    // Initialize mouse position and color
    v2MousePos[0] = v2MousePos[1] = 0.0f;
    v3Color[0] = 1.0f;
    v3Color[1] = v3Color[2] = 0.0f;
}

void drawCursor()
{
    // Set cursor color to magenta and plot point
    // wherever mouse position is located
    glColor3f(1.0f, 0.0f, 1.0f);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex2fv(v2MousePos);
    glEnd();
    glPointSize(1.0f);
}

void display(void)
{
    // Set background to white
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Set drawing color to current color
    glColor3fv(v3Color);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Call shape manager to display all of its shapes
    pShapeMngr->DisplayAllShapes(v2MousePos);
    
    drawCursor();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    // Set raster size to new window values
    iRasterSize[0] = w;
    iRasterSize[1] = h;

    // Generate 2D orthographic projection
    // using new window size and canvas size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, fCanvasSize[0], 0.0, fCanvasSize[1]);
    glViewport(0, 0, iRasterSize[0], iRasterSize[1]);

    // Redisplay scene
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    // Detect left mouse button down
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        // Create shape if a type is chosen and not currently drawing
        if(pShapeMngr->GetObjectType() != ShapeType::None)
            pShapeMngr->CreateShape();
        
        // Get mouse position in canvas space
        v2MousePos[0] = (float)x / iRasterSize[0] * fCanvasSize[0];
        v2MousePos[1] = (float)(iRasterSize[1] - y) / iRasterSize[1] * fCanvasSize[1];

        // Add shape point
        pShapeMngr->AddShapePoint(v2MousePos, v3Color);

        // Redisplay window to reflect changes
        glutPostRedisplay();
    }
}

void motion(int x, int y)
{
    // mouse events are handled by OS, eventually. When using mouse in the raster window, it assumes top-left is the origin.
    // Note: the raster window created by GLUT assumes bottom-left is the origin.
    v2MousePos[0] = (float)x / iRasterSize[0] * fCanvasSize[0];
    v2MousePos[1] = (float)(iRasterSize[1] - y) / iRasterSize[1] * fCanvasSize[1];

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    case 32: // Space bar
        // Functionality only needed for lines and polygons
        if (pShapeMngr->GetObjectType() == ShapeType::Line || pShapeMngr->GetObjectType() == ShapeType::Polygons)
        {
            // If currently drawing something, complete the shape
            // and reset the current shape pointer for a new shape
            // to take its place when ready to draw
            if (pShapeMngr->GetCurrentShape())
            {
                pShapeMngr->GetCurrentShape()->CompleteShape();
                pShapeMngr->SetCurrentShape(nullptr);
            }
        }
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
        v3Color[0] = 1.0f;
        v3Color[1] = 0.0f;
        v3Color[2] = 0.0f;
        glutPostRedisplay();
        break;
    case 3: // green
        v3Color[0] = 0.0f;
        v3Color[1] = 1.0f;
        v3Color[2] = 0.0f;
        glutPostRedisplay();
        break;
    case 4: // blue
        v3Color[0] = 0.0f;
        v3Color[1] = 0.0f;
        v3Color[2] = 1.0f;
        glutPostRedisplay();
        break;
    case 5: // black
        v3Color[0] = 0.0f;
        v3Color[1] = 0.0f;
        v3Color[2] = 0.0f;
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
    // Setup colors menu
    int colorMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Red", 2);
    glutAddMenuEntry("Green", 3);
    glutAddMenuEntry("Blue", 4);
    glutAddMenuEntry("Black", 5);

    // Setup objects menu
    int objectsMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Point", 6);
    glutAddMenuEntry("Line", 7);
    glutAddMenuEntry("Triangle", 8);
    glutAddMenuEntry("Quad", 9);
    glutAddMenuEntry("Polygon", 10);

    // Setup sizes menu
    int sizesMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Small", 11);
    glutAddMenuEntry("Medium", 12);
    glutAddMenuEntry("Large", 13);

    // Create main menu and attach sub-menus
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
    glutInitWindowSize(iRasterSize[0], iRasterSize[1]);
    glutCreateWindow("(A1 - Shape Renderer) Mouse Event - Draw a shape");

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
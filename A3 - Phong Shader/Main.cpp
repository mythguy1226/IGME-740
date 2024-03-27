// This OpenGL project demonstrates a simple interactive camera implementation and a few vertex and fragment shaders. 
// Two modes of camera controls (press c to switch between two modes): 
// 1. Focus Mode: Holding ALT and Left Mouse Button (LMB) and moving the mouse will rotate the camera about the LookAt Position
//                Holding ALT and MMB and moving the mouse will pan the camera.
//                Holding ALT and RMB and moving the mouse will zoom the camera.
// 2. First-Person Mode: Pressing W, A, S, or D will move the camera
//                       Holding LMB and moving the mouse will roate the camera.
// Basic shader - demonstrate the basic use of vertex and fragment shader
// Displacement shader - a special fireball visual effects with Perlin noise function
// Toon shading shader - catoonish rendering effects
// Per-vertex shading v.s. per-fragment shading = visual comparison between two types of shading 

#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/constants.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Camera.h"
#include "Text.h"
#include "Mesh.h"

#include <iostream>
using namespace std;
using namespace glm;

int g_winWidth  = 1024;
int g_winHeight = 512;

Camera g_cam;
Text g_text;

unsigned char g_keyStates[256];

char v_shader_file1[] = "..\\shaders\\perVert_phong.vert"; // phong per vert shading
char f_shader_file1[] = "..\\shaders\\perVert_phong.frag"; // phong per vert shading
char v_shader_file2[] = "..\\shaders\\perFrag_phong.vert"; // phong per frag shading
char f_shader_file2[] = "..\\shaders\\perFrag_phong.frag"; // phong per frag shading

const char meshFile[128] = "..\\Mesh\\teapot.obj"; // mesh to render

Mesh g_mesh1;
Mesh g_mesh2;

vec3 g_lightPos1 = vec3(3.0f, 3.0f, 3.0f);
vec3 g_lightPos2 = vec3(1.0f, 0.0f, -2.0f);

int selectedLight = 1;

float g_time = 0.0f;

void initialization() 
{    
    g_cam.set(3.0f, 4.0f, 14.0f, 0.0f, 1.0f, -0.5f, g_winWidth, g_winHeight);
	g_text.setColor(0.0f, 0.0f, 0.0f);

	g_mesh1.create(meshFile, v_shader_file1, f_shader_file1);
	g_mesh2.create(meshFile, v_shader_file2, f_shader_file2);
}

/****** GL callbacks ******/
void initialGL()
{    
	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	
	glClearColor (1.0f, 1.0f, 1.0f, 0.0f);
	
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

void idle()
{
    // add any stuff to update at runtime ....

    g_cam.keyOperation(g_keyStates, g_winWidth, g_winHeight);

	glutPostRedisplay();
}

void display()
{	 
	glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	// add any stuff you'd like to draw	

	glUseProgram(0);
	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	g_cam.drawGrid();
    g_cam.drawCoordinateOnScreen(g_winWidth, g_winHeight);
    g_cam.drawCoordinate();
		

	g_time = (float)glutGet(GLUT_ELAPSED_TIME)/1000.0f;

	// Draw the teapot meshes
	mat4 m4Model = translate(mat4(), vec3(0.0f, 2.0f, 0.0f)) * scale(mat4(), vec3(0.5f));
	g_mesh1.draw(m4Model, g_cam.viewMat, g_cam.projMat, g_lightPos1, g_lightPos2, g_time);

	m4Model = translate(mat4(), vec3(3.0f, 2.0f, 0.0f)) * scale(mat4(), vec3(0.5f));
	g_mesh2.draw(m4Model, g_cam.viewMat, g_cam.projMat, g_lightPos1, g_lightPos2, g_time);

	// Draw the point lights
	mat4 m4LightModel = translate(mat4(), g_lightPos1);
	g_cam.drawLight(m4LightModel, selectedLight == 1);
	m4LightModel = translate(mat4(), g_lightPos2);
	g_cam.drawLight(m4LightModel, selectedLight == 2);

    glutSwapBuffers();
}

void reshape(int w, int h)
{
	g_winWidth = w;
	g_winHeight = h;
	if (h == 0) {
		h = 1;
	}
	g_cam.setProjectionMatrix(g_winWidth, g_winHeight);
    g_cam.setViewMatrix();
    glViewport(0, 0, w, h);
}

void mouse(int button, int state, int x, int y)
{
    g_cam.mouseClick(button, state, x, y, g_winWidth, g_winHeight);
}

void motion(int x, int y)
{
    g_cam.mouseMotion(x, y, g_winWidth, g_winHeight);
}

void keyup(unsigned char key, int x, int y)
{
    g_keyStates[key] = false;
}

void keyboard(unsigned char key, int x, int y)
{
    g_keyStates[key] = true;
	switch(key) { 
		case 27:
			exit(0);
			break;
        case 'c': // switch cam control mode
            g_cam.switchCamMode();
			glutPostRedisplay();
            break;
        case ' ':
            g_cam.PrintProperty();
            break;
		case '+':
			g_mesh1.normal_offset += 0.01;
			break;
		case'-':
			g_mesh1.normal_offset -= 0.01;
			break;

		case '1': // Switch to light 1
			selectedLight = 1;
			break;
		case '2': // Switch to light 2
			selectedLight = 2;
			break;

		case 'a': // Move along negative x axis
			switch (selectedLight)
			{
				case 1: // Light 1
					g_lightPos1.x -= 0.1f;
					break;
				case 2: // Light 2
					g_lightPos2.x -= 0.1f;
					break;
			}
			break;
		case 'd': // Move along positive x axis
			switch (selectedLight)
			{
			case 1: // Light 1
				g_lightPos1.x += 0.1f;
				break;
			case 2: // Light 2
				g_lightPos2.x += 0.1f;
				break;
			}
			break;

		case 'w': // Move along negative z axis
			switch (selectedLight)
			{
			case 1: // Light 1
				g_lightPos1.z -= 0.1f;
				break;
			case 2: // Light 2
				g_lightPos2.z -= 0.1f;
				break;
			}
			break;
		case 's': // Move along positive z axis
			switch (selectedLight)
			{
			case 1: // Light 1
				g_lightPos1.z += 0.1f;
				break;
			case 2: // Light 2
				g_lightPos2.z += 0.1f;
				break;
			}
			break;

		case 'j': // Move along negative z axis
			switch (selectedLight)
			{
			case 1: // Light 1
				g_lightPos1.y -= 0.1f;
				break;
			case 2: // Light 2
				g_lightPos2.y -= 0.1f;
				break;
			}
			break;
		case 'u': // Move along positive z axis
			switch (selectedLight)
			{
			case 1: // Light 1
				g_lightPos1.y += 0.1f;
				break;
			case 2: // Light 2
				g_lightPos2.y += 0.1f;
				break;
			}
			break;
	}
}

int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(g_winWidth, g_winHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("VertFrag Shader Example");
	
	glewInit();
	initialGL();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
    glutKeyboardUpFunc(keyup);
    glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

	initialization();
	
    glutMainLoop();
    return EXIT_SUCCESS;
}
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
#include "ParticleSystem.h"

#include <iostream>
using namespace std;
using namespace glm;

int g_winWidth = 1024;
int g_winHeight = 512;

Camera g_cam;
Text g_text;

unsigned char g_keyStates[256];

unsigned int curTime = 0; //the milliseconds since the start
unsigned int preTime = 0;

// Particle system and sphere location
ParticleSystem parSys;
vec3 sphereLoc;

// Particle num variables for managing resolution
int particlesX = 64;
int particlesY = 32;

// File paths to needed shaders
char v_shader_file[] = "..\\shaders\\v_shader.vert";
char f_shader_file[] = "..\\shaders\\f_shader.frag";
char c_shader_file[] = "..\\shaders\\c_shader.comp";

void initialization()
{
	// Init the particle system with default values
	parSys.create(particlesX, particlesY, vec3(-10.0, 0.0, -5.0), vec3(10.0, 10.0, -5.0),
		c_shader_file, v_shader_file, f_shader_file);

	// Setup camera
	g_cam.set(38.0f, 13.0f, 4.0f, 0.0f, 0.0f, 0.0f, g_winWidth, g_winHeight, 45.0f, 0.01f, 10000.0f);
	g_text.setColor(0.0f, 0.0f, 0.0f);

	// Initialize sphere location
	sphereLoc = vec3(0.0, 5.0, -8.0);
}

/****** GL callbacks ******/
void initialGL()
{
	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle()
{
	// add any stuff to update at runtime ....
	curTime = glutGet(GLUT_ELAPSED_TIME);
	
	// Call upon particle system's update function to pass in
	// needed values for the compute shader
	parSys.update(vec3(0.0f, 5.0f, 20.0f), sphereLoc, 2.0f);

	g_cam.keyOperation(g_keyStates, g_winWidth, g_winHeight);

	glutPostRedisplay();

	preTime = curTime;
}

void display()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glUseProgram(0);
	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	// Display particle system
	parSys.draw(1.0f, g_cam.viewMat, g_cam.projMat);

	// Display typical camera stuff
	g_cam.drawGrid();
	g_cam.drawCoordinateOnScreen(g_winWidth, g_winHeight);
	g_cam.drawCoordinate();

	// Display sphere and projection sphere/lines
	g_cam.drawSphere(translate(mat4(), sphereLoc));
	g_cam.drawProjection(vec3(0.0f, 5.0f, 20.0f), vec3(-10.0, 0.0, -5.0), vec3(10.0, 10.0, -5.0));

	// display the text
	if (g_cam.isFocusMode()) {
		string str = "Cam mode: Focus";
		g_text.draw(10, 30, const_cast<char*>(str.c_str()), g_winWidth, g_winHeight);
	}
	else if (g_cam.isFPMode()) {
		string str = "Cam mode: FP";
		g_text.draw(10, 30, const_cast<char*>(str.c_str()), g_winWidth, g_winHeight);
	}

	glPopMatrix();
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
	switch (key) {
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
	case 'a': // Move along negative x axis
		sphereLoc.x -= 0.1f;
		break;
	case 'd': // Move along positive x axis
		sphereLoc.x += 0.1f;
		break;

	case 'w': // Move along negative z axis
		sphereLoc.z -= 0.1f;
		break;
	case 's': // Move along positive z axis
		sphereLoc.z += 0.1f;
		break;

	case 'j': // Move along negative z axis
		sphereLoc.y -= 0.1f;
		break;
	case 'u': // Move along positive z axis
		sphereLoc.y += 0.1f;
		break;
	case '+': // Double particle system resolution
		particlesX *= 2;
		particlesY *= 2;

		// Clamp resolution
		if (particlesX > 8192)
			particlesX = 8192;
		if (particlesY > 4096)
			particlesY = 4096;

		// Remap the system
		parSys.create(particlesX, particlesY, vec3(-10.0, 0.0, -5.0), vec3(10.0, 10.0, -5.0),
			c_shader_file, v_shader_file, f_shader_file);
		break;
	case '-': // Half particle system resolution
		particlesX /= 2;
		particlesY /= 2;

		// Clamp resolution
		if (particlesX < 16)
			particlesX = 16;
		if (particlesY < 8)
			particlesY = 8;

		// Remap the system
		parSys.create(particlesX, particlesY, vec3(-10.0, 0.0, -5.0), vec3(10.0, 10.0, -5.0),
			c_shader_file, v_shader_file, f_shader_file);
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(g_winWidth, g_winHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Compute Shader Example: A Simple particle System");

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
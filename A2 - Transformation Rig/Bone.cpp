#include "Bone.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

Bone::Bone()
{
	m_pPosition = new float[3];
	m_fRotation = 0.0f;
	m_pScale = new float[3];
}

void Bone::drawRect(float size, const float* c)
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

void Bone::RenderBone()
{
	glPushMatrix();
	glTranslatef(m_pPosition[0], m_pPosition[1], m_pPosition[2]);
	glRotatef(m_fRotation, 0.0f, 0.0f, 1.0f);
	glScalef(m_pScale[0], m_pScale[1], m_pScale[2]);
	drawRect(1.0f, new float[3]{0.0f, 0.0f, 0.0f});
	glPopMatrix();
}

void Bone::SetParent(Bone* a_pParent)
{
	m_pParent = a_pParent;
}

void Bone::AddChild(Bone* a_pChild)
{
	m_lChildren.push_back(a_pChild);
}

void Bone::RemoveChild(Bone* a_pChild)
{
	
}

void Bone::SetPosition(float x, float y, float z)
{
	m_pPosition[0] = x;
	m_pPosition[1] = y;
	m_pPosition[2] = z;
}

void Bone::SetRotation(float angle)
{
	m_fRotation = angle;
}

void Bone::SetScale(float x, float y, float z)
{
	m_pScale[0] = x;
	m_pScale[1] = y;
	m_pScale[2] = z;
}

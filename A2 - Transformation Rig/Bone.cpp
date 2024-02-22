#include "Bone.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

Bone::Bone()
{
	m_v3Position = vector3();
	m_fRotation = 0.0f;
	m_v3Scale = vector3();
}

void Bone::drawRect(float size, vector3 a_v3Color)
{
	glColor3fv(glm::value_ptr(a_v3Color));
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
	glRotatef(m_fRotation, 0.0f, 0.0f, 1.0f);
	glScalef(m_v3Scale.x, m_v3Scale.y, m_v3Scale.z);
	glTranslatef(m_v3Position.x, m_v3Position.y, m_v3Position.z);
	drawRect(1.0f, vector3());
	glPopMatrix();

	// Repeat this for all children if applicable
	for (int i = 0; i < m_lChildren.size(); i++)
		m_lChildren[i]->RenderBone();

}

void Bone::SetParent(Bone* a_pParent)
{
	m_pParent = a_pParent;
	a_pParent->AddChild(this);
}

void Bone::AddChild(Bone* a_pChild)
{
	m_lChildren.push_back(a_pChild);
}

void Bone::RemoveChild(Bone* a_pChild)
{
	
}

float Bone::GetRotation()
{
	return m_fRotation;
}

void Bone::SetPosition(float x, float y, float z)
{
	m_v3Position.x = x;
	m_v3Position.y = y;
	m_v3Position.z = z;
}

void Bone::SetRotation(float angle)
{
	m_fRotation = angle;

	// Set children to share same rotation
	for (int i = 0; i < m_lChildren.size(); i++)
		m_lChildren[i]->SetRotation(angle);
}

void Bone::SetScale(float x, float y, float z)
{
	m_v3Scale.x = x;
	m_v3Scale.y = y;
	m_v3Scale.z = z;
}

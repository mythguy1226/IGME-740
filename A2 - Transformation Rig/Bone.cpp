#include "Bone.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>

Bone::Bone()
{
	// Init member fields here
	m_v3Position = vector3();
	m_fRotation = 0.0f;
	m_v3Scale = vector3();
	m_v3Pivot = vector3();
}

Bone::~Bone()
{
	Release();
}

void Bone::Release()
{
	// Clean up all pointers here and clean list of children
	m_lChildren.clear();

	if(m_pParent)
		delete m_pParent;
	m_pParent = nullptr;
}

void Bone::drawRect(vector3 a_v3Size, vector3 a_v3Color)
{
	// Render rectangle in immediate mode
	// taking in size and color
	glColor3fv(glm::value_ptr(a_v3Color));
	glLineWidth(3.0f);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-a_v3Size.x, a_v3Size.y); // vertex 1
	glVertex2f(-a_v3Size.x, -a_v3Size.y); // vertex 4
	glVertex2f(a_v3Size.x, -a_v3Size.y); // vertex 3
	glVertex2f(a_v3Size.x, a_v3Size.y); // vertex 2
	glVertex2f(-a_v3Size.x, a_v3Size.y); // vertex 1
	glEnd();
}

Bone* Bone::GetParent()
{
	// Return the parent
	return m_pParent;
}

void Bone::SetParent(Bone* a_pParent)
{
	// Set parent for this bone
	// and add this bone to parent's list of children
	m_pParent = a_pParent;
	a_pParent->AddChild(this);
}

void Bone::AddChild(Bone* a_pChild)
{
	// Add child to bone's list of children
	m_lChildren.push_back(a_pChild);
}

float Bone::GetRotation()
{
	// Return angle of rotation
	return m_fRotation;
}

void Bone::SetPosition(float x, float y, float z)
{
	// Set the position
	m_v3Position.x = x;
	m_v3Position.y = y;
	m_v3Position.z = z;
}

void Bone::SetRotation(float angle)
{
	// Set the angle of rotation
	m_fRotation = angle;
}

void Bone::SetScale(float x, float y, float z)
{
	// Set the scale
	m_v3Scale.x = x;
	m_v3Scale.y = y;
	m_v3Scale.z = z;
}

void Bone::SetSelected(Bone* a_pSelection)
{
	// Set the globally selected bone
	m_pSelectedBone = a_pSelection;
}

void Bone::SetPivot(float x, float y, float z)
{
	// Set the pivot
	m_v3Pivot.x = x;
	m_v3Pivot.y = y;
	m_v3Pivot.z = z;
}

vector3 Bone::DetermineColor()
{
	// Set color to black by default
	vector3 v3Color = vector3();

	// Check if selected and turn red if selected
	if (m_pSelectedBone == this)
		v3Color = vector3(1.0f, 0.0f, 0.0f);
	return v3Color;
}


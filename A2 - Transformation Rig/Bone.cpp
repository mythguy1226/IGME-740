#include "Bone.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>

Bone::Bone()
{
	m_v3Position = vector3();
	m_fRotation = 0.0f;
	m_v3Scale = vector3();
}

void Bone::drawRect(vector3 a_v3Size, vector3 a_v3Color)
{
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

void Bone::RenderBone()
{
	// Set descendants of the selected bone
	m_pSelectedBone->SetDescendants(m_pSelectedBone);

	// Get the parent pivot
	vector3 parentPivot = m_v3Pivot;
	if(currentDescendant)
		parentPivot = m_pSelectedBone->m_v3Pivot;

	// Get bone color
	vector3 v3Color;
	if (this == m_pSelectedBone)
		v3Color = vector3(1.0f, 0.0f, 0.0f);

	glPushMatrix();
	glTranslatef(parentPivot.x, parentPivot.y, parentPivot.z);
	glRotatef(m_fRotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-parentPivot.x, -parentPivot.y, -parentPivot.z);
	glTranslatef(m_v3Position.x, m_v3Position.y, m_v3Position.z);
	drawRect(m_v3Scale, v3Color);
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
	m_fPrevRotation = m_fRotation;

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

void Bone::SetSelected(Bone* a_pSelection)
{
	m_pSelectedBone = a_pSelection;
}

void Bone::SetPivot(float x, float y, float z)
{
	m_v3Pivot.x = x;
	m_v3Pivot.y = y;
	m_v3Pivot.z = z;
}

void Bone::SetDescendants(Bone* a_pParent)
{
	for (int i = 0; i < a_pParent->m_lChildren.size(); i++)
		a_pParent->m_lChildren[i]->currentDescendant = true;
	for (int i = 0; i < a_pParent->m_lChildren.size(); i++)
		SetDescendants(a_pParent->m_lChildren[i]);
}

void Bone::ResetDescendants(Bone* a_pRoot)
{

}


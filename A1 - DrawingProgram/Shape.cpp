#include "Shape.h"
#include <iostream>

Shape::Shape(ShapeType a_eType, ShapeSize a_eSize)
{
	// Init member fields
	m_eType = a_eType;
	m_eSize = a_eSize;
	m_v3Color = new float[3]{ 1.0f, 0.0f, 0.0f };

	// Set max points per shape
	switch (a_eType)
	{
	case Point:
		m_iMaxVertices = 1;
		break;
	case Line:
		m_iMaxVertices = 100;
		break;
	case Triangle:
		m_iMaxVertices = 3;
		break;
	case Quad:
		m_iMaxVertices = 2;
		break;
	case Polygons:
		m_iMaxVertices = 100;
		break;
	}

	// Set shape size based on given enum type
	switch (a_eSize)
	{
	case Small:
		m_fSize = 2.0f;
		break;
	case Medium:
		m_fSize = 5.0f;
		break;
	case Large:
		m_fSize = 10.0f;
		break;
	}
}

Shape::Shape(Shape& a_pOther)
{
	// Copy the color and type
	m_v3Color = a_pOther.m_v3Color;
	m_eType = a_pOther.m_eType;

	// Copy over vertex trackers and completion status
	m_iMaxVertices = a_pOther.m_iMaxVertices;
	m_bIsComplete = a_pOther.m_bIsComplete;

	// Copy vertex data
	m_lVertices = a_pOther.m_lVertices;
}

Shape& Shape::operator=(Shape& a_pOther)
{
	// Make sure you're not copying the same thing
	if (this != &a_pOther)
	{
		// Copy the color and type
		this->m_v3Color = a_pOther.m_v3Color;
		this->m_eType = a_pOther.m_eType;

		// Copy over vertex trackers and completion status
		this->m_iMaxVertices = a_pOther.m_iMaxVertices;
		this->m_bIsComplete = a_pOther.m_bIsComplete;

		// Copy vertex data
		this->m_lVertices = a_pOther.m_lVertices;
	}

	return *this;
}

Shape::~Shape() 
{ 
	// Release used memory from pointers
	Release();
}

void Shape::Release()
{
	// Clear vertex data
	m_lVertices.clear();

	// Delete color data
	delete[] m_v3Color;
	m_v3Color = nullptr;
}

void Shape::AddVertex(float a_fX, float a_fY, float* a_v3Color)
{
	// Return if shape has been completed
	if (m_bIsComplete)
		return;

	// Set the shape's color to what is passed in
	m_v3Color = new float[3]{a_v3Color[0], a_v3Color[1], a_v3Color[2]};

	// Update vertices and complete
	// shape if reached max vertices
	m_lVertices.push_back(a_fX);
	m_lVertices.push_back(a_fY);
	if (m_lVertices.size() / 2 == m_iMaxVertices)
		CompleteShape();
}

void Shape::CompleteShape()
{
	// Set complete flag to true
	m_bIsComplete = true;
}

void Shape::RenderShape(float* a_v2MousePos)
{
	// Set drawing color based on shape color
	if(m_v3Color)
		glColor3fv(m_v3Color);

	// Switch condition for deciding 
	// what type of shape to draw
	switch (m_eType)
	{
	case Point: // Single Point

		// Plot a single point based on chosen size
		glPointSize(m_fSize);
		glBegin(GL_POINTS);
		glVertex2f(m_lVertices[0], m_lVertices[1]);
		glEnd();
		CompleteShape();
		break;
	case Line: // Strip of lines

		// Start showing lines when there are vertices drawn
		if (m_lVertices.size() / 2 > 0)
		{
			glLineWidth(m_fSize);
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < m_lVertices.size(); i += 2)
				glVertex2f(m_lVertices[i], m_lVertices[(i + 1) % m_lVertices.size()]);
			if(!m_bIsComplete) // Show next point if still drawing
				glVertex2fv(a_v2MousePos);
			glEnd();
			glLineWidth(2.0f);
		}
		break;
	case Triangle: // Triangles

		// Outline triangle when plotting points still
		if (m_lVertices.size() / 2 > 0 && m_lVertices.size() / 2 < m_iMaxVertices)
		{
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < m_lVertices.size(); i+=2)
				glVertex2f(m_lVertices[i], m_lVertices[(i + 1) % m_lVertices.size()]);
			glVertex2fv(a_v2MousePos);
			glVertex2f(m_lVertices[0], m_lVertices[1]); // First point in list to close the line strip
			glEnd();
		}
		// Once triangle has all 3 vertices, fill it in
		else if (m_lVertices.size() / 2 == m_iMaxVertices)
		{
			glBegin(GL_TRIANGLES);
			for (int i = 0; i < m_lVertices.size(); i+=2)
				glVertex2f(m_lVertices[i], m_lVertices[(i + 1) % m_lVertices.size()]);
			glEnd();
		}
		break;
	case Quad: // Quads

		// Use line strip to outline box when still deciding on 2nd corner
		if (m_lVertices.size() / 2 == 1)
		{
			glBegin(GL_LINE_STRIP);
			glVertex2f(m_lVertices[0], m_lVertices[1]); // vertex 1
			glVertex2f(a_v2MousePos[0], m_lVertices[1]); // vertex 3
			glVertex2f(a_v2MousePos[0], a_v2MousePos[1]); // vertex 4
			glVertex2f(m_lVertices[0], a_v2MousePos[1]); // vertex 2
			glVertex2f(m_lVertices[0], m_lVertices[1]); // vertex 1
			glEnd();
		}
		// Fill in the quad using the 2 corners
		else if (m_lVertices.size() / 2 == 2)
		{
			glBegin(GL_TRIANGLE_STRIP);
			glVertex2f(m_lVertices[0], m_lVertices[1]); // vertex 1
			glVertex2f(m_lVertices[0], m_lVertices[3]); // vertex 2
			glVertex2f(m_lVertices[2], m_lVertices[1]); // vertex 3
			glVertex2f(m_lVertices[2], m_lVertices[3]); // vertex 4
			glEnd();
			CompleteShape();
		}
		break;
	case Polygons: // Polygons

		// Use line strip when not enough vertices to fill yet
		if (m_lVertices.size() / 2 > 0 && m_lVertices.size() / 2 < 2)
		{
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < m_lVertices.size(); i+=2)
				glVertex2f(m_lVertices[i], m_lVertices[(i + 1) % m_lVertices.size()]);
			glVertex2fv(a_v2MousePos);
			glEnd();
		}
		// Fill in polygon once there is more than one vertex
		else if (m_lVertices.size() / 2 > 1)
		{
			glBegin(GL_POLYGON);
			for (int i = 0; i < m_lVertices.size(); i+=2)
				glVertex2f(m_lVertices[i], m_lVertices[(i + 1) % m_lVertices.size()]);
			if (!m_bIsComplete) // Show next point if still drawing
				glVertex2fv(a_v2MousePos);
			glEnd();
		}
		break;
	}
}

#include "Shape.h"
#include <iostream>

Shape::Shape(ShapeType type, ShapeSize size)
{
	// Init member fields and number of points
	m_eType = type;
	m_eSize = size;
	int numPoints = 0;

	// Set number of points to allocate given type
	switch (type)
	{
	case Point:
		numPoints = 1;
		break;
	case Line:
		numPoints = 100;
		break;
	case Triangle:
		numPoints = 3;
		break;
	case Quad:
		numPoints = 2;
		break;
	case Polygons:
		numPoints = 100;
		break;
	}

	// Set shape size based on given enum type
	switch (size)
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

	// Initialize float array holding 
	// vertex data of positions
	m_aVertices = new float[2 * numPoints];
	m_iMaxVertices = numPoints;
}

Shape::Shape(Shape& other)
{
	// Copy the color and type
	m_v3Color = other.m_v3Color;
	m_eType = other.m_eType;

	// Copy over vertex trackers and completion status
	m_iNumVertices = other.m_iNumVertices;
	m_iMaxVertices = other.m_iMaxVertices;
	m_bIsComplete = other.m_bIsComplete;

	// Copy all vertex data
	std::copy(other.m_aVertices, other.m_aVertices + other.m_iNumVertices, m_aVertices);
}

Shape& Shape::operator=(Shape& other)
{
	// Make sure you're not copying the same thing
	if (this != &other)
	{
		// Copy the color and type
		this->m_v3Color = other.m_v3Color;
		this->m_eType = other.m_eType;

		// Copy over vertex trackers and completion status
		this->m_iNumVertices = other.m_iNumVertices;
		this->m_iMaxVertices = other.m_iMaxVertices;
		this->m_bIsComplete = other.m_bIsComplete;

		// Copy all vertex data
		std::copy(other.m_aVertices, other.m_aVertices + other.m_iNumVertices, this->m_aVertices);
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
	// Delete vertex data
	delete[] m_aVertices;
	m_aVertices = nullptr;

	// Delete color data
	delete[] m_v3Color;
	m_v3Color = nullptr;
}

void Shape::AddVertex(float x, float y, float* color)
{
	// Return if shape has been completed
	if (m_bIsComplete)
		return;

	// Add vertices to vertex array
	m_aVertices[m_iNumVertices * 2] = x;
	m_aVertices[(m_iNumVertices * 2) + 1] = y;

	// Set the shape's color to what is passed in
	m_v3Color = new float[3]{color[0], color[1], color[2]};

	// Update vertices and complete
	// shape if reached max vertices
	m_iNumVertices++;
	if (m_iNumVertices == m_iMaxVertices)
		CompleteShape();
}

void Shape::CompleteShape()
{
	// Set complete flag to true
	m_bIsComplete = true;
}

void Shape::RenderShape(float* mousePos)
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
		glVertex2f(m_aVertices[0], m_aVertices[1]);
		glEnd();
		CompleteShape();
		break;
	case Line: // Strip of lines

		// Start showing lines when there is more than one vertex
		if (m_iNumVertices > 1)
		{
			glLineWidth(m_fSize);
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < m_iNumVertices; i++)
				glVertex2fv(m_aVertices + i * 2);
			glVertex2fv(mousePos);
			glEnd();
		}
		break;
	case Triangle: // Triangles

		// Outline triangle when plotting points still
		if (m_iNumVertices > 0 && m_iNumVertices < m_iMaxVertices)
		{
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < m_iNumVertices; i++)
				glVertex2fv(m_aVertices + i * 2);
			glVertex2fv(mousePos);
			glVertex2f(m_aVertices[0], m_aVertices[1]);
			glEnd();
		}
		// Once triangle has all 3 vertices, fill it in
		else if (m_iNumVertices == m_iMaxVertices)
		{
			glBegin(GL_TRIANGLES);
			for (int i = 0; i < m_iNumVertices; i++)
				glVertex2fv(m_aVertices + i * 2);
			glEnd();
		}
		break;
	case Quad: // Quads

		// Use line strip to outline box when still deciding on 2nd corner
		if (m_iNumVertices == 1)
		{
			glBegin(GL_LINE_STRIP);
			glVertex2f(m_aVertices[0], m_aVertices[1]); // vertex 1
			glVertex2f(mousePos[0], m_aVertices[1]); // vertex 3
			glVertex2f(mousePos[0], mousePos[1]); // vertex 4
			glVertex2f(m_aVertices[0], mousePos[1]); // vertex 2
			glVertex2f(m_aVertices[0], m_aVertices[1]); // vertex 1
			glEnd();
		}
		// Fill in the quad using the 2 corners
		else if (m_iNumVertices == 2)
		{
			glBegin(GL_TRIANGLE_STRIP);
			glVertex2f(m_aVertices[0], m_aVertices[1]); // vertex 1
			glVertex2f(m_aVertices[0], m_aVertices[3]); // vertex 2
			glVertex2f(m_aVertices[2], m_aVertices[1]); // vertex 3
			glVertex2f(m_aVertices[2], m_aVertices[3]); // vertex 4
			glEnd();
			CompleteShape();
		}
		break;
	case Polygons: // Polygons

		// Use line strip when not enough vertices to fill yet
		if (m_iNumVertices > 0 && m_iNumVertices < 2) 
		{
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < m_iNumVertices; i++)
				glVertex2fv(m_aVertices + i * 2);
			glVertex2fv(mousePos);
			glEnd();
		}
		// Fill in polygon once there is more than one vertex
		else if (m_iNumVertices > 1)
		{
			glBegin(GL_POLYGON);
			for (int i = 0; i < m_iNumVertices; i++)
				glVertex2fv(m_aVertices + i * 2);
			glVertex2fv(mousePos);
			glEnd();
		}
		break;
	}
}

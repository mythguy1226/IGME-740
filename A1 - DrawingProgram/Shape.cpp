#include "Shape.h"
#include <iostream>

void Shape::Init()
{

}

void Shape::Release()
{
	delete[] m_aVertices;
	m_aVertices = nullptr;

	delete[] m_v3Color;
	m_v3Color = nullptr;
}

Shape::Shape(ShapeType type)
{
	m_eType = type;

	int numPoints = 0;

	// Set number of points to allocate given type
	switch (type)
	{
	case Point:
		numPoints = 1;
		break;
	case Line:
		numPoints = 40;
		break;
	case Triangle:
		numPoints = 3;
		break;
	case Quad:
		numPoints = 4;
		break;
	case Polygons:
		numPoints = 40;
		break;
	}

	m_aVertices = new float[2 * numPoints];
	maxVertices = numPoints;
}

Shape::Shape(Shape& other)
{

}

Shape& Shape::operator=(Shape& other)
{
	return *this;
	// TODO: insert return statement here
}

Shape::~Shape() 
{ 
	Release();
}

void Shape::AddVertex(float x, float y, float* color)
{
	// Return if shape has been completed
	if (m_bIsComplete)
		return;

	// Add vertices to vertex array
	m_aVertices[numVertices * 2] = x;
	m_aVertices[(numVertices * 2) + 1] = y;

	// Set the shape's color to what is passed in
	m_v3Color = new float[3]{color[0], color[1], color[2]};

	// Update vertices and complete
	// shape if reached max vertices
	numVertices++;
	if (numVertices == maxVertices)
		CompleteShape();
}

void Shape::CompleteShape()
{
	m_bIsComplete = true;
}

void Shape::RenderShape(float* mousePos)
{
	if(m_v3Color)
		glColor3fv(m_v3Color);

	switch (m_eType)
	{
	case Point:
		glBegin(GL_POINTS);
		glVertex2f(m_aVertices[0], m_aVertices[1]);
		glEnd();
		CompleteShape();
		break;
	case Line:
		if (numVertices > 1)
		{
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < numVertices; i++)
				glVertex2fv(m_aVertices + i * 2);
			glVertex2fv(mousePos);
			glEnd();
		}
		break;
	case Triangle:
		if (numVertices > 0 && numVertices < maxVertices)
		{
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < numVertices; i++)
				glVertex2fv(m_aVertices + i * 2);
			glVertex2fv(mousePos);
			glEnd();
		}
		else if (numVertices == maxVertices) // Generate the triangle
		{
			glBegin(GL_TRIANGLES);
			for (int i = 0; i < numVertices; i++)
				glVertex2fv(m_aVertices + i * 2);
			glEnd();
		}
		break;
	case Quad:
		if (numVertices == 1)
		{
			glBegin(GL_LINE_STRIP);
			glVertex2f(m_aVertices[0], m_aVertices[1]); // vertex 1
			glVertex2f(mousePos[0], m_aVertices[1]); // vertex 3
			glVertex2f(mousePos[0], mousePos[1]); // vertex 4
			glVertex2f(m_aVertices[0], mousePos[1]); // vertex 2
			glVertex2f(m_aVertices[0], m_aVertices[1]); // vertex 1
			glEnd();
		}
		else if (numVertices == 2)
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
	case Polygons:
		if (numVertices > 0 && numVertices < 2)
		{
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < numVertices; i++)
				glVertex2fv(m_aVertices + i * 2);
			glVertex2fv(mousePos);
			glEnd();
		}
		else if (numVertices > 1) // Generate the triangle
		{
			glBegin(GL_POLYGON);
			for (int i = 0; i < numVertices; i++)
				glVertex2fv(m_aVertices + i * 2);
			glVertex2fv(mousePos);
			glEnd();
		}
		break;
	}
}

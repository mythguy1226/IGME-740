#ifndef __SHAPE__
#define __SHAPE__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

enum ShapeType
{
	Point,
	Line,
	Triangle,
	Quad,
	Polygons,
	None,
};

class Shape
{
	
public:
	float* m_aVertices;
	int numVertices = 0;
	int maxVertices = 0;
	bool m_bIsComplete = false;
	float* m_v3Color;
	ShapeType m_eType;

	void Init();
	void Release();

	Shape(ShapeType type);

	Shape(Shape& other);
	Shape& operator=(Shape& other);
	~Shape();

	void AddVertex(float x, float y, float* color);
	void CompleteShape();

	void RenderShape(float* mousePos);
};

#endif // __SHAPE__
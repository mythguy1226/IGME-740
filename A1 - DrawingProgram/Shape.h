#ifndef __SHAPE__
#define __SHAPE__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

// Enum used for indicating type of shape being drawn
enum ShapeType
{
	Point,
	Line,
	Triangle,
	Quad,
	Polygons,
	None,
};

// Enum used for indicating size for certain shapes
enum ShapeSize
{
	Small,
	Medium,
	Large,
};

// Typedefs needed within and from including this header
typedef unsigned int uint;

class Shape
{
	// Array of all floats in the shape
	float* m_aVertices;

	// Tracker for current number of drawn vertices
	// and max amount of vertices allocated to this object
	int m_iNumVertices = 0;
	int m_iMaxVertices = 0;

public:
	// Flag for indicating whether to keep drawing or not
	bool m_bIsComplete = false;

	// Color, shape type
	float* m_v3Color;
	ShapeType m_eType;

	// Size variables
	ShapeSize m_eSize = ShapeSize::Small;
	GLfloat m_fSize = 2.0f;

	// Constructor
	Shape(ShapeType type, ShapeSize size);

	// Rule of 3 (Copy Constructor/Copy Assignment Operator/Destructor)
	Shape(Shape& other);
	Shape& operator=(Shape& other);
	~Shape();

	// Cleans up pointers held in this object
	void Release();

	// Method used for adding a point to the shape 
	// and indicating current color of the shape
	void AddVertex(float x, float y, float* color);
	
	// Method used for updating completion flag
	void CompleteShape();

	// Method used for rendering shape at display time
	void RenderShape(float* mousePos);
};

#endif // __SHAPE__
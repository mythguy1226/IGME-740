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

/* CLASS: Shape
 * USAGE: Class utilized for storing shape object data and 
 * rendering shape instances
 */
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
	Shape(ShapeType a_eType, ShapeSize a_eSize);

	// Rule of 3 (Copy Constructor/Copy Assignment Operator/Destructor)
	Shape(Shape& a_pOther);
	Shape& operator=(Shape& a_pOther);
	~Shape();

	// Cleans up pointers held in this object
	void Release();

	// Method used for adding a point to the shape 
	// and indicating current color of the shape
	void AddVertex(float a_fX, float a_fY, float* a_v3Color);
	
	// Method used for updating completion flag
	void CompleteShape();

	// Method used for rendering shape at display time
	void RenderShape(float* a_v2MousePos);
};

#endif // __SHAPE__
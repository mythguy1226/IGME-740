#pragma once

#include "Shape.h"
#include <vector>

/* CLASS: ShapeManager
 * USAGE: Singleton class used for handling shape storage and
 * fields used for drawing such as object type and size
 */
class ShapeManager
{
	// Private fields used for handling drawing
	// and storing of shapes
	ShapeType m_eCurrentObjectType = ShapeType::None;
	ShapeSize m_eCurrentObjectSize = ShapeSize::Small;
	Shape* m_pCurrentShape = nullptr;
	std::vector<Shape*> m_lShapes;

	// Method used for initializing object fields
	void Init();

	// Constructor/Destructor
	ShapeManager();
	~ShapeManager();
public:
	
	// Method used for getting singleton instance
	static ShapeManager* GetInstance();

	// Method used for releasing pointer memory
	// and other cleanup
	void Release();

	// Method used for rendering all shapes in list
	void DisplayAllShapes(float* a_v2MousePos);

	// Methods called upon when drawing shapes
	void CreateShape();
	void AddShapePoint(float* a_v2MousePos, float* a_v3Color);

	// Access modifiers for current shape
	Shape* GetCurrentShape();
	void SetCurrentShape(Shape* a_pShape);

	// Access modifiers for selected object type
	ShapeType GetObjectType();
	void SetObjectType(ShapeType a_eType);

	// Access modifiers for selected object size
	ShapeSize GetObjectSize();
	void SetObjectSize(ShapeSize a_eSize);
};


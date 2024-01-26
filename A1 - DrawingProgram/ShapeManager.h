#pragma once

#include "Shape.h"
#include <vector>

class ShapeManager
{
	ShapeType m_eCurrentObjectType = ShapeType::None;
	ShapeSize m_eCurrentObjectSize = ShapeSize::Small;
	Shape* m_pCurrentShape = nullptr;
	std::vector<Shape*> m_lShapes;

	void Init();
	ShapeManager();
	~ShapeManager();
public:
	
	static ShapeManager* GetInstance();
	void Release();

	void DisplayAllShapes(float* mousePos);

	Shape* GetCurrentShape();

	ShapeType GetObjectType();

	void SetObjectType(ShapeType a_eType);

	void SetObjectSize(ShapeSize a_eSize);

	void CreateShape();

	void AddShapePoint(float* mousePos, float* color);
};


#include "ShapeManager.h"

void ShapeManager::Init()
{
	ShapeType m_eCurrentObjectType = ShapeType::None;
	ShapeSize m_eCurrentObjectSize = ShapeSize::Small;
	Shape* m_pCurrentShape = nullptr;
	std::vector<Shape*> m_lShapes = std::vector<Shape*>();
}

ShapeManager::ShapeManager()
{
	Init();
}

ShapeManager::~ShapeManager()
{
	Release();
}

ShapeManager* ShapeManager::GetInstance()
{
	// Instantiate static instance of manager
	static ShapeManager pShapeMngr;

	return &pShapeMngr;
}

void ShapeManager::Release()
{
	// Clear all shapes
	m_lShapes.clear();

	// Release current shape
	delete m_pCurrentShape;
	m_pCurrentShape = nullptr;
}

void ShapeManager::DisplayAllShapes(float* mousePos)
{
	// Iterate through each shape and call its render method
	for (Shape* pShape : m_lShapes)
	{
		pShape->RenderShape(mousePos);
	}
}

Shape* ShapeManager::GetCurrentShape()
{
	return m_pCurrentShape;
}

ShapeType ShapeManager::GetObjectType()
{
	return m_eCurrentObjectType;
}

void ShapeManager::SetObjectType(ShapeType a_eType)
{
	// If currently being drawn then return
	if (m_pCurrentShape)
		if (!m_pCurrentShape->m_bIsComplete)
			return;

	m_eCurrentObjectType = a_eType;
}

void ShapeManager::SetObjectSize(ShapeSize a_eSize)
{
	// Set the new size
	m_eCurrentObjectSize = a_eSize;
}

void ShapeManager::CreateShape()
{
	// Instantiate shape and add to list
	if (!m_pCurrentShape)
	{
		m_pCurrentShape = new Shape(m_eCurrentObjectType, m_eCurrentObjectSize);
		m_lShapes.push_back(m_pCurrentShape);
	}
}

void ShapeManager::AddShapePoint(float* mousePos, float* color)
{
	// Return if null
	if (!m_pCurrentShape)
		return;

	// Add a vertex to the new shape
	m_pCurrentShape->AddVertex(mousePos[0], mousePos[1], color);

	// Once shape is complete set
	// current to a new shape and add to list
	if (m_pCurrentShape->m_bIsComplete)
	{
		m_pCurrentShape = nullptr;
	}
}

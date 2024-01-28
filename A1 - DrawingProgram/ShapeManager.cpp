#include "ShapeManager.h"

void ShapeManager::Init()
{
	// Set defaults and initialize needed fields
	ShapeType m_eCurrentObjectType = ShapeType::None;
	ShapeSize m_eCurrentObjectSize = ShapeSize::Small;
	Shape* m_pCurrentShape = nullptr;
	std::vector<Shape*> m_lShapes = std::vector<Shape*>();
}

ShapeManager::ShapeManager()
{
	// Initialize object fields
	Init();
}

ShapeManager::~ShapeManager()
{
	// Release pointer memory and clear out list
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

void ShapeManager::DisplayAllShapes(float* a_v2MousePos)
{
	// Iterate through each shape and call its render method
	for (Shape* pShape : m_lShapes)
	{
		pShape->RenderShape(a_v2MousePos);
	}
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

void ShapeManager::AddShapePoint(float* a_v2MousePos, float* a_v3Color)
{
	// Return if null
	if (!m_pCurrentShape)
		return;

	// Add a vertex to the new shape
	m_pCurrentShape->AddVertex(a_v2MousePos[0], a_v2MousePos[1], a_v3Color);

	// Once shape is complete set
	// current to a new shape and add to list
	if (m_pCurrentShape->m_bIsComplete)
	{
		m_pCurrentShape = nullptr;
	}
}

Shape* ShapeManager::GetCurrentShape()
{
	// Return current shape being drawn
	return m_pCurrentShape;
}

void ShapeManager::SetCurrentShape(Shape* a_pShape)
{
	// Set the current shape
	m_pCurrentShape = a_pShape;
}

ShapeType ShapeManager::GetObjectType()
{
	// Return selected object type
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

ShapeSize ShapeManager::GetObjectSize()
{
	// Return selected object size
	return m_eCurrentObjectSize;
}

void ShapeManager::SetObjectSize(ShapeSize a_eSize)
{
	// Set the new size
	m_eCurrentObjectSize = a_eSize;
}

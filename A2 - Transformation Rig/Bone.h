#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

// Define math specific typedefs
typedef glm::vec3 vector3;

class Bone
{
public:
	// Transform information
	vector3 m_v3Position = vector3();
	float m_fRotation = 0.0f;
	vector3 m_v3Scale = vector3();
	vector3 m_v3Pivot = vector3();

	// Parent and child bones
	Bone* m_pParent = nullptr;
	std::vector<Bone*> m_lChildren;

	// Constructor
	Bone();

	// Destructor/Release
	~Bone();
	void Release();

	// Method used for drawing rectangle to display bone
	void drawRect(vector3 a_v3Size, vector3 a_v3Color);

	// Getter/Setter methods for parent/children
	Bone* GetParent();
	void SetParent(Bone* a_pParent);
	void AddChild(Bone* a_pChild);

	// Getter/Setter methods for transform
	float GetRotation();
	void SetPosition(float x, float y, float z);
	void SetRotation(float angle);
	void SetScale(float x, float y, float z);
	void SetSelected(Bone* a_pSelection);
	void SetPivot(float x, float y, float z);

	// Returns which color to render bone in
	vector3 DetermineColor();
};

// Selected Bone
static Bone* m_pSelectedBone = nullptr;


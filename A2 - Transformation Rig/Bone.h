#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_access.hpp"

// Define math specific typedefs
typedef glm::vec2 vector2;
typedef glm::vec3 vector3;


class Bone
{
	// Parent and child bones
	Bone* m_pParent = nullptr;


	// Transform information
	vector3 m_v3Position = vector3();
	float m_fRotation = 0.0f;
	float m_fPrevRotation = 0.0f;
	vector3 m_v3Scale = vector3();

	// Pivot
	vector3 m_v3Pivot = vector3();


public:
	std::vector<Bone*> m_lChildren;
	bool currentDescendant = false;
	Bone();

	void drawRect(vector3 a_v3Size, vector3 a_v3Color);
	void RenderBone();

	Bone* GetParent();


	void SetParent(Bone* a_pParent);
	void AddChild(Bone* a_pChild);
	void RemoveChild(Bone* a_pChild);

	float GetRotation();

	void SetPosition(float x, float y, float z);
	void SetRotation(float angle);
	void SetScale(float x, float y, float z);

	void SetSelected(Bone* a_pSelection);

	void SetPivot(float x, float y, float z);

	void SetDescendants(Bone* a_pParent);
	void ResetDescendants(Bone* a_pRoot);
};

// Selected Bone
static Bone* m_pSelectedBone = nullptr;


#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

// Define math specific typedefs
typedef glm::vec2 vector2;
typedef glm::vec3 vector3;

class Bone
{
	// Parent and child bones
	Bone* m_pParent = nullptr;
	std::vector<Bone*> m_lChildren;

	// Transform information
	vector3 m_v3Position;
	float m_fRotation;
	vector3 m_v3Scale;

public:
	Bone();

	void drawRect(float size, vector3 a_v3Color);
	void RenderBone();

	void SetParent(Bone* a_pParent);
	void AddChild(Bone* a_pChild);
	void RemoveChild(Bone* a_pChild);

	float GetRotation();

	void SetPosition(float x, float y, float z);
	void SetRotation(float angle);
	void SetScale(float x, float y, float z);
};


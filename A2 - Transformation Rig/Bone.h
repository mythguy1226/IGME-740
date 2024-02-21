#pragma once
#include <vector>

class Bone
{
	// Parent and child bones
	Bone* m_pParent = nullptr;
	std::vector<Bone*> m_lChildren;

	// Transform information
	float* m_pPosition;
	float m_fRotation;
	float* m_pScale;

public:
	Bone();

	void drawRect(float size, const float* c);
	void RenderBone();

	void SetParent(Bone* a_pParent);
	void AddChild(Bone* a_pChild);
	void RemoveChild(Bone* a_pChild);

	void SetPosition(float x, float y, float z);
	void SetRotation(float angle);
	void SetScale(float x, float y, float z);
};


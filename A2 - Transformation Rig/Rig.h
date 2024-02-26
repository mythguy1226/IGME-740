#pragma once

#include "Bone.h"

class Rig
{

public:
	// Root and selected bone references
	Bone* m_pRoot;
	Bone* selectedBone;

	// Constructor
	Rig();

	// Destructor/Release
	~Rig();
	void Release();

	// Methods for managing bones construction and
	// display in rig
	void ConstructRig();
	void RenderRig();
	void UpdateBoneRotations(float a_fAngle);

	// Methods used for managing selected bone in rig
	void SelectBone(Bone* a_pBone);
	int m_iCurrentChildIndex = 0;
	void SelectParent();
	void SelectFirstChild();
	void SelectNextChild(int a_iIndexChange);
};


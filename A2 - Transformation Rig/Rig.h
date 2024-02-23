#pragma once

#include "Bone.h"

class Rig
{

public:
	Bone* m_pRoot;
	Bone* selectedBone;
	Rig();

	void ConstructRig();
	void UpdateBoneRotations(float a_fAngle);

	void SelectBone(Bone* a_pBone);
	int m_iCurrentChildIndex = 0;
	void SelectParent();
	void SelectFirstChild();
	void SelectNextChild(int a_iIndexChange);
};


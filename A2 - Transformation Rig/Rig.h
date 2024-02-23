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
};


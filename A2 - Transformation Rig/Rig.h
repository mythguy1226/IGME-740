#pragma once

#include "Bone.h"
class Rig
{

public:
	Bone* m_pRoot;
	Rig();

	void AddBone(Bone* a_pBone);
};


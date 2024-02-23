#include "Rig.h"

Rig::Rig()
{
	m_pRoot = new Bone();
	selectedBone = m_pRoot;
	selectedBone->SetSelected(true);
}

void Rig::ConstructRig()
{
	// Set position, pivot, and scale of root bone
	// AKA the torso
	m_pRoot->SetPosition(0.0f, -1.0f, 0.0f);
	m_pRoot->SetPivot(0.0f, -2.0f, 0.0f);
	m_pRoot->SetScale(1.25f, 1.0f, 1.0f);

	// Chest
	Bone* chestBone = new Bone();
	chestBone->SetParent(m_pRoot);
	chestBone->SetPosition(0.0f, 1.0f, 0.0f);
	chestBone->SetPivot(0.0f, 0.0f, 0.0f);
	chestBone->SetScale(2.0f, 1.0f, 1.0f);

	//// Neck
	Bone* neckBone = new Bone();
	neckBone->SetParent(m_pRoot);
	neckBone->SetPosition(0.0f, 3.0f, 0.0f);
	neckBone->SetPivot(0.0f, 2.0f, 0.0f);
	neckBone->SetScale(0.25f, 0.5f, 1.0f);
	
	// Head
	Bone* headBone = new Bone();
	headBone->SetParent(neckBone);
	headBone->SetPosition(0.0f, 4.0f, 0.0f);
	headBone->SetPivot(0.0f, 3.0f, 0.0f);
	headBone->SetScale(1.0f, 1.0f, 1.0f);

	//// Left Arm 1
	Bone* leftA1Bone = new Bone();
	leftA1Bone->SetParent(chestBone);
	leftA1Bone->SetPosition(-3.0f, 1.0f, 0.0f);
	leftA1Bone->SetPivot(-2.0f, 1.0f, 0.0f);
	leftA1Bone->SetScale(1.0f, 0.5f, 1.0f);
	
	// Left Arm 2
	Bone* leftA2Bone = new Bone();
	leftA2Bone->SetParent(leftA1Bone);
	leftA2Bone->SetPosition(-5.0f, 1.0f, 0.0f);
	leftA2Bone->SetPivot(-4.0f, 1.0f, 0.0f);
	leftA2Bone->SetScale(1.0f, 0.5f, 1.0f);
	
	// Left Hand
	Bone* leftHandBone = new Bone();
	leftHandBone->SetParent(leftA2Bone);
	leftHandBone->SetPosition(-7.0f, 1.0f, 0.0f);
	leftHandBone->SetPivot(-6.0f, 1.0f, 0.0f);
	leftHandBone->SetScale(1.0f, 1.0f, 1.0f);

	selectedBone->SetSelected(false);
	selectedBone = leftA1Bone;
	selectedBone->SetSelected(true);
	
	//// Right Arm 1
	//Bone* rightA1Bone = new Bone();
	//rightA1Bone->SetParent(m_pRoot);
	//rightA1Bone->SetPosition(3.0f, 2.0f, 0.0f);
	//rightA1Bone->SetScale(1.0f, 0.5f, 1.0f);
	//
	//// Right Arm 2
	//Bone* rightA2Bone = new Bone();
	//rightA2Bone->SetParent(rightA1Bone);
	//rightA2Bone->SetPosition(5.0f, 2.0f, 0.0f);
	//rightA2Bone->SetScale(1.0f, 0.5f, 1.0f);
	//
	//// Right Hand
	//Bone* rightHandBone = new Bone();
	//rightHandBone->SetParent(rightA2Bone);
	//rightHandBone->SetPosition(7.0f, 1.0f, 0.0f);
	//rightHandBone->SetScale(1.0f, 1.0f, 1.0f);
	//
	//// Left Leg 1
	//Bone* leftL1Bone = new Bone();
	//leftL1Bone->SetParent(torsoBone);
	//leftL1Bone->SetPosition(-1.5f, -3.0f, 0.0f);
	//leftL1Bone->SetScale(0.5f, 1.0f, 1.0f);
	//
	//// Left Leg 2
	//Bone* leftL2Bone = new Bone();
	//leftL2Bone->SetParent(leftL1Bone);
	//leftL2Bone->SetPosition(-1.5f, -5.0f, 0.0f);
	//leftL2Bone->SetScale(0.5f, 1.0f, 1.0f);
	//
	//// Left Foot
	//Bone* leftFootBone = new Bone();
	//leftFootBone->SetParent(leftL2Bone);
	//leftFootBone->SetPosition(-1.2f, -13.0f, 0.0f);
	//leftFootBone->SetScale(1.0f, 0.5f, 1.0f);
	//
	//// Right Leg 1
	//Bone* rightL1Bone = new Bone();
	//rightL1Bone->SetParent(torsoBone);
	//rightL1Bone->SetPosition(1.5f, -3.0f, 0.0f);
	//rightL1Bone->SetScale(0.5f, 1.0f, 1.0f);
	//
	//// Right Leg 2
	//Bone* rightL2Bone = new Bone();
	//rightL2Bone->SetParent(rightL1Bone);
	//rightL2Bone->SetPosition(1.5f, -5.0f, 0.0f);
	//rightL2Bone->SetScale(0.5f, 1.0f, 1.0f);
	//
	//// Right Foot
	//Bone* rightFootBone = new Bone();
	//rightFootBone->SetParent(rightL2Bone);
	//rightFootBone->SetPosition(1.2f, -13.0f, 0.0f);
	//rightFootBone->SetScale(1.0f, 0.5f, 1.0f);

}

void Rig::UpdateBoneRotations(float a_fAngle)
{
	selectedBone->SetRotation(selectedBone->GetRotation() + a_fAngle);
}



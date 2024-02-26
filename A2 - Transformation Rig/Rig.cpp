#include "Rig.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

Rig::Rig()
{
	// Make root bone and select by default
	m_pRoot = new Bone();
	SelectBone(m_pRoot);
}

Rig::~Rig()
{
	Release();
}

void Rig::Release()
{
	// Clean up all pointers here
	if(selectedBone)
		delete selectedBone;
	selectedBone = nullptr;

	if(m_pRoot)
		delete m_pRoot;
	m_pRoot = nullptr;
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
	chestBone->SetPosition(0.0f, 2.0f, 0.0f);
	chestBone->SetPivot(0.0f, 1.0f, 0.0f);
	chestBone->SetScale(2.0f, 1.0f, 1.0f);

	//// Neck
	Bone* neckBone = new Bone();
	neckBone->SetParent(chestBone);
	neckBone->SetPosition(0.0f, 1.5f, 0.0f);
	neckBone->SetPivot(0.0f, 1.0f, 0.0f);
	neckBone->SetScale(0.25f, 0.5f, 1.0f);
	
	// Head
	Bone* headBone = new Bone();
	headBone->SetParent(neckBone);
	headBone->SetPosition(0.0f, 1.5f, 0.0f);
	headBone->SetPivot(0.0f, 0.5f, 0.0f);
	headBone->SetScale(1.0f, 1.0f, 1.0f);

	//// Left Arm 1
	Bone* leftA1Bone = new Bone();
	leftA1Bone->SetParent(chestBone);
	leftA1Bone->SetPosition(-3.0f, 0.0f, 0.0f);
	leftA1Bone->SetPivot(-2.0f, 0.0f, 0.0f);
	leftA1Bone->SetScale(1.0f, 0.5f, 1.0f);
	
	// Left Arm 2
	Bone* leftA2Bone = new Bone();
	leftA2Bone->SetParent(leftA1Bone);
	leftA2Bone->SetPosition(-2.0f, 0.0f, 0.0f);
	leftA2Bone->SetPivot(-1.0f, 0.0f, 0.0f);
	leftA2Bone->SetScale(1.0f, 0.5f, 1.0f);
	
	// Left Hand
	Bone* leftHandBone = new Bone();
	leftHandBone->SetParent(leftA2Bone);
	leftHandBone->SetPosition(-2.0f, 0.0f, 0.0f);
	leftHandBone->SetPivot(-1.0f, 0.0f, 0.0f);
	leftHandBone->SetScale(1.0f, 1.0f, 1.0f);
	
	// Right Arm 1
	Bone* rightA1Bone = new Bone();
	rightA1Bone->SetParent(chestBone);
	rightA1Bone->SetPosition(3.0f, 0.0f, 0.0f);
	rightA1Bone->SetPivot(2.0f, 0.0f, 0.0f);
	rightA1Bone->SetScale(1.0f, 0.5f, 1.0f);

	// Right Arm 2
	Bone* rightA2Bone = new Bone();
	rightA2Bone->SetParent(rightA1Bone);
	rightA2Bone->SetPosition(2.0f, 0.0f, 0.0f);
	rightA2Bone->SetPivot(1.0f, 0.0f, 0.0f);
	rightA2Bone->SetScale(1.0f, 0.5f, 1.0f);

	// Right Hand
	Bone* rightHandBone = new Bone();
	rightHandBone->SetParent(rightA2Bone);
	rightHandBone->SetPosition(2.0f, 0.0f, 0.0f);
	rightHandBone->SetPivot(1.0f, 0.0f, 0.0f);
	rightHandBone->SetScale(1.0f, 1.0f, 1.0f);
	
	// Left Leg 1
	Bone* leftL1Bone = new Bone();
	leftL1Bone->SetParent(m_pRoot);
	leftL1Bone->SetPosition(-0.75f, -2.0f, 0.0f);
	leftL1Bone->SetPivot(-0.75f, -1.0f, 0.0f);
	leftL1Bone->SetScale(0.5f, 1.0f, 1.0f);
	
	// Left Leg 2
	Bone* leftL2Bone = new Bone();
	leftL2Bone->SetParent(leftL1Bone);
	leftL2Bone->SetPosition(0.0f, -2.0f, 0.0f);
	leftL2Bone->SetPivot(0.0f, -1.0f, 0.0f);
	leftL2Bone->SetScale(0.5f, 1.0f, 1.0f);
	
	// Left Foot
	Bone* leftFootBone = new Bone();
	leftFootBone->SetParent(leftL2Bone);
	leftFootBone->SetPosition(-0.5f, -1.5f, 0.0f);
	leftFootBone->SetPivot(0.0f, -1.0f, 0.0f);
	leftFootBone->SetScale(1.0f, 0.5f, 1.0f);
	
	// Right Leg 1
	Bone* rightL1Bone = new Bone();
	rightL1Bone->SetParent(m_pRoot);
	rightL1Bone->SetPosition(0.75f, -2.0f, 0.0f);
	rightL1Bone->SetPivot(0.75f, -1.0f, 0.0f);
	rightL1Bone->SetScale(0.5f, 1.0f, 1.0f);
	
	// Right Leg 2
	Bone* rightL2Bone = new Bone();
	rightL2Bone->SetParent(rightL1Bone);
	rightL2Bone->SetPosition(0.0f, -2.0f, 0.0f);
	rightL2Bone->SetPivot(0.0f, -1.0f, 0.0f);
	rightL2Bone->SetScale(0.5f, 1.0f, 1.0f);
	
	// Right Foot
	Bone* rightFootBone = new Bone();
	rightFootBone->SetParent(rightL2Bone);
	rightFootBone->SetPosition(0.5f, -1.5f, 0.0f);
	rightFootBone->SetPivot(0.0f, -1.0f, 0.0f);
	rightFootBone->SetScale(1.0f, 0.5f, 1.0f);
}

void Rig::RenderRig()
{
	glPushMatrix(); // Global space/ torso area

	// Display torso bone
	glTranslatef(m_pRoot->m_v3Pivot.x, m_pRoot->m_v3Pivot.y, m_pRoot->m_v3Pivot.z);
	glRotatef(m_pRoot->m_fRotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-m_pRoot->m_v3Pivot.x, -m_pRoot->m_v3Pivot.y, -m_pRoot->m_v3Pivot.z);

	glTranslatef(m_pRoot->m_v3Position.x, m_pRoot->m_v3Position.y, m_pRoot->m_v3Position.z);
	m_pRoot->drawRect(m_pRoot->m_v3Scale, m_pRoot->DetermineColor());

	glPushMatrix(); // Chest bone area

	// Display chest bone
	Bone* chestBone = m_pRoot->m_lChildren[0];
	glTranslatef(chestBone->m_v3Pivot.x, chestBone->m_v3Pivot.y, chestBone->m_v3Pivot.z);
	glRotatef(chestBone->m_fRotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-chestBone->m_v3Pivot.x, -chestBone->m_v3Pivot.y, -chestBone->m_v3Pivot.z);

	glTranslatef(chestBone->m_v3Position.x, chestBone->m_v3Position.y, chestBone->m_v3Position.z);
	m_pRoot->drawRect(chestBone->m_v3Scale, chestBone->DetermineColor());

	glPushMatrix(); // Left arm

	// Display left arm bone 1
	Bone* leftA1Bone = chestBone->m_lChildren[1];
	glTranslatef(leftA1Bone->m_v3Pivot.x, leftA1Bone->m_v3Pivot.y, leftA1Bone->m_v3Pivot.z);
	glRotatef(leftA1Bone->m_fRotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-leftA1Bone->m_v3Pivot.x, -leftA1Bone->m_v3Pivot.y, -leftA1Bone->m_v3Pivot.z);

	glTranslatef(leftA1Bone->m_v3Position.x, leftA1Bone->m_v3Position.y, leftA1Bone->m_v3Position.z);
	m_pRoot->drawRect(leftA1Bone->m_v3Scale, leftA1Bone->DetermineColor());

	// Display left arm bone 2
	Bone* leftA2Bone = leftA1Bone->m_lChildren[0];
	glTranslatef(leftA2Bone->m_v3Pivot.x, leftA2Bone->m_v3Pivot.y, leftA2Bone->m_v3Pivot.z);
	glRotatef(leftA2Bone->m_fRotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-leftA2Bone->m_v3Pivot.x, -leftA2Bone->m_v3Pivot.y, -leftA2Bone->m_v3Pivot.z);

	glTranslatef(leftA2Bone->m_v3Position.x, leftA2Bone->m_v3Position.y, leftA2Bone->m_v3Position.z);
	m_pRoot->drawRect(leftA2Bone->m_v3Scale, leftA2Bone->DetermineColor());

	// Display left hand bone
	Bone* leftHandBone = leftA2Bone->m_lChildren[0];
	glTranslatef(leftHandBone->m_v3Pivot.x, leftHandBone->m_v3Pivot.y, leftHandBone->m_v3Pivot.z);
	glRotatef(leftHandBone->m_fRotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-leftHandBone->m_v3Pivot.x, -leftHandBone->m_v3Pivot.y, -leftHandBone->m_v3Pivot.z);

	glTranslatef(leftHandBone->m_v3Position.x, leftHandBone->m_v3Position.y, leftHandBone->m_v3Position.z);
	m_pRoot->drawRect(leftHandBone->m_v3Scale, leftHandBone->DetermineColor());

	glPopMatrix(); // Back to chest area

	glPushMatrix(); // Right arm

	// Display right arm bone 1
	Bone* rightA1Bone = chestBone->m_lChildren[2];
	glTranslatef(rightA1Bone->m_v3Pivot.x, rightA1Bone->m_v3Pivot.y, rightA1Bone->m_v3Pivot.z);
	glRotatef(rightA1Bone->m_fRotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-rightA1Bone->m_v3Pivot.x, -rightA1Bone->m_v3Pivot.y, -rightA1Bone->m_v3Pivot.z);

	glTranslatef(rightA1Bone->m_v3Position.x, rightA1Bone->m_v3Position.y, rightA1Bone->m_v3Position.z);
	m_pRoot->drawRect(rightA1Bone->m_v3Scale, rightA1Bone->DetermineColor());

	// Display right arm bone 2
	Bone* rightA2Bone = rightA1Bone->m_lChildren[0];
	glTranslatef(rightA2Bone->m_v3Pivot.x, rightA2Bone->m_v3Pivot.y, rightA2Bone->m_v3Pivot.z);
	glRotatef(rightA2Bone->m_fRotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-rightA2Bone->m_v3Pivot.x, -rightA2Bone->m_v3Pivot.y, -rightA2Bone->m_v3Pivot.z);

	glTranslatef(rightA2Bone->m_v3Position.x, rightA2Bone->m_v3Position.y, rightA2Bone->m_v3Position.z);
	m_pRoot->drawRect(rightA2Bone->m_v3Scale, rightA2Bone->DetermineColor());

	// Display right hand bone
	Bone* rightHandBone = rightA2Bone->m_lChildren[0];
	glTranslatef(rightHandBone->m_v3Pivot.x, rightHandBone->m_v3Pivot.y, rightHandBone->m_v3Pivot.z);
	glRotatef(rightHandBone->m_fRotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-rightHandBone->m_v3Pivot.x, -rightHandBone->m_v3Pivot.y, -rightHandBone->m_v3Pivot.z);

	glTranslatef(rightHandBone->m_v3Position.x, rightHandBone->m_v3Position.y, rightHandBone->m_v3Position.z);
	m_pRoot->drawRect(rightHandBone->m_v3Scale, rightHandBone->DetermineColor());

	glPopMatrix(); // Back to chest area

	glPushMatrix(); // Neck to Head

	// Display neck bone
	Bone* neckBone = chestBone->m_lChildren[0];
	glTranslatef(neckBone->m_v3Pivot.x, neckBone->m_v3Pivot.y, neckBone->m_v3Pivot.z);
	glRotatef(neckBone->m_fRotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-neckBone->m_v3Pivot.x, -neckBone->m_v3Pivot.y, -neckBone->m_v3Pivot.z);

	glTranslatef(neckBone->m_v3Position.x, neckBone->m_v3Position.y, neckBone->m_v3Position.z);
	m_pRoot->drawRect(neckBone->m_v3Scale, neckBone->DetermineColor());

	// Display head bone
	Bone* headBone = neckBone->m_lChildren[0];
	glTranslatef(headBone->m_v3Pivot.x, headBone->m_v3Pivot.y, headBone->m_v3Pivot.z);
	glRotatef(headBone->m_fRotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-headBone->m_v3Pivot.x, -headBone->m_v3Pivot.y, -headBone->m_v3Pivot.z);

	glTranslatef(headBone->m_v3Position.x, headBone->m_v3Position.y, headBone->m_v3Position.z);
	m_pRoot->drawRect(headBone->m_v3Scale, headBone->DetermineColor());

	glPopMatrix(); // Back to chest area
	glPopMatrix(); // Back to torso area

	glPushMatrix(); // Left Leg

	// Display left leg bone 1
	Bone* leftL1Bone = m_pRoot->m_lChildren[1];
	glTranslatef(leftL1Bone->m_v3Pivot.x, leftL1Bone->m_v3Pivot.y, leftL1Bone->m_v3Pivot.z);
	glRotatef(leftL1Bone->m_fRotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-leftL1Bone->m_v3Pivot.x, -leftL1Bone->m_v3Pivot.y, -leftL1Bone->m_v3Pivot.z);

	glTranslatef(leftL1Bone->m_v3Position.x, leftL1Bone->m_v3Position.y, leftL1Bone->m_v3Position.z);
	m_pRoot->drawRect(leftL1Bone->m_v3Scale, leftL1Bone->DetermineColor());

	// Display left leg bone 2
	Bone* leftL2Bone = leftL1Bone->m_lChildren[0];
	glTranslatef(leftL2Bone->m_v3Pivot.x, leftL2Bone->m_v3Pivot.y, leftL2Bone->m_v3Pivot.z);
	glRotatef(leftL2Bone->m_fRotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-leftL2Bone->m_v3Pivot.x, -leftL2Bone->m_v3Pivot.y, -leftL2Bone->m_v3Pivot.z);

	glTranslatef(leftL2Bone->m_v3Position.x, leftL2Bone->m_v3Position.y, leftL2Bone->m_v3Position.z);
	m_pRoot->drawRect(leftL2Bone->m_v3Scale, leftL2Bone->DetermineColor());

	// Display left foot bone
	Bone* leftFootBone = leftL2Bone->m_lChildren[0];
	glTranslatef(leftFootBone->m_v3Pivot.x, leftFootBone->m_v3Pivot.y, leftFootBone->m_v3Pivot.z);
	glRotatef(leftFootBone->m_fRotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-leftFootBone->m_v3Pivot.x, -leftFootBone->m_v3Pivot.y, -leftFootBone->m_v3Pivot.z);

	glTranslatef(leftFootBone->m_v3Position.x, leftFootBone->m_v3Position.y, leftFootBone->m_v3Position.z);
	m_pRoot->drawRect(leftFootBone->m_v3Scale, leftFootBone->DetermineColor());

	glPopMatrix(); // Back to torso area

	glPushMatrix(); // Right Leg

	// Display right leg bone 1
	Bone* rightL1Bone = m_pRoot->m_lChildren[2];
	glTranslatef(rightL1Bone->m_v3Pivot.x, rightL1Bone->m_v3Pivot.y, rightL1Bone->m_v3Pivot.z);
	glRotatef(rightL1Bone->m_fRotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-rightL1Bone->m_v3Pivot.x, -rightL1Bone->m_v3Pivot.y, -rightL1Bone->m_v3Pivot.z);

	glTranslatef(rightL1Bone->m_v3Position.x, rightL1Bone->m_v3Position.y, rightL1Bone->m_v3Position.z);
	m_pRoot->drawRect(rightL1Bone->m_v3Scale, rightL1Bone->DetermineColor());

	// Display right leg bone 2
	Bone* rightL2Bone = rightL1Bone->m_lChildren[0];
	glTranslatef(rightL2Bone->m_v3Pivot.x, rightL2Bone->m_v3Pivot.y, rightL2Bone->m_v3Pivot.z);
	glRotatef(rightL2Bone->m_fRotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-rightL2Bone->m_v3Pivot.x, -rightL2Bone->m_v3Pivot.y, -rightL2Bone->m_v3Pivot.z);

	glTranslatef(rightL2Bone->m_v3Position.x, rightL2Bone->m_v3Position.y, rightL2Bone->m_v3Position.z);
	m_pRoot->drawRect(rightL2Bone->m_v3Scale, rightL2Bone->DetermineColor());

	// Display right foot bone
	Bone* rightFootBone = rightL2Bone->m_lChildren[0];
	glTranslatef(rightFootBone->m_v3Pivot.x, rightFootBone->m_v3Pivot.y, rightFootBone->m_v3Pivot.z);
	glRotatef(rightFootBone->m_fRotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-rightFootBone->m_v3Pivot.x, -rightFootBone->m_v3Pivot.y, -rightFootBone->m_v3Pivot.z);

	glTranslatef(rightFootBone->m_v3Position.x, rightFootBone->m_v3Position.y, rightFootBone->m_v3Position.z);
	m_pRoot->drawRect(rightFootBone->m_v3Scale, rightFootBone->DetermineColor());

	glPopMatrix(); // Back to torso area
	glPopMatrix(); // Pop global space
}

void Rig::UpdateBoneRotations(float a_fAngle)
{
	// Update rotations here with new angle
	selectedBone->SetRotation(selectedBone->GetRotation() + a_fAngle);
}

void Rig::SelectBone(Bone* a_pBone)
{
	// Sets the selected bone
	selectedBone = a_pBone;
	m_pRoot->SetSelected(selectedBone);
}

void Rig::SelectParent()
{
	// Get and select parent as bone
	Bone* parent = selectedBone->GetParent();
	if (parent)
		SelectBone(parent);
}

void Rig::SelectFirstChild()
{
	// Return early if bone doesnt have children
	if (selectedBone->m_lChildren.size() == 0)
		return;

	// Select first child as bone
	Bone* child = selectedBone->m_lChildren[0];
	SelectBone(child);
}

void Rig::SelectNextChild(int a_iIndexChange)
{
	// Return early if bone doesnt have children
	if (selectedBone->m_lChildren.size() == 0)
		return;

	if (a_iIndexChange < 0) // Leftward
	{
		// Loop to back of list
		if (m_iCurrentChildIndex + a_iIndexChange < 0)
			m_iCurrentChildIndex = selectedBone->m_lChildren.size() - 1;
		else
			m_iCurrentChildIndex += a_iIndexChange;

	}
	else // Rightward
	{
		// Loop to front of list
		if (m_iCurrentChildIndex + a_iIndexChange > selectedBone->m_lChildren.size() - 1)
			m_iCurrentChildIndex = 0;
		else
			m_iCurrentChildIndex += a_iIndexChange;
	}

	// Guard code for any weird indexing issues
	if (selectedBone->m_lChildren.size() == 1)
		m_iCurrentChildIndex = 0;

	// Select bone based on calculated index
	SelectBone(selectedBone->m_lChildren[m_iCurrentChildIndex]);
}




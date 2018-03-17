#pragma once
#include "Vector2f.h"
#include "Level.h"
class Avatar
{
public:
	enum class ActionState { waiting = 1, moving = 2, transforming = 3, jumping =4};
	Avatar();

	void Update(float elapsedSec, const Level& level);
	void Draw()const;
	void PowerUpHit();
	Rectf GetShape() const;
private:
	// Data members
	Rectf m_Shape;
	float m_HorSpeed;
	float m_JumpSpeed;
	Vector2f m_Velocity;
	Vector2f m_Acceleration;
	ActionState m_ActionState;
	float m_AccuTransformSec;
	float m_MaxTransformSec;
	int m_Power;
	

	//Sprite related
	Texture m_SpritesTexture;
	float m_ClipHeight;
	float m_ClipWidth;
	int m_NrOfFrames;
	int m_NrFramesPerSecond;
	float m_AnimTime;
	int m_AnimeFrame;

	//Functions
	void HandleTransforming(float elapsedSec); // Do tranformation and set back to actionState::moving
	void HandleVelocityVer(float elapsedSec, const Level& level); //Handles vertical grav and collision
	bool HandleMovement(float elapsedSec, const Level& level); // Handles movement and returns true if moved during function
	void HandleWaitingState(bool IsMoving, const Level& level); // switch between moving and waiting

	void DrawAvatar() const; // Drawing the avater

	void UpdateAvatar(float elapsedSec); //Updating which col we have to drawn from and updating the time

	bool IsInBoundariesHor(float xPos, const Level& level) const; // to make sure that the avater doesn't leave the boundaries
};


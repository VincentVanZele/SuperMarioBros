#include "stdafx.h"
#include "Avatar.h"
#include "utils.h"

Avatar::Avatar()
	: m_Shape{ Rectf{ 50,280,72.f,97 } }
	, m_HorSpeed{ 200.f }, m_JumpSpeed{ 600.f }
	, m_Velocity{ 0.f, 0.f }
	, m_Acceleration{ Vector2f{ 0,-981.f } }
	, m_ActionState{ ActionState::moving }
	, m_AccuTransformSec{ 0.f }, m_MaxTransformSec{ 1.f }
	, m_Power{ 0 }
	//Sprite related
	, m_SpritesTexture{ "Resources/Images/Sprites.png" }
	, m_ClipHeight{ 17.f }, m_ClipWidth{ 14.f }
	, m_NrOfFrames{ 10 }, m_NrFramesPerSecond{ 10 }
	, m_AnimTime{ 0.f }, m_AnimeFrame{ 0 } // set this to 0 after testing
	

{
}

void Avatar::Update(float elapsedSec, const Level& level)
{

	if (m_ActionState != ActionState::transforming) //only if you are not transforming
	{
		HandleVelocityVer(elapsedSec, level);
		HandleWaitingState(HandleMovement(elapsedSec, level), level); // Handle movement and use the output (IsMoved) as input to change waiting state or not
	}
	HandleTransforming(elapsedSec); // Do tranformation and set back to actionState::moving (if there was a transformationg, this is handled in the function)

	UpdateAvatar(elapsedSec);
}

void Avatar::Draw() const
{
	DrawAvatar(); // Draw the Avatar

}

void Avatar::PowerUpHit()
{
	m_ActionState = ActionState::transforming; // when you hit a powerup set the actionstate to transforming
	//m_Power++;
}

Rectf Avatar::GetShape() const
{
	return m_Shape;
}

void Avatar::HandleTransforming(float elapsedSec)
{

	if (m_ActionState == ActionState::transforming) // Only do this when you are in transformingState
	{
		m_AccuTransformSec += elapsedSec;
		if (m_MaxTransformSec < m_AccuTransformSec) // if the accumulated transformed seconds is equal to the max transformed sec, go back to moving state
		{
			m_ActionState = ActionState::moving;
			m_AccuTransformSec = 0.f; // set the transform seconds back to 0, so you can keep using it
			m_Velocity.y = 0.f; // set the y velocity to 0, to make you fall after transformation instead of jumping back in the air
		}
	}
}

void Avatar::HandleVelocityVer(float elapsedSec, const Level& level)
{
	m_Velocity += m_Acceleration * elapsedSec;
	m_Shape.bottom += m_Velocity.y *elapsedSec;

	level.HandleCollision(m_Shape, m_Velocity); // after the gravity check if you are on the ground or not
}

bool Avatar::HandleMovement(float elapsedSec, const Level& level)
{
	bool IsMoved{ false };
	 // this turns to true there was a movement, if there was no movement this will be kept false

						   // Check keyboard state
	const Uint8 *pStates = SDL_GetKeyboardState(nullptr);

	if (pStates[SDL_SCANCODE_RIGHT])
	{
		m_Velocity.x = (m_HorSpeed + m_Acceleration.x) * elapsedSec;

		float tempLeft = m_Shape.left + m_Velocity.x;
		if (IsInBoundariesHor(tempLeft, level) == true)
		{
			m_Shape.left = tempLeft;
		}


		IsMoved = true;
	}
	if (pStates[SDL_SCANCODE_LEFT])
	{
		m_Velocity.x = -((m_HorSpeed + m_Acceleration.x) * elapsedSec);
		float tempLeft = m_Shape.left + m_Velocity.x;
		if (IsInBoundariesHor(tempLeft, level) == true)
		{
			m_Shape.left = tempLeft;
		}

		IsMoved = true;
	}
	if (pStates[SDL_SCANCODE_UP] && level.IsOnGround(m_Shape) == true) // cannot jump when not on the ground aka already jumping
	{
		m_Velocity.y = m_JumpSpeed;
		m_ActionState = ActionState::jumping;
		IsMoved = true;
	}
	if (pStates[SDL_SCANCODE_UP] && level.IsOnPlatform(m_Shape) == true) // cannot jump when not on the ground aka already jumping
	{
		m_Velocity.y = m_JumpSpeed;

		IsMoved = true;
	}
	return IsMoved;
}

void Avatar::HandleWaitingState(bool IsMoving, const Level& level)
{

	if (IsMoving == false && level.IsOnGround(m_Shape))
	{
		m_ActionState = ActionState::waiting;
	}
	else if (IsMoving == false && level.IsOnPlatform(m_Shape))
	{
		m_ActionState = ActionState::waiting;
	}
	else
	{
		m_ActionState = ActionState::moving;

	}
}

void Avatar::DrawAvatar() const
{
	const int kNmbrOfStates{ 3 }; // number of the states (moving, waiting, transofrming)
	Rectf src{}; // putting our source rect in it after the if statement

				 //Drawing when you are transforming you have to take the transforming state form the previous powerup and not the current one (hence the -1)
	//if (m_ActionState == ActionState::transforming)
	if (m_ActionState == ActionState::jumping)
	{
		src = Rectf{ m_AnimeFrame * m_ClipWidth , (int(m_ActionState) + (kNmbrOfStates * (m_Power-1 ))) * m_ClipHeight,m_ClipWidth,m_ClipHeight };
	}
	else
	{
		src = Rectf{ m_AnimeFrame * m_ClipWidth, (int(m_ActionState) + (kNmbrOfStates * m_Power)) * m_ClipHeight, m_ClipWidth, m_ClipHeight };
	}

	// if the velocity is smaller than 0, we are going left, thus we have to animate our character in an other way
	if (m_Velocity.x < 0)
	{
		glPushMatrix(); // open glMatrix
		glScalef(-1, 1, 1); // flip the x axis
		Rectf temp{ -(m_Shape.left + m_Shape.width) ,m_Shape.bottom,m_Shape.width,m_Shape.height }; // temp value to draw in the correct position over the now axis
		m_SpritesTexture.Draw(temp, src);
		glPopMatrix(); // close glMatrix
	}
	else
	{
		m_SpritesTexture.Draw(m_Shape, src); /*draw the character like nornal*/
	}

}

void Avatar::UpdateAvatar(float elapsedSec)
{
	m_AnimTime += elapsedSec;
	if (m_AnimTime > 1.f / m_NrFramesPerSecond)	//when the time is more than the given time for 1 second
	{
		m_AnimeFrame++;							// add 1 to ani frame 
		if (m_AnimeFrame == m_NrOfFrames)		// if the aniframe is equal to nrOfFrames
		{
			m_AnimeFrame = 0;					// set the aniframe to 1
		}
		m_AnimTime = 0; // we want this to be 0, so we can do it over and over again for every frame
	}
}

bool Avatar::IsInBoundariesHor(float xPos, const Level& level) const
{
	Rectf boundaries{ level.GetBoundaries() }; // saving the bounadries as a var, to get easier acces

											   //prevent going through left border
	if (xPos  < boundaries.left)
	{
		return false;
	}

	//prevent going through right border
	if (xPos + m_Shape.width   > boundaries.left + boundaries.left + boundaries.width)
	{
		return false;
	}

	return true; // if none of the statments are met, we know that it is in between the borders
}

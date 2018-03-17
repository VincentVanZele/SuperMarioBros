#include "stdafx.h"
#include "PowerUp.h"
#include <iostream>
#include "utils.h"

const float PowerUp::radius{ 35.f };
PowerUp::PowerUp(const Point2f& center, PowerUp::Type type)
	:m_Texture{ "Resources/Images/PowerUp.png"}
	,m_Type{type}
	,m_Shape{ Circlef{ center, radius } }
	,m_RotSpeed{ 360.f }
	,m_TextClip{ GetTextureClip()}
	,m_Angle{0.f}
{
	
}

void PowerUp::Update(float elapsedSec)
{
	m_Angle += m_RotSpeed * elapsedSec;
}

void PowerUp::Draw() const
{
	//using matrix to rotate the powerup
	glPushMatrix();
		glTranslatef(m_Shape.center.x, m_Shape.center.y, 0);
		glRotatef(m_Angle, 0, 0, 1);
		m_Texture.Draw(Point2f{ -m_Shape.radius, -m_Shape.radius }, m_TextClip);
	glPopMatrix();

	
}

bool PowerUp::IsOverlapping(const Rectf & rect) const
{

	return utils::IsOverlapping(rect, m_Shape);
}

//PowerUp::~PowerUp()
//{
//}

const Rectf PowerUp::GetTextureClip()
{
	Rectf tempValue{}; // making a ver to put the result in
	
	//switch on type and based on the type get the correct clip
	switch (m_Type)
	{
	case Type::green:
		tempValue.left = 0.f;
		tempValue.bottom = m_Texture.GetHeight() /2;
		tempValue.width = m_Texture.GetWidth();
		tempValue.height = m_Texture.GetHeight()/2;
		break;
	case Type::brown:
		tempValue.left = 0.f;
		tempValue.bottom = m_Texture.GetHeight();
		tempValue.width = m_Texture.GetWidth();
		tempValue.height = m_Texture.GetHeight() / 2;
		break;
	}
	return tempValue;
}









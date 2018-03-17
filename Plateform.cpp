#include "stdafx.h"
#include "Plateform.h"


Plateform::Plateform(const Point2f & bottomleft)
	:m_Shape{bottomleft.x,bottomleft.y,0,0}
	,m_texture{ "Resources/Images/platform.png" }
{
	m_Shape.width = m_texture.GetWidth();
	m_Shape.height = m_texture.GetHeight();
	m_VerticesPlat.push_back(Point2f(m_Shape.left, m_Shape.left));
	m_VerticesPlat.push_back(Point2f(m_Shape.left + m_Shape.width, m_Shape.bottom));
	m_VerticesPlat.push_back(Point2f(m_Shape.left + m_Shape.width, m_Shape.bottom + m_Shape.height));
	m_VerticesPlat.push_back(Point2f(m_Shape.left, m_Shape.bottom + m_Shape.height));
}

void Plateform::Draw() const
{
	m_texture.Draw(m_Shape);
}

void Plateform::HandleCollision(Rectf & actorShape, Vector2f & actorVelocity) const
{
	Point2f rayStart{ actorShape.left + actorShape.width / 2 , actorShape.bottom + actorShape.height }; // Point = bottem point of the actor in the 
	Point2f rayEnd{ actorShape.left + actorShape.width / 2 , actorShape.bottom }; // using this to get a straight raycast
	utils::HitInfo hitInfo; // use this to save the value of the raycast
							//float elipson{ 0.001f }; // var to check if there is collision



	if (utils::Raycast(m_VerticesPlat, rayStart, rayEnd, hitInfo))
	{
		actorVelocity.y = 0;
		actorShape.bottom = hitInfo.intersectPoint.y - 1.f;
	}
	//std::cout << hitInfo.lambda << std::endl;
}

bool Plateform::IsOnGround(const Rectf & actorShape, const Vector2f & actorVelocity)
{
	return false;
}



#include "stdafx.h"
#include "Level.h"
#include "utils.h"
#include "SVGParser.h"

Level::Level()
	:m_BackgroundTexture("Resources/Images/background.png")
	, m_FenceTexture("Resources/Images/Fence.png")
	, m_EndSignTexture("Resources/Images/EndSign.png")
	, m_EndSignShape(Rectf{ 730.0f,220.0f,70.0f,50.0f })
	, m_FenceBottomLeft(Point2f{ 200.f,190.f })
	, m_Vertices{ GetVertices() }
	, m_Boundaries{ 0.f,0.f,m_BackgroundTexture.GetWidth(), m_BackgroundTexture.GetHeight() }
	, m_Platform{ Point2f(300.0f,350.0f) }
{

}

void Level::DrawBackground() const
{

	m_BackgroundTexture.Draw();
}

void Level::DrawForeground() const
{
	m_Platform.Draw();
	m_EndSignTexture.Draw(m_EndSignShape);
	m_FenceTexture.Draw(m_FenceBottomLeft);

}
void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const
{
	m_Platform.HandleCollision(actorShape, actorVelocity);
	Point2f rayStart{ actorShape.left + actorShape.width / 2 , actorShape.bottom + actorShape.height }; // Point = bottem point of the actor in the 
	Point2f rayEnd{ actorShape.left + actorShape.width / 2 , actorShape.bottom }; // using this to get a straight raycast
	utils::HitInfo hitInfo; // use this to save the value of the raycast
							//float elipson{ 0.001f }; // var to check if there is collision



	if (utils::Raycast(m_Vertices, rayStart, rayEnd, hitInfo))
	{
		actorVelocity.y = 0;
		actorShape.bottom = hitInfo.intersectPoint.y - 1.f;
	}
	//std::cout << hitInfo.lambda << std::endl;

#pragma region ShowLines
	// !!!!!!!!!! This is bad code !!!!!!!!!!
	// do not use it as final, only to test


	//// DrawinIntersection Point
	//utils::DrawEllipse(hitInfo.intersectPoint, 8, 8);

	//// Draw the line
	//utils::SetColor(Color4f{ 1.f,1.f,0.f,1.f });
	//utils::DrawLine(rayStart, rayEnd, 2);

	////Normal (green)
	//utils::SetColor({ 0.f,1.f,0.f,1.f });
	//DrawVector(hitInfo.intersectPoint, hitInfo.normal * -20 /*normalized*/);

	////reflectedRay (white)
	//Vector2f reflectedVector;
	//Vector2f rayVec{ rayStart };
	//reflectedVector = rayVec.Reflect(hitInfo.normal);
	//utils::SetColor({ 1.f,1.f,1.f,1.f });
	//DrawVector(hitInfo.intersectPoint, reflectedVector * (1 - hitInfo.lambda));

#pragma endregion ShowLines


	//if (abs(hitInfo.lambda) < elipson || abs(hitInfo.lambda - 1.f) < 0.1) // if this is true we know that there is a collision
	//{
	//	actorVelocity.y = 0.f; // set the velocity to 0

	//	if (!abs(hitInfo.lambda - 1.f ) < 0.1) // if the lamba is not 1
	//	{
	//		actorShape.bottom = hitInfo.intersectPoint.y; // set the position to be the possition of the 
	//		//std::cout << "ok\n"; // to test if it works
	//	}
	//	
	//}


}

bool Level::IsOnGround(const Rectf & actorShape) const
{
	Point2f rayStart{ actorShape.left + actorShape.width / 2 , actorShape.bottom + actorShape.height }; // Point = bottem point of the actor in the 
	Point2f rayEnd{ actorShape.left + actorShape.width / 2 , actorShape.bottom }; // using this to get a straight raycast
	utils::HitInfo hitInfo; // use this to save the value of the raycast

	utils::Raycast(m_Vertices, rayStart, rayEnd, hitInfo);


	if (utils::IsPointInRect(hitInfo.intersectPoint, actorShape) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Level::IsOnPlatform(const Rectf & actorShape) const
{
	Point2f rayStart{ actorShape.left + actorShape.width / 2 , actorShape.bottom + actorShape.height }; // Point = bottem point of the actor in the 
	Point2f rayEnd{ actorShape.left + actorShape.width / 2 , actorShape.bottom }; // using this to get a straight raycast
	utils::HitInfo hitInfo; // use this to save the value of the raycast

	utils::Raycast(m_Platform.m_VerticesPlat, rayStart, rayEnd, hitInfo);


	if (utils::IsPointInRect(hitInfo.intersectPoint, actorShape) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Level::HasReachedEnd(const Rectf & actorShape)
{
	if (utils::IsOverlapping(actorShape, m_EndSignShape))
	{
		return true;
	}
	return false;
}

Rectf Level::GetBoundaries() const
{
	return m_Boundaries;
}

std::vector<Point2f> Level::GetVertices()
{
	std::vector<std::vector<Point2f>> temp;
	SVGParser::GetVerticesFromSvgFile("Resources/Images/level.svg", temp);

	return temp[0];
}


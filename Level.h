#pragma once
#include <vector>
#include "Texture.h"
#include "Vector2f.h"
#include "Plateform.h"
class Level
{
public:
	Level();
	void DrawBackground() const;
	void DrawForeground() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorShape) const;
	bool IsOnPlatform(const Rectf& actorShape) const;
	bool HasReachedEnd(const Rectf& actorShape);
	Rectf GetBoundaries() const;

private:
	//Data members
	std::vector<Point2f> m_Vertices;
	Texture m_BackgroundTexture;
	Texture m_FenceTexture;
	Point2f m_FenceBottomLeft;
	Rectf m_Boundaries;
	Plateform m_Platform;
	Rectf m_EndSignShape;
	Texture m_EndSignTexture;
	//functions
	std::vector<Point2f> GetVertices();
};


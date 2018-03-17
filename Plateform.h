#pragma once
#include "Texture.h"
#include "Vector2f.h"
#include "utils.h"

class Plateform
{
public:
	Plateform(const Point2f& bottomleft);
	void Draw() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity);
	std::vector<Point2f> m_VerticesPlat;
private:
	Rectf m_Shape;
	Texture m_texture;
	
};


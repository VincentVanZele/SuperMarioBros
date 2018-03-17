#pragma once
#include "Texture.h"

class PowerUp
{
public:
	enum class Type
	{
		green = 1,
		brown = 2
	};

	PowerUp(const Point2f& center, PowerUp::Type type);

	void Update(float elapsedSec);
	void Draw() const;
	bool IsOverlapping(const Rectf& rect) const;
	static const float radius;

private:
	const Type m_Type;
	Circlef m_Shape;
	const Texture m_Texture;
	const Rectf m_TextClip;
	const float m_RotSpeed;
	float m_Angle;

	const Rectf GetTextureClip();
	
};
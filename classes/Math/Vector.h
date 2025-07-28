#pragma once
namespace Math
{
	struct Vec2
	{
		Vec2() 
			: X{ 0.f }
			, Y{ 0.f } 
		{}
		
		Vec2(float x, float y)
			: X{ x }
			, Y{ y }
		{}

		float X;
		float Y;

		Vec2 operator-(const Vec2& other) const
		{
			return Vec2(X - other.X, Y - other.Y);
		}
	};
}
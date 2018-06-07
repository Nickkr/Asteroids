#pragma once

struct circleShape
{
public:
	circleShape(float radius)
		: radius(radius)
	{}

	float getRadius() const { return radius; }

private:
	float radius;
};

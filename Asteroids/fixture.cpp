#include "fixture.h"

mat4x4 fixture::computeTransform() const
{
	float angle = body->getAngle();
	vec2 pos = body->getPos();

	mat4x4 m = { 0 };
	// 2d rotation 
	m._00 = cosf(angle);
	m._11 = cosf(angle);
	m._01 = -sinf(angle);
	m._10 = sinf(angle);

	// translation
	m._03 = pos.x;
	m._13 = pos.y;
	// homogeneous coordinates
	m._33 = 1;

	return m;
} 
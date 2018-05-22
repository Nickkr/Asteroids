#include "fixture.h"

void fixture::draw(renderContext& context)
{
	mat4x4 transform = computeTransform();
	glUniformMatrix4fv(context.modelViewLocation, 1, false, &transform._00);
	shape->draw();
}

mat4x4 fixture::computeTransform() const
{
	float angle = body->getAngle();
	vec2 pos = body->getPos();

	mat4x4 m = { 0 };
	// 2d rotation 
	m._00 = scale * cosf(angle);
	m._11 = scale * cosf(angle);
	m._01 = scale * -sinf(angle);
	m._10 = scale * sinf(angle);

	// translation
	m._03 = pos.x;
	m._13 = pos.y;
	// homogeneous coordinates
	m._33 = 1;

	return m;
}
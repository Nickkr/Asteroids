#pragma once

#include <math.h>
#include "math.h"

const float pi = acosf(-1.0f);
const float angularVelocity = 2 * pi / (1);

struct gameState {
	vec2 shipPos = { 0, 0 };
	float shipHeading = 0;
	float shipVelocity = 0.1;

	bool turnLeft = false;
	bool turnRight = false ;

	mat4x4 computeShipTransformation() const;

	void update(float dt);
};

// shipForwardDirection vector 
// shipVelocity float
// dt float time since last update call
void gameState::update(float dt)
{
	if (turnLeft)
	{
		shipHeading += angularVelocity * dt;
	}
	if (turnRight)
	{
		shipHeading -= angularVelocity * dt;
	}
	vec2 shipForwardDirection = { cosf(shipHeading), sinf(shipHeading) };
	shipPos += shipForwardDirection * shipVelocity * dt;
}

mat4x4 gameState::computeShipTransformation() const
{
	mat4x4 m = { 0 };
	// 2d rotation 
	m._00 = cosf(shipHeading);
	m._11 = cosf(shipHeading);
	m._01 = -sinf(shipHeading);
	m._10 = sinf(shipHeading);

	// homogene coords 
	m._33 = 1;

	// translation
	m._03 = shipPos.x;
	m._13 = shipPos.y;
	
	return m;
}
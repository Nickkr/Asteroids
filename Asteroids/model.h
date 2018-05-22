#pragma once

#include <math.h>
#include "math.h"

const float pi = acosf(-1.0f);
const float angularVelocity = 2 * pi / (1);
const float linearAcceleration = 1; // (m/s^2)
const float maxLinearVelocity = 1.0f;
const float linearDamping = 0.8f;

struct gameState
{
	vec2 shipPos = { 0, 0 };
	float shipHeading = 0;
	float shipVelocity = 0;

	vec2 asteroidPos = { 0,0 };
	float asteroidHeading = 1;
	float asteroidTravelHeading = 30 / 180.0f * pi;

	float ufoHeading = 2;
	vec2 ufoPos = { 0,0 };

	bool turnLeft = false;
	bool turnRight = false;

	bool boostingForward = false;
	bool boostingBackward = false;

	mat4x4 computeShipTransformation() const;
	mat4x4 computeAsteroidTransformation() const;
	mat4x4 computeUfoTransformation() const;

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
	if (boostingForward)
	{
		shipVelocity += linearAcceleration * dt;
	}
	if (boostingBackward)
	{
		shipVelocity += -linearAcceleration * dt;
	}
	if (shipVelocity >= maxLinearVelocity)
	{
		shipVelocity = maxLinearVelocity;
	}
	if (shipVelocity <= -maxLinearVelocity)
	{
		shipVelocity = -maxLinearVelocity;
	}
	vec2 shipForwardDirection = { cosf(shipHeading), sinf(shipHeading) };
	shipPos += shipForwardDirection * shipVelocity * dt;
	shipVelocity *= powf(linearDamping, dt);

	//when exiting map return on other side
	if (shipPos.x < -1.0f) shipPos.x += 2.0f;
	if (shipPos.x > 1.0f) shipPos.x -= 2.0f;
	if (shipPos.y < -1.0f) shipPos.y += 2.0f;
	if (shipPos.y > 1.0f) shipPos.y -= 2.0f;

	//asteroid
	asteroidHeading += angularVelocity / 30 * dt;
	vec2 asteroidForwardDirection = { cosf(asteroidTravelHeading), sinf(asteroidTravelHeading) };
	asteroidPos += asteroidForwardDirection * (maxLinearVelocity / 3) * dt;
	//when exiting map return on other side
	if (asteroidPos.x < -1.0f) asteroidPos.x += 2.0f;
	if (asteroidPos.x > 1.0f) asteroidPos.x -= 2.0f;
	if (asteroidPos.y < -1.0f) asteroidPos.y += 2.0f;
	if (asteroidPos.y > 1.0f) asteroidPos.y -= 2.0f;

	//UFO
	ufoHeading = angularVelocity * dt;
	vec2 ufoForwardDirection = { cosf(ufoHeading), sinf(ufoHeading) };
	ufoPos += ufoForwardDirection * (maxLinearVelocity / 3) * dt;
	//when exiting map return on other side
	if (ufoPos.x < -1.0f) ufoPos.x += 2.0f;
	if (ufoPos.x > 1.0f) ufoPos.x -= 2.0f;
	if (ufoPos.y < -1.0f) ufoPos.y += 2.0f;
	if (ufoPos.y > 1.0f) ufoPos.y -= 2.0f;
}

mat4x4 gameState::computeAsteroidTransformation() const
{
	const float scale = 0.3f;
	mat4x4 m = { 0 };
	// 2d rotation 
	m._00 = scale * cosf(asteroidHeading);
	m._11 = scale * cosf(asteroidHeading);
	m._01 = scale * -sinf(asteroidHeading);
	m._10 = scale * sinf(asteroidHeading);

	// homogene coords 
	m._33 = 1;

	// translation
	m._03 = asteroidPos.x;
	m._13 = asteroidPos.y;

	return m;
}

mat4x4 gameState::computeUfoTransformation() const
{
	const float scale = 0.02f;
	mat4x4 m = { 0 };
	// 2d rotation 
	m._00 = scale * cosf(ufoHeading);
	m._11 = scale * cosf(ufoHeading);
	m._01 = scale * -sinf(ufoHeading);
	m._10 = scale * sinf(ufoHeading);

	// homogene coords 
	m._33 = 1;

	// translation
	m._03 = ufoPos.x;
	m._13 = ufoPos.y;

	return m;
}


mat4x4 gameState::computeShipTransformation() const
{
	const float scale = 0.1f;
	mat4x4 m = { 0 };
	// 2d rotation 
	m._00 = scale * cosf(shipHeading);
	m._11 = scale *cosf(shipHeading);
	m._01 = scale * -sinf(shipHeading);
	m._10 = scale * sinf(shipHeading);

	// homogene coords 
	m._33 = 1;

	// translation
	m._03 = shipPos.x;
	m._13 = shipPos.y;

	return m;
}
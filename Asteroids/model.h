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

	bool accelerating()
	{
		return (boostingForward || boostingBackward);
	} 

	mat4x4 computeShipTransformation() const;
	mat4x4 computeAsteroidTransformation() const;
	mat4x4 computeUfoTransformation() const;

	void update(float dt);
};

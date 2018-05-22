#pragma once

#include "math.h"
#include "rigidBody.h"
#include <math.h>

static const float pi = acosf(-1.0f);

struct gameState
{
	rect area;

	rigidBody ship;
	rigidBody asteroid;
	rigidBody ufo;

	bool turnLeft = false;
	bool turnRight = false;

	bool boostingForward = false;
	bool boostingBackward = false;

	void setup();
	void update(float dt);
	void updateControls();
};

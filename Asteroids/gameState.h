#pragma once

#include "math.h"
#include "gameObject.h"
#include <math.h>

static const float pi = acosf(-1.0f);

struct gameState
{
	rect area;

	gameObject ship = { gameObjectType::ship, 0.04f };
	gameObject asteroid = { gameObjectType::asteroid, 0.09f };
	gameObject ufo = { gameObjectType::ufo, 0.04f };

	bool turnLeft = false;
	bool turnRight = false;

	bool boostingForward = false;
	bool boostingBackward = false;
	
	bool collision = false;

	void setup();
	void update(float dt);
	void updateControls();
};

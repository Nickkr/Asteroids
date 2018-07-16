#pragma once

#include "math.h"
#include "gameObject.h"
#include <math.h>
#include <vector>
#include <memory>

static const float pi = acosf(-1.0f);

struct gameState
{
	rect area;
	int playerScore = 0;

	gameObject ship = { gameObjectType::ship, 0.04f };
	gameObject ufo = { gameObjectType::ufo, 0.04f };

	std::vector<std::unique_ptr<gameObject>> asteroids;
	std::vector<std::unique_ptr<gameObject>> bullets;
	std::vector<std::unique_ptr<gameObject>> ufoBullets;

	//asteroid spawn and last spawn coord counter
	std::vector<vec2> asteroidSpawnCoords = { {0,-1}, {-1,0}, {0,1}, {1,0} };
	int spawnCoordCounter = 0;

	bool turnLeft = false;
	bool turnRight = false;

	bool boostingForward = false;
	bool boostingBackward = false;
	
	bool collision = false;

	float gameTime = 0;
	float shipStateTimeStamp = 0;
	float lastUfoBulletTime = 0;
	float lastAsteroidSpawn = 0;
	float ufoKilledTime = 0;

	void setup();
	void spawnUfo();
	void update(float dt);
	void updateControls();
	void addAsteroid();
	void shootBullet();
	void ufoAttack();
};

#pragma once

#include "fixture.h"

enum class gameObjectType
{
	ship,
	asteroid,
	ufo,
	bullet
};

class gameObject : public fixture
{
public:
	gameObject(gameObjectType type, float radius);

	void onCollisionWith(gameObject& other);

	void kill() { alive = false;  }
	void revive() { alive = true; }
	void respawn();
	bool isAlive() const { return alive;  }
	bool invincible = false;

private:
	gameObjectType type;
	rigidBody body;
	circleShape shape;

	bool alive = true;
};
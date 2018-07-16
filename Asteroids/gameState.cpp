#include "gameState.h"
#include "gameSettings.inl"
#include "collision.h"
#include <random>



void gameState::setup()
{
	area = rect{{ -1, -1 }, { 1, 1 }};
	ship.getBody()->setLinearDamping(0.8f);
	ship.getBody()->setMaxLinearVelocity(maxLinearVelocity);

	addAsteroid();

	vec2 ufoForwardDirection = { cosf(ufoHeading), sinf(ufoHeading) };
	ufo.getBody()->setLinearVelocity(ufoForwardDirection * (maxLinearVelocity / 3));
	ufo.getBody()->setPos({ -0.9f , 0.5f });

}

void gameState::addAsteroid()
{
	auto asteroid = std::make_unique<gameObject>(gameObjectType::asteroid, 0.09f);
	asteroid->getBody()->setAngularVelocity(angularVelocity / 30);
	float travelHeading =  rand() % 360 / 180.0f * pi; //0-359 degrees in radian fly direction
	vec2 asteroidForwardDirection = { cosf(travelHeading), sinf(travelHeading) };
	asteroid->getBody()->setLinearVelocity(asteroidForwardDirection * (maxLinearVelocity / 3));
	asteroid->getBody()->setPos(asteroidSpawnCoords[spawnCoordCounter % 4]);
	asteroids.push_back(std::move(asteroid));
	++spawnCoordCounter; //next asteroid spawns at next position defined in vector
}

// dt float time since last update call
void gameState::update(float dt)
{
	gameTime += dt;
	ship.getBody()->resetForceAndTorque();

	updateControls();

	if (enableMomentum)
	{
		ship.getBody()->update(dt);
	}
	else
	{
		// Rotate the velocity vector along with the ship for snappier controls
		float oldHeading = ship.getBody()->getAngle();
		ship.getBody()->update(dt);
		float newHeading = ship.getBody()->getAngle();
		float rotation = newHeading - oldHeading;
		vec2 shipVelocity = ship.getBody()->getLinearVelocity();
		vec2 rotatedShipVelocity = {
			cosf(rotation) * shipVelocity.x - sinf(rotation) * shipVelocity.y,
			cosf(rotation) * shipVelocity.y + sinf(rotation) * shipVelocity.x
		};
		ship.getBody()->setLinearVelocity(rotatedShipVelocity);
	}
	ship.getBody()->confineTo(area);

	for (auto& asteroid : asteroids)
	{
		asteroid->getBody()->update(dt);
		asteroid->getBody()->confineTo(area);
	}

	ufo.getBody()->update(dt);
	ufo.getBody()->confineTo(area);
	
	if (!ship.isAlive())
	{
		if (shipStateTimeStamp == 0)
		{
			shipStateTimeStamp = gameTime + respawnTimer;
		}
		else if (gameTime > shipStateTimeStamp)
		{
			shipStateTimeStamp = 0;
			ship.respawn();
		}
	}

	if (ship.isInvincible())
	{
		if (shipStateTimeStamp == 0)
		{
			shipStateTimeStamp = gameTime + invincibleAfterSpawnTimer;
		}
		else if (gameTime > shipStateTimeStamp)
		{
			shipStateTimeStamp = 0;
			ship.setInvincible(false);
		}
	}
	else
	{
		this->collision = checkCollision(ufo, ship);
		if (!this->collision)
		{
			for (auto& asteroid : asteroids)
			{
				if (checkCollision(*asteroid, ship))
				{
					this->collision = true;
					break;
				}
			}
		}
	}
}

// TODO: Move to controller
void gameState::updateControls()
{
	float shipAngularVelocity = 0;
	if (turnLeft)
	{
		shipAngularVelocity += angularVelocity;
	}
	if (turnRight)
	{
		shipAngularVelocity -= angularVelocity;
	}

	float shipAcceleration = 0;
	if (boostingForward)
	{
		shipAcceleration += linearAcceleration;
	}
	if (boostingBackward)
	{
		shipAcceleration += -linearAcceleration;
	}
	float shipHeading = ship.getBody()->getAngle();
	vec2 shipForwardDirection = { cosf(shipHeading), sinf(shipHeading) };
	vec2 shipForce = shipForwardDirection * shipAcceleration;

	ship.getBody()->applyForce(shipForce);
	ship.getBody()->setAngularVelocity(shipAngularVelocity);
}

#include "gameState.h"
#include "gameSettings.inl"
#include "collision.h"

void gameState::setup()
{
	area = rect{{ -1, -1 }, { 1, 1 }};
	ship.getBody()->setLinearDamping(0.8f);
	ship.getBody()->setMaxLinearVelocity(maxLinearVelocity);

	asteroid.getBody()->setAngularVelocity(angularVelocity / 30);
	vec2 asteroidForwardDirection = { cosf(asteroidTravelHeading), sinf(asteroidTravelHeading) };
	asteroid.getBody()->setLinearVelocity(asteroidForwardDirection * (maxLinearVelocity / 3));

	vec2 ufoForwardDirection = { cosf(ufoHeading), sinf(ufoHeading) };
	ufo.getBody()->setLinearVelocity(ufoForwardDirection * (maxLinearVelocity / 3));
}

// dt float time since last update call
void gameState::update(float dt)
{
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

	asteroid.getBody()->update(dt);
	asteroid.getBody()->confineTo(area);

	ufo.getBody()->update(dt);
	ufo.getBody()->confineTo(area);

	if (!invincible)
	{
		this->collision = checkCollision(asteroid, ship) || checkCollision(ufo, ship);
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

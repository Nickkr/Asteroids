#include "gameState.h"
#include "gameSettings.inl"
#include "collision.h"

void gameState::setup()
{
	area = rect{{ -1, -1 }, { 1, 1 }};
	ship.setLinearDamping(0.8);
	ship.setMaxLinearVelocity(maxLinearVelocity);

	asteroid.setAngularVelocity(angularVelocity / 30);
	vec2 asteroidForwardDirection = { cosf(asteroidTravelHeading), sinf(asteroidTravelHeading) };
	asteroid.setLinearVelocity(asteroidForwardDirection * (maxLinearVelocity / 3));

	vec2 ufoForwardDirection = { cosf(ufoHeading), sinf(ufoHeading) };
	ufo.setLinearVelocity(ufoForwardDirection * (maxLinearVelocity / 3));
}

// dt float time since last update call
void gameState::update(float dt)
{
	ship.resetForceAndTorque();

	updateControls();

	if (enableMomentum)
	{
		ship.update(dt);
	}
	else
	{
		// Rotate the velocity vector along with the ship for snappier controls
		float oldHeading = ship.getAngle();
		ship.update(dt);
		float newHeading = ship.getAngle();
		float rotation = newHeading - oldHeading;
		vec2 shipVelocity = ship.getLinearVelocity();
		vec2 rotatedShipVelocity = {
			cos(rotation) * shipVelocity.x - sin(rotation) * shipVelocity.y,
			cos(rotation) * shipVelocity.y + sin(rotation) * shipVelocity.x
		};
		ship.setLinearVelocity(rotatedShipVelocity);
	}
	ship.confineTo(area);

	asteroid.update(dt);
	asteroid.confineTo(area);

	ufo.update(dt);
	ufo.confineTo(area);
	checkCollision(asteroid.getPos(), ship.getPos());
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
	float shipHeading = ship.getAngle();
	vec2 shipForwardDirection = { cosf(shipHeading), sinf(shipHeading) };
	vec2 shipForce = shipForwardDirection * shipAcceleration;

	ship.applyForce(shipForce);
	ship.setAngularVelocity(shipAngularVelocity);
}

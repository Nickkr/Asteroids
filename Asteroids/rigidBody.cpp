#include "rigidBody.h"
#include <math.h>

void rigidBody::update(float dt)
{
	linearVelocity *= powf(linearDamping, dt);
	linearVelocity += force * dt;
	float velocityMagnitudeSquared = length_squared(linearVelocity);
	if (velocityMagnitudeSquared >= maxLinearVelocitySquared)
	{
		linearVelocity *= sqrtf(maxLinearVelocitySquared / velocityMagnitudeSquared);
	}
	pos += linearVelocity * dt;

	angularVelocity *= powf(angularDamping, dt);
	angularVelocity += torque * dt;
	angle += angularVelocity * dt;
}

void rigidBody::confineTo(rect area)
{
	vec2 size = area.max - area.min;
	vec2 relPos = pos - area.min;
	relPos.x = fmodfPositive(relPos.x, size.x);
	relPos.y = fmodfPositive(relPos.y, size.y);
	pos = area.min + relPos;
}

void rigidBody::resetForceAndTorque()
{
	force = { 0, 0 };
	torque = 0;
}

void rigidBody::applyForce(vec2 force)
{
	this->force += force;
}

void rigidBody::applyTorque(float torque)
{
	this->torque += torque;
}
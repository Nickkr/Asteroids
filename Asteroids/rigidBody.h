#pragma once

#include "math.h"

// Simplified rigid body with center of mass at origin and mass 1.
class rigidBody
{
public:
	void resetForceAndTorque();
	void applyForce(vec2 force);
	void applyTorque(float torque);

	void setLinearVelocity(vec2 linearVelocity) { this->linearVelocity = linearVelocity; }
	vec2 getLinearVelocity() const { return linearVelocity; }
	void setAngularVelocity(float angularVelocity) { this->angularVelocity = angularVelocity; }
	float getAngularVelocity() const { return angularVelocity; }

	void update(float dt);
	void confineTo(rect area);

	void setPos(vec2 pos) { this->pos = pos; }
	vec2 getPos() const { return pos;  }
	void setAngle(float angle) { this->angle = angle; }
	float getAngle() const { return angle;  }

	void setLinearDamping(float linearDamping) { this->linearDamping = linearDamping; }
	void setAngularDamping(float angularDamping) { this->angularDamping = angularDamping; }

	void setMaxLinearVelocity(float maxLinearVelocity) { this->maxLinearVelocitySquared = maxLinearVelocity * maxLinearVelocity; }

private:
	vec2 pos = { 0, 0 };
	vec2 linearVelocity = { 0, 0 };
	vec2 force = { 0, 0 };

	float angle = 0;
	float angularVelocity = 0;
	float torque = 0;

	float linearDamping = 1.0;
	float angularDamping = 1.0;

	float maxLinearVelocitySquared = 1000.0;
};
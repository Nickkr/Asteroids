#include "ship.h"

void ship::onCollisionWith(gameObject& other)
{
	this->kill();
}
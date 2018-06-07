#include "gameObject.h"

gameObject::gameObject(gameObjectType type, float radius)
	: type(type), shape(radius)
{
	setBody(&body);
	setShape(&shape);
}

void gameObject::onCollisionWith(gameObject& other)
{
	if (this->type == gameObjectType::ship)
	{
		if (other.type == gameObjectType::asteroid
			|| other.type == gameObjectType::ufo)
		{
			kill();
		}
	}

	if (this->type == gameObjectType::asteroid
		|| this->type == gameObjectType::ufo)
	{
		if (other.type == gameObjectType::bullet)
		{
			kill();
		}
	}
}
#pragma once

#include "polygonShape.h"
#include "gameObject.h"

class ship : public gameObject
{
public:
	ship(polygonShape* renderObject)
		: renderObject(renderObject)
	{}

	virtual void onCollisionWith(gameObject& other);

private:
	polygonShape* renderObject;
};
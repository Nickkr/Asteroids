#pragma once

#include "gameObject.h"
#include "polygonShape.h"

class asteroid : public gameObject
{
public:
	asteroid(polygonShape* renderObject)
		: renderObject(renderObject)
	{}

	virtual void onCollisionWith(gameObject& other) = 0;

private:
	polygonShape* renderObject;
};
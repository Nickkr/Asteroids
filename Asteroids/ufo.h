#pragma once

#include "gameObject.h"
#include "polygonShape.h"

class ufo : public gameObject
{
public:
	ufo(polygonShape* renderObject)
		: renderObject(renderObject)
	{}

	virtual void onCollisionWith(gameObject& other) = 0;

private:
	polygonShape * renderObject;
};
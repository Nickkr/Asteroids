#include "gameView.h"
#include "polygonShapes.inl"
#include "collision.h"
#include <stdio.h>

void gameView::setup()
{
	shipCruisingShape.build(shipCruisingVertices, 0.1f);
	shipAcceleratingShape.build(shipAcceleratingVertices, 0.1f);
	asteroidShape.build(asteroidVertices, 0.3f);
	ufoShape.build(ufoVertices, 0.02f);
}

void gameView::draw(renderContext& context)
{
	mat4x4 shipTransform = state.ship.computeTransform();

	if (state.ship.isAlive())
	{
		if (state.boostingForward || state.boostingBackward)
		{
			shipAcceleratingShape.draw(context, shipTransform, state.ship.isInvincible());
		}
		else
		{
			shipCruisingShape.draw(context, shipTransform, state.ship.isInvincible());
		}
	}
	for (auto& asteroid : state.asteroids)
	{
		asteroidShape.draw(context, asteroid->computeTransform(), asteroid->isInvincible());

	}
	ufoShape.draw(context, state.ufo.computeTransform(), state.ufo.isInvincible());
}
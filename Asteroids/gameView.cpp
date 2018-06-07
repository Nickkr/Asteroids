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
	if (state.boostingForward || state.boostingBackward)
	{
		shipAcceleratingShape.draw(context, shipTransform, state.ship.isAlive() );
	}
	else
	{
		shipCruisingShape.draw(context, shipTransform, state.ship.isAlive() );
	}

	asteroidShape.draw(context, state.asteroid.computeTransform(), state.asteroid.isAlive() );
	ufoShape.draw(context, state.ufo.computeTransform(), state.ufo.isAlive() );
}
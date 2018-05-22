#include "gameView.h"
#include "polygonShapes.inl"

void gameView::setup()
{
	shipCruisingShape.build(shipCruisingVertices);
	shipAcceleratingShape.build(shipAcceleratingVertices);
	asteroidShape.build(asteroidVertices);
	ufoShape.build(ufoVertices);

	ship.setBody(&state.ship);
	ship.setShape(&shipCruisingShape);
	ship.setScale(0.1f);
	asteroid.setBody(&state.asteroid);
	asteroid.setShape(&asteroidShape);
	asteroid.setScale(0.3f);
	ufo.setBody(&state.ufo);
	ufo.setShape(&ufoShape);
	ufo.setScale(0.02f);
}

void gameView::draw(renderContext& context)
{
	if (state.boostingForward || state.boostingBackward)
	{
		ship.setShape(&shipAcceleratingShape);
	}
	else
	{
		ship.setShape(&shipCruisingShape);
	}
	ship.draw(context);
	asteroid.draw(context);
	ufo.draw(context);
}
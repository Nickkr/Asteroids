#include "gameView.h"
#include "polygonShapes.inl"
#include "collision.h"
#include <stdio.h>


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

void gameView::draw(renderContext& context, GLuint uniColor)
{
	if (state.boostingForward || state.boostingBackward)
	{
		ship.setShape(&shipAcceleratingShape);
	}
	else
	{
		ship.setShape(&shipCruisingShape);
	}

	//change color to red when a collision between asteroid and ship occur
	if (state.collision) {
		glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);
		ship.draw(context);
		asteroid.draw(context);
		glUniform3f(uniColor, 1.0f, 1.0f, 1.0f);
		ufo.draw(context);
	}
	else
	{
		ship.draw(context);
		asteroid.draw(context);
		ufo.draw(context);
	}

}
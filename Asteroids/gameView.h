#pragma once

#include "gameState.h"
#include "renderContext.h"
#include "polygonShape.h"
#include "fixture.h"

class gameView
{
public:
	gameView(gameState& state)
		: state(state)
	{}

	void setup();
	void draw(renderContext& context);

private:
	gameState& state;

	polygonShape shipCruisingShape;
	polygonShape shipAcceleratingShape;
	polygonShape asteroidShape;
	polygonShape ufoShape;
	polygonShape bulletShape;
};
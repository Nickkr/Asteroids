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

	void drawScore(renderContext& context);
	void drawLife(renderContext& context);

	polygonShape shipCruisingShape;
	polygonShape shipAcceleratingShape;
	polygonShape asteroidShape;
	polygonShape ufoShape;
	polygonShape bulletShape;

	polygonShape zeroShape;
	polygonShape oneShape;
	polygonShape twoShape;
	polygonShape threeShape;
	polygonShape fourShape;
	polygonShape fiveShape;
	polygonShape sixShape;
	polygonShape sevenShape;
	polygonShape eightShape;
	polygonShape nineShape;

	polygonShape shipLifeShape;
};
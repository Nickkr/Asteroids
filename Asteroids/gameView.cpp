#include "gameView.h"
#include "polygonShapes.inl"
#include "digitShapes.inl"
#include "collision.h"
#include <stdio.h>

void gameView::setup()
{
	shipCruisingShape.build(shipCruisingVertices, 0.1f);
	shipAcceleratingShape.build(shipAcceleratingVertices, 0.1f);
	asteroidShape.build(asteroidVertices, 0.3f);
	ufoShape.build(ufoVertices, 0.02f);
	bulletShape.build(bulletVertices, 0.01f);

	zeroShape.build(zeroVertices, 0.01f);
	oneShape.build(oneVertices, 0.01f);
	twoShape.build(twoVertices, 0.01f);
	threeShape.build(threeVertices, 0.01f);
	fourShape.build(fourVertices, 0.01f);
	fiveShape.build(fiveVertices, 0.01f);
	sixShape.build(sixVertices, 0.01f);
	sevenShape.build(sevenVertices, 0.01f);
	eightShape.build(eightVertices, 0.01f);
	nineShape.build(nineVertices, 0.01f);
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
		if(asteroid->isAlive())
		{
		asteroidShape.draw(context, asteroid->computeTransform(), asteroid->isInvincible());
		}
	}
	for (auto& bullet : state.bullets)
	{
		bulletShape.draw(context, bullet->computeTransform(), bullet->isInvincible());

	}
	for (auto& ufoBullet : state.ufoBullets)
	{
		bulletShape.draw(context, ufoBullet->computeTransform(), ufoBullet->isInvincible(), true);

	}
	if(state.ufo.isAlive())
	{ 
		ufoShape.draw(context, state.ufo.computeTransform(), state.ufo.isInvincible());
	}

	drawScore(context);
}

void gameView::drawScore(renderContext& context)
{
	float posx = 0.9f;
	float posy = 0.9f;
	float scale = 0.05f;
	float margin = 0.02f;

	const polygonShape* digitShapes[] = { &zeroShape, &oneShape, &twoShape, &threeShape,
		&fourShape, &fiveShape, &sixShape, &sevenShape, &eightShape, &nineShape };
	int value = state.playerScore; 
	float fontScale = 3;
	mat4x4 transform = { 0 };
	transform._00 = fontScale;
	transform._11 = fontScale;
	transform._22 = fontScale;
	transform._33 = 1;
	transform._03 = posx; 
	transform._13 = posy; 
	for (int i = 0; i < 6; ++i) {
		int digit = value % 10; value /= 10;
		digitShapes[digit]->draw(context, transform, false);
		transform._03 -= scale + margin; 
	}
}
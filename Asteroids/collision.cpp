#include "collision.h"
#include "math.h"
#include <stdio.h>

bool checkCollision(gameObject& a, gameObject& b)
{
	vec2 cA = a.getBody()->getPos();
	vec2 cB = b.getBody()->getPos();
	float rA = a.getShape()->getRadius();
	float rB = b.getShape()->getRadius();
	if (length_squared(cA - cB) <= squared(rA + rB)) 
	{
		a.onCollisionWith(b);
		b.onCollisionWith(a);
		return true;
	}
	return false;
}
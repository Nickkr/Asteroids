#include "collision.h"
#include <math.h>
#include <stdio.h>

bool checkCollision(vec2 a, vec2 b)
{
	float r1 = 0.09; //radius for asteroid collision
	float r2 = 0.04; //radius for ship collision
	if (length_squared(a - b) <= ( (r1 + r2) * (r1 + r2) ) ) 
	{
		printf("ship colliding with asteroid \n");
		return true;
	}
	return false;
}
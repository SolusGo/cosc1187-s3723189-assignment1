#include "i3d_math.h"
#include <math.h>
i3d_math::i3d_math(){}



bool i3d_math::circleCollision(double x, double y, double r, double x2, double y2, double r2)
{
	bool collided = false;
	double distance_X = x2 - x;
	double distance_Y = y2 - y;
	double distance = sqrt((distance_X * distance_X) + (distance_Y * distance_Y));

	if (distance <= r + r2)
	{
		collided = true;
	}

	return collided;
}

bool i3d_math::inRadius(double x, double y, double x2, double y2, double r2)
{
	double distance = sqrt(pow(x - x2, 2) + pow(y - y2, 2));
	if (distance <= r2)
	{
		return true;
	}

	return false;
}

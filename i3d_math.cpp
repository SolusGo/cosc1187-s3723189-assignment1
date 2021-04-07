#include "i3d_math.h"

i3d_math::i3d_math(){}

coord* i3d_math::scalarMulp(coord *previous, double velocity)
{
	previous->x = previous->x * velocity;
	previous->y = previous->y * velocity;

	return previous;
}

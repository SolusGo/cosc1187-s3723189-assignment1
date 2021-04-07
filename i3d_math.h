#ifndef COORD_H
#define COORD_H

struct coord
{
	double x, y;
};

class i3d_math {
public:
	i3d_math();
	coord *scalarMulp(coord *previouspos, double velocity);
};
#endif

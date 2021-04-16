#ifndef COORD_H
#define COORD_H

struct coord
{
	coord(double x_coord, double y_coord)
	{
		x = x_coord;
		y = y_coord;
	}

	coord()
	{
		x = 0;
		y = 0;
	}
	double x, y;
	
};


class i3d_math {
public:
	i3d_math();
	bool circleCollision(double x, double y, double r, double x2, double y2, double r2);
	bool inRadius(double x, double y, double x2, double y2, double r2);

};
#endif

#pragma once
#ifndef ASTEROID_H
#define ASTEROID
#include "i3d_math.h"
class Asteroid {
public:
	Asteroid();
	double getRadius();
	double getX();
	double getY();
	double getRotation();
	void generateFeatures(double min_x, double min_y, double max_x, double max_y);
	void move(double time);
	void resetPos();
private:
	double radius;
	double rotation;
	coord* pos;
	coord originPos;
	double velocity;
};



#endif
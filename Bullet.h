#pragma once

#ifndef BULLET_H
#define BULLET
#include "i3d_math.h"
#define BULLET_VELOCITY 1000.00
class Bullet {
public:
	~Bullet();
	Bullet(double x, double y, double angle);

	
	void move(double dt);

	void setStatus(bool status);


	//Getters
	double getX();
	double getY();
	double getAngle();

private:

	coord* pos;
	double velocity;
	double direction_angle;
	bool status;

	
};


#endif
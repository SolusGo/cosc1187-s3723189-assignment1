#pragma once
#ifndef SHIP_H
#define SHIP_H
#include "i3d_math.h"
#define VELOCITY 2000.0
#define TURNING_VELOCITY 1000.0
class Ship {


public:

	Ship();
	~Ship();
	
	double getx();
	double gety();
	
	void moveLeft(double time);
	void moveRight(double time);
	void moveUp(double time);
	void setPosition(int x, int y);
	void setTime(float number);
	void setRotation(double number);
	double getrotation();
	void determineDirection(double newAngle, double time);
	double getradius();
private:

	// Coords 
	double rotation;
	coord *pos;
	coord *dir;
	double velocity;
	double hitradius; 
	double elapsed_time;
	void determinePosition(double time);
};















#endif


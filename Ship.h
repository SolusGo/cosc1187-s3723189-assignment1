#pragma once
#ifndef SHIP_H
#define SHIP_H
#include "i3d_math.h"

class Ship {
	// Constructor/Desctructor

public:

	Ship();
	~Ship();
	
	double getx();
	double gety();
	
	void moveLeft();
	void moveRight();
	void moveUp(double time);
	void setPosition(int x, int y);
	void setTime(float number);
	double getrotation();
	void determineDirection(double newAngle);
	double getradius();
private:

	// Coords 
	double rotation;
	coord *pos;
	coord *dir;
	double velocity;
	double hitradius; 
	double elapsed_time;
	/*double determinePosition(double old, double dir);*/
	void determinePosition(double time);
};















#endif


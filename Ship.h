#pragma once
#ifndef SHIP_H
#define SHIP_H
#include "i3d_math.h"

class Ship {
	// Constructor/Desctructor
public:

	Ship();

	
	double getx();
	double gety();
	
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void setPosition(int x, int y);
	void setMaxPosition(int x, int y);
	void setTime(float number);
	double getrotation();
private:

	// Coords 
	int maxX;
	int maxY;
	double rotation;
	coord *pos;
	coord *dir;
	double velocity;
	double elapsed_time;
	double determinePosition(double old, double dir);

};















#endif


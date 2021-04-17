#pragma once
#ifndef ASTEROID_H
#define ASTEROID
#include "i3d_math.h"
#include <deque>

#define RANGE 300
#define MINIMUM 200
#define ROTATION_RANGE 200
#define ROTATION_MIN -100.0
#define RADIUS_RANGE 50
#define RADIUS_MIN 50
//TO CALCULATE POTENTIAL MAX = RANGE + MINIMUM 
class Asteroid {
public:
	Asteroid();
	double getRadius();
	double getX();
	double getY();
	double get_direction();
	double get_rotation();




	void generateFeatures(double min_x, double min_y, double max_x, double max_y);
	void move(double time);
	void resetPos();
	void reduceHealth(int i);
	std::deque<coord> get_corners();
	int get_hitpoints();
private:
	void initiateCorners();
	double radius;
	double direction_angle;
	
	coord* pos;
	coord originPos;
	double velocity;
	int hitpoints;
	double rotation_speed;
	double rotation;
	std::deque<coord> corners;
};


#endif
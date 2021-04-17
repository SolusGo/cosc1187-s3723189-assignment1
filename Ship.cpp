#include "Ship.h"
#include <math.h>
#include <iostream>


Ship::Ship() 
{
	
	pos = new coord();
	dir = new coord();
	this->pos->x = 500.00;
	this->pos->y = 500.00;
	this->dir->x = 500.00;
	this->dir->y = 550.00;
	this->velocity = VELOCITY;
	this->elapsed_time = 0.0;
	this->rotation = 315.0;
	this->hitradius = 140.0 / 2.0;
}

Ship::~Ship()
{
	delete pos;
	delete dir;
}

double Ship::getx()
{
	return this->pos->x;

}

double Ship::gety()
{
	return this->pos->y;
}

void Ship::setPosition(int x, int y)
{
	this->pos->x = x;
	this->pos->y = y;
}


void Ship::moveUp(double time)
{
	determinePosition(time);
}

void Ship::moveLeft(double time)
{
	determineDirection(TURNING_VELOCITY, time);
}

void Ship::moveRight(double time)
{
	determineDirection(-TURNING_VELOCITY, time);
}


void Ship::setTime(float number)
{
	this->elapsed_time = number;

}

void Ship::determinePosition(double time)
{
	double angle = (this->rotation + 90) * 3.14 / 180.0;
	double newYpos = this->pos->y + (sin(angle) * this->velocity * time);
	double newxpos = this->pos->x + (cos(angle) * this->velocity * time);

	this->pos->y = newYpos;
	this->pos->x = newxpos;
}

double Ship::getrotation()
{
	return this->rotation;
}

void Ship::determineDirection(double newAngle, double dt)
{
	
	double new_angle = this->rotation + newAngle* dt ;
	double angle_between = newAngle;

	if (361 <= new_angle)
	{
		new_angle = 0;
	}
	else if (-1 >= new_angle)
	{
		new_angle = 360;
	}

	this->rotation = new_angle;

} 

double Ship::getradius()
{
	return this->hitradius;
}

void Ship::setRotation(double x)
{
	this->rotation = x;
}

// Calculate movement NewPos = Oldps + (Dir * Vel * dt) where Dir = 1 or -1


#include "Ship.h"
#include <math.h>
#include <iostream>

#define VELOCITY 2000.0

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
	this->rotation = 0.0;
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

void Ship::moveLeft()
{
	determineDirection(10);
}

void Ship::moveRight()
{
	determineDirection(-10);
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

void Ship::determineDirection(double newAngle)
{
	
	double new_angle = this->rotation + newAngle;
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



	/*double x = this->dir->x - this->pos->x;
	double y = this->dir->y- this->pos->y;

	double angle = 45 * 3.14 / 180.0;

	this->dir->x = 10 * cos(0) + this->dir->x;
	this->dir->y = 10* sin(0) + this->dir->y;
	*/
	 
} 

double Ship::getradius()
{
	return this->hitradius;
}


// Calculate movement NewPos = Oldps + (Dir * Vel * dt) where Dir = 1 or -1


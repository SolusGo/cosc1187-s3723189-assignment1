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
	this->velocity = 1000.0;
	this->elapsed_time = 0.0;
	this->rotation = 0.0;
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
	//this->pos->y = determinePosition(this->pos->y, 1.0);
	determinePosition(time);

	
}

void Ship::moveLeft()
{
	//this->pos->x = determinePosition(this->pos->x, -1.0);



	

	determineDirection(10);
	printf("%f, %f : %f, %f \n", this->pos->x, this->pos->y, this->dir->x, this->dir->y);
}

void Ship::moveRight()
{
	//this->pos->x = determinePosition(this->pos->x, 1.0);
	



	
	determineDirection(-10);
	printf("%f, %f : %f, %f \n", this->pos->x, this->pos->y, this->dir->x, this->dir->y);

}


void Ship::setTime(float number)
{
	this->elapsed_time = number;

}

//double Ship::determinePosition(double old, double dir)
//{
//	double newPos = old + (dir * this->velocity * this->elapsed_time);
//	return newPos;
//}

void Ship::determinePosition(double time)
{
	double magnitude = sqrt((pow(this->dir->x - this->pos->x, 2)) + (pow(this->dir->y - this->pos->y, 2)));
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



	double x = this->dir->x - this->pos->x;
	double y = this->dir->y- this->pos->y;

	double angle = 45 * 3.14 / 180.0;
	printf("%f, %f \n", x, y);
	printf("%f, a %f \n", cos(145.00), this->rotation);


	this->dir->x = 10 * cos(angle) + this->dir->x;
	this->dir->y = 10* sin(angle) + this->dir->y;
	
	
} 



// Calculate movement NewPos = Oldps + (Dir * Vel * dt) where Dir = 1 or -1


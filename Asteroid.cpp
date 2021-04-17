#include "Asteroid.h"
#define _USE_MATH_DEFINES
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "i3d_math.h"


Asteroid::Asteroid()
{
	
	originPos.x = 1.0;
	originPos.y = 1.0;
	int random = rand() % 50 + 50;
	radius = random * 1.0;
	hitpoints = (int)random;
	this->pos = new coord();
	this->direction_angle = 0.0;
	this->velocity =(double)( rand() % RANGE) + MINIMUM;
	rotation_speed = (double)(rand() % ROTATION_RANGE) + ROTATION_MIN;
	rotation = (double)(rand() % 360);
	
}


double Asteroid::getX()
{
	return this->pos->x;
}

double Asteroid::getY()
{
	return this->pos->y;
}

double Asteroid::getRadius()
{
	return this->radius;
}

double Asteroid::get_direction()
{
	return this->direction_angle;
}

void Asteroid::generateFeatures(double min_x, double min_y, double max_x, double max_y)
{
	double tempX, tempY, theta;
	int xrange = (int) (max_x -  min_x);
	int yrange = (int) (max_y - min_y);

	
	theta = ((double)rand() / (double)RAND_MAX) * 2.0 * M_PI;
	
	tempX =   (max_x * 0.5) + cos(theta) * ((max_x / 2.0) + 100.00);
	
	tempY = (max_y * 0.5) + sin(theta) * ((max_x / 2.0) + 100.00);
	
	this->pos->x = tempX * 1.0;
	this->pos->y = tempY * 1.0;



	this->originPos.x = tempX * 1.0;
	this->originPos.y = tempY * 1.0;

	//Generate a random coordinate within the arena
	//Calculate angle based of position of asteroid and this coordinate inside arena
	
	
	tempX = rand() % xrange + min_x;
	tempY = rand() % yrange + min_y;

	double dest_x = (double)tempX;
	double dest_y = (double)tempY;
	double raidantheta = atan2(dest_y - this->getY(), dest_x - this->getX()) * 180/ 3.14159265;
	if (raidantheta < 0.0)
		raidantheta += 360.0;

	this->direction_angle = raidantheta;

	initiateCorners();

}

void Asteroid::resetPos()
{

	this->pos->x = this->originPos.x;
	this->pos->y = this->originPos.y;
	
}

void Asteroid::move(double time)
{
	
	double What = this->pos->x;
	double Eh = this->pos->y;
	
	double angle = (this->direction_angle) * 3.14 / 180.0;
	if (time > 0.0)
	{

		double newYpos = this->pos->y + (sin(angle) * this->velocity * time);
		double newxpos = this->pos->x + (cos(angle) * this->velocity * time);

		this->pos->y = newYpos;
		this->pos->x = newxpos;

		for (int i = 0; i < corners.size(); i++)
		{
			corners[i].x = corners[i].x + (cos(angle) * this->velocity * time);
			corners[i].y = corners[i].y + (sin(angle) * this->velocity * time);
		}

		rotation = rotation - rotation_speed * time;

		if (rotation >= 361.0)
		{
			rotation = 0.0;
		}

		if (rotation < 0.0)
		{
			rotation = 360.0;
		}

	}

	
	
}

void Asteroid::initiateCorners()
{
	
	double angle = 0.0;
	double r = 0.0;
	double x, y;
	
	for (r; r < 2.0 * M_PI;)
	{
		x = originPos.x + (radius*cos(r));
		y = originPos.y + (radius*sin(r));
		r += (20.0 + ((double)(rand() % 40))) * M_PI / 180.0;
		corners.push_back(coord(x, y));

	}


	
}

std::deque<coord> Asteroid::get_corners()
{
	return corners;
}

double Asteroid::get_rotation()
{
	return rotation;
}

void Asteroid::reduceHealth(int i)
{
	hitpoints -= i;
}

int Asteroid::get_hitpoints()
{
	return hitpoints;
}
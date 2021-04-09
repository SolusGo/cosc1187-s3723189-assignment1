#include "Asteroid.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "i3d_math.h"
Asteroid::Asteroid()
{
	srand(time(NULL));

	int random = rand() % 10 + 10;
	radius = random * 1.0;
	this->pos = new coord();
	this->rotation = 0.0;
	this->velocity = 200.0;
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

double Asteroid::getRotation()
{
	return this->rotation;
}

void Asteroid::generateFeatures(double min_x, double min_y, double max_x, double max_y)
{
	int tempX, tempY, randomSign;
	int xrange = (int) (max_x -  min_x);
	int yrange = (int) (max_y - min_y);
	randomSign = rand() % 2;

	if (randomSign == 0)
	{
		tempX = rand() % 400 + (int)max_x;
	}
	else
	{
		tempX = -(rand() % 400) + (int)min_x;
	}
	
	randomSign = rand() % 1;

	if (randomSign == 0)
	{
		tempY = rand() % 400 + (int)max_y;
	}
	else
	{
		tempY = -(rand() % 400) + (int)min_y;
	}

	this->pos->x = tempX * 1.0;
	this->pos->y = tempY * 1.0;

	tempX = rand() % xrange + min_x;
	tempY = rand() % yrange + min_y;

	double dest_x = (double)tempX;
	double dest_y = (double)tempY;

	double raidantheta = atan2(dest_y - this->getY(), dest_x - this->getX());
	if (raidantheta < 0.0)
		raidantheta += 360.0;

	this->rotation = raidantheta;
	std::cout << this->pos->y << " ];'" << this->pos->x << std::endl;
}

void Asteroid::move(double time)
{
	
	double What = this->pos->x;
	double Eh = this->pos->y;
	
	double angle = this->rotation;
	printf(" What %f\n", angle);
	if (time > 0.0)
	{

		double newYpos = this->pos->y + (sin(angle) * this->velocity * time);
		double newxpos = this->pos->x + (cos(angle) * this->velocity * time);

		this->pos->y = newYpos;
		this->pos->x = newxpos;
	}
	//std::cout << newYpos << " " << newxpos << std::endl;
}


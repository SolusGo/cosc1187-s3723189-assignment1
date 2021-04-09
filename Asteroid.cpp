#include "Asteroid.h"
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
	
	randomSign = rand() % 2;

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



	this->originPos.x = tempX * 1.0;
	this->originPos.y = tempY * 1.0;
	printf("%f, %f | %f, %f \n", originPos.x, originPos.y, this->pos->x, this->pos->y);
	
	tempX = rand() % xrange + min_x;
	tempY = rand() % yrange + min_y;

	double dest_x = (double)tempX;
	double dest_y = (double)tempY;
	double raidantheta = atan2(dest_y - this->getY(), dest_x - this->getX()) * 180/ 3.14159265;
	if (raidantheta < 0.0)
		raidantheta += 360.0;

	this->rotation = raidantheta;

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
	
	double angle = (this->rotation) * 3.14 / 180.0;
	//printf("x: %f, y: %f, angle; %f  \n", What, Eh, angle * 180/3.14);
	if (time > 0.0)
	{

		double newYpos = this->pos->y + (sin(angle) * this->velocity * time);
		double newxpos = this->pos->x + (cos(angle) * this->velocity * time);

		this->pos->y = newYpos;
		this->pos->x = newxpos;
	}
	//std::cout << this->pos->y << " " << this->pos->x << std::endl;
}


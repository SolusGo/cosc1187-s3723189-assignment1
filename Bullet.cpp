#include "Bullet.h"
#include <math.h>
#include <iostream>
Bullet::Bullet(double x, double y, double angle)
{
	pos = new coord(x, y);
	direction_angle = angle;
	velocity = BULLET_VELOCITY;
	status = true;
}


Bullet::~Bullet()
{
	delete pos;
}

void Bullet::move(double dt)
{
	double angle = (this->direction_angle + 90) * 3.14 / 180.0;
	double newYpos = this->pos->y + (sin(angle) * this->velocity * dt);
	double newxpos = this->pos->x + (cos(angle) * this->velocity * dt);
	this->pos->y = newYpos;
	this->pos->x = newxpos;
}


void Bullet::setStatus(bool status)
{
	this->status = status;
}

//Getters
double Bullet::getX()
{
	return pos->x;
}

double Bullet::getY()
{
	return pos->y;
}

double Bullet::getAngle()
{
	return direction_angle;
}




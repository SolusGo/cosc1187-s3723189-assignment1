#include "Ship.h"

Ship::Ship() 
{
	pos = new coord();
	dir = new coord();
	this->maxX = 500.00;
	this->maxY = 500.00;
	this->pos->x = 500.00;
	this->pos->y = 500.00;
	this->dir->x = 500.00;
	this->dir->y = 501.00;
	this->velocity = 500.0;
	this->elapsed_time = 0.0;
	this->rotation = 40.0;
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

void Ship::moveDown()
{
	this->pos->y = determinePosition(this->pos->y, -1.0);
}

void Ship::moveUp()
{
	this->pos->y = determinePosition(this->pos->y, 1.0);
	
}

void Ship::moveLeft()
{
	//this->pos->x = determinePosition(this->pos->x, -1.0);
	this->rotation += 1.0;
}

void Ship::moveRight()
{
	//this->pos->x = determinePosition(this->pos->x, 1.0);
	this->rotation -= 1.0;
}

void Ship::setMaxPosition(int x, int y)
{
	this->maxX = x;
	this->maxY = y;

}

void Ship::setTime(float number)
{
	this->elapsed_time = number;

}

double Ship::determinePosition(double old, double dir)
{
	double newPos = old + (dir * this->velocity * this->elapsed_time);
	return newPos;
}

double Ship::getrotation()
{
	return this->rotation;
}

// Calculate movement NewPos = Oldps + (Dir * Vel * dt) where Dir = 1 or -1


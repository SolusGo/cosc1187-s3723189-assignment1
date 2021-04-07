#include "GameState.h"
#include <math.h>
#include <iostream>
#include "Ship.h"

#if _WIN32
#   include <Windows.h>
#endif
#if __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif

GameState::GameState()
{
	this->min_X = 0.0;
	this->max_X = 0.0;
	this->min_Y = 0.0;
	this->max_Y = 0.0;
	this->ship = new Ship();
	this->elapsed_time = 0.0;
}

double GameState::getShipX()
{
	return this->ship->getx();
}

double GameState::getShipY()
{
	return this->ship->gety();
}

void GameState::setMax(double x, double y)
{
	this->max_X = x;
	this->max_Y = y;
}

void GameState::setMin(double x, double y)
{
	this->min_X = x;
	this->min_Y = y;
}

bool GameState::hasCollided()
{
	
	bool collided_x = ship->getx() >= this->max_X || ship->getx() <= this->min_X;
	bool collided_y = ship->gety() >= this->max_X || ship->gety() <= this->min_Y;
	if (collided_x || collided_y)
	{
		return true;
	}
	return false;
}

void GameState::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:

	case 'a':
		ship->moveLeft();
		break;
	case 'd':
		ship->moveRight();
		break;
	case 'w':
		if (!hasCollided())
		ship->moveUp(this->elapsed_time);
		else
		{
			this->ship->setPosition(400, 400);
		}
		break;
	case 'q':
		exit(EXIT_SUCCESS);
		break;
	default:
		break;
	}
}

void GameState::setTime(double time)
{
	this->elapsed_time = time;
}

double GameState::getShipRot()
{
	return this->ship->getrotation();
}
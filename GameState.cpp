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

void GameState::setArena(double x, double y)
{
	double vertical_wall = x * 0.10;
	double horizontal_wall = y * 0.10;
	this->min_X = vertical_wall;
	this->min_Y = horizontal_wall;
	this->max_X = vertical_wall*9.0;
	this->max_Y = horizontal_wall*9.0;
}

bool GameState::hasCollided()
{
	bool collided_max_x = inRadius(this->max_X, this->getShipY());
	bool collided_min_x = inRadius(this->min_X , this->getShipY());
	bool collided_max_y = inRadius(this->getShipX(), this->max_Y);
	bool collided_min_y = inRadius(this->getShipX(), this->min_Y);
	if (collided_max_x || collided_min_x || collided_max_y|| collided_min_y)
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

double GameState::getShipHitBox()
{
	return this->ship->getradius();
}

bool GameState::inRadius(double x, double y)
{
	double distance = sqrt(pow(x - this->getShipX(), 2) + pow(y - this->getShipY(), 2));
	printf("%f, %f \n", x, y);
	if (distance <= this->getShipHitBox())
	{
		return true;
	}

	return false;
}

double GameState::getArenaCoords(int i)
{
	double point = -1.0;

	switch (i)
	{
	case MIN_X:
		point = this->min_X;
		break;
	case MIN_Y:
		point = this->min_Y;
		break;
	case MAX_X:
		point = this->max_X;
		break;
	case MAX_Y:
		point = this->max_Y;
		break;
	}
	return point;
}
#include "GameState.h"
#include <math.h>
#include <iostream>
#include "Ship.h"
#include <stdlib.h>
#include "Asteroid.h"

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

#include<stdlib.h>
GameState::GameState()
{
	srand(time(NULL));

	this_time = clock();
	last_time = this_time;

	//  timers
	timer = 0.0;
	particle_timer = 0.0;

	this->min_coords = new coord();
	this->max_coords = new coord();
	this->ship = new Ship();
	this->ship_spawn = new coord();

	this->min_coords->x = 256.00;
	this->min_coords->y = 200.00;

	this->max_coords->x = 2304.00;
	this->max_coords->y = 1296.00;

	this->currentWave = 1;

	this->dt = 0.0;
	asteroid = new Asteroid();
	initiateAsteroids();
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
	this->min_coords->x = vertical_wall;
	this->min_coords->y = horizontal_wall;
	this->max_coords->x = vertical_wall*9.0;
	this->max_coords->y = horizontal_wall*9.0;
	this->ship_spawn->x = vertical_wall + 100.0;
	this->ship_spawn->y = horizontal_wall + 100.0;
	this->ship->setPosition(this->ship_spawn->x, this->ship_spawn->y);

	//printf("%f, %f, %f, %f \n", this->min_X, this->min_Y, this->max_X, this->max_Y);
}

bool GameState::hasCollided()
{
	bool collided_max_x = inRadius(this->max_coords->x, this->getShipY());
	bool collided_min_x = inRadius(this->min_coords->x, this->getShipY());
	bool collided_max_y = inRadius(this->getShipX(), this->max_coords->y);
	bool collided_min_y = inRadius(this->getShipX(), this->min_coords->y);
	if (collided_max_x || collided_min_x || collided_max_y|| collided_min_y)
	{
		return true;
	}

	for (int i = 0; i < this->currentWave; i++)
	{
		if (this->circleCollision(this->getAsteroidX(i), this->getAsteroidY(i), this->getAsteroidRadius(i)))
		{
			return true;
		}
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
		this->addParticle();
		break;
	case 'd':
		ship->moveRight();
		this->addParticle();
		break;
	case 'w':
		if (!hasCollided())
		{
			ship->moveUp(this->dt);
			this->addParticle();
		}

		asteroid->move(this->dt);
		break;
	case 'q':
		exit(EXIT_SUCCESS);
		break;
	default:
		break;
	}
}

// TODO: Implement Reset all asteroids spawnpoint method
// TODO: Implement particles 

void GameState::setTime(double time)
{
	this->dt = time;
}

double GameState::getShipRot()
{
	return this->ship->getrotation();
}

double GameState::getShipHitBox()
{
	return this->ship->getradius();
}


double GameState::getArenaCoords(int i)
{
	double point = -1.0;

	switch (i)
	{
	case MIN_X:
		point = this->min_coords->x;
		break;
	case MIN_Y:
		point = this->min_coords->y;
		break;
	case MAX_X:
		point = this->max_coords->x;
		break;
	case MAX_Y:
		point = this->max_coords->y;
		break;
	}
	return point;
}

void GameState::resetShip()
{
	this->ship->setPosition(this->ship_spawn->x, this->ship_spawn->y);
}


void GameState::initiateAsteroids()
{
	//asteroid->generateFeatures(min_coords->x, min_coords->y, max_coords->x, max_coords->y);

	for (int i = 0; i < MAX_ASTEROIDS; i++)
	{
		asteroids[i] = new Asteroid();
		asteroids[i]->generateFeatures(min_coords->x, min_coords->y, max_coords->x, max_coords->y);
	}
}



double GameState::getAsteroidRadius(int x)
{
	return this->asteroids[x]->getRadius();
}

void GameState::moveAsteroids()
{
	//this->asteroid->move(this->elapsed_time);
	for (int i = 0; i < this->currentWave; i++)
	{
		this->asteroids[i]->move(this->dt);
	}
}

double GameState::getAsteroidX(int x)
{
	return this->asteroids[x]->getX();
}

double GameState::getAsteroidY(int x)
{
	return this->asteroids[x]->getY();
}


/*
	Collision methods
*/
bool GameState::circleCollision(double x, double y, double r)
{
	bool collided = false;
	//Get distance
	double distance_X = ship->getx() - x;
	double distance_Y = ship->gety() - y;
	double distance = sqrt((distance_X * distance_X) + (distance_Y * distance_Y));

	if (distance <= r + this->ship->getradius())
	{
		collided = true;
	}

	return collided;

}

bool GameState::inRadius(double x, double y)
{
	double distance = sqrt(pow(x - this->getShipX(), 2) + pow(y - this->getShipY(), 2));
	if (distance <= this->getShipHitBox())
	{
		return true;
	}

	return false;
}


int GameState::nearWall()
{
	int number = -1;
	bool near_max_x = inRadius(this->max_coords->x - 150.00, this->getShipY());
	bool near_min_x = inRadius(this->min_coords->x + 150.00, this->getShipY());
	bool near_y = inRadius(this->getShipX(), this->max_coords->y - 150.00);
	bool near_min_y = inRadius(this->getShipX(), this->min_coords->y + 150.00);



	/*if (near_max_x || near_min_x || near_y || near_min_y)
	{
		return true;
	}*/

	if (near_max_x) 
	{
		number = 0;
	}
	else if (near_min_x)
	{
		number = 1;
	}
	else if (near_y)
	{
		number = 2;
	}
	else if (near_min_y)
	{
		number = 3;
	}
	
	return number;
}

void GameState::startWave()
{
	if (currentWave < MAX_ASTEROIDS)
	{
		this->currentWave++;
	}
	
	for (int i = 0; i < currentWave; i++)
	{
		this->asteroids[i]->resetPos();
	}
}

int GameState::getWave()
{
	return this->currentWave;
}

void GameState::checkGameStatus()
{

	std::deque<Particle*>::iterator it = particles.begin();
	for (it = particles.begin(); it != particles.end(); it++)
	{
		(*it)->move(this->dt);
	}

	manageParticles();

	this_time = clock();

	timer += (double)(this_time - last_time);
	
	particle_timer += (double)(this_time - last_time);

	last_time = this_time; 

	if (particle_timer > (double)(0.5 * CLOCKS_PER_SEC))
	{
		particle_timer -= (double)(1 * CLOCKS_PER_SEC);
		
	}

	if (timer > (double)(WAVE_INTERVAL * CLOCKS_PER_SEC))
	{
		timer -= (double)(WAVE_INTERVAL * CLOCKS_PER_SEC);
		startWave();
		
		
	}

	
}

void GameState::manageParticles()
{
	
	
	std::deque<Particle*>::iterator it = particles.begin();

	while (it != particles.end())
	{
		if ((*it)->getStatus() == false)
		{
			std::cout << "erased \n";
			it = particles.erase(it);
		} else
		it++;
	}

	

	for (it = particles.begin(); it != particles.end(); it++)
	{
		
		(*it)->reduceDuration();
	}
	
}

void GameState::addParticle()
{
	particles.push_back(new Particle(this->getShipRot(), ship->getx(), ship->gety()));
}



double GameState::getAlpha(int i)
{
	return particles[i]->getparticleTransparency();
}

double GameState::getParticles()
{
	return particles.size();
}

void GameState::setElapsedtime(double time)
{
	this->elapsedtime = time;
}

double GameState::getParticleX(int x)
{
	return particles[x]->getX();
}

double GameState::getParticleY(int x)
{
	return particles[x]->getY();
}

double GameState::getParticleRotation(int x)
{
	return particles[x]->getRotation();
}


double GameState::getParticleSize(int i)
{
	return particles[i]->getSize();
}
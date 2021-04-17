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

	fire_bullet = false;
	make_particle = false;
	//  timers
	timer = 0.0;
	game_time = 0.0;
	wave_timer = 0.0;
	bullet_timer = 0.0;
	particle_timer = 0.0;
	score = 0;
	ship_destroyed = false;
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
	initiateAsteroids();
}

GameState::~GameState()
{
	delete min_coords;
	delete max_coords;
	delete ship;
	delete ship_spawn;

}

void GameState::setArena(double x, double y)
{
	double vertical_wall = x * MIN_WALL_WIDTH;
	double horizontal_wall = y * MIN_WALL_HEIGHT;
	this->min_coords->x = vertical_wall;
	this->min_coords->y = horizontal_wall;
	this->max_coords->x = vertical_wall* MAX_WALL_WIDTH;
	this->max_coords->y = horizontal_wall* MAX_WALL_HEIGHT;
	this->ship_spawn->x = vertical_wall + 100.0;
	this->ship_spawn->y = horizontal_wall + 100.0;
	this->ship->setPosition(this->ship_spawn->x, this->ship_spawn->y);

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

	for (int i = 0; i < this->getNumAsteroids(); i++)
	{
		if (math.circleCollision(this->getAsteroidX(i), this->getAsteroidY(i), this->getAsteroidRadius(i), ship->getx(), ship->gety(), ship->getradius()))
		{
			return true;
		}
	}
	return false;
}

bool GameState::hasCollided(double x, double y)
{
	bool collided_max_x = x >= max_coords->x;

	bool collided_min_x = x <= min_coords->x;
	bool collided_max_y = y >= max_coords->y;
	bool collided_min_y = y <= min_coords->y;
	if (collided_max_x || collided_min_x || collided_max_y || collided_min_y)
	{
		return true;
	}

	
	return false;
}



void GameState::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{

	case SPACEBAR:
		if (fire_bullet == false)
		{
			fire_bullet = true;
		}
		if (!is_alive())
		{
			reset_Game();
		}
		break;

	case LEFT:
	case LEFT_2:
		if (is_alive())
		{
			make_particle = true;
			ship->moveLeft(dt);
			//this->addParticle();
		}
		else
		{
			reset_Game();
		}
		break;
	case RIGHT:
	case RIGHT_2:
		if (is_alive())
		{
			make_particle = true;
			ship->moveRight(dt);
			//this->addParticle();
		}
		else
		{
			reset_Game();
		}
		break;
	case FORWARD:
	case FORWARD_2:
		if (is_alive())
		{
			make_particle = true;
			ship->moveUp(this->dt);
			//this->addParticle();
		}
		else
		{
			reset_Game();
		}

		break;
	case EXIT_GAME:
	case EXIT_GAME_2:
		exit(EXIT_SUCCESS);
		break;
	default:
		if (!is_alive())
		{
			reset_Game();
		}
		
		break;
	}
}

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

void GameState::reset_Game()
{
	score = 0;
	currentWave = 0;
	game_time = 0.0;
	wave_timer = 0.0;
	startWave();
	resetShip();
}

void GameState::resetShip()
{
	this->ship->setPosition(this->ship_spawn->x, this->ship_spawn->y);
	this->ship->setRotation(315.0);
	ship_destroyed = false;
}


void GameState::initiateAsteroids()
{

	for (int i = 0; i < currentWave; i++)
	{
		asteroids.push_back(new Asteroid());
		asteroids.back()->generateFeatures(min_coords->x, min_coords->y, max_coords->x, max_coords->y);
	}


}



double GameState::getAsteroidRadius(int x)
{
	return this->asteroids[x]->getRadius();
}

void GameState::moveAsteroids()
{
	std::deque<Asteroid*>::iterator it = asteroids.begin();

	while (it != asteroids.end())
	{
		(*it)->move(this->dt);
		it++;
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



bool GameState::inRadius(double x, double y)
{
	double distance = sqrt(pow(x - this->getShipX(), 2) + pow(y - this->getShipY(), 2));
	if (distance <= this->getShipHitBox())
	{
		return true;
	}

	return false;
}



bool GameState::nearWall(int i)
{
	bool near_max_x = math.inRadius(this->max_coords->x - WARNING_DISTANCE, this->getShipY(), ship->getx(), ship->gety(), ship->getradius());
	bool near_min_x = math.inRadius(this->min_coords->x + WARNING_DISTANCE, this->getShipY(), ship->getx(), ship->gety(), ship->getradius());
	bool near_y = math.inRadius(this->getShipX(), this->max_coords->y - WARNING_DISTANCE, ship->getx(), ship->gety(), ship->getradius());
	bool near_min_y = math.inRadius(this->getShipX(), this->min_coords->y + WARNING_DISTANCE, ship->getx(), ship->gety(), ship->getradius());


	if (i == 1) 
	{
		return near_max_x;
	}
	else if (i == 3)
	{
		return  near_min_x;
	}
	else if (i == 2)
	{
		return near_y;
	}
	else if (i == 0)
	{
		return near_min_y;
	}
	
	return false;
}

void GameState::startWave()
{
	this->currentWave++;
	
	
	for (int i = 0; i < asteroids.size(); i++)
	{
		delete asteroids[i];
	}

	asteroids.clear();
	initiateAsteroids();
}

int GameState::getNumAsteroids()
{
	return this->asteroids.size();
}

void GameState::updateGameStatus()
{
	moveAsteroids();
	manageParticles();
	updateBulletStatus();

	if (hasCollided())
	{
		ship_destroyed = true;
		ship->setPosition(-1000, -1000);
	}

	std::deque<Asteroid*>::iterator it3 = asteroids.begin();

	while (it3 != asteroids.end())
	{
		if ((*it3)->get_hitpoints() <= 0)
		{
			score += 1;
			delete* it3;
			it3 = asteroids.erase(it3);
		}
		else
		it3++;
	}

	this_time = clock();

	timer += (double)((double)this_time - (double)last_time);
	bullet_timer += (double)((double)this_time - (double)last_time);
	particle_timer += (double)((double)this_time - (double)last_time);
	last_time = this_time; 

	if (particle_timer > (double)(PARTICLE_DELAY * CLOCKS_PER_SEC))
	{
		particle_timer -= (double)(PARTICLE_DELAY * CLOCKS_PER_SEC);
		if (make_particle == true)
		{
			this->addParticle();
			make_particle = false;
		}
	}

	if (bullet_timer > (double)(FIRING_RATE * CLOCKS_PER_SEC))
	{
		bullet_timer -= (double)(FIRING_RATE * CLOCKS_PER_SEC);
		if (fire_bullet == true)
		{
			bullets.push_back(new Bullet(ship->getx(), ship->gety(), ship->getrotation()));
			fire_bullet = false;
		}
	}


	if (timer > (double)(1 * CLOCKS_PER_SEC))
	{
		timer -= (double)(1 * CLOCKS_PER_SEC);

		game_time += 1.0;
		wave_timer += 1.0;
		
	}

	if (wave_timer == WAVE_INTERVAL)
	{
		wave_timer = 0;
		startWave();
	}

	std::deque<Particle*>::iterator it = particles.begin();
	for (it = particles.begin(); it != particles.end(); it++)
	{
		(*it)->move(this->dt);
	}

	std::deque<Bullet*>::iterator it2 = bullets.begin();
	while(it2 != bullets.end())
	{
		(*it2)->move(dt);
		it2++;
	}
	
	
}
//Manages Bullets
//Iterates and checks if hits wall/asteroid then changes game state ie. reduce asteroid health on collision
void GameState::updateBulletStatus()
{
	std::deque<Bullet*>::iterator it2 = bullets.begin();
	std::deque<Asteroid*>::iterator it;
	bool inRadius = false;
	bool collided = false;
	bool hit_wall = false;
	while (it2 != bullets.end())
	{
		it = asteroids.begin();

		while (it != asteroids.end())
		{
			inRadius = math.circleCollision((*it2)->getX(), (*it2)->getY(), 20, (*it)->getX(), (*it)->getY(),
				(*it)->getRadius());
			
			collided = inRadius;
			if (collided)
			{
				delete* it2;
				it2 = bullets.erase(it2);
				(*it)->reduceHealth(20);
				break;
			}
			it++;
		}

		if (collided == false)
		{
			hit_wall = hasCollided((*it2)->getX(), (*it2)->getY());
			
			if (hit_wall)
			{
				delete* it2;
				it2 = bullets.erase(it2);
			}
		}
		
		collided = hit_wall || inRadius;
		
		std::cout << collided << std::endl;
	
		if (collided == false)
		{
			it2++;
		}
		else
		{
			break;
		}
	}
}

// Manages particles

void GameState::manageParticles()
{
	
	
	std::deque<Particle*>::iterator it = particles.begin();
	//Check if a particle is considered "dead"
	while (it != particles.end())
	{
		if ((*it)->getStatus() == false)
		{
			delete *it;
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


//GETTERS 
double GameState::getAlpha(int i)
{
	return particles[i]->getparticleTransparency();
}

double GameState::getParticles()
{
	return particles.size();
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

std::deque<coord> GameState::get_asteroid_corners(int i)
{
	return asteroids[i]->get_corners();
}

double GameState::getAsteroidRotation(int i)
{
	return asteroids[i]->get_rotation();
}

double GameState::getBulletDirection(int i)
{
	return bullets[i]->getAngle();
}

double GameState::getBullet_X(int i)
{
	return bullets[i]-> getX();
}

double GameState::getBullet_Y(int i)
{
	return bullets[i]->getY();
}


int GameState::getBulletsSize()
{
	return bullets.size();
}

int GameState::getScore()
{
	return score;
}

double GameState::get_time()
{
	return game_time;
}

bool GameState::is_alive()
{
	return !ship_destroyed;
}

double GameState::getShipX()
{
	return this->ship->getx();
}

double GameState::getShipY()
{
	return this->ship->gety();
}
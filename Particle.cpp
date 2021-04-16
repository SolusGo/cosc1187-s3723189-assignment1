#include "Particle.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
Particle::Particle(double rotation, double x, double y)
{

	pos = new coord();
	setPosition(x, y);
	setRotation(rotation);
	rotation = 0.0;
	duration_timer = 0.0;
	this_time = clock();
	last_time = this_time;
	decayRate = 1.0 / DECAY;
	particleTransparency = 1.0;
	is_alive = true;
	velocity = PARTICLE_VELOCITY;
	size = INITIAL_PARTICLE_SIZE;
}

Particle::~Particle()
{
	delete pos;
}

void Particle::reduceDuration()
{
	this_time = clock();

	duration_timer += (double)(this_time - last_time);

	last_time = this_time;

	if (duration_timer > (double)(0.5 * CLOCKS_PER_SEC))
	{
		
		duration_timer -= (double)(0.5 * CLOCKS_PER_SEC);


		particleTransparency -= decayRate;
		if (particleTransparency <= 0)
		{
			particleTransparency = 0.1;
		}

		size -= 4.0;

		if (size <= 0)
		{
			size = 0.1;
		}
	}
	
	if (particleTransparency <= 0.1)
	{
		
		is_alive = false;
	}

}

void Particle::setPosition(double x, double y)
{
	this->pos->x = x;
	this->pos->y = y + rand() % 10 - 40;
}

void Particle::move(double time)
{
	double angle = (this->rotation) * 3.14 / 180.0;
	//printf("x: %f, y: %f, angle; %f  \n", What, Eh, angle * 180/3.14);
	if (time > 0.0)
	{

		double newYpos = this->pos->y + (sin(angle) * this->velocity * time);
		double newxpos = this->pos->x + (cos(angle) * this->velocity * time);
		this->pos->y = newYpos;
		this->pos->x = newxpos;
	}
}



bool Particle::getStatus()
{
	return this->is_alive;
}


// Set rotation

void Particle::setRotation(double r)
{
	if (r > 180)
	{
		this->rotation = r - 180.0 + 90;
	}
	else if (r <= 180)
	{
		this->rotation = r + 180.0 + 90;
	}
}


void Particle::resetStatus()
{
	this->is_alive = true;
}





// Getters

double Particle::getX()
{
	return this->pos->x;
}

double Particle::getY()
{
	return this->pos->y;
}

double Particle::getRotation()
{
	return this->rotation;
}

double Particle::getparticleTransparency()
{
	return particleTransparency;
}

double Particle::getSize()
{
	return size;
}
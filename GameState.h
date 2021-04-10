#pragma once

#ifndef GAMESTATE_H
#define GAME_STATE
#include "Ship.h"
#include "Asteroid.h"
#include <time.h>
#include <list>
#include <deque>
#include "Particle.h"
#define MIN_X  0
#define MIN_Y  1
#define MAX_X  2
#define MAX_Y  3
#define WAVE_INTERVAL 3
#define MAX_ASTEROIDS 50
#define MAX_PARTICLES 10
class GameState {

public:
	GameState();
	~GameState();


	void setArena(double x, double y);
	void keyboard(unsigned char key, int x, int y);
	double getShipRot();
	void setTime(double time);
	void setElapsedtime(double time);
	void moveAsteroids();


	void resetShip();
	double getParticles();
	void startWave();
	void checkGameStatus();
	void addParticle();
	void manageParticles();
	//Methods regarding collisions 
	bool hasCollided();
	int nearWall();
	
	//Getters 
	double getShipY();
	double getShipX();
	double getAsteroidX(int x);
	double getAsteroidY(int x);
	double getParticleX(int x);
	double getParticleY(int x);
	double getParticleRotation(int x);
	double getAlpha(int i);
	double getShipHitBox();
	double getArenaCoords(int i);
	double getAsteroidRadius(int x);
	double getParticleSize(int i);

	int getWave();

private:

	Ship* ship;
	coord* ship_spawn;
	coord* max_coords;
	coord* min_coords;
	
	clock_t this_time;
	clock_t last_time;
	double timer;
	double particle_timer;

	int currentWave;
	double dt;
	double elapsedtime;
	bool inRadius(double x, double y);



	bool circleCollision(double x, double y, double r);
	void initiateAsteroids();

	std::deque<Particle*> particles;

	Asteroid* asteroid;
	Asteroid* asteroids[MAX_ASTEROIDS] ;
};




#endif
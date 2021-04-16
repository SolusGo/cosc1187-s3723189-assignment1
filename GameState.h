#pragma once

#ifndef GAMESTATE_H
#define GAME_STATE
#include "Ship.h"
#include "Asteroid.h"
#include <time.h>
#include <list>
#include <deque>
#include "Particle.h"
#include "Bullet.h"
#include "i3d_math.h"
#define MIN_X  0
#define MIN_Y  1
#define MAX_X  2
#define MAX_Y  3
#define WAVE_INTERVAL 10
#define MAX_ASTEROIDS 50
#define MAX_PARTICLES 10
#define SPACEBAR 32
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

	void updateGameStatus();
	void updateBulletStatus();
	void resetShip();
	double getParticles();
	void startWave();
	void addParticle();
	void manageParticles();
	//Methods regarding collisions 
	bool hasCollided();
	int nearWall();
	
	//Getters
	
	//Ship
	double getShipY();
	double getShipX();
	double getShipHitBox();

	//Asteroid
	double getAsteroidX(int x);
	double getAsteroidY(int x);
	double getAsteroidRadius(int x);
	double getAsteroidRotation(int i);

	//Particle
	double getParticleX(int x);
	double getParticleY(int x);
	double getParticleRotation(int x);
	double getAlpha(int i);
	


	double getArenaCoords(int i);
	
	//Remove getParticleSize
	double getParticleSize(int i);


	//Bullet
	double getBulletDirection(int i);
	double getBullet_X(int i);
	double getBullet_Y(int i);
	int getBulletsSize();

	double get_time();
	bool is_alive();
	int getScore();

	std::deque<coord> get_asteroid_corners(int i);

	

	int getNumAsteroids();

private:

	Ship* ship;
	coord* ship_spawn;
	coord* max_coords;
	coord* min_coords;
	
	clock_t this_time;
	clock_t last_time;

	//USED FOR CLOCK() function
	double timer;
	double wave_timer;

	double game_time;


	int currentWave;
	int score;
	double dt;
	double elapsedtime;
	bool inRadius(double x, double y);
	bool ship_destroyed;


	void initiateAsteroids();

	std::deque<Particle*> particles;
	std::deque<Asteroid*> asteroids ;
	std::deque<Bullet*> bullets;


	void reset_Game();
	i3d_math math;

};




#endif
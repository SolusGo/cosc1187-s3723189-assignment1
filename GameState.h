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

#define FORWARD 'W'
#define FORWARD_2 'w'

#define LEFT 'A'
#define LEFT_2 'a'

#define RIGHT 'D'
#define RIGHT_2 'd'

#define EXIT_GAME 'q'
#define EXIT_GAME_2 'Q'

#define MIN_WALL_WIDTH 0.10 //Minimum height and Width of Arena Calculated ie. as MIN_WALL_WIDTH * VIEWPORT_WIDTH
#define MIN_WALL_HEIGHT 0.10 
#define MAX_WALL_WIDTH 9.0 //Max height and Width of Arena Calculated ie. as MAX_WALL_WIDTH * MIN_WALL_WIDTH * VIEWPORT_WIDTH
#define MAX_WALL_HEIGHT 9.0
#define WARNING_DISTANCE 150.0 //Distance from wall
#define FIRING_RATE 0.001 //BULLETS PER SECOND
#define PARTICLE_DELAY 0.0 // 0.0 = Particle every movement else calculation is PARTICLE_DELAY / 1 second
class GameState {

public:
	GameState();
	~GameState();



	//Methods regarding collisions 
	bool hasCollided(double x, double y);
	bool hasCollided();
	bool nearWall(int i);
	
	//Getters
	
	//Ship
	double getShipY();
	double getShipX();
	double getShipHitBox();
	double getShipRot();
	void resetShip();
	//Asteroid
	double getAsteroidX(int x);
	double getAsteroidY(int x);
	double getAsteroidRadius(int x);
	double getAsteroidRotation(int i);
	int getNumAsteroids();
	//Particle
	double getParticleX(int x);
	double getParticleY(int x);
	double getParticleRotation(int x);
	double getAlpha(int i);
	double getParticleSize(int i);
	double getParticles();


	//ARENA
	double getArenaCoords(int i);
	


	//Bullet
	double getBulletDirection(int i);
	double getBullet_X(int i);
	double getBullet_Y(int i);
	int getBulletsSize();

	//Game State
	double get_time();
	bool is_alive();
	int getScore();
	void setArena(double x, double y);
	void keyboard(unsigned char key, int x, int y);
	std::deque<coord> get_asteroid_corners(int i);
	void setTime(double time);
	void moveAsteroids();
	void updateGameStatus();
	void updateBulletStatus();
	void startWave();
	void addParticle();
	void manageParticles();


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
	double bullet_timer;
	double game_time;
	double particle_timer;

	int currentWave;
	int score;
	double dt;
	bool inRadius(double x, double y);
	bool ship_destroyed;
	bool fire_bullet;
	bool make_particle;
	
	void initiateAsteroids();

	std::deque<Particle*> particles;
	std::deque<Asteroid*> asteroids ;
	std::deque<Bullet*> bullets;

	void reset_Game();
	i3d_math math;

};




#endif
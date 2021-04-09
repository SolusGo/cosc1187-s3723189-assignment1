#pragma once

#ifndef GAMESTATE_H
#define GAME_STATE
#include "Ship.h"
#include "Asteroid.h"
#include <list>
#define MIN_X  0
#define MIN_Y  1
#define MAX_X  2
#define MAX_Y  3
#define WAVE_INTERVAL 3
#define MAX_ASTEROIDS 10
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
	
	void startWave();
	void checkGameStatus();
	//Methods regarding collisions 
	bool hasCollided();
	int nearWall();
	
	//Getters 
	double getShipY();
	double getShipX();
	double getAsteroidX(int x);
	double getAsteroidY(int x);
	double getShipHitBox();
	double getArenaCoords(int i);
	double getAsteroidRadius(int x);
	int getWave();

private:

	Ship* ship;
	coord* ship_spawn;
	coord* max_coords;
	coord* min_coords;
	
	int currentWave;
	double dt;
	double elapsedtime;
	bool inRadius(double x, double y);

	bool circleCollision(double x, double y, double r);
	void initiateAsteroids();
	Asteroid* asteroid;
	Asteroid* asteroids[MAX_ASTEROIDS] ;
};




#endif
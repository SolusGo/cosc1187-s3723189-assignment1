#pragma once

#ifndef GAMESTATE_H
#define GAME_STATE
#include "Ship.h"

#define MIN_X  0
#define MIN_Y  1
#define MAX_X  2
#define MAX_Y  3
class GameState {

public:
	GameState();

	double getShipY();
	double getShipX();
	void setArena(double x, double y);
	void keyboard(unsigned char key, int x, int y);
	bool hasCollided();
	double getShipRot();
	void setTime(double time);
	double getShipHitBox();
	double getArenaCoords(int i);
private:

	Ship* ship;
	double max_Y;
	double max_X;
	double min_Y;
	double min_X;
	double elapsed_time;
	bool inRadius(double x, double y);
};




#endif
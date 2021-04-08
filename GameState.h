#pragma once

#ifndef GAMESTATE_H
#define GAME_STATE
#include "Ship.h"
class GameState {

public:
	GameState();

	double getShipY();
	double getShipX();
	void setMax(double x, double y);
	void setMin(double x, double y);
	void keyboard(unsigned char key, int x, int y);
	bool hasCollided();
	double getShipRot();
	void setTime(double time);
	double getShipHitBox();
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
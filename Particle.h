#ifndef PARTICLE_H
#define PARTICLE
#include "i3d_math.h"
#include <time.h>
#define DECAY 2.0; // USED TO ADJUST DECAY RATE OF PARTICLES AND TRANSPARENCY RATE
#define PARTICLE_VELOCITY 100.0;
#define INITIAL_PARTICLE_SIZE 10.0
class Particle {
public:
	Particle(double rotation, double x, double y);
	~Particle();

	void reduceDuration();
	void setRotation(double r);
	void setPosition(double x, double y);
	void resetStatus();
	void move(double time);
	bool getStatus();
	double getX();
	double getSize();
	double getY();
	double getRotation();
	double getparticleTransparency();

private:
	coord* pos;
	double size;
	double particleTransparency;
	double decayRate;
	double rotation;
	double duration_timer;
	double velocity;
	bool is_alive;
	clock_t this_time;
	clock_t last_time;
	
};	




#endif 

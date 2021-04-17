#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Ship.h"
#include "GameState.h"
#include <math.h>
#include "i3d_math.h"
#include <string>
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

#define OUTLINE_R 255
#define OUTLINE_G 255
#define OUTLINE_B 255

#define FILL_R 0
#define FILL_G 0
#define FILL_B 0

#define WARNING_R 255
#define WARNING_G 0
#define WARNING_B 0

#define ASTEROID_R 255
#define ASTEROID_G 255
#define ASTEROID_B 255

#define BULLET_SIZE 5.0
#define BULLET_R 255
#define BULLET_G 255
#define BULLET_B 255

#define ARENA_R 255
#define ARENA_G 255
#define ARENA_B 255

double g_screen_width = 0.0;
double g_screen_height = 0.0;
double prev_time = 0.0;
double current_time = 0.0;
Ship* ship = new Ship();
GameState *game;




void key_presswrapper(unsigned char key, int x, int y)
{
	game->keyboard(key, x, y);
}

void on_reshape(int w, int h)
{
	fprintf(stderr, "on_reshape(%d, %d)\n", w, h);
	glViewport(0, 0, w, h);
	g_screen_width = 1.0 * w;
	g_screen_height = 1.0* h;
	game->setArena(g_screen_width, g_screen_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, w, 0.0, h, -1.0, 1.0);
}



void draw_ship()
{
	double scaledx = 100.0 / g_screen_width;
	double scaledy = 100.0 / g_screen_height;
	double height = scaledy * g_screen_height;
	double width = scaledx * g_screen_width;

	
	
	//Calculates the y coordinate for the bottom  middle segment of the shit 
	double middlebottom = (20.0 / 115.0) * height;
	glPushMatrix();
	glColor3f(FILL_R, FILL_G, FILL_B);

	glTranslatef(game->getShipX(), game->getShipY(), 0.0);
	glRotatef(game->getShipRot(), 0, 0, 1);
	glBegin(GL_TRIANGLES);

	
	//Bottom left point of ship
	glVertex2f(0.0 - width / 2, 0.0 - height / 2);

	//Bottom middle point

	glVertex2f(0.0, 0.0 - middlebottom);

	//Top point 

	glVertex2f(0.0, 0.0 + height / 1.50);

	glEnd();

	// Draw next triangle 
	glBegin(GL_TRIANGLES);

	glVertex2f(0.0, 0.0 - middlebottom);

	glVertex2f(0.0 + width / 2, 0.0 - height / 2);

	glVertex2f(0.0, 0.0 + height / 1.50);

	glEnd();
	glColor3f(OUTLINE_R, OUTLINE_G, OUTLINE_B);

	glBegin(GL_LINE_LOOP);
	
	//Bottom left point of ship
	glVertex2f(0.0 - width / 2, 0.0 - height / 2);

	//Bottom middle point

	glVertex2f(0.0, 0.0 - middlebottom);

	//Top point 

	glVertex2f(0.0, 0.0 + height / 1.50);
	
	glEnd();
	
	// Draw next triangle 
	glBegin(GL_LINE_LOOP);

	glVertex2f(0.0, 0.0 - middlebottom);

	glVertex2f(0.0 + width / 2, 0.0 - height / 2);

	glVertex2f(0.0, 0.0 + height / 1.50);
	//Top point 
	
	glEnd();
	glPopMatrix();

	
	//Draw particles 
	
	for (int i = 0; i < game->getParticles(); i++)
	{
		
		
		glPushMatrix();
		glTranslatef(game->getParticleX(i), game->getParticleY(i) + 50, 0.0);
		
		glRotatef(game->getParticleRotation(i) + 90, 0, 0, 1);
		glColor4f(255, 255, 255, game->getAlpha(i));
		glPointSize(game->getParticleSize(i));
		glBegin(GL_POINTS);
		glVertex2f(0, 0 - 50);
		glEnd();
		glPopMatrix();
		
	}

	
}

void drawText()
{
	glColor3f(255, 255, 255);
	glPushMatrix();
	glTranslatef(g_screen_width * 0.1, g_screen_height * 0.2 * 4.55, 0.0);

	
	std::string t = std::to_string(game->getScore());
	for (auto c = t.begin(); c != t.end(); ++c)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(g_screen_width * 0.20 * 3.75, g_screen_height * 0.2 * 4.55, 0.0);

	
	std::string ct = std::to_string(game->get_time());
	for (auto c = ct.begin(); c != ct.end(); ++c)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();

	

	if (!game->is_alive())
	{
		glPushMatrix();
		glTranslatef(g_screen_width * 0.2, g_screen_height * 0.50, 0.0);

		std::string string = "Press any key to start...";
		for (auto c = string.begin(); c != string.end(); ++c)
		{
			glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
		}
		glPopMatrix();
	}



}

//Draw all bullets
void drawBullets()
{
	glColor3f(BULLET_R, BULLET_G, BULLET_B);
	
	glPointSize(5.0);

	for (int i = 0; i < game->getBulletsSize(); i++)
	{
		glPushMatrix();
		glTranslatef(game->getBullet_X(i), game->getBullet_Y(i), 0.0);
		glRotatef(game->getBulletDirection(i), 0, 0, 1);
		glBegin(GL_POINTS);
		glVertex2f(0, 0 + 100);
		glEnd();
		glPopMatrix();
	}
}



//Draw all asteroids
void drawAsteroid()
{
	for (int j = 0; j < game->getNumAsteroids(); j++)
	{
		glColor3f(ASTEROID_R, ASTEROID_G, ASTEROID_B);
	
			std::deque<coord> corners = game->get_asteroid_corners(j);
			glPushMatrix();
			glTranslatef(game->getAsteroidX(j), game->getAsteroidY(j), 0.0);
			glRotatef(game->getAsteroidRotation(j) + 90, 0, 0, 1);
			glBegin(GL_LINE_LOOP);
			
			for (int i = 0; i < corners.size(); i++)
			{
				glVertex2d(corners[i].x - game->getAsteroidX(j) , corners[i].y - game->getAsteroidY(j));
			}
			glEnd();
			glPopMatrix();
			
	}
	
}


void drawArena()
{
	
	

	if (game->nearWall(0))
	{
		glColor3f(WARNING_R, WARNING_G, WARNING_B);
	}
	else
	{
		glColor3f(ARENA_R, ARENA_G, ARENA_B);
	}

	glBegin(GL_LINES);
	glVertex2f(game->getArenaCoords(MIN_X), game->getArenaCoords(MIN_Y));
	glVertex2f(game->getArenaCoords(MAX_X), game->getArenaCoords(MIN_Y));
	glEnd();

	if (game->nearWall(1))
	{
		glColor3f(WARNING_R, WARNING_G, WARNING_B);
	}
	else
	{
		glColor3f(ARENA_R, ARENA_G, ARENA_B);
	}
	glBegin(GL_LINES);
	glVertex2f(game->getArenaCoords(MAX_X), game->getArenaCoords(MIN_Y));
	glVertex2f(game->getArenaCoords(MAX_X), game->getArenaCoords(MAX_Y));
	glEnd();

	if (game->nearWall(2))
	{
		glColor3f(WARNING_R, WARNING_G, WARNING_B);
	}
	else
	{
		glColor3f(ARENA_R, ARENA_G, ARENA_B);
	}
	glBegin(GL_LINES);
	glVertex2f(game->getArenaCoords(MAX_X), game->getArenaCoords(MAX_Y));
	glVertex2f(game->getArenaCoords(MIN_X), game->getArenaCoords(MAX_Y));
	glEnd();

	if (game->nearWall(3))
	{
		glColor3f(WARNING_R, WARNING_G, WARNING_B);
	}
	else
	{
		glColor3f(ARENA_R, ARENA_G, ARENA_B);
	}

	glBegin(GL_LINES);
	glVertex2f(game->getArenaCoords(MIN_X), game->getArenaCoords(MAX_Y));
	glVertex2f(game->getArenaCoords(MIN_X), game->getArenaCoords(MIN_Y));
	glEnd();

}


void on_idle()
{
	current_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	double dt = current_time - prev_time;
	game->setTime(dt);
	game->updateGameStatus();
	prev_time = current_time;
	glutPostRedisplay();
}

void on_display()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//render_frame();
	
	if (game->is_alive())
	{
		draw_ship();
		drawBullets();
	}
	
	drawText();
	drawArena();
	drawAsteroid();
	//drawParticles();
	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("error: %s\n", gluErrorString(err));
	glutSwapBuffers();
}



void init()
{
	/* In this program these OpenGL calls only need to be done once,
	  but normally they would go elsewhere, e.g. display */

	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_BLEND); //Enable blending.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.
}

int main(int argc, char** argv)
{
	// initialise GameState
	game = new GameState();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Assignment 1");
	glutFullScreen();
	glutReshapeFunc(on_reshape);
	init();

	glutDisplayFunc(on_display);
	glutIdleFunc(on_idle);
	glutKeyboardFunc(key_presswrapper);
	game->setTime(glutGet(GLUT_ELAPSED_TIME));
	prev_time = glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();

	return EXIT_SUCCESS;
}



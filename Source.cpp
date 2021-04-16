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


double g_screen_width = 0.0;
double g_screen_height = 0.0;
double prev_time = 0.0;
double current_time = 0.0;
Ship* ship = new Ship();
GameState *game;


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	/* Put drawing code here */
	// ...

	/* Always check for errors! */
	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("display: %s\n", gluErrorString(err));

	glutSwapBuffers();
}



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
	glColor3f(255, 255, 255);

	//glTranslatef(ship->getx(), ship->gety(), 0.0);
	glTranslatef(game->getShipX(), game->getShipY(), 0.0);
	glRotatef(game->getShipRot(), 0, 0, 1);
	//glScalef(20, 20, 0.0);
	glBegin(GL_LINE_LOOP);
	//printf("width: %d, length: %d, x: %d, y: %d \n", width, height, ship->getx(), ship->gety());
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
	//printf("y: %d, y + height: %d \n", ship->gety(), ship->getx() + height);
	
	glEnd();
	glPopMatrix();

	
	//glPointSize(10);

	
	for (int i = 0; i < game->getParticles(); i++)
	{
		
		
		glPushMatrix();
		glTranslatef(game->getParticleX(i), game->getParticleY(i) + 50, 0.0);
		
		glRotatef(game->getParticleRotation(i) + 90, 0, 0, 1);
		glColor4f(255, 255, 255, game->getAlpha(i));
		glPointSize(game->getParticleSize(i));
		//printf("%f \n", game->getParticleSize(i));
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

void drawBullets()
{
	glColor3f(255, 255, 255);
	
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

void drawShipHitbox()
{
	glColor3f(255, 255, 255);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 100; i++)
	{
		double theta = 2.0 * 3.1415926 * (i*1.0) / 100.0;
		double x = game->getShipHitBox() * cos(theta);
		double y = game->getShipHitBox() * sin(theta);
		glVertex2f(x + game->getShipX(), y + game->getShipY());
	}
	glEnd();
}



void drawAsteroid()
{
	

	for (int j = 0; j < game->getNumAsteroids(); j++)
	{
		glColor3f(255, 255, 255);
	/*	glBegin(GL_LINE_LOOP);

		for (int i = 0; i < 100; i++)
		{
			double theta = 2.0 * 3.1415926 * (i * 1.0) / 100.0;
			double x = game->getAsteroidRadius(j) * cos(theta);
			double y = game->getAsteroidRadius(j) * sin(theta);
			glVertex2f(x + game->getAsteroidX(j), y + game->getAsteroidY(j));
		}
		glEnd();*/


		
			std::deque<coord> corners = game->get_asteroid_corners(j);
			glPushMatrix();
			glTranslatef(game->getAsteroidX(j), game->getAsteroidY(j), 0.0);
			glRotatef(game->getAsteroidRotation(j) + 90, 0, 0, 1);
			glBegin(GL_LINE_LOOP);
			
			for (int i = 0; i < corners.size(); i++)
			{
				//std::cout << corners[i].x << " " << corners[i].y << std::endl;
				glVertex2d(corners[i].x - game->getAsteroidX(j) , corners[i].y - game->getAsteroidY(j));
			}
			glEnd();
			glPopMatrix();
			
	}
	


}


void drawArena()
{
	/*if (game->nearWall())
	{
		glColor3f(255, 0, 0);
	}
	else
	{
		glColor3f(255, 255, 255);
	}*/

	int number = game->nearWall();

	if (number == 3)
	{
		glColor3f(255, 0, 0);
	}
	else
	{
		glColor3f(255, 255, 255);
	}

	glBegin(GL_LINES);
	glVertex2f(game->getArenaCoords(MIN_X), game->getArenaCoords(MIN_Y));
	glVertex2f(game->getArenaCoords(MAX_X), game->getArenaCoords(MIN_Y));
	glEnd();

	if (number == 0)
	{
		glColor3f(255, 0, 0);
	}
	else
	{
		glColor3f(255, 255, 255);
	}
	glBegin(GL_LINES);
	glVertex2f(game->getArenaCoords(MAX_X), game->getArenaCoords(MIN_Y));
	glVertex2f(game->getArenaCoords(MAX_X), game->getArenaCoords(MAX_Y));
	glEnd();

	if (number == 2)
	{
		glColor3f(255, 0, 0);
	}
	else
	{
		glColor3f(255, 255, 255);
	}
	glBegin(GL_LINES);
	glVertex2f(game->getArenaCoords(MAX_X), game->getArenaCoords(MAX_Y));
	glVertex2f(game->getArenaCoords(MIN_X), game->getArenaCoords(MAX_Y));
	glEnd();

	if (number == 1)
	{
		glColor3f(255, 0, 0);
	}
	else
	{
		glColor3f(255, 255, 255);
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
	//ship->setTime(dt);
	game->setTime(dt);
	
	game->setElapsedtime(current_time);
	/*if (game->hasCollided())
	{
		game->resetShip();
		
	}*/

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
	drawShipHitbox();
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



#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Ship.h"

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

/* You can ignore this for now, it just lets you exit when you press 'q' or ESC */
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:

	case 'a':
		ship->moveLeft();
		break;
	case 'd':
		ship->moveRight();
		break;
	case 's':
		ship->moveDown();
		break;
	case 'w':
		ship->moveUp();
		break;
	case 'q':
		exit(EXIT_SUCCESS);
		break;
	default:
		break;
	}
}

void on_reshape(int w, int h)
{
	fprintf(stderr, "on_reshape(%d, %d)\n", w, h);
	glViewport(0, 0, w, h);
	g_screen_width = 1.0 * w;
	g_screen_height = 1.0* h;
	ship->setMaxPosition(w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, w, 0.0, h, -1.0, 1.0);
}



void draw_ship()
{
	double scaledx = 100.0 / g_screen_width;
	double scaledy = 125.0 / g_screen_height;
	double height = scaledy * g_screen_height;
	double width = scaledx * g_screen_width;

	
	
	//Calculates the y coordinate for the bottom  middle segment of the shit 
	double middlebottom = (20.0 / 115.0) * height;
	glPushMatrix();
	glColor3f(255, 255, 255);
	glTranslatef(ship->getx(), ship->gety(), 0.0);
	glRotatef(ship->getrotation(), 0, 0, 1);
	//glScalef(20, 20, 0.0);
	glBegin(GL_LINE_LOOP);
	//printf("width: %d, length: %d, x: %d, y: %d \n", width, height, ship->getx(), ship->gety());
	//Bottom left point of ship
	glVertex2f(0.0 - width / 2, 0.0 - height / 2);

	//Bottom middle point

	glVertex2f(0.0, 0.0 - middlebottom);

	//Top point 

	glVertex2f(0.0, 0.0 + height / 2);
	
	glEnd();
	
	// Draw next triangle 
	glBegin(GL_LINE_LOOP);

	glVertex2f(0.0, 0.0 - middlebottom);

	glVertex2f(0.0 + width / 2, 0.0 - height / 2);

	glVertex2f(0.0, 0.0 + height / 2);
	//Top point 
	//printf("y: %d, y + height: %d \n", ship->gety(), ship->getx() + height);
	
	glEnd();

	glPopMatrix();
	
}

void draw_square()
{
	glColor3f(255, 255, 255);
	glBegin(GL_LINE_LOOP);
	glVertex2f(2460, 1340);
	glVertex2f(2560, 1340);
	glVertex2f(2560, 1440);
	glVertex2f(2460, 1440);
	glEnd();
}

void on_idle()
{
	current_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	double dt = current_time - prev_time;
	ship->setTime(dt);
	prev_time = current_time;
	glutPostRedisplay();
}

void on_display()
{
	
	//printf("current x: %d, current y: %d \n", ship->getx(), ship->gety());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//render_frame();
	draw_ship();

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
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Tutorial 1");
	//glutFullScreen();
	glutReshapeFunc(on_reshape);
	init();

	glutDisplayFunc(on_display);
	glutIdleFunc(on_idle);
	glutKeyboardFunc(keyboard);
	ship->setTime(glutGet(GLUT_ELAPSED_TIME));
	prev_time = glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();

	return EXIT_SUCCESS;
}

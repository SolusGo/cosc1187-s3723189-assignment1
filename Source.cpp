#include <stdlib.h>
#include <stdio.h>
#include <iostream>

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


int g_screen_width = 0;
int g_screen_height = 0;
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
	g_screen_width = w;
	g_screen_height = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, w, 0.0, h, -1.0, 1.0);
}

void render_frame()
{
	int smin = 100;
	int smax = 1000;
	int rsize = smin + (rand() % (smax - smin));
	int rposx = rand() % ((g_screen_width - rsize));
	int rposy = rand() % (g_screen_height - rsize);
	float rcolr = (float)rand() / RAND_MAX;
	float rcolg = (float)rand() / RAND_MAX;
	float rcolb = (float)rand() / RAND_MAX; 

	glColor3f(rcolr, rcolg, rcolb);
	glBegin(GL_LINE_LOOP);
	glVertex2f(rposx, rposy);
	glVertex2f(rposx + rsize, rposy);
	glVertex2f(rposx + rsize, rposy + rsize);
	glVertex2f(rposx, rposy + rsize);
	glEnd();
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
	glutPostRedisplay();
}

void on_display()
{
	std::cout << "this is being called" << std::endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	render_frame();

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
	glutFullScreen();
	glutReshapeFunc(on_reshape);
	std::cout << "hello world! \n";
	init();

	glutDisplayFunc(on_display);
	glutIdleFunc(on_idle);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return EXIT_SUCCESS;
}

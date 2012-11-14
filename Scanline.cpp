#include <iostream>
#include <cstdlib>
#include <fstream>
#include <GL/glut.h>
#include <eigen3/Eigen/Core>

#include "Polygon.h"

#define MAXPOINTS 40

#define STEP 1

using namespace std;
using namespace Eigen;
GLsizei wh = 1000;
GLsizei ww = 1000;

Polygon pol;

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0,1.0,1.0,1.0);
	pol.Fill(STEP);
	pol.Outline();
	glFlush();
}

void reshape(int w, int h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-(GLdouble)ww/2.0, (GLdouble)ww/2.0,-(GLdouble)wh/2.0, (GLdouble)wh/2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y){
	switch(button){
	case GLUT_LEFT_BUTTON:
		if(state==GLUT_DOWN && pol.N()<MAXPOINTS){
			pol.Add((double)(x-ww/2),(double)(wh/2-y));
			pol.Quads.clear();
			pol.Scanline();
		}
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void keyboard(unsigned char c, int x, int y){
	switch(c){
	case 27:
		exit(1);
		break;
	case 'r':
		pol.Reset();
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww, wh) ;
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape) ;
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop() ;
	return 0;
}

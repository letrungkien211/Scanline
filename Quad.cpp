/*
 * Quad.cpp
 *
 *  Created on: Jul 29, 2012
 *      Author: letrungkien7
 */

#include "Quad.h"
#include <GL/glut.h>

void Quad::Set(double x0, double x1, double y0, double y1,
		int index0, int index1, double slope0, double slope1){
	X[0]=x0; X[1]=x1; Y[0]=y0; Y[1]=y1; Index[0] = index0; Index[1] = index1;
	Slope[0]=slope0; Slope[1] = slope1;
}

bool Quad::operator==(const Quad &other){
	return (Index[0]==other.Index[0] && Index[1] == other.Index[1])||
			(Index[0]==other.Index[1] && Index[1] == other.Index[0]);
}

void Quad::Fill(double step){
	glBegin(GL_LINES);
	double x0_step = step*Slope[0];
	double x1_step = step*Slope[1];
	for(double y= Y[0], x0 = X[0], x1=X[1]; y<=Y[1]; y+=step, x0+=x0_step, x1+=x1_step){
		glVertex2d(x0,y);
		glVertex2d(x1,y);
	}
	glEnd();
}

/*
 * Polygon.h
 *
 *  Created on: Jul 29, 2012
 *      Author: letrungkien7
 */

#ifndef POLYGON_H_
#define POLYGON_H_

#include<eigen3/Eigen/Core>
#include <vector>
#include <GL/glut.h>

#include "Quad.h"

using namespace Eigen;
using namespace std;

typedef Matrix<double, 2, 1> Point;

class Polygon {
public:
	void Outline();
	void Reset();
	int N();
	void Add(double x, double y);
	void Scanline();
	void Fill(double step);
	vector<Point> Vertexes;
	vector<double> Slopes;
	vector<double> Y_Ordered;
	vector<Quad> Quads;
};

#endif /* POLYGON_H_ */

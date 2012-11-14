/*
 * Quad.h
 *
 *  Created on: Jul 29, 2012
 *      Author: letrungkien7
 */

#ifndef QUAD_H_
#define QUAD_H_

class Quad {
public:
	void Set(double x0, double x1, double y0, double y1,
			int index0, int index1, double slope1, double slope2);
	void Fill(double step);
	bool operator==(const Quad &other);
	double X[2], Y[2], Slope[2];
	int Index[2];
};

#endif /* QUAD_H_ */

#include "Polygon.h"
#include <GL/glut.h>
#include <algorithm>
#include <iostream>
#define MAXPOINTS 40

using namespace std;

struct data{
	double x;
	int index;
	bool operator<(const data & other){
		return x<other.x;
	}
};

template <class T>
bool compare(T x, T y){
	return x<y;
}

Point IntersectedPoint(const Point &A, const Point& B, const Point& C, const Point& D){
	Point a,b;
	a<<-(B-A)[1],(B-A)[0]; b<<-(D-C)[1],(D-C)[0];
	if ((a.dot(A-C))*(a.dot(A-D)) >=0 ||
			(b.dot(C-A))*(b.dot(C-B)) >=0)
		return Point(-1,-1);

	Matrix2d m;
	Point c;
	m << b[1], -a[1], -b[0], a[0];
	m/= (a[0]*b[1]-a[1]*b[0]);
	c << a[0]*A[0]+a[1]*A[1], b[0]*C[0]+b[1]*C[1];
	return m*c;
}

int Polygon::N(){
	return Vertexes.size();
}

void Polygon::Outline(){
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	for(int i=0, n=N(); i<n; ++i){
		glVertex2d((double)Vertexes[i][0], (double)Vertexes[i][1]);
	}
	glEnd();
}

void Polygon::Reset(){
	Vertexes.clear();
	Slopes.clear();
	Y_Ordered.clear();
	Quads.clear();
}

void Polygon::Add(double x, double y){
	Vertexes.push_back(Point(x,y));
	Y_Ordered.push_back(y);

	int n = N();
	Point p1;
	if (n == 1) p1 = Vertexes[n-1]; 
	else p1 = Vertexes[n-1]-Vertexes[n-2]; 
	Point p2 = Vertexes[n-1]-Vertexes[0];
	double tmp1 = p1[1] ? p1[0]/p1[1] : 0;
	double tmp2 = p2[1] ? p2[0]/p2[1] : 0;
	if(n==2){
		Slopes.push_back(tmp1);
	}
	else if(n==3){
		Slopes.push_back(tmp1);
		Slopes.push_back(tmp2);
	}
	else if(n>3){
		Slopes[n-2]= tmp1;
		Slopes.push_back(tmp2);
		Point tmp;
		for(int i=0; i<n-1; ++i){
			tmp = IntersectedPoint(Vertexes[n-1], Vertexes[0], Vertexes[i], Vertexes[i+1]);
			if(tmp[1]!=-1)
				Y_Ordered.push_back((double)tmp[1]);
			tmp = IntersectedPoint(Vertexes[n-2], Vertexes[n-1], Vertexes[i], Vertexes[i+1]);
			if(tmp[1]!=-1)
				Y_Ordered.push_back((double)tmp[1]);
		}
	}
	sort(Y_Ordered.begin(), Y_Ordered.end(), compare<double>);
}

void Polygon::Scanline(){
	int n = N();
	if(n>3){
		double current_y;
		double y1,y2;
		data d[2*MAXPOINTS];
		int cnt;
		Quad q;

		for(int k=0, y_ordered_size = Y_Ordered.size(); k<y_ordered_size-1; ++k){
			current_y = Y_Ordered[k]+0.01;
			cnt = 0;
			for(int i=0; i<n; ++i){
				y1 = Vertexes[i][1]; y2 = Vertexes[(i+1)%n][1];
				if((y1-current_y)*(y2-current_y)<0){
					d[cnt].x = Vertexes[i][0]+0.01+(Y_Ordered[k]+0.01-y1)*Slopes[i];
					d[cnt].index = i;
					cnt++;
				}
			}

			sort(d, d+cnt,compare<data>);

			vector<Quad>::iterator f;
			for(int j=0; j<cnt/2; j=j+1){
				q.Set(d[2*j].x, d[2*j+1].x, Y_Ordered[k], Y_Ordered[k+1],
						d[2*j].index, d[2*j+1].index, Slopes[d[2*j].index], Slopes[d[2*j+1].index]);

				f = find(Quads.begin(), Quads.end(), q);
				if(f==Quads.end())
					Quads.push_back(q);
				else
					f->Y[1] = Y_Ordered[k+1];
			}
		}
	}

}

void Polygon::Fill(double step){
	int n = N();
	if(n!=3){
		glColor3f(0.0,1.0,1.0);
		for(int i=0, size = Quads.size(); i<size; ++i)
			Quads[i].Fill(step);
	}
	else{
		Point p[2];
		Point slope[2];

		slope[0] = Vertexes[2]-Vertexes[0];
		slope[1] = Vertexes[2]-Vertexes[1];

		p[0] = Vertexes[0]; p[1] = Vertexes[1];

		glShadeModel(GL_SMOOTH);
		glBegin(GL_LINES);
		for(double t=0; t<=1; t+=0.001){
			glColor3f(1-t,0,t);
			glVertex2d((double)(p[0][0]+t*slope[0][0]), (double)(p[0][1]+t*slope[0][1]));
			glColor3f(0,1-t,t);
			glVertex2d((double)(p[1][0]+t*slope[1][0]), (double)(p[1][1]+t*slope[1][1]));
		}
		glEnd();
	}
}

#ifndef _SHAPE_H
#define _SHAPE_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <vector>

using namespace std;

class Shape
{
	const float pi = 3.14;// 15926;
	vector<float> vertD;
	public:
		void render1();
		void render2();
		void render3();
		void drawDisc(float res);
		void drawSquare();
		void drawWall();

};
#endif 

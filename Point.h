#ifndef __POINT_H_
#define __POINT_H_
#include <iostream>
#include <Windows.h>
#include "Utils.h"


class Point
{
	int x;
	int y;
	char Pointchar;
public:
	void setPoint(int _x, int _y, char _ch) {
		x = _x;
		y = _y;
		Pointchar = _ch;

	}
	void setPointChar(char ch) {
		Pointchar = ch;
	}
	void draw(char ch) const;

	// get data members of the class
	int getX() const { return x; }
	int getY() const { return y; }
	char getPointChar() const {
		return Pointchar;
	}
	
};
#endif
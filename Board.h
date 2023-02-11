#ifndef __BOARD_H_
#define __BOARD_H_
#include <iostream>
#include "Utils.h"
#include "Shape.h"
class Shape;

class Board {
	enum { ROWSIZE = 20, COLSIZE = 27, MIDDLE = 13, START = 0, SHAPEARRSIZE = 4,RANGE=4};
	char theBoardMatrix[ROWSIZE][COLSIZE];
	static constexpr char TAV = (char)178;

private:
	bool isTaken(int pointX, int pointY) const;

public:
	void matrixInit();//The board initialization
	void printBoard() const;
	void updateBoard(Point(&p1)[SHAPEARRSIZE][SHAPEARRSIZE]);
	void updatePointInBoard(int x, int y, char pointChar);//The function update the board matrix in the x.y coordinate with the point char
	bool isEmptyPlace(int pointX, int pointY) const;//The function returns true if in the matrix board where the (x,y) there is whitespace(=empty place),else false 
	bool isFullRow(int row, int leftLimit, int rightLimit) const;//The function returns true if the player has a full row with part of a Tetris shape
	void deleteRow(int row, int leftLimit, int rightLimit, bool isWithoutColor);//The function updates the matrix board according to the row with whitespaces, the function gets col in order to recognize the player

	bool isBombShouldEexplode(int x, int y) const;
	void bombExplode(int x, int y, int playerMaxCol, int playerMinCol);

	int deletedRowCounter(Shape& s, int leftLimit, int rightLimit) const;


};


#endif
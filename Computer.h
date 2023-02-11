#ifndef __COMPUTER_H_
#define __COMPUTER_H_
#include "Player.h"
#include "Point.h"
#include "Board.h"
#include "Shape.h"
#include "Bomb.h"
#include <ctime>
#include <windows.h>
#include <cstdlib> 
class Computer :public Player
{
	enum { ROWSIZE = 20, COLSIZE = 27, MIDDLE = 13, START = 0, SHAPEARRSIZE = 4 ,BOTTOM=18};
	enum {LEFT_MOVE = 0, RIGHT_MOVE = 2, DROP_MOVE = 8, DEFAULT_MOVE = -1, REACHED_THE_POSITION = -2,
		ROTATE=4};
	enum {GOOD_LEVEL='2',NOVICE_LEVEL='3'};
	enum { SIZE = 19, ARR_SIZE = 2 };
	enum { I_SHAPE = 19, O_SHAPE= 2 };
	static constexpr char TAV = (char)178;
	static constexpr char BOMB_TAV = '#';

	char level = '0';
	Shape tempShape = {};
	Board* theGameBoard;
	Bomb bomb;
	bool isOptimalMoveForBomb = true;
	bool isRandomMove = false;
	int countMoves = 1;
	int xDesPositionForBomb = 0;

	int xDesPositionForShape = 0;

	
private:
	
	void copyShape(Shape s1);
	void setBoard(Board* _theGameBoard) override;
	void findOptimalPlace(int& saverNumOfRotate, int rightLimit, int leftLimit);
	int numOfRotateForShape() const;
	void printMatrix(Point(&p1)[SHAPEARRSIZE][SHAPEARRSIZE])const;
	int getMove(int& numOfRotate, int rightLimit, int leftLimit, Point(&copyOfBottomShape)[SHAPEARRSIZE], int Xposition, int Yposition, bool& isReachedTheBottom, int& playerInput, Shape& s, bool& isFirstShapePlayer) override;
	int findRandomPlace(int rightLimit, int leftLimit)const;
	bool thereIsAwayToThisLocation();
	int getMoveForShape(int yDesPosition, int xDesPosition, int xPosition, int yPosition)const;
	bool thePathIsEmpty(Point(&copyOfBottomShape)[SHAPEARRSIZE], int yDes)const;
	int getDirection(char key)  override;//The function gets the select diraction char and return the key code from the arrowKeys, if the key didn`t find return -1
	void setBomb(Bomb b);
	void findOptimalPlaceForBomb(int rightLimit, int leftLimit, Point(&saver)) const;
	int getMoveForBomb(int rightLimit, int leftLimit, int Xposition, int Yposition, int& inputPlayer) override;
	void setWhichMove();

public:
	void setLevel(int _level);
};



#endif //_COMPUTER_H_
#ifndef __PLAYER1_H_
#define __PLAYER1_H_
#include <iostream>
#include "Utils.h"
#include "Point.h"
#include "Board.h"
#include "Shape.h"
class Player
{
	enum { ARROW_KEYS_SIZE = 10, NAME_SIZE = 9, PLAYER_1_KOD = 1 ,SIZE=4};
	int playerCode;
	char playerName[NAME_SIZE];
	int playerScore;
	Board* theGameBoard;


public:
	
	virtual ~Player() {};
	void setPlayerCode(int _code);
	void setPlayerScore(int _score);
	int getPlayerScore()const;
	void setPlayerName();
	void printPlayerName()const;
	void printPlayerScore()const;
	void printWinner()const;
	void printTie()const;

	virtual int getMove(int& numOfRotate, int rightLimit, int leftLimit, Point(&copyOfBottomShape)[SIZE], int Xposition, int Yposition, bool& isReachedTheBottom, int& playerInput, Shape& s, bool& isFirstShapePlayer) = 0;
	virtual int getDirection(char key) = 0;
	virtual void setBoard(Board* _theGameBoard) = 0;
	virtual	int getMoveForBomb(int rightLimit, int leftLimit, int Xposition, int Yposition, int& inputPlayer) = 0;




};

#endif 
#ifndef __HUMAN_H_
#define __HUMAN_H_
#include "Player.h"
#include "Shape.h"
#include "Bomb.h"



class Human :public Player
{
	enum { ARROW_KEYS_SIZE = 10 };
	char arrowKeys[ARROW_KEYS_SIZE];
	enum { ESC = 27 };
	static constexpr int INPUT_ITERATIONS = 20;
	enum { DROP_CAPITAL = 9, DROP_LOWER = 8,SIZE=4};
	Board* theGameBoard = 0;
	
private:

	int getDirection(char key)  override;//The function gets the select diraction char and return the key code from the arrowKeys, if the key didn`t find return -1
	int getMove(int& numOfRotate, int rightLimit, int leftLimit, Point(&copyOfBottomShape)[SIZE], int Xposition, int Yposition, bool& isReachedTheBottom, int& playerInput, Shape& s, bool& isFirstShapePlayer) override;
	void setBoard(Board* _theGameBoard) override;
	int getMoveForBomb(int rightLimit, int leftLimit, int Xposition, int Yposition, int& inputPlayer)override;



public:
	void setArrowKeys(const char* keys);

};



#endif
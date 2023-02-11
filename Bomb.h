#ifndef __BOMB_H_
#define __BOMB_H_
#include <iostream>
#include "Board.h"
#include "Point.h"
class  Bomb
{
	enum { PLAYER1 = 0, PLAYER2 = 1, COLSIZE = 27, ROWSIZE = 20, CENTER_PLAYER_2 = 19, CENTER_PLAYER_1 = 6
	};
	enum {
		L_CAPITAL = 0, L_LOWER = 1, R_CAPITAL = 2, R_LOWER = 3, DROP_CAPITAL = 8, DROP_LOWER = 9
	,DEFAULT_MOVE=-1};
	static constexpr char BOMB_TAV = '#';
	Board* theGameBoard;
	static constexpr int INPUT_ITERATIONS = 20;
	Point bomb;
	int direction;
	int randBomb = -1;
	bool IsAnewBomb = true;


private:
	void printBomb();
	void defaultMove();
	bool isValidMoveForBomb(int keyCode) const;
	void moveBomb(int x, int y);
	void deleteBomb();
	void drop();

public:
	void setBoard(Board* _theGameBoard);
	void initBomb(int whichPlayer);
	bool UpdateBomb();
	void setDirection(int dir);
	void copyBomb(Point(&saver));
	int getBombX()const;
	int getBombY()const;
	bool isAbomb();
	void UpdateRandBomb();
	bool isAnewBomb()const;

};
#endif
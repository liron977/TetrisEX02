#ifndef __THETETRISGAME_H_
#define __THETETRISGAME_H_
#include "Shape.h"
#include "Utils.h"
#include "Board.h"
#include "Player.h"
#include "Bomb.h"
class TheTetrisGame {
	enum { CENTER_PLAYER_1 = 10, CENTER_PLAYER_2 = 19, SIZE=4,ARR_SIZE = 2, PLAYER1 = 0, PLAYER2 = 1 };
	enum { PLAYER1_LEFT_LIMIT = 0, PLAYER2_RIGHT_LIMIT = 27, MIDDLE = 13, };
	enum { DROP_CAPITAL = 9, DROP_LOWER = 8 };
	enum { ESC = 27 };
	static constexpr int INPUT_ITERATIONS = 20;
	Shape playersShapes[ARR_SIZE] = {};
	Board theGameBoard;
	Player* playersArr[ARR_SIZE] = {};
	bool isPausedGame = false;
	Bomb bombsArr[ARR_SIZE] = {};
	int inputPlayer1 = -1;
	int inputPlayer2 = -1;
	void updateMenu(bool isWithoutColor, bool& ExitGame);
	void winners(bool player1won, bool player2won, bool& ExitGame);
	void bombRun(bool& isPlayerBombExplode, int whichPlayer, bool isWithoutColor, bool& ExitGame, int leftLimit, int rightLimit, int& inputPlayer);
	void initShape(bool& isPlayerBombExplode, int whichPlayer, bool isWithoutColor);
	void getInput(bool isWithoutColor, bool& ExitGame, int& inputPlayer1, int& inputPlayer2);
	void initDirection(int whichPlayer, int& numOfRotatePlayer, int rightLimit, int leftLimit, Point(&copyOfArrBottomShapePlayer)[4], int Xposition, int Yposition, bool& isReachedTheBottom, int& playerInput, Shape& s, bool& isFirstShapePlayer);

public:

	void init();
	void GameOver()const;
	void run(bool isWithoutColor, bool& ExitGame);
	void setIsPausedGame(bool _isPausedGame);
	void setPlayersArr(Player* _playersArr[]);
	void setPlayersScore(bool isReachedTheBottom, int playerNum, bool& isRowDeleted)const;

};

#endif
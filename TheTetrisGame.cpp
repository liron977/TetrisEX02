#include "TheTetrisGame.h"
#include <cstdlib> 
#include <iostream>
#include <ctime> 
#include <windows.h>
#include "Utils.h"
#include "Point.h"
#include "Shape.h"
#include "Board.h"
#include "Player.h"
#include "Menu.h"

void TheTetrisGame::init()
{

	theGameBoard.matrixInit();
	for (int i = 0; i < ARR_SIZE; i++) {
		playersArr[i]->setPlayerCode(i + 1);
		playersArr[i]->setPlayerName();
		playersShapes[i].initShapeMatrix();

	}
	system("cls");
	theGameBoard.printBoard();
	playersArr[PLAYER1]->printPlayerName();
	playersArr[PLAYER2]->printPlayerName();
	playersArr[PLAYER1]->setPlayerScore(0);
	playersArr[PLAYER2]->setPlayerScore(0);
	for (int i = 0; i < ARR_SIZE; i++)
	{
		playersShapes[i].setBoard(&theGameBoard);
		bombsArr[i].setBoard(&theGameBoard);
		playersArr[i]->setBoard(&theGameBoard);
	}
}



void TheTetrisGame::run(bool isWithoutColor, bool& ExitGame)
{
	srand((unsigned)time(0));
	int randShape;
	bool isReachedTheBottom1 = false;
	bool isReachedTheBottom2 = false;
	bool player1won = false;
	bool player2won = false;
	bool isRowDeleted = false;
	bool isPlayer1BombExplode = false;
	bool isPlayer2BombExplode = false;
	bool isFirstShapePlayer1 = true;
	bool isFirstShapePlayer2 = true;
	Point copyOfArrBottomShapePlayer1[SIZE] = {};
	Point copyOfArrBottomShapePlayer2[SIZE] = {};
	int numOfRotatePlayer1;
	int numOfRotatePlayer2;

	if (!isPausedGame) {
		randShape = (rand() % 7) + 1;
		playersShapes[PLAYER1].createShapePlayer(PLAYER1, randShape, isWithoutColor);
		initDirection(PLAYER1, numOfRotatePlayer1, MIDDLE, PLAYER1_LEFT_LIMIT, copyOfArrBottomShapePlayer1, playersShapes[PLAYER1].getMostLeftPoint().getX(), playersShapes[PLAYER1].getShapeBottomY(), isReachedTheBottom1, inputPlayer1, playersShapes[PLAYER1], isFirstShapePlayer1);
		isReachedTheBottom1 = playersShapes[PLAYER1].UpdateShape(isRowDeleted, isWithoutColor);

		randShape = (rand() % 7) + 1;
		playersShapes[PLAYER2].createShapePlayer(PLAYER2, randShape, isWithoutColor);
		initDirection(PLAYER2, numOfRotatePlayer2, PLAYER2_RIGHT_LIMIT, MIDDLE, copyOfArrBottomShapePlayer2, playersShapes[PLAYER2].getMostLeftPoint().getX(), playersShapes[PLAYER2].getShapeBottomY(), isReachedTheBottom2, inputPlayer2, playersShapes[PLAYER2], isFirstShapePlayer2);
		isReachedTheBottom2 = playersShapes[PLAYER2].UpdateShape(isRowDeleted, isWithoutColor);
		bombsArr[PLAYER1].UpdateRandBomb();
		bombsArr[PLAYER2].UpdateRandBomb();
	}

	do {

		playersShapes[PLAYER1].getBottomArrPoint(copyOfArrBottomShapePlayer1);
		playersShapes[PLAYER2].getBottomArrPoint(copyOfArrBottomShapePlayer2);
		cout.flush();

		getInput(isWithoutColor, ExitGame, inputPlayer1, inputPlayer2);

		if (ExitGame)
		{
			break;
		}

		if ((isReachedTheBottom1))//if shape reached to the bottom we need to create a new shape
		{
			if ((bombsArr[PLAYER1].isAbomb()) && (!isPlayer1BombExplode))//if its a bomb that didn't explode yet.
			{
				bombRun(isPlayer1BombExplode, PLAYER1, isWithoutColor, ExitGame, PLAYER1_LEFT_LIMIT, MIDDLE, inputPlayer1);

			}
			else//if its a shape. 
			{

				initShape(isPlayer1BombExplode, PLAYER1, isWithoutColor);
				initDirection(PLAYER1, numOfRotatePlayer1, MIDDLE, PLAYER1_LEFT_LIMIT, copyOfArrBottomShapePlayer1, playersShapes[PLAYER1].getMostLeftPoint().getX(), playersShapes[PLAYER1].getShapeBottomY(), isReachedTheBottom1, inputPlayer1, playersShapes[PLAYER1], isFirstShapePlayer1);
			}
		}
		else
		{
			initDirection(PLAYER1, numOfRotatePlayer1, MIDDLE, PLAYER1_LEFT_LIMIT, copyOfArrBottomShapePlayer1, playersShapes[PLAYER1].getMostLeftPoint().getX(), playersShapes[PLAYER1].getShapeBottomY(), isReachedTheBottom1, inputPlayer1, playersShapes[PLAYER1], isFirstShapePlayer1);

		}
		if ((isReachedTheBottom2))
		{
			if ((bombsArr[PLAYER2].isAbomb()) && (!isPlayer2BombExplode))//if its a bomb that didn't explode yet.
			{
				bombRun(isPlayer2BombExplode, PLAYER2, isWithoutColor, ExitGame, MIDDLE, PLAYER2_RIGHT_LIMIT, inputPlayer2);

			}
			else//if its a shape.
			{
				initShape(isPlayer2BombExplode, PLAYER2, isWithoutColor);
				initDirection(PLAYER2, numOfRotatePlayer2, PLAYER2_RIGHT_LIMIT, MIDDLE, copyOfArrBottomShapePlayer2, playersShapes[PLAYER2].getMostLeftPoint().getX(), playersShapes[PLAYER2].getShapeBottomY(), isReachedTheBottom2, inputPlayer2, playersShapes[PLAYER2], isFirstShapePlayer2);
			}
		}
		else
		{

			initDirection(PLAYER2, numOfRotatePlayer2, PLAYER2_RIGHT_LIMIT, MIDDLE, copyOfArrBottomShapePlayer2, playersShapes[PLAYER2].getMostLeftPoint().getX(), playersShapes[PLAYER2].getShapeBottomY(), isReachedTheBottom2, inputPlayer2, playersShapes[PLAYER2], isFirstShapePlayer2);

		}
		if (!isPlayer1BombExplode)
		{
			isReachedTheBottom1 = playersShapes[PLAYER1].UpdateShape(isRowDeleted, isWithoutColor);
			if (!(bombsArr[PLAYER1].isAbomb()))
				setPlayersScore(isReachedTheBottom1, PLAYER1, isRowDeleted);
		}

		if (!isPlayer2BombExplode) {
			isReachedTheBottom2 = playersShapes[PLAYER2].UpdateShape(isRowDeleted, isWithoutColor);
			if (!(bombsArr[PLAYER2].isAbomb()))
				setPlayersScore(isReachedTheBottom2, PLAYER2, isRowDeleted);

		}
		player1won = playersShapes[PLAYER2].isAplayerLost(isReachedTheBottom2);
		player2won = playersShapes[PLAYER1].isAplayerLost(isReachedTheBottom1);
		playersArr[PLAYER1]->printPlayerScore();
		playersArr[PLAYER2]->printPlayerScore();
		Sleep(300);

	} while (!player1won && !player2won);
	if (!ExitGame) {
		winners(player1won, player2won, ExitGame);
	}
	else {
		GameOver();
	}
}

void TheTetrisGame::initDirection(int whichPlayer, int& numOfRotatePlayer, int rightLimit, int leftLimit, Point(&copyOfArrBottomShapePlayer)[4], int Xposition, int Yposition, bool& isReachedTheBottom, int& playerInput, Shape& s, bool& isFirstShapePlayer) {


	playersShapes[whichPlayer].setDirection(playersArr[whichPlayer]->getMove(numOfRotatePlayer, rightLimit, leftLimit, copyOfArrBottomShapePlayer, Xposition, Yposition, isReachedTheBottom, playerInput, playersShapes[whichPlayer], isFirstShapePlayer));
	playerInput = -1;
	isFirstShapePlayer = false;

}

void TheTetrisGame::setPlayersArr(Player* _playersArr[]) {
	for (int i = 0; i < ARR_SIZE; i++)
	{
		playersArr[i] = _playersArr[i];
	}
}

void TheTetrisGame::updateMenu(bool isWithoutColor, bool& ExitGame) {

	Menu m;
	m.setIsPausedGameFromGame(true);
	m.setPlayersShapes(playersShapes);
	m.setPlayersArr(playersArr);
	setIsPausedGame(true);
	m.setIsWithoutColor(isWithoutColor);
	m.setBoardGameForMenu(theGameBoard);
	m.printMenu(ExitGame);
	return;
}

void TheTetrisGame::winners(bool player1won, bool player2won, bool& ExitGame)
{
	char input = ' ';
	Menu menu;
	menu.setIsPausedGameFromGame(false);
	setIsPausedGame(false);
	if (player1won && player2won)
	{
		if (playersArr[PLAYER1]->getPlayerScore() > playersArr[1]->getPlayerScore())
			playersArr[PLAYER1]->printWinner();
		if (playersArr[PLAYER1]->getPlayerScore() < playersArr[1]->getPlayerScore())
			playersArr[PLAYER2]->printWinner();
		else
		{
			playersArr[PLAYER2]->printTie();
		}
	}
	else if (player1won) {
		playersArr[PLAYER1]->printWinner();
	}
	else {
		playersArr[PLAYER2]->printWinner();
	}
	do {

		if (_kbhit())
		{
			input = _getch();
		}
	} while (input != ESC);
	menu.printMenu(ExitGame);

}

void TheTetrisGame::GameOver()const {
	system("cls");
	gotoxy(30, 9);
	cout << "GAME OVER!!";
	gotoxy(20, 10);
	cout << "@LIRON KOTEV AND CHEN PAKMAN,2021,MTA";
	Sleep(200);
	gotoxy(0, 20);

}

void TheTetrisGame::bombRun(bool& isPlayerBombExplode, int whichPlayer, bool isWithoutColor, bool& ExitGame, int leftLimit, int rightLimit, int& inputPlayer) {

	if (bombsArr[whichPlayer].isAnewBomb()) {
		bombsArr[whichPlayer].initBomb(whichPlayer);

	}
	bombsArr[whichPlayer].setDirection(playersArr[whichPlayer]->getMoveForBomb(rightLimit, leftLimit, bombsArr[whichPlayer].getBombX(), bombsArr[whichPlayer].getBombY(), inputPlayer));
	inputPlayer = -1;
	isPlayerBombExplode = bombsArr[whichPlayer].UpdateBomb();


}

void TheTetrisGame::initShape(bool& isPlayerBombExplode, int whichPlayer, bool isWithoutColor) {

	int randShape;

	isPlayerBombExplode = false;
	randShape = (rand() % 7) + 1;
	if (whichPlayer == 1)
		playersShapes[whichPlayer].createShapePlayer(PLAYER2, randShape, isWithoutColor);
	else
	{
		playersShapes[whichPlayer].createShapePlayer(PLAYER1, randShape, isWithoutColor);
	}

	bombsArr[whichPlayer].UpdateRandBomb();

}

void TheTetrisGame::getInput(bool isWithoutColor, bool& ExitGame, int& inputPlayer1, int& inputPlayer2)
{

	char key = 0;
	int dir = 0;
	for (int i = 0; i < INPUT_ITERATIONS; i++) {
		if (_kbhit()) {
			key = _getch();

			if ((playersArr[PLAYER1]->getDirection(key)) != -1) {
				inputPlayer1 = playersArr[PLAYER1]->getDirection(key);
			}
			if ((playersArr[PLAYER2]->getDirection(key)) != -1) {
				inputPlayer2 = playersArr[PLAYER2]->getDirection(key);

			}

			if (key == ESC) {
				updateMenu(isWithoutColor, ExitGame);
				break;
			}
		}

	}
}

void TheTetrisGame::setPlayersScore(bool isReachedTheBottom, int playerNum, bool& isRowDeleted) const {


	if (isReachedTheBottom)
	{
		playersArr[playerNum]->setPlayerScore(playersArr[playerNum]->getPlayerScore() + 50);
	}
	if (isRowDeleted)
		playersArr[playerNum]->setPlayerScore(playersArr[playerNum]->getPlayerScore() + 1000);
	isRowDeleted = false;
}
void TheTetrisGame::setIsPausedGame(bool _isPausedGame) {
	isPausedGame = _isPausedGame;
}
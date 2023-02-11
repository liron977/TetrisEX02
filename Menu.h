#ifndef __MENU_H_
#define __MENU_H_
#include <iostream>
#include "Shape.h"
#include "TheTetrisGame.h"
#include "Human.h"
#include "Computer.h"
#include "Player.h"

class Menu {
	enum { SIZE = 2 };
	enum { H_VS_H = '1', H_VS_C = '2', C_VS_C = '3', PAUSEDGAME = '4', INSTRUCTIONS = '8', EXIT = '9', WITHOUT_COLOR = '5', WITH_COLOR = '6', SETTINGS = '7' };
	bool isPausedGame = false;
	char playerChoice = '0';
	Board TheBoardGame;
	TheTetrisGame newGame;
	Shape playersShapes[SIZE] = {};
	Player* playersArr[SIZE] = {};
	Computer c1;
	Computer c2;
	Human h1, h2;
	
	bool isWithoutColor = false;
	bool ExitGame = false;
	void setPlayerChoise(int _playerChoice) {
		playerChoice = _playerChoice;
	}
	void getPlayerChoise();
	void selectedAction(bool& ExitGame);//The function gets the number of the action that the player selected from the menu 
	void printInstructions(bool& ExitGame);

	bool getIsWithoutColor() const {
		return isWithoutColor;
	}
	void printLevelMenu(int playerNum);
	void printSettings();
public:
	
	void setIsPausedGameFromGame(bool _isPausedGame) {
		isPausedGame = _isPausedGame;
	}
	void setBoardGameForMenu(Board& _TheBoardGame) {
		TheBoardGame = _TheBoardGame;
	}
	void setPlayersShapes(Shape _playersShapes[]);
	void setPlayersArr(Player* _playersArr[]);
	void printMenu(bool& ExitGame);
	void setIsWithoutColor(bool _isWithoutColor)
	{
		isWithoutColor = _isWithoutColor;
	}





};
#endif 
		



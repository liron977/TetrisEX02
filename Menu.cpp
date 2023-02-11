#include "Menu.h"
void Menu::printMenu(bool& ExitGame) {
	int yLocation = 8;
	system("cls");
	gotoxy(10, 10);
	for (int i = 21; i < 71; i++) {
		gotoxy(i, 5);
		cout << "*";
		gotoxy(i, 21);
		cout << "*";
	}
	for (int j = 5; j <= 21; j++) {
		gotoxy(21, j);
		cout << "*";
		gotoxy(70, j);
		cout << "*";
	}
	gotoxy(38, 6);
	cout << "MENU:";
	gotoxy(23, yLocation);
	yLocation += 2;
	cout << "(1) Start a new game - Human vs Human";
	gotoxy(23, yLocation);
	yLocation += 2;
	cout << "(2) Start a new game - Human vs Computer";
	gotoxy(23, yLocation);
	yLocation += 2;
	cout << "(3) Start a new game - Computer vs Computer";
	if (isPausedGame) {
		gotoxy(23, yLocation);
		yLocation += 2;
		cout << "(4) Continue a paused game";
	}

	gotoxy(23, yLocation);
	cout << "(8) Present instructions and keys";
	yLocation += 2;
	gotoxy(23, yLocation);
	cout << "(9) EXIT";
	if (!isPausedGame)
	{
		yLocation += 2;
		gotoxy(23, yLocation);
		cout << "(7) Settings";
	}


	getPlayerChoise();
	selectedAction(ExitGame);
	gotoxy(0, 20);
	return;
}
void Menu::selectedAction(bool& ExitGame) {


	if (playerChoice == SETTINGS && !isPausedGame)
	{
		printSettings();
		if (playerChoice == WITHOUT_COLOR)
			setIsWithoutColor(true);
		else
		{
			setIsWithoutColor(false);
		}
	}
	if ((playerChoice == SETTINGS && isPausedGame))
	{
		getPlayerChoise();
	}

	if (playerChoice == H_VS_H) {
		system("cls");
		h1.setArrowKeys("AaDdsSwWxX");
		h2.setArrowKeys("JjLlkKiImM");

		playersArr[0] = &h1;
		playersArr[1] = &h2;
	}
	else if (playerChoice == H_VS_C) {
		system("cls");
		h1.setArrowKeys("AaDdsSwWxX");

		playersArr[0] = &h1;
		playersArr[1] = &c1;

		printLevelMenu(2);
		c1.setLevel(playerChoice);
	}
	else if (playerChoice == C_VS_C) {

		playersArr[0] = &c1;
		playersArr[1] = &c2;


		printLevelMenu(1);
		c1.setLevel(playerChoice);
		printLevelMenu(2);
		c2.setLevel(playerChoice);

	}

	if (((playerChoice == C_VS_C) || (playerChoice == H_VS_C) || (playerChoice == H_VS_H)))
	{


		system("cls");
		newGame.setPlayersArr(playersArr);
		newGame.init();
		newGame.run(isWithoutColor, ExitGame);
		playerChoice = 0;
		return;

	}

	if (playerChoice == PAUSEDGAME)
	{
		if (isPausedGame) {//Update the board after pausing the game
			newGame.setIsPausedGame(true);
			system("cls");
			TheBoardGame.printBoard();
			playersArr[0]->printPlayerName();
			playersArr[1]->printPlayerName();
			return;
		}
		else {
			printMenu(ExitGame);
		}
	}
	if (playerChoice == INSTRUCTIONS) {
		system("cls");
		printInstructions(ExitGame);
	}
	if (playerChoice == EXIT) {
		ExitGame = true;
		
	}
	return;

}
void Menu::printInstructions(bool& ExitGame) {
	gotoxy(10, 10);
	for (int i = 0; i < 76; i++) {
		for (int yRowLocation = 5; yRowLocation < 19; yRowLocation += 2) {
			gotoxy(i, yRowLocation);
			cout << "-";
		}
	}
	for (int j = 5; j <= 17; j++) {
		for (int yColLocation = 0; yColLocation <= 85; yColLocation += 25) {
			gotoxy(yColLocation, j);
			cout << "|";
		}
	}
	gotoxy(0, 0);
	cout << "(3) Back to menu";
	gotoxy(0, 1);
	cout << "Score values: *Line clear-1000*,*Soft drop-50*";
	gotoxy(28, 3);
	cout << "INSTRUCTIONS AND KEYS";
	gotoxy(10, 6);
	cout << "KEYS";
	gotoxy(32, 6);
	cout << "Left Player";
	gotoxy(57, 6);
	cout << "Right Player";
	gotoxy(1, 8);
	cout << "LEFT";
	gotoxy(26, 8);
	cout << "a or A";
	gotoxy(51, 8);
	cout << "j or J";
	gotoxy(1, 10);
	cout << "RIGHT";
	gotoxy(26, 10);
	cout << "d or D";
	gotoxy(51, 10);
	cout << "l (small L) or L";
	gotoxy(1, 12);
	cout << "ROTATE clockwise";
	gotoxy(26, 12);
	cout << "s or S";
	gotoxy(51, 12);
	cout << "k or K";
	gotoxy(1, 14);
	cout << "ROTATE counterclockwise";
	gotoxy(26, 14);
	cout << "w or W";
	gotoxy(51, 14);
	cout << "i or I (uppercase i)";
	gotoxy(1, 16);
	cout << "DROP";
	gotoxy(26, 16);
	cout << "x or X";
	gotoxy(51, 16);
	cout << "m or M";
	gotoxy(0, 19);
	cout << "Tetris has very simple rules: you can only move the pieces in specific ways" << endl << "your game is over if your pieces reach the top of the screen." << endl << "You have to make full horizontal lines with the different shaped blocks that" << endl << "fall into the game area." << endl << "Full lines will then disappear and provide points. " << endl << "The more lines you make, the more points you earn.";
	while (true)
	{
		if (_kbhit()) {
			if (_getch() == '3') {
				printMenu(ExitGame);
				break;
			}
		}
	}
}
void Menu::setPlayersShapes(Shape _playersShapes[]) {
	for (int i = 0; i < SIZE; i++)
	{
		playersShapes[i] = _playersShapes[i];
	}
}
void Menu::setPlayersArr(Player* _playersArr[]) {
	for (int i = 0; i < SIZE; i++)
	{
		playersArr[i] = _playersArr[i];
	}
}
void Menu::getPlayerChoise() {
	char key;
	while (true) {//until the player will press on key
		if (_kbhit()) {
			key = _getch();
			if (key == H_VS_H || key == H_VS_C || key == C_VS_C || key == INSTRUCTIONS || key == EXIT || key == WITHOUT_COLOR || key == PAUSEDGAME || key == SETTINGS)
			{
				if (isPausedGame && key == SETTINGS)
					continue;
				else {
					setPlayerChoise(key);
					break;
				}


			}

		}
	}

}
void Menu::printLevelMenu(int playerNum) {

	int yLocation = 8;
	system("cls");
	gotoxy(10, 10);
	for (int i = 15; i < 71; i++) {
		gotoxy(i, 5);
		cout << "*";
		gotoxy(i, 15);
		cout << "*";
	}
	for (int j = 5; j <= 15; j++) {
		gotoxy(15, j);
		cout << "*";
		gotoxy(70, j);
		cout << "*";
	}
	gotoxy(30, 6);

	cout << "Choose Level for player " << playerNum << ":";
	gotoxy(33, yLocation);
	yLocation += 2;
	cout << "(1) BEST";
	gotoxy(33, yLocation);
	yLocation += 2;
	cout << "(2) GOOD";
	gotoxy(33, yLocation);
	yLocation += 2;
	cout << "(3) NOVICE";

	getPlayerChoise();

	system("cls");

}
void Menu::printSettings() {


	gotoxy(0, 0);
	cout << "(3) Back to menu";
	int yLocation = 8;
	system("cls");
	gotoxy(10, 10);
	for (int i = 13; i < 71; i++) {
		gotoxy(i, 5);
		cout << "*";
		gotoxy(i, 13);
		cout << "*";
	}
	for (int j = 5; j <= 13; j++) {
		gotoxy(13, j);
		cout << "*";
		gotoxy(70, j);
		cout << "*";
	}

	gotoxy(32, 6);
	cout << "Choose game mode";
	gotoxy(29, yLocation);
	yLocation += 2;
	cout << "(5) Game without colors";
	gotoxy(29, yLocation);
	yLocation += 2;
	cout << "(1) Game with colors";

	getPlayerChoise();
	if (playerChoice == WITHOUT_COLOR)
		setIsWithoutColor(true);
	else
	{
		setIsWithoutColor(false);
	}
	printMenu(ExitGame);


}
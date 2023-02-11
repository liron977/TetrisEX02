#include <windows.h>
#include <iostream>
#include "TheTetrisGame.h"
#include "Menu.h"


int main()
{

	bool ExitGame = false;
	Menu m;
	removeCursor();
	m.printMenu(ExitGame);
	TheTetrisGame G;
	G.GameOver();

}
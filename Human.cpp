#include "Human.h"
int Human::getDirection(char key) {//humen
	for (int i = 0; i < ARROW_KEYS_SIZE; i++)
	{
		if (key == arrowKeys[i])
			return i;
	}
	return -1;//The key is not the key of the current player.
}

void Human::setArrowKeys(const char* keys) {//humen

	for (int i = 0; i < ARROW_KEYS_SIZE; i++)
	{
		arrowKeys[i] = keys[i];
	}
}
int  Human::getMove(int& numOfRotate, int rightLimit, int leftLimit, Point(&copyOfBottomShape)[SIZE], int Xposition, int Yposition, bool& isReachedTheBottom, int& playerInput, Shape& s, bool& isFirstShapePlayer)
{
	return  playerInput;
}

int Human::getMoveForBomb(int rightLimit, int leftLimit, int Xposition, int Yposition, int& inputPlayer)
{
	return inputPlayer;
}
void Human::setBoard(Board* _theGameBoard) {
	theGameBoard = _theGameBoard;
}
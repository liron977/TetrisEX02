#include "Bomb.h"

void Bomb::printBomb() {

	bomb.draw(BOMB_TAV);
}
void Bomb::defaultMove() {

	bomb.setPoint(bomb.getX(), bomb.getY() + 1, BOMB_TAV);
	theGameBoard->updatePointInBoard(bomb.getX(), bomb.getY(), BOMB_TAV);
}
void Bomb::moveBomb(int x, int y) {

	bomb.setPoint(bomb.getX() + x, bomb.getY() + y, BOMB_TAV);
	theGameBoard->updatePointInBoard(bomb.getX(), bomb.getY(), BOMB_TAV);
	direction = -1;

}
bool Bomb::isValidMoveForBomb(int keyCode)const {
	if ((keyCode == L_CAPITAL) || (keyCode == L_LOWER)) {//LEFT
		if (theGameBoard->isEmptyPlace(bomb.getX() - 1, bomb.getY())) {
			return true;
		}
		return false;
	}
	else if ((keyCode == R_CAPITAL) || (keyCode == R_LOWER)) {//RIGHT
		if (theGameBoard->isEmptyPlace(bomb.getX() + 1, bomb.getY())) {
			return true;
		}
		return false;
	}
	else if ((keyCode == DEFAULT_MOVE)) {//Defult move(down)
		if ((!(theGameBoard->isEmptyPlace(bomb.getX(), bomb.getY() + 1))) && (bomb.getX() != 0)) {
			return false;
		}

	}
	return true;
}

void Bomb::initBomb(int whichPlayer) {

	int x = 0;

	if (whichPlayer == PLAYER1) {
		x = CENTER_PLAYER_1;
		direction = CENTER_PLAYER_1;

	}
	else {
		x = CENTER_PLAYER_2;
		direction = CENTER_PLAYER_2;
	}
	bomb.setPoint(x, 0, BOMB_TAV);
	IsAnewBomb = false;
}
void Bomb::setDirection(int dir)
{
	direction = dir;


}
bool Bomb::UpdateBomb()
{
	int leftLimit;
	int rightLimit;

	if (isValidMoveForBomb(-1)) {
		deleteBomb();
		defaultMove();
	}

	if ((direction == L_CAPITAL || direction == L_LOWER) && isValidMoveForBomb(direction)) { // LEFT
		deleteBomb();
		moveBomb(-1, 0);
		printBomb();
	}
	else if ((direction == R_CAPITAL || direction == R_LOWER) && isValidMoveForBomb(direction)) {// Right
		deleteBomb();
		moveBomb(1, 0);
		printBomb();

	}
	if (((direction == DROP_CAPITAL || direction == DROP_LOWER)) && (isValidMoveForBomb(-1))) {
		drop();
	}
	if (theGameBoard->isBombShouldEexplode(bomb.getX(), bomb.getY())) {
		if ((0 <= bomb.getX()) && (bomb.getX() <= COLSIZE / 2)) { //Player 1
			leftLimit = 1;
			rightLimit = COLSIZE / 2;
		}
		else { //Player 2
			leftLimit = COLSIZE / 2 + 1;
			rightLimit = COLSIZE - 1;
		}
		theGameBoard->bombExplode(bomb.getY(), bomb.getX(), rightLimit, leftLimit);
		IsAnewBomb = true;
		return true;
	}

	else
	{
		printBomb();
		theGameBoard->updatePointInBoard(bomb.getX(), bomb.getY(), BOMB_TAV);
	}
	direction = -1;
	return false;
}
void Bomb::deleteBomb() {
	bomb.draw(' ');
	theGameBoard->updatePointInBoard(bomb.getX(), bomb.getY(), ' ');
}
void Bomb::drop() {
	while (bomb.getY() < 17 && isValidMoveForBomb(-1)) {
		deleteBomb();
		moveBomb(0, 1);
		printBomb();
		theGameBoard->updatePointInBoard(bomb.getX(), bomb.getY(), BOMB_TAV);
	}

}


void Bomb::copyBomb(Point(&saver)) {

	bomb.setPoint(saver.getX(), saver.getY(), saver.getPointChar());

}
bool Bomb::isAnewBomb()const {
	return IsAnewBomb;
}
int Bomb::getBombX()const
{
	return (bomb.getX());
}
int Bomb::getBombY()const
{
	return (bomb.getY());
}
bool Bomb::isAbomb() {
	if (randBomb == 0) {
		return true;
	}
	return false;
}
void Bomb::UpdateRandBomb() {
	randBomb = rand() % 20;
}
void Bomb::setBoard(Board* _theGameBoard) {
	theGameBoard = _theGameBoard;
}
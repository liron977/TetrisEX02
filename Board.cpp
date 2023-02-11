#include "Board.h"
#include "Shape.h"

void Board::updateBoard(Point(&p1)[SHAPEARRSIZE][SHAPEARRSIZE]) {
	int y = 0, x = 0;
	for (int i = 0; i < SHAPEARRSIZE; i++) {
		for (int j = 0; j < SHAPEARRSIZE; j++) {
			x = p1[i][j].getX();
			y = p1[i][j].getY();
			if (x != 0) {
				theBoardMatrix[y][x] = p1[i][j].getPointChar();
			}
		}
	}
}
void Board::updatePointInBoard(int y, int x, char pointChar) {
	theBoardMatrix[x][y] = pointChar;
}
void Board::matrixInit() {
	for (int i = 0; i < ROWSIZE; i++)
	{
		for (int j = 0; j < COLSIZE; j++)
		{
			if (j == START || j == MIDDLE || j == COLSIZE - 1)
				theBoardMatrix[i][j] = '|';
			else if (i == ROWSIZE - 1)
			{
				(theBoardMatrix[i][j]) = '*';
			}
			else
			{
				(theBoardMatrix[i][j]) = ' ';
			}
		}
	}
}
void Board::printBoard()const {
	for (int i = 0; i < ROWSIZE; i++)
	{
		for (int j = 0; j < COLSIZE; j++)
		{

			cout << theBoardMatrix[i][j];
		}
		cout << endl;
	}
}
bool Board::isEmptyPlace(int pointX, int pointY) const {
	if (theBoardMatrix[pointY][pointX] == ' ')
		return true;
	return false;
}
bool Board::isFullRow(int row, int leftLimit, int rightLimit) const {
	for (int i = leftLimit; i < rightLimit; i++) {
		if (theBoardMatrix[row][i] == ' ')
			return false;
	}
	return true;
}
void Board::deleteRow(int row, int leftLimit, int rightLimit, bool isWithoutColor) {
	for (int i = row; i - 1 > 1; i--)
	{
		if (!isWithoutColor) {
			setTextColor(RED);
		}
		for (int j = leftLimit; j < rightLimit; j++) {
			gotoxy(j, i);
			cout << theBoardMatrix[i][j];
		}
		Sleep(10);
		setTextColor(WHITE);
		for (int j = leftLimit; j < rightLimit; j++) {
			updatePointInBoard(j, i, theBoardMatrix[i - 1][j]);
			gotoxy(j, i);
			cout << theBoardMatrix[i - 1][j];
		}
	}
}
bool Board::isBombShouldEexplode(int x, int y)const {


	bool isBombEexplodeFlag = isTaken(y + 1, x);
	return (isBombEexplodeFlag);
}
bool Board::isTaken(int pointX, int pointY) const {
	if ((theBoardMatrix[pointX][pointY] == TAV) || (pointX == ROWSIZE - 1))
		return true;
	return false;
}
void Board::bombExplode(int x, int y, int playerMaxCol, int playerMinCol) {

	for (int i = x - RANGE; i <= x + RANGE; i++)
	{
		if ((i < ROWSIZE - 1) && (i >= 0))
		{
			for (int j = y - RANGE; j <= y + RANGE; j++) {

				if ((j >= playerMinCol) && (j < playerMaxCol))
				{
					if (!isEmptyPlace(j, i)) {
						theBoardMatrix[i][j] = ' ';

						gotoxy(j, i);
						cout << theBoardMatrix[i][j];

					}
				}
			}
		}
	}


}

int Board::deletedRowCounter(Shape& s, int leftLimit, int rightLimit) const
{
	int count = 0;

	s.updateShapeInBoard();
	for (int i = 0; i < SHAPEARRSIZE; i++)
	{
		for (int j = 0; j < SHAPEARRSIZE; j++)
		{
			if (isFullRow(i, leftLimit, rightLimit))
				count++;
		}
	}

	s.deleteMatrix();

	return count;

}
#include "Computer.h"


void Computer::printMatrix(Point(&p1)[SHAPEARRSIZE][SHAPEARRSIZE])const

{
	for (int i = 0; i < SHAPEARRSIZE; i++)
	{
		for (int j = 0; j < SHAPEARRSIZE; j++)
		{
			if (p1[i][j].getPointChar() == TAV)
			{

				p1[i][j].draw(TAV);

			}
		}
	}
	setTextColor(WHITE);
}

void Computer::findOptimalPlace(int& saverNumOfRotate, int rightLimit, int leftLimit) {

	Point saver[SHAPEARRSIZE][SHAPEARRSIZE] = {};
	for (int i = 0; i < SHAPEARRSIZE; i++) {
		for (int j = 0; j < SHAPEARRSIZE; j++) {
			saver[i][j].setPoint(i, j, ' ');

		}
	}
	tempShape.setShapeToTheLeft(leftLimit);
	bool isrotate = false;
	int i = 0, j = 0;
	bool isRowDeleted = false;
	int shapeBottomRow = 0;
	int maxDeletedRow = 0, rowNumber = 0, currDeletedRow, numOfRotate, index = 0, minNumRow = 0;
	numOfRotate = numOfRotateForShape();
	do {
		tempShape.setShapeToTheLeft(leftLimit);
		for (i = 0; i < ROWSIZE - 1; i++) {
			for (j = leftLimit; j < rightLimit; j++) {

				if (tempShape.isVaildPosition(i)) {
					if (thereIsAwayToThisLocation()) {
						currDeletedRow = theGameBoard->deletedRowCounter(tempShape, leftLimit, rightLimit);
						if (currDeletedRow != 0) {
							isRowDeleted = true;
							if (currDeletedRow > maxDeletedRow) {
								maxDeletedRow = currDeletedRow;
								tempShape.copyToShapeMatrix(saver);

								saverNumOfRotate = index + 1;

							}
						}
						else {
							shapeBottomRow = tempShape.getShapeBottomY();
							if ((shapeBottomRow > minNumRow) && (!isRowDeleted)) {
								minNumRow = shapeBottomRow;
								tempShape.copyToShapeMatrix(saver);
								saverNumOfRotate = index;
							}
						}
					}
				}
				tempShape.setShapeCol();


			}
			tempShape.setShapeToTheLeft(leftLimit);
			if (tempShape.getShapeBottomY() < BOTTOM)
				tempShape.setShapeRow();
		}
		tempShape.setShapeToTheTop();
		tempShape.setShapeToTheCenter();
		if (tempShape.isValidRotateClockWise()) {
			tempShape.rotateClockwise();
			isrotate = true;

		}

		index++;

	} while (index <= numOfRotate);

	tempShape.copyFromShapeMatrix(saver);
}

int Computer::numOfRotateForShape() const {
	int shapeCode = tempShape.getShapeCode();
	if (shapeCode == I_SHAPE)
		return 1;//I SHAPE max num of rotate
	if (shapeCode == O_SHAPE)
		return 0;//O SHAPE max num of rotate
	return 3;//other shapes max num of rotate
}




int Computer::getMove(int& numOfRotate, int rightLimit, int leftLimit, Point(&copyOfBottomShape)[SHAPEARRSIZE], int Xposition, int Yposition, bool& isReachedTheBottom, int& playerInput, Shape& s, bool& isFirstShapePlayer) {
	setWhichMove();
	isOptimalMoveForBomb = true;
	int yDesPosition = 0;
	int optionalnumOfRotate;
	if (isRandomMove) {
		countMoves++;
		xDesPositionForShape = findRandomPlace(rightLimit, leftLimit);
		yDesPosition = BOTTOM;
		optionalnumOfRotate = numOfRotateForShape();
		if (optionalnumOfRotate != 0) {
			numOfRotate = (rand() % optionalnumOfRotate);
		}
		isRandomMove = false;
	}

	else if (isReachedTheBottom || isFirstShapePlayer) {
		copyShape(s);
		countMoves++;
		findOptimalPlace(numOfRotate, rightLimit, leftLimit);
		xDesPositionForShape = tempShape.getMostLeftPoint().getX();
		yDesPosition = tempShape.getShapeBottomY();

	}
	if (numOfRotate > 0) {
		numOfRotate--;
		return ROTATE;
	}
	else if (Xposition > xDesPositionForShape) {

		return LEFT_MOVE;//left
	}
	else if (Xposition < xDesPositionForShape) {

		return RIGHT_MOVE;//right
	}

	else if (Xposition = xDesPositionForShape) {
		if (thePathIsEmpty(copyOfBottomShape, yDesPosition)) {

			return DROP_MOVE;//Drop

		}

	}
	return DEFAULT_MOVE;
}
bool Computer::thePathIsEmpty(Point(&copyOfBottomShape)[SHAPEARRSIZE], int yDes)const {
	int yPosition = 0;

	for (int i = 0; i < SIZE; i++) {
		yPosition = copyOfBottomShape[i].getY() + 1;
		if (copyOfBottomShape[i].getPointChar() == TAV) {
			while (yPosition < yDes) {
				if (!theGameBoard->isEmptyPlace(copyOfBottomShape[i].getX(), yPosition))
				{
					return false;
				}
				yPosition++;

			}
		}

	}
	return true;
}
int Computer::findRandomPlace(int rightLimit, int leftLimit)const
{
	int xRandPlace = (rand() % rightLimit) + leftLimit;
	return xRandPlace;
}

bool  Computer::thereIsAwayToThisLocation() {
	int xDesPosition = tempShape.getMostLeftPoint().getX();
	int yDesPosition = tempShape.getShapeBottomY();
	
	Point saveCurrShape[SHAPEARRSIZE][SHAPEARRSIZE];
	int nextMove;
	tempShape.copyToShapeMatrix(saveCurrShape);
	tempShape.setShapeToTheTop();

	int xPosition;
	int yPosition;

	do {
		xPosition = tempShape.getMostLeftPoint().getX();
		yPosition = tempShape.getShapeBottomY();
		nextMove = getMoveForShape(yDesPosition, xDesPosition, xPosition, yPosition);
		if (nextMove == REACHED_THE_POSITION) {
			tempShape.copyFromShapeMatrix(saveCurrShape);
			return true;
		}

		if (nextMove == RIGHT_MOVE)
		{
			if (tempShape.isValidMoveForShape(RIGHT_MOVE))
			{
				tempShape.setShapeMatrix(1, 0);
			}
		}
		if (nextMove == LEFT_MOVE)
		{
			if (tempShape.isValidMoveForShape(LEFT_MOVE))
			{
				tempShape.setShapeMatrix(-1, 0);
			}
		}
		if (tempShape.isValidMoveForShape(DEFAULT_MOVE))
			tempShape.setShapeMatrix(0, 1);

	} while (!tempShape.isReachedToTheBottom());
	yPosition = tempShape.getShapeBottomY();
	if (xDesPosition == xPosition && yDesPosition == yPosition) {
		tempShape.copyFromShapeMatrix(saveCurrShape);
		return true;
	}
	tempShape.copyFromShapeMatrix(saveCurrShape);
	return false;


}
int Computer::getMoveForShape(int yDesPosition, int xDesPosition, int xPosition, int yPosition)const {

	if (xPosition > xDesPosition) {

		return LEFT_MOVE;//left
	}
	if (xPosition < xDesPosition) {

		return RIGHT_MOVE;//right
	}
	if (yPosition == yDesPosition)
		return REACHED_THE_POSITION;


	return DEFAULT_MOVE;

}
int Computer::getDirection(char key)
{
	return DEFAULT_MOVE;
}


void Computer::findOptimalPlaceForBomb(int rightLimit, int leftLimit, Point(&saver))const
{
	int i = 0, j = 0;
	int center = 0;
	bool isFindPlace = false;
	for (i = 1; i < ROWSIZE - 1 && !isFindPlace; i++) {
		for (j = leftLimit + 1; j < rightLimit - 1; j++) {
			if (!theGameBoard->isEmptyPlace(j, i)) {
				saver.setPoint(j, i - 1, BOMB_TAV);
				isFindPlace = true;
				break;
			}

		}
	}
	if (!isFindPlace)
		saver.setPoint((leftLimit - rightLimit) / 2, 0, BOMB_TAV);
}
void Computer::setBomb(Bomb b)
{
	bomb = b;
}

int Computer::getMoveForBomb(int rightLimit, int leftLimit, int Xposition, int Yposition, int& inputPlayer) {

	Point pointSaver;

	int yDesPosition;
	if (isRandomMove) {
		xDesPositionForBomb = findRandomPlace(rightLimit, leftLimit);
		yDesPosition = BOTTOM;
		countMoves++;
		isRandomMove = false;
		

	}
	else if (isOptimalMoveForBomb) {

		pointSaver = {};
		countMoves++;
		findOptimalPlaceForBomb(rightLimit, leftLimit, pointSaver);
		bomb.copyBomb(pointSaver);
		xDesPositionForBomb = bomb.getBombX();
		yDesPosition = bomb.getBombY();
		countMoves++;
		isOptimalMoveForBomb = false;
	}

	if (xDesPositionForBomb < Xposition) {

		return LEFT_MOVE;//left
	}
	if (Xposition < xDesPositionForBomb) {

		return RIGHT_MOVE;//right
	}

	if (xDesPositionForBomb = Xposition) {
		return DROP_MOVE;//Drop

	}

	return DEFAULT_MOVE;

}
void Computer::setLevel(int _level) {

	level = _level;

}
void Computer::setWhichMove() {
	if (level == GOOD_LEVEL && countMoves % 15 == 0) {
		isRandomMove = true;


	}
	if (level == NOVICE_LEVEL && countMoves % 5 == 0) {
		isRandomMove = true;

	}
	else {

		isRandomMove = false;
	}
}

void Computer::copyShape(Shape s1)
{
	tempShape = s1;
}
void Computer::setBoard(Board* _theGameBoard) {
	theGameBoard = _theGameBoard;
}
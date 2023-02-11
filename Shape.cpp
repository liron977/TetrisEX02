#include "Shape.h"
#include "Point.h"
#include "Board.h"


void Shape::initShapeMatrix()
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			shapeMatrix[i][j].setPoint(i, j, ' ');

		}
	}
}

void Shape::printMatrix()
{

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (shapeMatrix[i][j].getPointChar() == TAV)
			{
				setTextColor(color);
				shapeMatrix[i][j].draw(TAV);

			}
		}
	}
	setTextColor(WHITE);
	theGameBoard->updateBoard(shapeMatrix);
}

void Shape::deleteMatrix() const
{

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (shapeMatrix[i][j].getPointChar() == TAV)
			{
				shapeMatrix[i][j].draw(' ');
				theGameBoard->updatePointInBoard(shapeMatrix[i][j].getX(), shapeMatrix[i][j].getY(), ' ');

			}
		}
	}
}



Point Shape::getMostLeftPoint()const
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++) {
			if (shapeMatrix[i][j].getPointChar() == TAV)
			{
				return shapeMatrix[i][j];
			}
		}
	}
	return shapeMatrix[0][0];
}

Point& Shape::getBottomPoint()const
{
	Point currBottomPoint = shapeMatrix[1][0];
	int lastJ = 0;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if ((shapeMatrix[i][j].getPointChar() == TAV) && j >= lastJ)
			{
				currBottomPoint = shapeMatrix[i][j];
			}
		}
	}
	return currBottomPoint;
}

void Shape::getBottomArrPoint(Point(&currBottomPoint)[SIZE]) const
{
	int k = 0;
	int lastJ = 0;
	bool isFullRowInBoard = false;
	for (int i = 0; i < SIZE; i++)
	{
		currBottomPoint[i] = {};
	}
	for (int i = SIZE-1; i >= 0; i--)
	{
		for (int j = SIZE-1; j >= 0; j--)
		{
			if ((shapeMatrix[i][j].getPointChar() == TAV))
			{
				currBottomPoint[k] = shapeMatrix[i][j];
				j = -1;
				k++;
				if (k == 4) {
					break;
				}
			}
		}
	}

}

bool Shape::UpdateShape(bool& isRowDeleted, bool isWithoutColor)
{
	bool isReachedTheBottom = false;
	int leftLimit = 0;
	int rightLimit = 0;

	if (isValidMoveForShape(-1)) {
		deleteMatrix();
		setShapeMatrix(0, 1);
		theGameBoard->updateBoard(shapeMatrix);
	}
	else {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				if (shapeMatrix[i][j].getPointChar() == TAV) {

					if ((0 <= shapeMatrix[i][j].getX()) && (shapeMatrix[i][j].getX() <= BOARD_COL_SIZE / 2)) { //Player 1
						leftLimit = 1;
						rightLimit = BOARD_COL_SIZE / 2;
					}
					else { //Player 2
						leftLimit = BOARD_COL_SIZE / 2 + 1;
						rightLimit = BOARD_COL_SIZE - 1;
					}
					if (theGameBoard->isFullRow(shapeMatrix[i][j].getY(), leftLimit, rightLimit)) {
						theGameBoard->deleteRow(shapeMatrix[i][j].getY(), leftLimit, rightLimit, isWithoutColor);
						isRowDeleted = true;
					}
				}
			}
		}
		isReachedTheBottom = true;
		return isReachedTheBottom;


	}
	if ((direction == L_CAPITAL || direction == L_LOWER) && isValidMoveForShape(direction)) // LEFT
	{
		deleteMatrix();
		setShapeMatrix(-1, 0);
		theGameBoard->updateBoard(shapeMatrix);
		printMatrix();
	}

	else if ((direction == R_CAPITAL || direction == R_LOWER) && isValidMoveForShape(direction)) // Right
	{
		deleteMatrix();
		setShapeMatrix(1, 0);
		theGameBoard->updateBoard(shapeMatrix);
		printMatrix();

	}
	else if ((direction == CLOCKWISE_CAPITAL || direction == CLOCKWISE_LOWER) && shapeCode != 5 && isValidRotateClockWise()) {
		deleteMatrix();
		rotateClockwise();
		theGameBoard->updateBoard(shapeMatrix);
	}
	else if ((direction == COUNTER_CLOCKWISE_CAPITAL || direction == COUNTER_CLOCKWISE_LOWER) && (shapeCode != 5) && (isValidCounterRotateClockWise())) {

		deleteMatrix();
		CounterRotateClockWise();
		theGameBoard->updateBoard(shapeMatrix);

	}

	if (((direction == DROP_CAPITAL || direction == DROP_LOWER)) && (isValidMoveForShape(-1)))
	{
		drop(isWithoutColor);
		theGameBoard->updateBoard(shapeMatrix);
	}



	if (!isRowDeleted)
	{
		printMatrix();
		theGameBoard->updateBoard(shapeMatrix);
	}
	return isReachedTheBottom;

}

void Shape::createShapePlayer(int x, int numShape, bool& isWithoutColor)
{
	if (isWithoutColor)
	{
		setColor(WHITE);
	}
	else
	{
		Color randColor = static_cast<Color>((rand() % YELLOW) + 1);
		setColor(randColor);
	}
	initShapeMatrix();
	int z = 18;//The center of the second player board.
	if (x == 0)
		z = 5;//The center of the first player board.
	switch (numShape)
	{
	case (J_SHAPE):
		shapeMatrix[2][0].setPoint(z + 3, 0, TAV);
		shapeMatrix[2][1].setPoint(z + 3, 1, TAV);
		shapeMatrix[1][1].setPoint(z + 2, 1, TAV);
		shapeMatrix[0][1].setPoint(z + 1, 1, TAV);
		setshapeCode(1);
		break;
	case (I_SHAPE):
		shapeMatrix[0][0].setPoint(z, 0, TAV);
		shapeMatrix[1][0].setPoint(z + 1, 0, TAV);
		shapeMatrix[2][0].setPoint(z + 2, 0, TAV);
		shapeMatrix[3][0].setPoint(z + 3, 0, TAV);
		setshapeCode(2);
		break;
	case (L_SHAPE):
		shapeMatrix[0][0].setPoint(z, 0, TAV);
		shapeMatrix[0][1].setPoint(z, 1, TAV);
		shapeMatrix[1][1].setPoint(z + 1, 1, TAV);
		shapeMatrix[2][1].setPoint(z + 2, 1, TAV);
		setshapeCode(3);
		break;

	case (Z_SHAPE):
		shapeMatrix[1][0].setPoint(z + 1, 0, TAV);
		shapeMatrix[2][0].setPoint(z + 2, 0, TAV);
		shapeMatrix[2][1].setPoint(z + 2, 1, TAV);
		shapeMatrix[3][1].setPoint(z + 3, 1, TAV);
		setshapeCode(4);
		break;

	case (O_SHAPE):

		shapeMatrix[0][1].setPoint(z + 1, 1, TAV);
		shapeMatrix[0][2].setPoint(z + 1, 2, TAV);
		shapeMatrix[1][1].setPoint(z + 2, 1, TAV);
		shapeMatrix[1][2].setPoint(z + 2, 2, TAV);
		setshapeCode(5);
		break;

	case (T_SHAPE):

		shapeMatrix[2][0].setPoint(z + 2, 0, TAV);
		shapeMatrix[1][1].setPoint(z + 1, 1, TAV);
		shapeMatrix[2][1].setPoint(z + 2, 1, TAV);
		shapeMatrix[3][1].setPoint(z + 3, 1, TAV);
		setshapeCode(6);
		break;

	case (S_SHAPE):

		shapeMatrix[2][0].setPoint(z + 2, 0, TAV);
		shapeMatrix[3][0].setPoint(z + 3, 0, TAV);
		shapeMatrix[1][1].setPoint(z + 1, 1, TAV);
		shapeMatrix[2][1].setPoint(z + 2, 1, TAV);
		setshapeCode(7);
		break;
	}

}

bool Shape::isValidMoveForShape(int keyCode) const
{


	bool isvalidMove = true;
	if ((keyCode == 0) || (keyCode == 1))//LEFT
	{
		Point currBottomPoint[SIZE];
		getLeftPointsArr(currBottomPoint);
		for (int i = 0; i < SIZE; i++) {

			if (currBottomPoint[i].getPointChar() == TAV) {
				if (!theGameBoard->isEmptyPlace(currBottomPoint[i].getX() - 1, currBottomPoint[i].getY()))
				{

					return false;
				}
			}


		}
		return true;


	}
	if ((keyCode == R_CAPITAL) || (keyCode == R_LOWER)) //RIGHT
	{
		Point currRightPoints[SIZE];
		getRightPointsArr(currRightPoints);


		for (int i = 0; i < SIZE; i++) {

			if (currRightPoints[i].getPointChar() == TAV) {
				if (!theGameBoard->isEmptyPlace(currRightPoints[i].getX() + 1, currRightPoints[i].getY()))
				{

					return false;
				}
			}


		}
		return true;


	}
	if ((keyCode == -1))//Defult move(down).
	{
		Point currBottomPoint[SIZE];
		getBottomArrPoint(currBottomPoint);
		for (int i = 0; i < SIZE; i++)
		{

			if ((!(theGameBoard->isEmptyPlace(currBottomPoint[i].getX(), currBottomPoint[i].getY() + 1))) && (currBottomPoint[i].getX() != 0)) {
				isvalidMove = false;
				return isvalidMove;
			}
		}

	}
	return isvalidMove;
}

void Shape::rotateClockwise()
{
	for (int x = 0; x < 2; x++) {
		// Consider elements in group
		// of 4 in current square
		for (int y = x; y < 3 - x; y++) {
			// Store current cell in
			// temp variable
			Point temp;
			temp = shapeMatrix[x][y];

			// Move values from right to top
			shapeMatrix[x][y].setPoint(x - y + shapeMatrix[y][3 - x].getX(), y - (3 - x) + shapeMatrix[y][3 - x].getY(), shapeMatrix[y][3 - x].getPointChar());

			// Move values from bottom to right
			shapeMatrix[y][3 - x].setPoint(y - (3 - x) + shapeMatrix[3 - x][3 - y].getX(), 3 - x - (3 - y) + shapeMatrix[3 - x][3 - y].getY(), shapeMatrix[3 - x][3 - y].getPointChar());

			// Move values from left to bottom
			shapeMatrix[3 - x][3 - y].setPoint((3 - x) - (3 - y) + shapeMatrix[3 - y][x].getX(), 3 - y - x + shapeMatrix[3 - y][x].getY(), shapeMatrix[3 - y][x].getPointChar());

			// Assign temp to left
			shapeMatrix[3 - y][x].setPoint((3 - y) - x + temp.getX(), x - y + temp.getY(), temp.getPointChar());


		}
	}

}

void Shape::CounterRotateClockWise()
{

	// Traverse each cycle
	for (int x = 0; x < 2; x++) {
		for (int y = x; y < 3 - x; y++) {

			// Swap elements of each cycle
			// in clockwise direction
			Point temp;
			temp = shapeMatrix[x][y];

			shapeMatrix[x][y].setPoint(x - (3 - y) + shapeMatrix[3 - y][x].getX(), y - x + shapeMatrix[3 - y][x].getY(), shapeMatrix[3 - y][x].getPointChar());
			shapeMatrix[3 - y][x].setPoint(3 - y - (3 - x) + shapeMatrix[3 - x][3 - y].getX(), x - (3 - y) + shapeMatrix[3 - x][3 - y].getY(), shapeMatrix[3 - x][3 - y].getPointChar());
			shapeMatrix[3 - x][3 - y].setPoint(3 - x - y + shapeMatrix[y][3 - x].getX(), 3 - y - (3 - x) + shapeMatrix[y][3 - x].getY(), shapeMatrix[y][3 - x].getPointChar());
			shapeMatrix[y][3 - x].setPoint(y - x + temp.getX(), 3 - x - y + temp.getY(), temp.getPointChar());
		}
	}

}

bool  Shape::isValidRotateClockWise() const
{
	for (int x = 0; x < 2; x++) {
		// Consider elements in group
		// of 4 in current square
		for (int y = x; y < 3 - x; y++) {
			Point temp;
			temp = shapeMatrix[x][y];
			if (!(theGameBoard->isEmptyPlace(x - y + shapeMatrix[y][3 - x].getX(), y - (3 - x) + shapeMatrix[y][3 - x].getY())) && !(isPartOfTheShape(x - y + shapeMatrix[y][3 - x].getX(), y - (3 - x) + shapeMatrix[y][3 - x].getY())) && shapeMatrix[y][3 - x].getPointChar() == TAV) {
				return false;
			}
			if (!(theGameBoard->isEmptyPlace(y - (3 - x) + shapeMatrix[3 - x][3 - y].getX(), 3 - x - (3 - y) + shapeMatrix[3 - x][3 - y].getY())) && !(isPartOfTheShape(y - (3 - x) + shapeMatrix[3 - x][3 - y].getX(), 3 - x - (3 - y) + shapeMatrix[3 - x][3 - y].getY())) && shapeMatrix[3 - x][3 - y].getPointChar() == TAV) {
				return false;
			}
			if (!(theGameBoard->isEmptyPlace((3 - x) - (3 - y) + shapeMatrix[3 - y][x].getX(), 3 - y - x + shapeMatrix[3 - y][x].getY())) && !(isPartOfTheShape((3 - x) - (3 - y) + shapeMatrix[3 - y][x].getX(), 3 - y - x + shapeMatrix[3 - y][x].getY())) && shapeMatrix[3 - y][x].getPointChar() == TAV) {
				return false;
			}
			if (!(theGameBoard->isEmptyPlace((3 - y) - x + temp.getX(), x - y + temp.getY())) && !(isPartOfTheShape((3 - y) - x + temp.getX(), x - y + temp.getY())) && temp.getPointChar() == TAV) {

				return false;

			}
		}
	}
	return true;

}


bool  Shape::isValidCounterRotateClockWise()const
{

	for (int x = 0; x < 2; x++) {
		// Consider elements in group
		// of 4 in current square
		for (int y = x; y < 3 - x; y++) {
			Point temp;
			temp = shapeMatrix[x][y];
			if (!(theGameBoard->isEmptyPlace(x - (3 - y) + shapeMatrix[3 - y][x].getX(), y - x + shapeMatrix[3 - y][x].getY())) && !(isPartOfTheShape(x - (3 - y) + shapeMatrix[3 - y][x].getX(), y - x + shapeMatrix[3 - y][x].getY())) && shapeMatrix[3 - y][x].getPointChar() == TAV) {
				return false;
			}
			if (!(theGameBoard->isEmptyPlace(3 - y - (3 - x) + shapeMatrix[3 - x][3 - y].getX(), x - (3 - y) + shapeMatrix[3 - x][3 - y].getY())) && !(isPartOfTheShape(3 - y - (3 - x) + shapeMatrix[3 - x][3 - y].getX(), x - (3 - y) + shapeMatrix[3 - x][3 - y].getY())) && shapeMatrix[3 - x][3 - y].getPointChar() == TAV) {
				return false;
			}
			if (!(theGameBoard->isEmptyPlace(3 - x - y + shapeMatrix[y][3 - x].getX(), 3 - y - (3 - x) + shapeMatrix[y][3 - x].getY())) && !(isPartOfTheShape(3 - x - y + shapeMatrix[y][3 - x].getX(), 3 - y - (3 - x) + shapeMatrix[y][3 - x].getY())) && shapeMatrix[y][3 - x].getPointChar() == TAV) {
				return false;
			}
			if (!(theGameBoard->isEmptyPlace(y - x + temp.getX(), 3 - x - y + temp.getY())) && !(isPartOfTheShape(y - x + temp.getX(), 3 - x - y + temp.getY())) && temp.getPointChar() == TAV) {

				return false;

			}
		}
	}
	return true;

}
bool Shape::isPartOfTheShape(int x, int y) const {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (shapeMatrix[i][j].getX() == x && shapeMatrix[i][j].getY() == y && shapeMatrix[i][j].getPointChar() == TAV) {
				{
					return true;
				}
			}
		}
	}
	return false;
}


void Shape::drop(bool  isWithoutColor)
{
	while (getBottomPoint().getY() < BOTTOM-1 && isValidMoveForShape(-1))
	{
		deleteMatrix();
		setShapeMatrix(0, 1);
		printMatrix();
		theGameBoard->updateBoard(shapeMatrix);
	}
}
bool Shape::isAplayerLost(bool isReachedTheBottom) const
{
	Point currBottomPoint[SIZE];
	getBottomArrPoint(currBottomPoint);
	for (int i = 0; i < SIZE; i++)
	{
		if ((currBottomPoint[i].getY() == 2 || currBottomPoint[i].getY() == 1) && isReachedTheBottom)
		{
			return true;
		}
	}
	return false;
}
void  Shape::setShapeMatrix(int valueX, int valueY) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (shapeMatrix[i][j].getPointChar() == TAV) {
				shapeMatrix[i][j].setPoint(shapeMatrix[i][j].getX() + valueX, shapeMatrix[i][j].getY() + valueY, TAV);
			}
		}
	}
}

void Shape::copyToShapeMatrix(Point(&destination)[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			destination[i][j] = shapeMatrix[i][j];
		}
	}
}
void Shape::copyFromShapeMatrix(Point(&destination)[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			shapeMatrix[i][j] = destination[i][j];
		}
	}
}
int Shape::getShapeCode() const {
	return shapeCode;
}
void Shape::setShapeToTheTop() {
	int y = BOTTOM;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (shapeMatrix[i][j].getPointChar() == TAV) {
				if (shapeMatrix[i][j].getY() < y)
					y = shapeMatrix[i][j].getY();

			}
		}
	}
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (shapeMatrix[i][j].getPointChar() == TAV)
			{

				shapeMatrix[i][j].setPoint(shapeMatrix[i][j].getX(), shapeMatrix[i][j].getY() - y + 2, TAV);


			}
		}

	}

}
void Shape::setShapeToTheCenter() {

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (shapeMatrix[i][j].getPointChar() == TAV)
			{

				shapeMatrix[i][j].setPoint(shapeMatrix[i][j].getX() + 3, shapeMatrix[i][j].getY(), TAV);


			}
		}

	}

}
void Shape::setShapeToTheLeft(int leftLimit) {

	Point leftPoint = getMostLeftPoint();
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (shapeMatrix[i][j].getPointChar() == TAV)
			{

				shapeMatrix[i][j].setPoint(shapeMatrix[i][j].getX() - leftPoint.getX() + leftLimit + 1, shapeMatrix[i][j].getY(), TAV);


			}
		}

	}
}
bool Shape::isVaildPosition(int& currRow) const
{
	Point currBottomPoint[SIZE];
	getBottomArrPoint(currBottomPoint);

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++)
		{
			if (shapeMatrix[i][j].getPointChar() == TAV)
			{
				if (!theGameBoard->isEmptyPlace(shapeMatrix[i][j].getX(), shapeMatrix[i][j].getY()))
					return false;
			}
		}
	}
	for (int i = 0; i < SIZE; i++)
	{
		if (currBottomPoint[i].getPointChar() == TAV) {
			if (!theGameBoard->isEmptyPlace(currBottomPoint[i].getX(), currBottomPoint[i].getY() + 1)) {
				return true;
			}
		}

	}


	return false;
}

void Shape::updateShapeInBoard() {

	theGameBoard->updateBoard(shapeMatrix);
}

void  Shape::setShapeCol() {

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (shapeMatrix[i][j].getPointChar() == TAV)
			{
				shapeMatrix[i][j].setPoint(shapeMatrix[i][j].getX() + 1, shapeMatrix[i][j].getY(), TAV);
			}
		}

	}

}
void Shape::setShapeRow() {

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (shapeMatrix[i][j].getPointChar() == TAV)
			{
				shapeMatrix[i][j].setPoint(shapeMatrix[i][j].getX(), shapeMatrix[i][j].getY() + 1, TAV);
			}
		}

	}

}


int Shape::getShapeBottomY()const {
	int maxY = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (shapeMatrix[i][j].getPointChar() == TAV) {
				if (shapeMatrix[i][j].getY() > maxY)
					maxY = shapeMatrix[i][j].getY();

			}
		}
	}
	return maxY;
}

bool Shape::isReachedToTheBottom()const {
	Point currBottomPoint[SIZE];
	getBottomArrPoint(currBottomPoint);


	for (int i = 0; i < SIZE; i++)
	{
		if (currBottomPoint[i].getPointChar() == TAV) {
			if (!theGameBoard->isEmptyPlace(currBottomPoint[i].getX(), currBottomPoint[i].getY() + 1)) {
				return true;
			}
		}

	}
	return false;
}
void Shape::getLeftPointsArr(Point(&currLeftPointArr)[SIZE])const {
	for (int i = 0; i < SIZE; i++)
	{
		currLeftPointArr[i] = {};
	}
	int k = 0;
	bool isFound = false;
	for (int i = 0; i < SIZE && !isFound; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (shapeMatrix[i][j].getPointChar() == TAV) {
				currLeftPointArr[k] = shapeMatrix[i][j];
				k++;
				isFound = true;

			}
			if (isFound && j == SIZE - 1)
				break;
		}

	}
}


void Shape::getRightPointsArr(Point(&currRightPointArr)[SIZE])const {
	for (int i = 0; i < SIZE; i++)
	{
		currRightPointArr[i] = {};
	}
	int k = 0;
	bool isFound = false;
	for (int i = SIZE - 1; i > 0 && !isFound; i--) {
		for (int j = 0; j < SIZE; j++) {
			if (shapeMatrix[i][j].getPointChar() == TAV) {
				currRightPointArr[k] = shapeMatrix[i][j];
				k++;
				isFound = true;

			}
			if (isFound && j == SIZE - 1)
				break;
		}

	}

}
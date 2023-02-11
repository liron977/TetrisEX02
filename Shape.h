#ifndef __SHAPE_H_
#define __SHAPE_H_
#include <iostream>
#include "Point.h"
#include "Board.h"
#include "Color.h"
class Board;

class Shape
{

	enum { SIZE = 4, BOARD_COL_SIZE = 27,BOTTOM=18 };
	enum {L_CAPITAL = 0, L_LOWER = 1, R_CAPITAL = 2, R_LOWER = 3, CLOCKWISE_CAPITAL = 4, CLOCKWISE_LOWER = 5, COUNTER_CLOCKWISE_CAPITAL = 6, COUNTER_CLOCKWISE_LOWER = 7, DROP_CAPITAL = 8, DROP_LOWER = 9};
	enum { J_SHAPE=1,I_SHAPE=2,L_SHAPE=3,Z_SHAPE=4,O_SHAPE = 5,T_SHAPE=6,S_SHAPE=7};
	Point shapeMatrix[SIZE][SIZE];
	int shapeCode;
	int direction;
	int shapeCount;
	Board* theGameBoard;
	Color color;
	static constexpr char TAV = (char)178;

	void setshapeCode(int _shapeCode) {
		shapeCode = _shapeCode;
	}
	Point& getBottomPoint()const;
	bool isPartOfTheShape(int x, int y)const;
	void CounterRotateClockWise();
	void drop(bool isWithoutColor);
	void setColor(Color c) {
		color = c;
	}
	void  getLeftPointsArr(Point(&currLeftPointArr)[SIZE])const;
	void getRightPointsArr(Point(&currLeftPointArr)[SIZE])const;

public:
	bool isValidMoveForShape(int keyCode)const;
	Point getMostLeftPoint()const;
	void getBottomArrPoint(Point(&currBottomPoint)[SIZE])const;
	void setBoard(Board* _theGameBoard) {
		theGameBoard = _theGameBoard;
	}
	void initShapeMatrix();
	bool UpdateShape(bool& isRowDeleted, bool isWithoutColor);
	void setDirection(int dir) {
		direction = dir;
	}
	void createShapePlayer(int x, int numShape, bool& isWithoutColor);
	bool isAplayerLost(bool isReachedTheBottom) const;
	Board* getBoard() const {
		return theGameBoard;
	}
	void copyFromShapeMatrix(Point(&destination)[SIZE][SIZE]);
	void copyToShapeMatrix(Point(&destination)[SIZE][SIZE]);
	bool isValidCounterRotateClockWise()const;
	bool  isValidRotateClockWise()const;
	void rotateClockwise();
	int getShapeCode() const;
	void setShapeMatrix(int valueX, int valueY);
	void printMatrix();
	void setShapeToTheLeft(int leftLimit);
	bool isVaildPosition(int& currRow) const;
	void updateShapeInBoard();
	void  setShapeCol();
	void setShapeRow();
	void deleteMatrix()const;
	void setShapeToTheTop();
	void setShapeToTheCenter();
	int getShapeBottomY()const;
	bool isReachedToTheBottom()const;





};
#endif
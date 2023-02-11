#include "Point.h"

void Point::draw(char ch) const {
	gotoxy(x, y);
	cout << ch << endl;
}

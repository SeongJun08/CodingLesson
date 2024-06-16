#include <iostream>
#include "Point2D.h"
#include <cmath>

void Point2D::Setter(int x, int y)
{
	mX = x;
	mY = y;
}

void Point2D::Print()
{
	std::cout << "(" << mX << "," << mY << ")" << std::endl;
}

float Point2D::Distance()
{
	int distance;
	distance = sqrt(pow(mX, 2) + pow(mY, 2));
	std::cout << (float)distance << std::endl;
	return 0;
}

#include <iostream>
#include "Point2D.h"

int main()
{
	Point2D p1, p2;

	p1.Setter(2, 2);
	p2.Setter(4, 3);

	p1.Print();
	p1.Distance();

	p2.Print();
	p2.Distance();
}
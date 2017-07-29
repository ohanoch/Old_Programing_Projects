#include "snake.h"

link::link()
{
	xLink=DIMX/2;
	yLink=DIMY/2;
}

link::link (int x, int y)
{
	xLink=x;
	yLink=y;
}

void link::move (int x, int y)
{
	xLink=x;
	yLink=y;
}

int link::getX()
{
	return xLink;
}

int link::getY()
{
	return yLink;
}

bool link::operator==(link& l)
{
	if (xLink==l.getX() && yLink==l.getY())
	{
		return true;
	}

	return false;
}

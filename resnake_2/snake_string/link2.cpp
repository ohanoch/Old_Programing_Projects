#include "snake3.h"

//extern int ROWS;
//extern int COLS;

link::link()
{
	xLink=ROWS/2;
	yLink=COLS/2;
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

void link::operator^(link& l)
{
        this->move(l.getX(), l.getY());
}

#include "ATM_MouseEvent.h"

void ATM_MouseEvent::setMouseDownPos(int x, int y)
{
	x0 = x;
	y0 = y;
	p0 = zerosMinMap;
}

void ATM_MouseEvent::setMouseUpPos(int x, int y)
{
	dx = x - x0;
	dy = y - y0;
	zerosMinMap = p0 - Point(dx*scale, dy*scale);
}

void ATM_MouseEvent::setMouseMovePos(int x, int y)
{
	dx = x - x0;
	dy = y - y0;
	zerosMinMap = p0 - Point(dx*scale, dy*scale);
}

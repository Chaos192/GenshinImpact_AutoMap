#include "ATM_MouseEvent.h"

void ATM_MouseEvent::setMouseLeftDownPos(int x, int y)
{
	X = x;
	Y = y;
	x0 = x;
	y0 = y;
	p0 = zerosMinMap;
}

void ATM_MouseEvent::setMouseLeftUpPos(int x, int y)
{
	X = x;
	Y = y;
	dx = x - x0;
	dy = y - y0;
	zerosMinMap = p0 - Point(dx*scale, dy*scale);
}

void ATM_MouseEvent::setMouseLeftMovePos(int x, int y)
{
	X = x;
	Y = y;
	dx = x - x0;
	dy = y - y0;
	zerosMinMap = p0 - Point(dx*scale, dy*scale);
}

void ATM_MouseEvent::setMouseMidDownPos(int x, int y)
{
	X = x;
	Y = y;
	x1 = x;
	y1 = y;
	p1 = offGiMinMap;
}

void ATM_MouseEvent::setMouseMidUpPos(int x, int y)
{
	X = x;
	Y = y;
	dx = x - x1;
	dy = y - y1;
	offGiMinMap = p1 + Point(dx, dy);
	std::cout << offGiMinMap.x <<" "<< offGiMinMap.y << std::endl;
}

void ATM_MouseEvent::setMouseMidMovePos(int x, int y)
{
	X = x;
	Y = y;
	dx = x - x1;
	dy = y - y1;
	offGiMinMap = p1 + Point(dx, dy);
}

void ATM_MouseEvent::normalizationZerosMinMap(Rect rangeRect)
{
	if (zerosMinMap.x < rangeRect.x)
	{
		zerosMinMap.x = rangeRect.x;
		x0 = X;
	}
	if (zerosMinMap.y < rangeRect.y)
	{
		zerosMinMap.y = rangeRect.y;
		y0 = Y;
	}
	if (zerosMinMap.x > rangeRect.width)
	{
		zerosMinMap.x = rangeRect.width;
		x0 = X;

	}
	if (zerosMinMap.y > rangeRect.height)
	{
		zerosMinMap.y = rangeRect.height;
		y0 = Y;
	}
}

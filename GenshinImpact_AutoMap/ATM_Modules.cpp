#include "ATM_Modules.h"

double ATM_Modules::dis(double x1, double x2)
{
	return sqrt(x1*x1+x2*x2);
}

double ATM_Modules::dis(Point p)
{
	return dis(p.x,p.y);
}

double ATM_Modules::dis(Point p1, Point p2)
{
	return dis(p1.x-p2.x,p1.y-p2.y);
}

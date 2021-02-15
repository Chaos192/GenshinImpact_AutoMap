#pragma once
#include <opencv2/opencv.hpp>
using namespace cv;
class ATM_MouseEvent
{
	int x0 = 0;
	int y0 = 0;
	int x1 = 0;
	int y1 = 0;
	int dx = 0;
	int dy = 0;
public:

	Point p0 = Point(0, 0);
	Point p1 = Point(0, 0);
	double value = 0.0;
	double scale = 1.0;

	//×ó¼üµ¥»÷±êÖ¾
	bool bLCD = false;
	bool bLCU = false;
	Point zerosMinMap;
	void setMouseDownPos(int x, int y);
	void setMouseUpPos(int x, int y);
	void setMouseMovePos(int x, int y);
};


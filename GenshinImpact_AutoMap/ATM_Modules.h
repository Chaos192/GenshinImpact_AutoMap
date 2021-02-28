#pragma once
#include <opencv2/opencv.hpp>
using namespace cv;
namespace ATM_Modules
{
	double dis(double x1,double x2);
	double dis(Point p);
	double dis(Point p1, Point p2);

	bool isContains(Rect & r, Point & p);
};

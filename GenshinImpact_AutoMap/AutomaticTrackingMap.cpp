#include "AutomaticTrackingMap.h"

AutomaticTrackingMap::AutomaticTrackingMap()
{
	using namespace cv;
	Mat mat = imread(".//resource/GIMAP.png");
	namedWindow("test", 256);
	imshow("test", mat);
}

AutomaticTrackingMap::~AutomaticTrackingMap()
{
}

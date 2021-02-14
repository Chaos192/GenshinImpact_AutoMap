#include "AutomaticTrackingMap.h"

AutomaticTrackingMap::AutomaticTrackingMap()
{
	using namespace cv;

	RES.GIMAP(Rect(1500, 1500, 250, 200)).copyTo(MainMat);



	std::vector<Mat> mv0;
	std::vector<Mat> mv1;

	//Õ®µ¿∑÷¿Î
	split(MainMat, mv0);
	split(RES.MAINMASK, mv1);
	mv0.push_back(mv1[0]);
	merge(mv0, MainMat);
	//namedWindow("test", 256);
	//imshow("test", MainMat);
}

AutomaticTrackingMap::~AutomaticTrackingMap()
{
}

void AutomaticTrackingMap::Mat2QImage()
{
	//cv::cvtColor(MainMat, MainMatTmp, cv::COLOR_BGRA2RGBA);
	MainMatTmp = MainMat;
	MainImg = QImage((uchar*)(MainMatTmp.data), MainMatTmp.cols, MainMatTmp.rows, MainMatTmp.cols*(MainMatTmp.channels()), QImage::Format_RGB32);
}

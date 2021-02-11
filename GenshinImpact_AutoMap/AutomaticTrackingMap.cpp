#include "AutomaticTrackingMap.h"

AutomaticTrackingMap::AutomaticTrackingMap()
{
	using namespace cv;
	Mat mat = imread(".//resource/GIMAP.bmp", IMREAD_UNCHANGED);

	mat(Rect(1500, 1500, 250, 200)).copyTo(MainMat);
	namedWindow("test", 256);
	imshow("test", MainMat);
}

AutomaticTrackingMap::~AutomaticTrackingMap()
{
}

void AutomaticTrackingMap::Mat2QImage()
{
	cv::cvtColor(MainMat, MainMatTmp, cv::COLOR_BGR2RGB);//only RGB of Qt
	MainImg = QImage((uchar*)(MainMatTmp.data), MainMatTmp.cols, MainMatTmp.rows, MainMatTmp.cols*(MainMatTmp.channels()),QImage::Format_RGB888);
}

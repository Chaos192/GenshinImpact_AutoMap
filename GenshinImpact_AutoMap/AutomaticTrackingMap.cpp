#include "AutomaticTrackingMap.h"

AutomaticTrackingMap::AutomaticTrackingMap()
{
	using namespace cv;

	RES.GIMAP(Rect(1500, 1500, 250, 200)).copyTo(MainMat);



	std::vector<Mat> mv0;
	std::vector<Mat> mv1;

	//通道分离
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
	MainImg = QImage((uchar*)(MainMatTmp.data), MainMatTmp.cols, MainMatTmp.rows, MainMatTmp.cols*(MainMatTmp.channels()), QImage::Format_ARGB32);
}

void AutomaticTrackingMap::getGiHandle()
{
	giHandle = FindWindowA(NULL, "原神");
	if (giHandle != NULL)
	{
		GetWindowRect(giHandle, &giRect);
	}
}

void AutomaticTrackingMap::getThisHandle()
{
	;//giHandle = FindWindowA(NULL, "原神");
}

void AutomaticTrackingMap::getThisHandle(HWND _thisHandle)
{
	thisHandle = _thisHandle;
}

void AutomaticTrackingMap::setWindowsPos()
{
	SetWindowPos(thisHandle, HWND_TOPMOST, giRect.left + offGiMinMap.x, giRect.top + offGiMinMap.y, 0, 0, SWP_NOSIZE);
}

void AutomaticTrackingMap::setWindowsPos(HWND _thisHandle)
{
	SetWindowPos(_thisHandle, HWND_TOPMOST, giRect.left + offGiMinMap.x, giRect.top + offGiMinMap.y, 0, 0, SWP_NOSIZE);
}

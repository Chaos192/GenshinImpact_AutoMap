#pragma once
#include <QtWidgets/QMainWindow>
#include <opencv2/opencv.hpp>


class AutomaticTrackingMap
{
	cv::Mat MainMat;
	cv::Mat MainMatTmp;
public:
	AutomaticTrackingMap();
	~AutomaticTrackingMap();
public:
	QImage MainImg;

	void Mat2QImage();
};

typedef AutomaticTrackingMap ATmap;


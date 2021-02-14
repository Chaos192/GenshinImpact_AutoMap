#pragma once
#include <QtWidgets/QMainWindow>
#include <opencv2/opencv.hpp>
#include <vector>
#include "ATM_Resource.h"

class AutomaticTrackingMap
{
	//º”‘ÿ◊ ‘¥
	ATM_Resource RES;

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


#pragma once
#include <QtWidgets/QMainWindow>
#include <opencv2/opencv.hpp>


class AutomaticTrackingMap
{
public:
	AutomaticTrackingMap();
	~AutomaticTrackingMap();
public:
	QImage MainImg;
};

typedef AutomaticTrackingMap ATmap;


#pragma once
#include <QtWidgets/QMainWindow>
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include <vector>
#include "ATM_Resource.h"

class AutomaticTrackingMap
{
	//加载资源
	ATM_Resource RES;

	cv::Mat MainMat;
	cv::Mat MainMatTmp;
public:
	AutomaticTrackingMap();
	~AutomaticTrackingMap();
public:
	//原神游戏窗口句柄
	HWND giHandle;
	//自动悬浮窗句柄
	HWND thisHandle;
	//原神窗口区域
	RECT giRect;
	//原神窗口区域保存对比用
	RECT giRectTmp;

	Point offGiMinMap = Point(288, 82);

	QImage MainImg;

	void Mat2QImage();

public:
	void getGiHandle();
	void getThisHandle();
	void getThisHandle(HWND _thisHandle);

	void setWindowsPos();
	void setWindowsPos(HWND _thisHandle);
};

typedef AutomaticTrackingMap ATmap;


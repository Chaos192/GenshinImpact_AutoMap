#pragma once
#include <QtWidgets/QMainWindow>
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include <vector>
#include "ATM_Resource.h"
#include "ATM_MouseEvent.h"
#include "ATM_GiState.h"


class AutomaticTrackingMap
{
	//加载资源
	ATM_Resource RES;
	ATM_GiState GIS;

	cv::Mat MainMat;
	cv::Mat MainMatTmp;
public:
	AutomaticTrackingMap();
	~AutomaticTrackingMap();
public:

	ATM_MouseEvent MET;

	//自动悬浮窗句柄
	HWND thisHandle;



	//悬浮窗大小
	Size autoMapSize = Size(250, 200);
	//完整地图大小
	Size mapSize = Size(RES.GIMAP.cols, RES.GIMAP.rows);
	//完整地图世界中心，相对原点
	Point mapWorldCenter = Point(1416, 3306);

	//悬浮窗中心所对大地图位置
	Point zerosMinMap = Point(1466, 3272);
	//悬浮窗相对原神窗口位置
	Point offGiMinMap = Point(250, 100);
	//
	Rect minMapRect;

	//原神是否正在运行标志



	//Qt
	QImage MainImg;

	void Init(HWND mapWindowsHandle);
	void Exit();

	void FrontEndUpdata();
	void BackEndUpdata();

	void Mat2QImage();

public:
	Mat getViewMap();

	void getGiState();
	void setThisState();


	void getGiHandle();
	void getThisHandle();
	void getThisHandle(HWND _thisHandle);

	void setWindowsPos();
	void setWindowsPos(HWND _thisHandle);

	void setMouseDownPos(int x,int y);
	void setMouseUpPos(int x, int y);
	void setMouseMovePos(int x, int y);
};

typedef AutomaticTrackingMap ATmap;


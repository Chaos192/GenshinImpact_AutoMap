#pragma once
#include <iostream>
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
using namespace std;
using namespace cv;

enum RectMode
{
	FW_UNDIFINDE = -1,
	FW_MINIMIZE = 0,
	F_1920x1080 = 1,
	W_1920x1080 = 2,
	F_1680x1050 = 3,
	W_1680x1050 = 4,
	F_1600x900 = 5,
	W_1600x900 = 6,
	F_1440x900 = 7,
	W_1440x900 = 8,
	F_1400x1050 = 9,
	W_1400x1050 = 10,
	F_1366x768 = 11,
	W_1366x768 = 12,

};

class ATM_GiState
{
public:
	//原神游戏窗口句柄
	HWND giHandle;
	//原神窗口区域
	RECT giRect;
	//原神窗口区域保存对比用
	RECT giRectTmp;
	RECT giClientRect;

	//原神游戏窗口截图
	Mat giFrame;
	//原神游戏窗口截图有效区域
	//Mat giFrameROI;
	//
	Mat giFrameRect;
	//
	Mat giFramePaimon;
	//
	Mat giFrameMap;

	Mat giFrameUID;

	string giWndClass = "UnityWndClass";
	string giName = "原神";

	//原神是否运行中
	bool isRunning = false;
	//派蒙是否可见即是否处于主画面
	bool isPaimonVisible = false;
	//原神是否全屏
	bool isFullScreen = false;
	//窗口分辨率模式
	int giRectMode = RectMode::FW_MINIMIZE;

	int resIdPaimon = 0;
	//窗口大小
	Size giSize;

	bool isRun();
	void getHandle();
	void getRect();
	int getGiRectMode();
	int getGiState();
	Point getOffset();

	void getAllScreen();

	void getGiScreen();
	void getGiFrame();
	void getGiFramePaimon();
	void getGiFrameMap();
	void getGiFrameUID();

	void setGiNameClass(LANGID SystemLanguageID);

	void setGiHandle(HWND GiHandle);
};


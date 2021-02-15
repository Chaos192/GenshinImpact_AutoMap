#pragma once
#include <Windows.h>
#include <opencv2/opencv.hpp>
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

	bool isRunning = false;
	bool isPaimonVisible = false;
	bool isFullScreen = false;
	int giRectMode = RectMode::FW_MINIMIZE;
	cv::Size giSize;

	bool giIsRunningFlag = false;

	//原神是否派蒙可见，即在主画面
	bool giIsPaimonVisibleFlag = false;

	bool isRun();
	void getHandle();
	void getRect();
	int getGiRectMode();
	int getGiState();
	cv::Point getOffset();
};


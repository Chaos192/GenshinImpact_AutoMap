#pragma once
#include <Windows.h>
namespace ATM
{
#define FW_UNDIFINDE -1
#define FW_MINIMIZE 0
#define F_1920x1080 1
#define W_1920x1080 2
#define F_1680x1050 3
#define W_1680x1050 4
#define F_1600x900 5
#define W_1600x900 6
#define F_1440x900 7
#define W_1440x900 8
#define F_1400x1050 9
#define W_1400x1050 10
#define F_1366x768 11
#define W_1366x768 12
}


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

	int giRectMode = FW_MINIMIZE;

	bool giIsRunningFlag = false;

	//原神是否派蒙可见，即在主画面
	bool giIsPaimonVisibleFlag = false;

	bool isRun();
	void getHandle();
	int getGiRectMode();

};


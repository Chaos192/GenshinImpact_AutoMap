#pragma once
#include <QtWidgets/QMainWindow>
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include <vector>
#include "ATM_Resource.h"
#include "ATM_MouseEvent.h"
#include "ATM_GiState.h"
#include "ATM_ThreadMatch.h"
#include "ATM_ObjectLists.h"
#include "ATM_SendSocket.h"
#include "ATM_ActivationKYJG.h"
#include "ATM_SaveLoadFile.h"
#include "ATM_Modules.h"

enum ThisWinState
{
	Normal,
	Minimize,
	NoTop,
	Top,
	TopShow,
	Wait,
};

class AutomaticTrackingMap
{
	//加载资源
	ATM_Resource RES;
	//原神窗口信息
	ATM_GiState GIS;
	//多线程匹配
	ATM_ThreadMatch TMS;
	//加载物品标记
	ATM_ObjectLists OLS;
	//Socket通信
	ATM_SendSocket SST;
	//空荧酒馆激活
	ATM_ActivationKYJG AKY;
	//存档
	ATM_SaveLoadFile SLF;

	cv::Mat MainMat;
	cv::Mat MainMatTmp;

	int thisStateMode = 0;
	int thisStateModeNext = 0;
	bool isFristChangeThisState = true;

public:
	AutomaticTrackingMap();
	~AutomaticTrackingMap();
public:

	//鼠标位置
	ATM_MouseEvent MET;

	//自动悬浮窗句柄
	HWND thisHandle=NULL;
	//是否启用自动追踪
	bool isAutoMode = false;
	bool isAutoInitFinish = false;

	//窗口大小
	Size autoWindowSize = Size(300, 300);
	//悬浮窗大小
	Size autoMapSize = Size(300, 300);//Size(212, 212);
	Point autoMapCenter = Point(150, 150);//Point(106,106);
	//完整地图大小
	Size mapSize = Size(RES.GIMAP.cols, RES.GIMAP.rows);
	//完整地图世界中心，相对原点
	Point mapWorldCenter = Point(1416, 3306);

	//悬浮窗中心所对大地图位置
	Point2d zerosMinMap = Point(1466, 3272);
	//悬浮窗相对原神窗口位置
	Point offGiMinMap = Point(250, 100);
	//
	Rect minMapRect;

	//原神是否正在运行标志

	string SystemUserName="";
	string SystemUserLocalLow="";
	string SystemUserFileIndex="";
	string ApplicationCompanyName = "天理系统";
	string ApplicationName="悬浮窗自动地图";
	LANGID SystemLanguageID=0;
	string SystemLanguage = "Chinese";
	//Qt
	QImage MainImg;

	void Init(HWND mapWindowsHandle);
	void Exit();

	void FrontEndUpdata();
	void BackEndUpdata();

	void Mat2QImage();

	void CustomProcess(int i);

public:
	Mat getViewMap();

	void getGiState();
	void setThisState_Normal();
	void setThisState_Minimize();
	void setThisState_Top();
	void setThisState_TopShow();

	void getThisOffset();

	void getGiHandle();
	void getThisHandle();
	void getThisHandle(HWND _thisHandle);

	void setWindowsPos();
	void setWindowsPos(HWND _thisHandle);

	void setMoveMapDownPos(int x,int y);
	void setMoveMapUpPos(int x, int y);
	void setMoveMapMovePos(int x, int y);

	void setOffsetDownPos(int x, int y);
	void setOffsetUpPos(int x, int y);
	void setOffsetMovePos(int x, int y);

	void setScaleMapDelta(int x, int y,int delta);

	void setAutoMode();
	bool getAutoMode();

	void setObjIsShow(int klass);
	void setObjFlagIsShow();
	void setAddFlagOnPos();
	void setKongYingJiuGuanState();

	void setGenshinImpactWndHandle(HWND giHandle);

	void testSaveScreen();

	int getUID();
	void saveLocal();
	void loadLocal();

private:
	void getSystemInfo();
private:
	int getThisState();
	void getKYJGState();
	void setThisState();
	void setThreadMatchMat();

	void drawStarObjectLists();
	void drawObjectLists();
	void drawFlagLists();
	void drawAvatar();
	void CopyToThis();
	void CopyToLocal();
private:
	void addWeightedAlpha(Mat &backgroundImage, Mat& Image, Mat &maskImage);
	void addWeightedAlpha(Mat &backgroundImage, Mat& Image, Mat &maskImage,double alpha);
	void addWeightedPNG(Mat &backgroundImage, Mat& Image);
	Mat rotateAvatar(double angle);
	Mat rotateAvatar(double angle,double scale);
};

typedef AutomaticTrackingMap ATmap;


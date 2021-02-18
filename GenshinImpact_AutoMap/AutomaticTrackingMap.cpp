#include "AutomaticTrackingMap.h"

AutomaticTrackingMap::AutomaticTrackingMap()
{
}

AutomaticTrackingMap::~AutomaticTrackingMap()
{
	Exit();
}

void AutomaticTrackingMap::Init(HWND mapWindowsHandle)
{
	/*
	数据状态初始化
	*/
	MET.zerosMinMap = zerosMinMap;
	getGiHandle();
	getThisHandle(mapWindowsHandle);


	/*
	后端数据更新
	*/
	BackEndUpdata();


	
	/**/
}

void AutomaticTrackingMap::Exit()
{
}

//前端显示
void AutomaticTrackingMap::FrontEndUpdata()
{
	/*
	设置部分
	*/

	setThisState();
	setThreadMatchMat();




	/*
	显示部分
	*/

	//获取显示区域地图
	MainMat = getViewMap();
	//添加物品图标
	//添加当前位置图标

	/*
	显示输出部分
	*/

	//图片输出到Qt显示
	Mat2QImage();
}

//后端状态数据
void AutomaticTrackingMap::BackEndUpdata()
{
	/*
	数据处理部分
	*/

	if (isAutoMode)
	{
		//多线程检查输出
		TMS.CheckThread();
		TMS.GetMatchResults();
		//多线程初始化
		TMS.cThreadSurfMapInit(RES.GIMAP);
		TMS.cThreadSurfMapMatch();

		if (TMS.tIsEndSurfMapInit)
		{
			zerosMinMap = TMS.pos;
		}
	}

	/*
	获取部分
	*/

	//获取原神窗口状态
	getGiState();

	//获取本身相对原神位置
	getThisOffset();
	getThisState();

	/*
	状态转移部分
	*/

	//判断当前本身窗口状态
	thisStateMode = getThisState();


}

void AutomaticTrackingMap::Mat2QImage()
{
	std::vector<Mat> mv0;
	std::vector<Mat> mv1;

	//通道分离
	split(MainMat, mv0);
	split(RES.MAINMASK, mv1);
	mv0.push_back(mv1[0]);
	merge(mv0, MainMat);
	MainImg = QImage((uchar*)(MainMat.data), MainMat.cols, MainMat.rows, MainMat.cols*(MainMat.channels()), QImage::Format_ARGB32);
}

Mat AutomaticTrackingMap::getViewMap()
{
	static Mat minMap;

	Point minMapPoint = Point(0, 0);

	Size reMapSize = autoMapSize;
	reMapSize.width = (int)(reMapSize.width * MET.scale);
	reMapSize.height = (int)(reMapSize.height * MET.scale);

	Size R = reMapSize / 2;

	Point LT = zerosMinMap - Point(R);
	Point RB = zerosMinMap + Point(R);

	minMapPoint = LT;

	if (LT.x < 0)
	{
		minMapPoint.x = 0;
	}
	if (LT.y < 0)
	{
		minMapPoint.y = 0;
	}
	if (RB.x > mapSize.width)
	{
		minMapPoint.x = mapSize.width - reMapSize.width;
	}
	if (RB.y > mapSize.height)
	{
		minMapPoint.y = mapSize.height - reMapSize.height;
	}
	minMapRect = Rect(minMapPoint, reMapSize);

	resize(RES.GIMAP(minMapRect), minMap, autoMapSize);
	//minMap = matMap(Rect(minMapPoint, reMapSize));

	return minMap;

}

void AutomaticTrackingMap::getGiState()
{
	GIS.getGiState();
	if (GIS.giRectMode > 0)
	{
		GIS.getGiFrame();
	}
}

void AutomaticTrackingMap::setThisState_Normal()
{
	//设置窗口位置
	//setWindowsPos();
	SetWindowPos(thisHandle, HWND_TOP, GIS.giRect.left + offGiMinMap.x, GIS.giRect.top + offGiMinMap.y, 0, 0, SWP_NOSIZE);
}

void AutomaticTrackingMap::setThisState_Minimize()
{
	//最小化显示窗口
	ShowWindow(thisHandle, SW_MINIMIZE);
	//设置原神窗口为前台
	SetForegroundWindow(GIS.giHandle);/* 对原神窗口的操作 */

}

void AutomaticTrackingMap::setThisState_Top()
{
	//设置窗口位置
	setWindowsPos();
	//还原显示窗口
	ShowWindow(thisHandle, SW_SHOW);
}

void AutomaticTrackingMap::setThisState_TopShow()
{
	//设置窗口位置
	setWindowsPos();
	//还原显示窗口
	ShowWindow(thisHandle, SW_SHOW);
	//设置原神窗口为前台
	SetForegroundWindow(GIS.giHandle);/* 对原神窗口的操作 */
}

void AutomaticTrackingMap::getThisOffset()
{
	static Point offGiMinMapTmp;
	if (GIS.giRectMode > 0)
	{
		offGiMinMapTmp = GIS.getOffset();
		if (offGiMinMap != offGiMinMapTmp)
		{
			offGiMinMap = offGiMinMapTmp;
		}
	}
}

void AutomaticTrackingMap::getGiHandle()
{
	GIS.getHandle();
}

void AutomaticTrackingMap::getThisHandle()
{
	thisHandle = FindWindowA(NULL, "GenshinImpact_AutoMap");
}

void AutomaticTrackingMap::getThisHandle(HWND _thisHandle)
{
	thisHandle = _thisHandle;
}

void AutomaticTrackingMap::setWindowsPos()
{
	SetWindowPos(thisHandle, HWND_TOPMOST, GIS.giRect.left + offGiMinMap.x, GIS.giRect.top + offGiMinMap.y, 0, 0, SWP_NOSIZE);
}

void AutomaticTrackingMap::setWindowsPos(HWND _thisHandle)
{
	SetWindowPos(_thisHandle, HWND_TOPMOST, GIS.giRect.left + offGiMinMap.x, GIS.giRect.top + offGiMinMap.y, 0, 0, SWP_NOSIZE);
}

void AutomaticTrackingMap::setMouseDownPos(int x, int y)
{
	MET.setMouseDownPos(x, y);
}

void AutomaticTrackingMap::setMouseUpPos(int x, int y)
{
	MET.setMouseUpPos(x, y);
	MET.normalizationZerosMinMap(Rect(0, 0, mapSize.width, mapSize.width));
	zerosMinMap = MET.zerosMinMap;
}

void AutomaticTrackingMap::setMouseMovePos(int x, int y)
{
	MET.setMouseMovePos(x, y);
	MET.normalizationZerosMinMap(Rect(0,0,mapSize.width,mapSize.width));
	zerosMinMap = MET.zerosMinMap;
	
}

void AutomaticTrackingMap::setAutoMode()
{
	isAutoMode = !isAutoMode;
}

bool AutomaticTrackingMap::getAutoMode()
{
	return isAutoMode;
}

int AutomaticTrackingMap::getThisState()
{
	//备份状态，以便检查是否跳过窗口状态设置，防止持续激活原神窗口，鼠标焦点无法转移。
	thisStateModeNext = thisStateMode;
	//根据原神状态判断下一帧时悬浮窗状态
	if (GIS.isRunning)
	{
		if (isAutoMode)
		{
			if (GIS.isPaimonVisible)
			{
				thisStateModeNext = ThisWinState::TopShow;
			}
			else
			{
				thisStateModeNext = ThisWinState::Minimize;
			}
		}
		else
		{
			thisStateModeNext = ThisWinState::Top;
		}
	}
	else
	{
		thisStateModeNext = ThisWinState::Normal;
	}
	//如果状态与上一帧不同，就设置状态，否则跳过
	if (isFristChangeThisState||thisStateModeNext != thisStateMode)
	{
		thisStateMode = thisStateModeNext;
		isFristChangeThisState = true;
	}
	else
	{
		thisStateModeNext = ThisWinState::Wait;
	}

	return thisStateMode;
}

void AutomaticTrackingMap::setThisState()
{
	//if (thisStateModeNext == ThisWinState::Wait)return;
	if (isFristChangeThisState != true)
	{
		return;
	}
	else
	{
		isFristChangeThisState = false;
	}
	switch (thisStateMode)
	{
		case ThisWinState::Normal:
		{
			setThisState_Normal();
			break;
		}
		case ThisWinState::Minimize:
		{
			setThisState_Minimize();
			break;
		}
		case ThisWinState::Top:
		{
			//设置本身置顶当前窗口状态
			setThisState_Top();
			break;
		}
		case ThisWinState::TopShow:
		{
			//设置本身置顶当前窗口状态
			setThisState_TopShow();
			break;
		}
		default:
		{
			setThisState_Normal();
			break;
		}
	}
}

void AutomaticTrackingMap::setThreadMatchMat()
{
	if (GIS.isRunning)
	{
		Mat matRGB2GRAY;
		cvtColor(GIS.giFrameMap, matRGB2GRAY, CV_RGB2GRAY);
		TMS.getObjMinMap(matRGB2GRAY);
		cvtColor(GIS.giFramePaimon, matRGB2GRAY, CV_RGB2GRAY);
		TMS.getObjPaimon(matRGB2GRAY);
		cvtColor(GIS.giFrameUID, matRGB2GRAY, CV_RGB2GRAY);
		TMS.getObjUID(matRGB2GRAY);
	}
	else
	{
		TMS.isExistObjMinMap = false;
		TMS.isExistObjPaimon = false;
		TMS.isExistObjUID = false;
	}
}

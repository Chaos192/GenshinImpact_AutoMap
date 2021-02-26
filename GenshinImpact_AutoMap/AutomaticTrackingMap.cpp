#include "AutomaticTrackingMap.h"

AutomaticTrackingMap::AutomaticTrackingMap()
{
	getSystemInfo();
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
	MET.offGiMinMap = offGiMinMap;
	SST.setPort(23333);//6666


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
	//MainMat(Rect(0, 0, 212, 212)) = getViewMap();
	//getViewMap().copyTo(MainMat(Rect(0,0,212,212))) ;
	//添加物品图标
	drawObjectLists();

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
		TMS.cThreadTemplatePaimonMatch(RES.GIPAIMON[GIS.resIdPaimon]);
		TMS.cThreadOrbAvatarInit(RES.GIAVATAR);
		TMS.cThreadOrbAvatarMatch();
		TMS.cThreadTemplateUIDInit(RES.GINUMUID);
		TMS.cThreadTemplateUIDMatch();

		if (TMS.tIsEndSurfMapInit)
		{
			isAutoInitFinish = true;
			zerosMinMap = TMS.pos;
			MET.zerosMinMap = zerosMinMap;
			GIS.isPaimonVisible = TMS.isPaimonVisial;

			if (TMS.isPaimonVisial&&TMS.isContinuity)
			{
				SST.AutoMapUdpSocketSend(zerosMinMap.x, zerosMinMap.y, TMS.rotationAngle,TMS.uid);
			}
		}
	}

	/*
	获取部分
	*/

	//获取原神窗口状态
	getGiState();
	getKYJGState();
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
	//MainMat = Scalar(0, 0, 0);

	//通道分离
	split(MainMat, mv0);
	split(RES.MAINMASK, mv1);
	mv0.push_back(mv1[0]);
	//mv0[3] = mv1[0];
	merge(mv0, MainMat);
	MainImg = QImage((uchar*)(MainMat.data), MainMat.cols, MainMat.rows, MainMat.cols*(MainMat.channels()), QImage::Format_ARGB32);
}

void AutomaticTrackingMap::CustomProcess(int i)
{
	GIS.getGiFrame();
	string name("OutputPNG_id_");
	name.append(to_string(i));
	name.append("_GiFrame.png");
	if (GIS.isRunning)
	{
		;
	}
}

Mat AutomaticTrackingMap::getViewMap()
{
	static Mat minMap;

	Point minMapPoint = Point(0, 0);

	Size reMapSize = autoMapSize;
	Point2d reAutoMapCenter = autoMapCenter;
	reMapSize.width = (reMapSize.width * MET.scale);
	reMapSize.height = (reMapSize.height * MET.scale);
	reAutoMapCenter = autoMapCenter * MET.scale;

	Point2d LT = zerosMinMap - reAutoMapCenter;
	Point2d RB = zerosMinMap +Point2d(reMapSize)- reAutoMapCenter;

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
	//cvtColor(minMap, minMap, CV_RGB2RGBA);
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
	//ShowWindow(thisHandle, SW_SHOW);
	ShowWindow(thisHandle, SW_RESTORE);
}

void AutomaticTrackingMap::setThisState_TopShow()
{
	//设置窗口位置
	setWindowsPos();
	//还原显示窗口
	//ShowWindow(thisHandle, SW_SHOW);
	ShowWindow(thisHandle, SW_RESTORE);
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

void AutomaticTrackingMap::setMoveMapDownPos(int x, int y)
{
	MET.setMouseLeftDownPos(x, y);
}

void AutomaticTrackingMap::setMoveMapUpPos(int x, int y)
{
	MET.setMouseLeftUpPos(x, y);
	MET.normalizationZerosMinMap(Rect(0, 0, mapSize.width, mapSize.width));
	zerosMinMap = MET.zerosMinMap;
}

void AutomaticTrackingMap::setMoveMapMovePos(int x, int y)
{
	MET.setMouseLeftMovePos(x, y);
	MET.normalizationZerosMinMap(Rect(0,0,mapSize.width,mapSize.width));
	zerosMinMap = MET.zerosMinMap;
	
}

void AutomaticTrackingMap::setOffsetDownPos(int x, int y)
{
	//MET.offGiMinMap = offGiMinMap;
	MET.setMouseMidDownPos(x, y);

}

void AutomaticTrackingMap::setOffsetUpPos(int x, int y)
{
	MET.setMouseMidUpPos(x, y);
	offGiMinMap = MET.offGiMinMap;
}

void AutomaticTrackingMap::setOffsetMovePos(int x, int y)
{
	MET.setMouseMidMovePos(x, y);
	offGiMinMap = MET.offGiMinMap;
}

void AutomaticTrackingMap::setScaleMapDelta(int x, int y,int delta)
{
	double dx = (x - autoMapCenter.x)*MET.scale;
	double dy = (y - autoMapCenter.y)*MET.scale;

	if (delta > 0) 
	{
		if (MET.scale > 0.5)
		{
			MET.scale /= 1.2;
			MET.zerosMinMap.x += dx * 0.2;//1.2-1
			MET.zerosMinMap.y += dy * 0.2;//1.2-1
			zerosMinMap = MET.zerosMinMap;
		}
	}
	else 
	{
		if (MET.scale < 6)
		{
			MET.scale *= 1.2;
			MET.zerosMinMap.x -= dx * 0.2;//1.2-1
			MET.zerosMinMap.y -= dy * 0.2;//1.2-1
			zerosMinMap = MET.zerosMinMap;
		}
	}
}

void AutomaticTrackingMap::setAutoMode()
{
	isAutoMode = !isAutoMode;
}

bool AutomaticTrackingMap::getAutoMode()
{
	return isAutoMode;
}

void AutomaticTrackingMap::setObjIsShow(int klass)
{
	OLS.setShow(klass);
}

void AutomaticTrackingMap::setObjFlagIsShow()
{
	OLS.setShowFlag();
}

void AutomaticTrackingMap::setAddFlagOnPos()
{
	OLS.appendFlag(zerosMinMap.x, zerosMinMap.y);
}

void AutomaticTrackingMap::setKongYingJiuGuanState()
{
	if (AKY.isRunKYJG)
	{
		AKY.setState(GIS.giHandle);
	}
}

void AutomaticTrackingMap::setGenshinImpactWndHandle(HWND giHandle)
{
	GIS.setGiHandle(giHandle);
}

void AutomaticTrackingMap::getSystemInfo()
{
	char strBuffer[256] = { 0 };
	DWORD dwSize = 256;
	GetUserNameA(strBuffer, &dwSize);
	SystemUserName = strBuffer;
	SystemUserLocalLow.append("C:\\User\\");
	SystemUserLocalLow.append(SystemUserName);
	SystemUserLocalLow.append("\\AppData\\LocalLow\\");
	SystemUserCompanyIndex = SystemUserLocalLow;
	SystemUserCompanyIndex.append(ApplicationCompanyName);
	SystemUserCompanyIndex.append("\\");

	SystemLanguageID = GetSystemDefaultLangID();
	GIS.setGiNameClass(SystemLanguageID);
	switch (SystemLanguageID)
	{
		case 0X0804:
		{
			SystemLanguage = "Chinese";
			break;
		}
		case 0x0409:
		{
			SystemLanguage = "English";
			break;
		}
		default:
		{
			SystemLanguage = "English";
			break;
		}
	}
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
			if (TMS.tIsEndSurfMapInit == true)
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
				thisStateModeNext = ThisWinState::TopShow;
			}

			if (AKY.isActivationMap)
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

void AutomaticTrackingMap::getKYJGState()
{
	AKY.getKYJGHandle();
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
	if (GIS.isRunning&&GIS.giRectMode > 0)
	{
		Mat matRGB2GRAY;
		cvtColor(GIS.giFrameMap, matRGB2GRAY, CV_RGB2GRAY);
		TMS.getObjMinMap(matRGB2GRAY);
		cvtColor(GIS.giFramePaimon, matRGB2GRAY, CV_RGB2GRAY);
		TMS.getObjPaimon(matRGB2GRAY);
		//cvtColor(GIS.giFrameUID, matRGB2GRAY, CV_RGB2GRAY);
		TMS.getObjUID(GIS.giFrameUID);
	}
	else
	{
		TMS.isExistObjMinMap = false;
		TMS.isExistObjPaimon = false;
		TMS.isExistObjUID = false;
	}
}

void AutomaticTrackingMap::drawObjectLists()
{
	int x = 0, y = 0;
	Point p;
	Mat ObjIconROIMat;
	const int dx = 16, dy = 16;//图标顶点到图标中心的偏移
	for (int objKlass = 0; objKlass < OLS.objectListsNumber(); objKlass++)
	{
		if (OLS.isShow(objKlass))
		{
			for (int objOrder = 0; objOrder < OLS.objectsNumber(objKlass); objOrder++)
			{
				p= OLS.p(objKlass, objOrder);
				if (isContains(minMapRect, p))
				{
					x = (int)((p.x - minMapRect.x) / MET.scale) - dx;
					y = (int)((p.y - minMapRect.y) / MET.scale) - dy;
					//该x，y周围要有足够的空间来填充图标
					if (x > 0 && y > 0 && x + RES.GIOBJICON[objKlass].cols < autoMapSize.width&&y + RES.GIOBJICON[objKlass].rows < autoMapSize.height)
					{
						ObjIconROIMat = MainMat(Rect(x, y, RES.GIOBJICON[objKlass].cols, RES.GIOBJICON[objKlass].rows));
						//RES.GIOBJICON[objKlass].copyTo(ObjIconROIMat, RES.GIOBJICONMASK[objKlass]);
						addWeightedAlpha(ObjIconROIMat, RES.GIOBJICON[objKlass], RES.GIOBJICONMASK[objKlass]);
					}
				}
			}
		}
	}
	if (OLS.isShowFlag())
	{
		for (int objOrder = 0; objOrder < OLS.flagNumber(); objOrder++)
		{
			p = OLS.fp(objOrder);
			if (isContains(minMapRect, p))
			{
				x = (int)((p.x - minMapRect.x) / MET.scale) - dx;
				y = (int)((p.y - minMapRect.y) / MET.scale) - dy;
				//该x，y周围要有足够的空间来填充图标
				if (x > 0 && y > 0 && x + RES.GIOBJFLAGICON[0].cols < autoMapSize.width&&y + RES.GIOBJFLAGICON[0].rows < autoMapSize.height)
				{
					ObjIconROIMat = MainMat(Rect(x, y, RES.GIOBJFLAGICON[0].cols, RES.GIOBJFLAGICON[0].rows));
					//RES.GIOBJICON[objKlass].copyTo(ObjIconROIMat, RES.GIOBJICONMASK[objKlass]);
					addWeightedAlpha(ObjIconROIMat, RES.GIOBJFLAGICON[0], RES.GIOBJFLAGICONMASK[0]);
				}
			}
		}
	}

}

bool AutomaticTrackingMap::isContains(Rect & r, Point & p)
{
	if (p.x<r.x || p.x>(r.x + r.width) || p.y<r.y || p.y>(r.y + r.height))
	{
		return false;
	}
	else
	{
		return true;
	}
	return false;
}

void AutomaticTrackingMap::addWeightedAlpha(Mat & backgroundImage, Mat & Image, Mat &maskImage)
{
	std::vector<cv::Mat>scr_channels;
	std::vector<cv::Mat>dstt_channels;
	std::vector<cv::Mat>alpha_channels;
	split(Image, scr_channels);
	split(backgroundImage, dstt_channels);
	split(maskImage, alpha_channels);

	Mat Alpha = alpha_channels[0];

	for (int i = 0; i < 3; i++)
	{
		dstt_channels[i] = dstt_channels[i].mul(Alpha / 255.0);
		dstt_channels[i] += scr_channels[i].mul(1.0 - Alpha / 255.0);
	}
	merge(dstt_channels, backgroundImage);
}

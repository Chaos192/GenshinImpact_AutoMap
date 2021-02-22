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
	MET.offGiMinMap = offGiMinMap;
	SST.setPort(6666);

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
		if (TMS.tIsEndSurfMapInit)
		{
			zerosMinMap = TMS.pos;
			MET.zerosMinMap = zerosMinMap;
			GIS.isPaimonVisible = TMS.isPaimonVisial;

			if (TMS.isPaimonVisial&&TMS.isContinuity)
			{
				SST.AutoMapUdpSocketSend(zerosMinMap.x, zerosMinMap.y, 0.0);
			}
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

void AutomaticTrackingMap::CustomProcess(int i)
{
	//GIS.getGiFrame();
	//string name("OutputPNG_id_");
	//name.append(to_string(i));
	//name.append("_GiFrame.png");
	//if (GIS.isRunning)
	//{
	//	//imwrite(name, GIS.giFrame);
	//}

	Mat k;
	MainMat(Rect(100,100,32,32)).copyTo(k);
	addWeightedAlpha(k, RES.GIOBJICON[0],RES.GIOBJICONMASK[0]);
	imshow("asd", k);
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
	if (GIS.isRunning&&GIS.giRectMode > 0)
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

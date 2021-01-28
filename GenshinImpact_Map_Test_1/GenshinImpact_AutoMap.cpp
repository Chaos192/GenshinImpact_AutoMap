#include "GenshinImpact_AutoMap.h"

giam::GenshinImpact_AutoMap::GenshinImpact_AutoMap()
{
	//init();

	cvtColor(matMap, matMatchMap, CV_RGB2GRAY);
	giMatch = giAMM(matMatchMap);
	giConfig.load();
}

giam::GenshinImpact_AutoMap::~GenshinImpact_AutoMap()
{
	if (tMatchInit != nullptr)tMatchInit->join();
	if (tMatchMap != nullptr)tMatchMap->join();
	if (tMatchStar != nullptr)tMatchStar->join();
	if (tMatchTarget != nullptr)tMatchTarget->join();
}

//初始化
bool giam::GenshinImpact_AutoMap::init()
{
	
	isInit = false;
	isRun = true;
	

	//初始化背景
	autoMapMat = Mat(autoMapSize, CV_8UC4, Scalar(200, 200, 200, 255));
	//创建窗口
	namedWindow(autoMapWindowsName);
	//设置回调
	setMouseCallback(autoMapWindowsName, on_MouseHandle, (void*)this);
	//获取悬浮窗句柄
	thisHandle = FindWindowA(NULL, autoMapWindowsName.c_str());
	//初始化绘图
	imshow(autoMapWindowsName, autoMapMat);
	//获取原神窗口状态
	giCheckWindows();
	//如果全屏，调整悬浮窗初始位置
	if (giIsFullScreenFlag)offGiMinMap = Point(288, 82);
	//设置窗口位置
	SetWindowPos(thisHandle, HWND_TOPMOST, giRect.left + offGiMinMap.x, giRect.top + offGiMinMap.y, autoMapSize.width, autoMapSize.height, SWP_NOMOVE);
	//设置窗口为无边框
	SetWindowLong(thisHandle, GWL_STYLE, GetWindowLong(thisHandle, GWL_EXSTYLE | WS_EX_TOPMOST)); //改变窗口风格
	ShowWindow(thisHandle, SW_SHOW);

	tMatchInit = new thread(&giam::GenshinImpact_AutoMap::thread_MatchInit,this,ref(giMatch),ref(tMuMatch));

	return false;
}

//运行
bool giam::GenshinImpact_AutoMap::run()
{
	//运行框架
	if (isInit) { init(); }
	//运行循环
	while (isRun)
	{
		//更新原神窗口状态
		giCheckWindows();

		//更新线程状态
		thisCheckThread();

		//如果窗口不处于最小化状态，对画面进行更新
		if (!thisIsIconic())
		{
			//前后端分离
			//前端显示
			//后端追踪

			//匹配可传送目标
			//mapTarget();
			giMatch.setObject(giFrameMap);
			giMatch.test3();

			//匹配当前所在位置
			mapMatchMap();

			//匹配标志物品
			mapStar();

			customProcess();


			//地图图标文字等更新
			mapUpdata();
		}

		//显示
		mapShow();
	}
	//退出处理
	exit();
	return false;
}

//退出
bool giam::GenshinImpact_AutoMap::exit()
{
	giConfig.save();
	return false;
}

//从大地图中截取显示区域
Mat giam::GenshinImpact_AutoMap::getMinMap()
{
	static Mat minMap;

	Point minMapPoint = Point(0, 0);

	Size reMapSize = autoMapSize;
	reMapSize.width = (int)(reMapSize.width * giMEF.scale);
	reMapSize.height = (int)(reMapSize.height * giMEF.scale);

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
		minMapPoint.x = mapSize.width- reMapSize.width;
	}
	if (RB.y > mapSize.height)
	{
		minMapPoint.y = mapSize.height - reMapSize.height;
	}
	minMapRect = Rect(minMapPoint, reMapSize);

	resize(matMap(minMapRect), minMap, autoMapSize);
	//minMap = matMap(Rect(minMapPoint, reMapSize));

	return minMap;
}

//判断RECT是否相等
bool giam::GenshinImpact_AutoMap::isEqual(RECT & r1, RECT & r2)
{
	if (r1.bottom != r2.bottom || r1.left != r2.left || r1.right != r2.right || r1.top != r2.top)
	{
		return false;
	}
	else
	{
		return true;
	}
	return false;
}

//判断RECT是否包含Point
bool giam::GenshinImpact_AutoMap::isContains(RECT & r, Point & p)
{
	if (p.x<r.left || p.x>r.right||p.y<r.top||p.y>r.bottom)
	{
		return false;
	}
	else
	{
		return true;
	}

	return false;
}

//判断Rect是否包含Point
bool giam::GenshinImpact_AutoMap::isContains(Rect & r, Point & p)
{
	if (p.x<r.x || p.x>(r.x+r.width) || p.y<r.y || p.y>(r.y+r.height))
	{
		return false;
	}
	else
	{
		return true;
	}
	return false;
}

int giam::GenshinImpact_AutoMap::dis2(Point p)
{
	return dis2(p.x,p.y);
}

int giam::GenshinImpact_AutoMap::dis2(int x, int y)
{
	return x * x + y * y;
}

//原神是否运行
bool giam::GenshinImpact_AutoMap::giIsRunning()
{
	//尝试获取原神句柄
	giHandle = FindWindowA(NULL, "原神");
	if (giHandle != NULL)
	{
		giIsRunningFlag = true;
	}
	else
	{
		giIsRunningFlag = false;
	}
	return giIsRunningFlag;
}

//原神是否可见
bool giam::GenshinImpact_AutoMap::giIsDisplay()
{
	if (giIsRunningFlag)
	{
		giIsDisplayFlag = !IsIconic(giHandle);
		GetWindowRect(giHandle, &giRect);
		giSize.width = giRect.right - giRect.left;//+6
		giSize.height = giRect.bottom - giRect.top;//+29
		//+6,+29
		//cout << giRect.bottom - giRect.top << "," << giRect.right - giRect.left << endl;
	}
	else
	{
		giIsDisplayFlag = false;
	}
	return giIsDisplayFlag;
}

//原神是否最大化
//bool giam::GenshinImpact_AutoMap::giIsZoomed()
//{
//	if (giHandle != NULL && giIsDisplayFlag)
//	{
//		giIsZoomedFlag = IsZoomed(giHandle);
//		//获取原神窗口区域
//		GetWindowRect(giHandle, &giRect);
//		giSize.width = giRect.bottom - giRect.top;
//		giSize.height = giRect.right - giRect.left;
//		cout << giRect.bottom - giRect.top <<"," << giRect.right- giRect.left  << endl;
//		return;
//	}
//	giIsZoomedFlag = false;
//}

//原神是否全屏
bool giam::GenshinImpact_AutoMap::giIsFullScreen()
{
	giIsFullScreenFlag = false;
	if (giIsDisplay())
	{
		static RECT rcDesk;
		GetWindowRect(GetDesktopWindow(), &rcDesk);
		if (giRect.left <= rcDesk.left&& giRect.top <= rcDesk.top&& giRect.right >= rcDesk.right&& giRect.bottom >= rcDesk.bottom)
		{
			giIsFullScreenFlag = true;
		}
		giGetScreen();
		giScreenROI();
		giGetPaimon();
		giIsPaimonVisible();
	}
	return giIsFullScreenFlag;
}

bool giam::GenshinImpact_AutoMap::giIsPaimonVisible()
{
	static Mat tmp;
	static Mat matPaimon;
	if (giIsFullScreenFlag)
	{
		matPaimon = matPaimon1;
	}
	else
	{
		matPaimon = matPaimon2;
	}
	cv::matchTemplate(matPaimon, giFramePaimon, tmp, cv::TM_CCOEFF_NORMED);

	double minVal, maxVal;
	cv::Point minLoc, maxLoc;
	//寻找最佳匹配位置
	cv::minMaxLoc(tmp, &minVal, &maxVal, &minLoc, &maxLoc);
	//cout << minVal << "" << maxVal << endl;
	if (minVal  < 0.66)
	{
		if (giIsPaimonVisibleFlag)giFlag.isUpHUD = true;
		giIsPaimonVisibleFlag = false;

	}
	else
	{
		if (!giIsPaimonVisibleFlag)giFlag.isUpHUD = true;
		giIsPaimonVisibleFlag = true;
		giGetMap();
	}
	return giIsPaimonVisibleFlag;
}

//检查原神窗口状态
void giam::GenshinImpact_AutoMap::giCheckWindows()
{
	giIsRunning();
	giIsDisplay();
	//giIsZoomed();
	giIsFullScreen();
}

//获取原神画面
void giam::GenshinImpact_AutoMap::giGetScreen()
{
	
	static HBITMAP	hBmp;
	RECT rc;
	BITMAP bmp;

	DeleteObject(hBmp);

	if (giHandle == NULL)return;

	//获取目标句柄的窗口大小RECT
	GetWindowRect(giHandle, &rc);

	//获取目标句柄的DC
	HDC hScreen = GetDC(giHandle);
	HDC hCompDC = CreateCompatibleDC(hScreen);

	//获取目标句柄的宽度和高度
	int	nWidth = rc.right - rc.left;
	int	nHeight = rc.bottom - rc.top;

	//创建Bitmap对象
	hBmp = CreateCompatibleBitmap(hScreen, nWidth, nHeight);//得到位图

	SelectObject(hCompDC, hBmp); //不写就全黑
	BitBlt(hCompDC, 0, 0, nWidth, nHeight, hScreen, 0, 0, SRCCOPY);

	//释放对象
	DeleteDC(hScreen);
	DeleteDC(hCompDC);

	//类型转换
	GetObject(hBmp, sizeof(BITMAP), &bmp);

	int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel / 8;
	int depth = bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;

	//mat操作
	giFrame.create(cv::Size(bmp.bmWidth, bmp.bmHeight), CV_MAKETYPE(CV_8U, nChannels));
	
	GetBitmapBits(hBmp, bmp.bmHeight*bmp.bmWidth*nChannels, giFrame.data);
}

void giam::GenshinImpact_AutoMap::giScreenROI()
{
	if (giIsFullScreenFlag)
	{
		giFrameROI = giFrame(Rect(0, 0, 285, 240)); 
		//giFrame(Rect(0, 0, 285, 240)).copyTo(giFrameRect);
		cvtColor(giFrameROI, giFrameRect, CV_RGB2GRAY);
	}
	else
	{
		giFrameROI = giFrame(Rect(0, 0, 250, 210));
		//giFrame(Rect(0, 0, 250, 210)).copyTo(giFrameRect);
		cvtColor(giFrameROI, giFrameRect, CV_RGB2GRAY);
	}
}

void giam::GenshinImpact_AutoMap::giGetPaimon()
{
	//(18,8,48,55) 1366 768
	if (giIsFullScreenFlag)
	{
		giFrameRect(Rect(26, 12, 68, 77)).copyTo(giFramePaimon);
		//giFrameRect(Rect(0, 0, 94, 89)).copyTo(giFramePaimon);
	}
	else
	{
		giFrameRect(Rect(23, 11, 59, 67)).copyTo(giFramePaimon);
		//giFrameRect(Rect(0, 0, 82, 78)).copyTo(giFramePaimon);
	}
}

void giam::GenshinImpact_AutoMap::giGetMap()
{
	if (giIsFullScreenFlag)
	{
		giFrameRect(Rect(62, 19, 212, 212)).copyTo(giFrameMap);
	}
	else
	{
		giFrameRect(Rect(54, 17, 185, 185)).copyTo(giFrameMap);
	}
}

bool giam::GenshinImpact_AutoMap::thisIsIconic()
{
	thisIsIconicFlag = IsIconic(thisHandle);
	return thisIsIconicFlag;
}

bool giam::GenshinImpact_AutoMap::isNeedFindStar()
{
	Rect Roi(zerosMinMap.x - 150, zerosMinMap.y - 150, 300, 300);
	Point tmpP;
	bool res = false;
	for (int i = 0; i < min(giFlag.max, giObjTable.num); i++)
	{
		for (int j = 0; j < giObjTable.obj[i].size(); j++)
		{
			tmpP = Point(giObjTable.obj[i].at(j).x, giObjTable.obj[i].at(j).y);
			//目标点在小地图显示区域内
			if (isContains(Roi, tmpP))
			{
				res = true;
			}
		}
	}

	return res;
}

bool giam::GenshinImpact_AutoMap::isNeedFindStar(int& id, Point &p)
{
	Rect Roi(zerosMinMap.x - 150, zerosMinMap.y - 150, 300, 300);
	Point tmpP;
	bool res = false;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < giObjTable.obj[i].size(); j++)
		{
			tmpP = Point(giObjTable.obj[i].at(j).x, giObjTable.obj[i].at(j).y);
			//目标点在小地图显示区域内
			if (isContains(Roi, tmpP))
			{
				id = j;
				p = tmpP;
				res = true;
			}
		}
	}

	return res;
}

bool giam::GenshinImpact_AutoMap::isNeedFindStar(vector<int>& lisId, vector<Point> &lisP)
{
	lisId.clear();
	lisP.clear();
	Rect Roi(zerosMinMap.x - 70, zerosMinMap.y - 70, 140, 140);
	Point tmpP;
	bool res = false;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < giObjTable.obj[i].size(); j++)
		{
			tmpP = Point(giObjTable.obj[i].at(j).x, giObjTable.obj[i].at(j).y);
			//目标点在小地图显示区域内
			if (isContains(Roi, tmpP))
			{
				lisId.push_back(j);
				lisP.push_back(tmpP);
				res = true;
			}
		}
	}
	return res;
}

bool giam::GenshinImpact_AutoMap::isNeedFindStar(vector<int>& lisType,vector<int>& lisId, vector<Point> &lisP)
{
	lisType.clear();
	lisId.clear();
	lisP.clear();
	Rect Roi(zerosMinMap.x - 70, zerosMinMap.y - 70, 140, 140);
	Point tmpP;
	bool res = false;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < giObjTable.obj[i].size(); j++)
		{
			tmpP = Point(giObjTable.obj[i].at(j).x, giObjTable.obj[i].at(j).y);
			//目标点在小地图显示区域内
			if (isContains(Roi, tmpP))
			{
				lisType.push_back(i);
				lisId.push_back(j);
				lisP.push_back(tmpP);
				res = true;
			}
		}
	}
	return res;
}

//设置HUD
void giam::GenshinImpact_AutoMap::setHUD()
{
	if (giIsRunningFlag)
	{
		giHUD.runState = "Genshin Impact Is Running";
		giHUD.runTextColor = Scalar(0, 255, 0);

	}
	else
	{
		giHUD.runState = "Genshin Impact Not Run";
		giHUD.runTextColor = Scalar(0, 0, 255);
	}

	if (giIsDisplayFlag)
	{
		giHUD.displayFlagColor = Scalar(0, 255, 0);
	}
	else
	{
		giHUD.displayFlagColor = Scalar(0, 0, 255);
	}

	if (giIsPaimonVisibleFlag)
	{
		giHUD.paimonFlagColor = Scalar(0, 255, 0);
	}
	else
	{
		giHUD.paimonFlagColor = Scalar(128, 128, 128);
	}

	if (giFlag.isAutoMove)
	{
		giHUD.autoMoveFlagColor = Scalar(0, 255, 0);
	}
	else
	{
		giHUD.autoMoveFlagColor = Scalar(128, 128, 128);
	}

	if (tIsEndInit)
	{
		giHUD.isEndMatchInit = Scalar(0, 255, 0);
	}
	else
	{
		giHUD.isEndMatchInit = Scalar(128, 128, 128);
	}
}

//绘制HUD
void giam::GenshinImpact_AutoMap::addHUD(Mat img)
{
	Mat tmp;

	//绘制背景条
	Mat backRect(20, autoMapSize.width, CV_8UC4, Scalar(200, 200,200, 255));
	tmp = img(Rect(0,0, autoMapSize.width, 20));
	cv::addWeighted(tmp, 0.6, backRect, 0.4, 0, tmp);
	
	//绘制小图标
	Mat backgound;
	tmp = img(giTab.pngARect);//Rect(30, 0, giTab.pngA.cols, giTab.pngA.rows)
	tmp.copyTo(backgound);
	giTab.pngA.copyTo(tmp, giTab.pngAMask);
	if (!giFlag.isShow[0])
	{
		//小图标半隐藏
		cv::addWeighted(tmp, 0.5, backgound, 0.5, 0, tmp);
	}
	else
	{
		cv::addWeighted(tmp, 0.7, backgound, 0.2, 0, tmp);
	}

	tmp = img(giTab.pngBRect);//Rect(30, 0, giTab.pngA.cols, giTab.pngA.rows)
	tmp.copyTo(backgound);
	giTab.pngB.copyTo(tmp, giTab.pngBMask);

	if (!giFlag.isShow[1])
	{
		//小图标半隐藏
		cv::addWeighted(tmp, 0.5, backgound, 0.5, 0, tmp);
	}
	else
	{
		cv::addWeighted(tmp, 0.7, backgound, 0.2, 0, tmp);
	}

	tmp.release();
	tmp = img(Rect(autoMapSize.width - giTab.sysIcon1.cols , 0, giTab.sysIcon1.cols, giTab.sysIcon1.rows));
	tmp.copyTo(backgound);
	giTab.sysIcon1.copyTo(tmp, giTab.sysIcon1Mask);
	cv::addWeighted(tmp, 0.5, backgound, 0.5, 0, tmp);

	tmp.release();

	Mat star;
	img(Rect(autoMapSize.width / 2 - 5, autoMapSize.height / 2 - 5, 11, 11)).copyTo(star);
	tmp = img(Rect(autoMapSize.width / 2 - 5, autoMapSize.height / 2 - 5, 11, 11));
	circle(star, Point(5, 5), 4, giHUD.minStarColor, 1, LINE_AA);
	addWeighted(tmp, 0.5, star, 0.5, 0, tmp);

	//圆点显示原神状态
	cv::circle(img, Point(6, 10), 4, giHUD.paimonFlagColor, -1);
	cv::circle(img, Point(16, 10), 4, giHUD.autoMoveFlagColor, -1);
	cv::circle(img, Point(26, 10), 4, giHUD.isEndMatchInit, -1);

	//putText(img, giHUD.runState, Point(24, 12), FONT_HERSHEY_COMPLEX_SMALL, 0.4, giHUD.runTextColor, 1);

	putText(img, to_string((int)(1.0/FRL.runningTime)), Point(80, 18), FONT_HERSHEY_COMPLEX_SMALL, 1, giHUD.runTextColor, 1);

}

//设置标记是否显示
void giam::GenshinImpact_AutoMap::setFLAG()
{
	// mouse click change giFlag.isShow[] state

}

//在地图上绘制标记
void giam::GenshinImpact_AutoMap::addFLAG(Mat img)
{
	int dx = 0;
	int dy = 0;
	Point p;
	Mat r;
	int x = 0;
	int y = 0;

	//更新Flag为真
	if (giFlag.isUpdata||giFlag.isGetMap||giFlag.isAutoMove)
	{
		for (int i = 0; i < min(giFlag.max, giObjTable.num); i++)
		{
			//显示Flag为真
			if (giFlag.isShow[i])
			{
				dx = giTab.lisPoint[i].x;
				dy = giTab.lisPoint[i].y;

				for (int j = 0; j < giObjTable.obj[i].size(); j++)
				{

					p = Point(giObjTable.obj[i].at(j).x, giObjTable.obj[i].at(j).y);
					//目标点在小地图显示区域内
					if (isContains(minMapRect, p))
					{
						x = (int)((p.x - minMapRect.x) / giMEF.scale) - dx;
						y = (int)((p.y - minMapRect.y) / giMEF.scale) - dy;

						//该x，y周围要有足够的空间来填充图标
						if (x > 0 && y > 0 && x + giTab.lis[i].cols < autoMapSize.width&&y + giTab.lis[i].rows < autoMapSize.height)
						{
							r = img(Rect(x , y , giTab.lis[i].cols, giTab.lis[i].rows));
							giTab.lis[i].copyTo(r, giTab.lisMask[i]);
						}

					}

				}
			}
			else
			{
				;
			}
		}
		//显示匹配出的star
		p = mapMatchStar;
		if (isContains(minMapRect, p))
		{
			x = (int)((p.x - minMapRect.x) / giMEF.scale) - giTab.starPoint.x;
			y = (int)((p.y - minMapRect.y) / giMEF.scale) - giTab.starPoint.y;

			//该x，y周围要有足够的空间来填充图标
			if (x > 0 && y > 0 && x + giTab.star.cols < autoMapSize.width&&y + giTab.star.rows < autoMapSize.height)
			{
				r = img(Rect(x, y, giTab.star.cols, giTab.star.rows));
				giTab.star.copyTo(r, giTab.starMask);
			}

		}
		//显示列表里已发现的
		for (int i = 0; i < min(giFlag.max, giObjTable.num); i++)
		{
				dx = giTab.lisPoint[i].x;
				dy = giTab.lisPoint[i].y;

				for (int j = 0; j < giObjTable.obj[i].size(); j++)
				{
					if (giConfig.data[j][i] == 1)
					{
						p = Point(giObjTable.obj[i].at(j).x, giObjTable.obj[i].at(j).y);
						//目标点在小地图显示区域内
						if (isContains(minMapRect, p))
						{
							x = (int)((p.x - minMapRect.x) / giMEF.scale) - dx;
							y = (int)((p.y - minMapRect.y) / giMEF.scale) - dy;

							//该x，y周围要有足够的空间来填充图标
							if (x > 0 && y > 0 && x + giTab.lis[i].cols < autoMapSize.width&&y + giTab.lis[i].rows < autoMapSize.height)
							{
								r = img(Rect(x, y, giTab.lis[i].cols, giTab.lis[i].rows));
								giTab.lis[i].copyTo(r, giTab.lisMask[i]);
							}
					}
				}
			}
		}
		//批量添加物品的显示
		/*
		for (int i = 0; i < 4; i++)
		{
			dx = giTab.lisPoint[i].x;
			dy = giTab.lisPoint[i].y;

			for (int j = 0; j < giObjTable.at.size(i); j++)
			{

				p = Point(giObjTable.at.objptr[i].at(j).x, giObjTable.at.objptr[i].at(j).y);
				//目标点在小地图显示区域内
				if (isContains(minMapRect, p))
				{
					x = (int)((p.x - minMapRect.x) / giMEF.scale) - dx;
					y = (int)((p.y - minMapRect.y) / giMEF.scale) - dy;

					//该x，y周围要有足够的空间来填充图标
					if (x > 0 && y > 0 && x + giTab.lis[i].cols < autoMapSize.width&&y + giTab.lis[i].rows < autoMapSize.height)
					{
						r = img(Rect(x, y, giTab.lis[i].cols, giTab.lis[i].rows));
						giTab.lis[i].copyTo(r, giTab.lisMask[i]);
					}

				}

			}
		}
		*/

		giFlag.isUpdata = false;
	}

}

//测试用
void giam::GenshinImpact_AutoMap::customProcess()
{
	//如果窗口不处于最小化状态，对画面进行更新

	//循环计数
	_count++;
	

}

//匹配指定目标
void giam::GenshinImpact_AutoMap::mapTarget()
{
	static DWORD exitTargetCode;
	if (tMatchTarget == nullptr)
	{
		//设置匹配图像当前小地图
		giMatch.setObject(giFrameMap);
		tMatchTarget = new thread(&giam::GenshinImpact_AutoMap::thread_MatchTarget, this, ref(giMatch), ref(tMuMatch));
	}
	if (tMatchTarget != nullptr)
	{
		GetExitCodeThread(tMatchTarget->native_handle(), &exitTargetCode);
		if (exitTargetCode == 0)
		{
			tMatchTarget->join();
			delete tMatchTarget;
			tMatchTarget = nullptr;
			tIsEndTarget = true;
		}
	}
}

void giam::GenshinImpact_AutoMap::mapMatchMap()
{
	static Point tmp;
	static DWORD exitMapCode;
	if (tIsEndInit == false)return;
	if (giIsPaimonVisibleFlag&&giFlag.isAutoMove)
	{
		if (tMatchMap == nullptr)
		{
			//设置匹配图像当前小地图
			giMatch.setObject(giFrameMap);
			double t = t = (double)cv::getTickCount();

			tMatchMap = new thread(&giam::GenshinImpact_AutoMap::thread_MatchMap, this, ref(giMatch), ref(tMuMatch));

			t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
			cout << "new Thread time:" << t << "s" << endl;
		}
		if (tIsEndMap == false)
		{
			GetExitCodeThread(tMatchMap->native_handle(), &exitMapCode);
			if (exitMapCode == 0)
			{
				double t = t = (double)cv::getTickCount();

				tMatchMap->join();
				delete tMatchMap;
				tMatchMap = nullptr;
				tIsEndMap = true;

				t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
				cout << "delete Thread time:" << t << "s" << endl;
			}
		}
		if (tIsEndMap)
		{
			if (giMatch.getIsCanGet())
			{
				zerosMinMap = giMatch.getLocation();
				//cout << zerosMinMap << endl;
				if (zerosMinMap != tmp)
				{
					tmp = zerosMinMap;
					giFlag.isGetMap = true;
					giFlag.isUpHUD = true;
				}
			}
			tIsEndMap = false;
		}
	}
}

//匹配风、岩神瞳
void giam::GenshinImpact_AutoMap::mapStar()
{
	static vector<Point> p;
	static Point findP;
	static vector<int> type;
	static vector<int> id;
	static DWORD exitStarCode;
	static const Point Compensation_factor(16,48);
	static int minVal = 0;
	static int matchId = 0;

	Rect tmp;
	if (tIsEndInit == false)return;
	//根据当前位置，获取周围大地图140px范围内所有star，如果没有则false
	if (isNeedFindStar(type,id, p) || tMatchStar != nullptr)
	{
		
		if (tMatchStar == nullptr)
		{
			//设置匹配图像当前小地图
			giMatch.setObject(giFrameMap);
			tMatchStar = new thread(&giam::GenshinImpact_AutoMap::thread_MatchStar, this, ref(giMatch), ref(tMuMatch));
		}
		if (tMatchStar != nullptr)
		{
			GetExitCodeThread(tMatchStar->native_handle(), &exitStarCode);
			if (exitStarCode == 0)
			{
				tMatchStar->join();
				delete tMatchStar;
				tMatchStar = nullptr;
				tIsEndStar = true;
			}
		}
		if (tIsEndStar&&id.size()>0)
		{
			//进程检测到star，未检测到则为false
			if (giMatch.getIsFindStar())
			{
				//获得star位置，相对小地图中心
				findP = giMatch.getFindStar();
				//位置映射至大地图，根据已知当前位置，将会包含当前位置所带有的误差
				Point tmpP = findP * 2 + zerosMinMap;

				minVal = dis2(tmpP - p.at(0));
				matchId = 0;
				for (int i = 1; i < id.size(); i++)
				{
					if (dis2(tmpP - p.at(i)) < minVal)
					{
						minVal = dis2(tmpP - p.at(i));
						matchId = i;
					}
				}
				if (minVal > 1000)cout << minVal << endl;
				mapMatchStar = tmpP;
				switch (giConfig.data[id.at(matchId)][type.at(matchId)])
				{
					case 0:
					{
						giConfig.data[id.at(matchId)][type.at(matchId)] = 1;//已发现
						break;
					}
					case 1:
					{
						break;
					}
					default:
						break;
				}
			}
			else
			{
				//判断周围是否应该存在star
				
			}
			tIsEndStar = false;
		}

		//cout << id << ":" <<"|"<< p.x << "," << p.y <<"||"<< zerosMinMap.x <<","<< zerosMinMap.y << "|" << endl;

		//zerosMinMap
	}
}

//地图数据状态更新
void giam::GenshinImpact_AutoMap::mapUpdata()
{
	//更新用
	static Mat tmpMap;



	//如果窗口不处于最小化状态，对画面进行更新
	if (!thisIsIconic())
	{
		
		giFlag.isGetMap = true;
		//截取地图
		if (giFlag.isGetMap || giFlag.isUpHUD)
		{
			getMinMap().copyTo(tmpMap);
			giFlag.isGetMap = false;
			giFlag.isUpHUD = true;
		}
		if (giFlag.isUpHUD)
		{
			//设置显示标记
			setFLAG();
			addFLAG(tmpMap);
			//设置显示HUD
			setHUD();
			addHUD(tmpMap);

			//将加工好的画面赋给显示变量
			tmpMap.copyTo(autoMapMat);
			giFlag.isUpHUD = false;
			tmpMap.release();
		}
	}
}

//地图显示刷新
void giam::GenshinImpact_AutoMap::mapShow()
{
	//如果悬浮窗窗口不存在，停止运行并退出
	if (!IsWindow(thisHandle))
	{
		isRun = false;
		return;
	}

	//如果窗口不处于最小化状态，对画面进行更新
	if (!thisIsIconicFlag)
	{
		imshow(autoMapWindowsName, autoMapMat);
		//如果平移了悬浮窗或者原神窗口有移动，悬浮窗随之移动
		if (offGiMinMap != offGiMinMapTmp|| (!isEqual(giRect, giRectTmp)))
		{
			if (giIsFullScreenFlag)offGiMinMap = Point(288, 82);else offGiMinMap = Point(250, 100);
			//窗口跟随原神平移
			//平移窗口。giRect：如果原神已经退出，则使用关闭前的位置
			SetWindowPos(thisHandle, HWND_TOPMOST, giRect.left + offGiMinMap.x, giRect.top + offGiMinMap.y, 0, 0, SWP_NOSIZE);
			offGiMinMapTmp = offGiMinMap;
			giRectTmp = giRect;
		}
	}

	//原神是否运行
	if (giIsRunningFlag)
	{
		//是否自动追踪
		switch (giFlag.isAutoMove)
		{
			case true:
			{
				//是否处于可见状态
				switch (giIsDisplayFlag)
				{
					case true:
					{
						//处于主界面且悬浮窗处于最小化，恢复悬浮窗
						if (giIsPaimonVisibleFlag && thisIsIconicFlag)
						{
							ShowWindow(thisHandle, SW_RESTORE);
							SetForegroundWindow(giHandle);
						}
						//不处于主界面且悬浮窗不处于最小化，最小化悬浮窗
						if ((!giIsPaimonVisibleFlag) && (!thisIsIconicFlag))
						{
							ShowWindow(thisHandle, SW_MINIMIZE);
						}
						break;
					}
					case false:
					{
						//悬浮窗不处于最小化，最小化悬浮窗
						if (!thisIsIconicFlag)
						{
							ShowWindow(thisHandle, SW_MINIMIZE);
						}
						break;
					}
				}
				break;
			}
			case false:
			{
				//是否处于可见状态
				switch (giIsDisplayFlag)
				{
					case true:
					{
						if (thisIsIconicFlag)
						{
							ShowWindow(thisHandle, SW_RESTORE);
							SetForegroundWindow(giHandle);
						}
						break;
					}
					case false:
					{
						if (!thisIsIconicFlag)
						{
							//处于不可见状态则令悬浮窗进行最小化
							ShowWindow(thisHandle, SW_MINIMIZE);
						}
						break;
					}
				}

				break;
			}
		}
	}

	//等待显示更新
	FRL.Wait();

}

//检查匹配初始化线程是否结束
void giam::GenshinImpact_AutoMap::thisCheckThread()
{
	static DWORD exitInitCode;
	//static DWORD exitMapCode;
	//static DWORD exitStarCode;
	//static DWORD exitTargetCode;
	if (tMatchInit != nullptr)
	{
		GetExitCodeThread(tMatchInit->native_handle(), &exitInitCode);
		if (exitInitCode == 0)
		{
			tMatchInit->join();
			delete tMatchInit;
			tMatchInit = nullptr;
			tIsEndInit = true;
		}
		
	}
}

//鼠标回调
void giam::GenshinImpact_AutoMap::on_MouseHandle(int event, int x, int y, int flags, void * parm)
{
	GenshinImpact_AutoMap& gi = *(giam::GenshinImpact_AutoMap*) parm;

	gi.giMEF.value = flags;

	switch (event)	
	{
	case EVENT_MOUSEMOVE: 
	{
		break;
	}
	case EVENT_LBUTTONDOWN: 
	{
		gi.giMEF.x0 = x;
		gi.giMEF.y0 = y;
		gi.giMEF.p0 = gi.zerosMinMap;
		break;
	}
	case EVENT_RBUTTONDOWN:
	{
		break;
	}
	case EVENT_MBUTTONDOWN: 
	{
		gi.giMEF.x1 = x;
		gi.giMEF.y1 = y;
		gi.giMEF.p1 = gi.offGiMinMap;//Point(gi.offGiMinMap.x - x, gi.offGiMinMap.y - y);
		break;
	}
	case EVENT_LBUTTONUP: 
	{
		for (int i = 0; i < gi.giObjTable.num; i++)
		{
			Rect& r = gi.giTab.lisRect[i];

			if (x<r.x || x>(r.x + r.width) || y<r.y || y>(r.y + r.height))
			{

			}
			else
			{
				gi.giFlag.isShow[i] = !gi.giFlag.isShow[i];
				gi.giFlag.isUpdata = true;
				gi.giFlag.isGetMap = true;
			}
		}
		break;
	}
	case EVENT_RBUTTONUP: 
	{
		break;
	}
	case EVENT_MBUTTONUP: 
	{
		break;
	}
	case EVENT_LBUTTONDBLCLK: 
	{
		if (x > gi.autoMapSize.width - gi.giTab.sysIcon1.cols&&y <= gi.giTab.sysIcon1.rows)
		{
			gi.isRun = false;
		}
		else
		{
			gi.giFlag.isAutoMove = !gi.giFlag.isAutoMove;
			gi.giFlag.isUpdata = true;

		}
		break;
	}
	case EVENT_RBUTTONDBLCLK: 
	{

		break;
	}
	case EVENT_MBUTTONDBLCLK:
	{
		break;
	}
	case EVENT_MOUSEWHEEL:
	{
		gi.giMEF.value = getMouseWheelDelta(flags);

		if (gi.giMEF.value < 0)
		{
			if (gi.giMEF.scale < 6)
			{
				gi.giMEF.scale *= 1.2;
			}
		}
		else if (gi.giMEF.value > 0)
		{
			if (gi.giMEF.scale > 0.5)
			{
				gi.giMEF.scale /= 1.2;
			}
		}
		gi.giFlag.isGetMap = true;
		gi.giFlag.isUpdata = true;
		break;
	}
	case EVENT_MOUSEHWHEEL:
	{
		break;
	}
	default:
		break;
	}

	switch (flags)
	{
	case EVENT_FLAG_LBUTTON:
	{
		if (x > gi.autoMapSize.width - gi.giTab.sysIcon1.cols&&x < gi.autoMapSize.width && y < gi.giTab.sysIcon1.rows&&y>0)
		{
			//gi.giMEF.dx = x - gi.giMEF.x1;
			//gi.giMEF.dy = y - gi.giMEF.y1;
			//gi.offGiMinMap = gi.giMEF.p1 + Point(gi.giMEF.dx, gi.giMEF.dy);
		}
		else
		{
			gi.giMEF.dx = x - gi.giMEF.x0;
			gi.giMEF.dy = y - gi.giMEF.y0;
			gi.zerosMinMap = gi.giMEF.p0 - Point((int)(gi.giMEF.dx*gi.giMEF.scale), (int)(gi.giMEF.dy*gi.giMEF.scale));
			gi.giFlag.isUpdata = true;
			gi.giFlag.isGetMap = true;
		}

		break;
	}
	case EVENT_FLAG_RBUTTON:
	{
		break;
	}
	case EVENT_FLAG_MBUTTON:
	{
		//gi.giMEF.dx = x - gi.giMEF.x1;
		//gi.giMEF.dy = y - gi.giMEF.y1;
		gi.offGiMinMap = gi.giMEF.p1 + Point(x - gi.giMEF.x1, y - gi.giMEF.y1);

		break;
	}
	case EVENT_FLAG_CTRLKEY:
	{
		break;
	}
	case EVENT_FLAG_SHIFTKEY:
	{
		break;
	}
	case EVENT_FLAG_ALTKEY:
	{
		break;
	}
	default:
		break;
	}
}

void giam::GenshinImpact_AutoMap::thread_MatchInit(giAMM & match, mutex& mu)
{
	mu.lock();

	match.init();

	mu.unlock();
}

void giam::GenshinImpact_AutoMap::thread_MatchMap(giAMM & match, mutex& mu)
{
	mu.lock();

	match.test();

	mu.unlock();
}

void giam::GenshinImpact_AutoMap::thread_MatchStar(giAMM & match, mutex& mu)
{
	mu.lock();

	match.test2();

	mu.unlock();
}

void giam::GenshinImpact_AutoMap::thread_MatchTarget(giAMM & match, mutex& mu)
{
	//while (!match.isFinishMatchTarget)
	//{
	//	match.test3();
	//}
	mu.lock();
	
	match.test3();

	mu.unlock();

	//Mat img_scene(giFrameMap);// = (Rect(36, 36, object.cols - 72, object.rows - 72)); //minMap

	//if (maxVal > 0.75)
	//{
	//	isStarPoint = maxLoc + Point(img_object_mask.size() / 2) - Point(img_scene.size() / 2);
	//	isFindStar = true;
	//}
	//else
	//{
	//	isFindStar = false;
	//}

	
}

//void giam::GenshinImpact_AutoMap::thread_Match(giAMM & match) {}

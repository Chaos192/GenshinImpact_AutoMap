#include "GenshinImpact_AutoMap.h"

giam::GenshinImpact_AutoMap::GenshinImpact_AutoMap()
{
}

giam::GenshinImpact_AutoMap::~GenshinImpact_AutoMap()
{
}

bool giam::GenshinImpact_AutoMap::init()
{
	AT.on();
	
	isInit = true;
	isRun = true;
	
	autoMapMat = Mat(autoMapSize, CV_8UC4, Scalar(200, 200, 200, 255));

	namedWindow(autoMapWindowsName);
	setMouseCallback(autoMapWindowsName, on_MouseHandle, (void*)this);
	thisHandle = FindWindow(NULL, autoMapWindowsName.c_str());

	imshow(autoMapWindowsName, autoMapMat);
	return false;
}

bool giam::GenshinImpact_AutoMap::run()
{
	if (!isInit) { init(); }
	while (isRun)
	{
		//customProcess();
		mapUpdata();
		mapShow();
	}
	exit();
	return false;
}

bool giam::GenshinImpact_AutoMap::exit()
{
	return false;
}

Mat giam::GenshinImpact_AutoMap::getMinMap()
{
	Mat minMap;

	Point minMapPoint = Point(0, 0);

	Size R = autoMapSize / 2;

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
		minMapPoint.x = mapSize.width- autoMapSize.width;
	}
	if (RB.y > mapSize.height)
	{
		minMapPoint.y = mapSize.height - autoMapSize.height;
	}

	minMap = mapMat(Rect(minMapPoint, autoMapSize));

	return minMap;
}

void giam::GenshinImpact_AutoMap::giIsRunning()
{
	if (AT)
	{
		//AutoTest Work Is On
		giIsRunningFlag = AT;
		return;
	}
	else
	{
		//
		giHandle = FindWindow(NULL, "原神");
		if (giHandle != NULL)
		{
			giIsRunningFlag= true;
			return;
		}
	}
	giIsRunningFlag= false;
}

void giam::GenshinImpact_AutoMap::giIsDisplay()
{
	if (AT)
	{
		//AutoTest Work Is On
		giIsDisplayFlag = AT;
		return;
	}
	else
	{
		//
		if (giHandle != NULL)
		{
			giIsDisplayFlag= !IsIconic(giHandle);
			return;
		}
	}
	giIsDisplayFlag= false;
}

void giam::GenshinImpact_AutoMap::giIsZoomed()
{
	if (AT)
	{
		//AutoTest Work Is On
		giIsZoomedFlag = !AT;
		return;
	}
	else
	{
		//
		if (giHandle != NULL)
		{
			//WindowFromPoint();
			giIsZoomedFlag=IsZoomed(giHandle);
			return;
		}
	}
	giIsZoomedFlag = false;
	return;
}

void giam::GenshinImpact_AutoMap::giCheckWindows()
{
	giIsRunning();
	giIsDisplay();
	giIsZoomed();
}

void giam::GenshinImpact_AutoMap::giGetScreen()
{
	HBITMAP	hBmp;
	RECT rc;
	BITMAP bmp;
	//获取目标句柄的窗口大小RECT
	GetWindowRect(giHandle, &rc);
	//获取目标句柄的DC
	HDC hScreen = GetDC(giHandle);
	HDC	hCompDC = CreateCompatibleDC(hScreen);
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
	giFrame.create(cvSize(bmp.bmWidth, bmp.bmHeight), CV_MAKETYPE(CV_8U, nChannels));
	GetBitmapBits(hBmp, bmp.bmHeight*bmp.bmWidth*nChannels, giFrame.data);
}

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
	};
	if (giIsDisplayFlag)
	{
		giHUD.displayFlagColor = Scalar(0, 255, 0);
	}
	else
	{
		giHUD.displayFlagColor = Scalar(0, 0, 255);
	}

}

void giam::GenshinImpact_AutoMap::addHUD(Mat img)
{
	Mat blueRect(30, autoMapSize.width, CV_8UC4, Scalar(255, 0, 0, 255));
	Mat tmp = img(Rect(0,0, autoMapSize.width, 30));
	addWeighted(tmp, 0.5, blueRect, 0.5, 0, tmp);

	Mat star;
	img(Rect(autoMapSize.width / 2 - 5, autoMapSize.height / 2 - 5, 11, 11)).copyTo(star);
	tmp = img(Rect(autoMapSize.width / 2 - 5, autoMapSize.height / 2 - 5, 11, 11));
	circle(star, Point(5, 5), 4, giHUD.minStarColor, 2, LINE_AA);
	addWeighted(tmp, 0.5, star, 0.5, 0, tmp);



	circle(img, Point(12, 12), 8, giHUD.displayFlagColor, -1);

	putText(img, giHUD.runState, Point(28, 20), FONT_HERSHEY_COMPLEX_SMALL, 1, giHUD.runTextColor, 2);

	putText(img, to_string(FRL.runningTime*1000), Point(50, 50), FONT_HERSHEY_COMPLEX_SMALL, 1, giHUD.runTextColor, 2);

}

void giam::GenshinImpact_AutoMap::customProcess()
{
	switch ((rand()%3))
	{
	case 0:
		zerosMinMap.x = zerosMinMap.x + 30;
		break;
	case 1:
		break;
	case 2:
		zerosMinMap.x = zerosMinMap.x - 30;
	default:
		break;
	}

	switch ((rand() % 3))
	{
	case 0:
		zerosMinMap.y = zerosMinMap.y + 30;
		break;
	case 1:
		break;
	case 2:
		zerosMinMap.y = zerosMinMap.y - 30;
	default:
		break;
	}
}

void giam::GenshinImpact_AutoMap::mapUpdata()
{
	Mat tmpMap;


	giCheckWindows();

	giGetScreen();

	//
	getMinMap().copyTo(tmpMap);
	setHUD();
	addHUD(tmpMap);

	autoMapMat = tmpMap;
	//tmpMap
}

void giam::GenshinImpact_AutoMap::mapShow()
{
	if (IsWindow(thisHandle))
	{
		imshow(autoMapWindowsName, autoMapMat);
		FRL.Wait();
	}
	else
	{
		isRun = false;
	}
}

void giam::GenshinImpact_AutoMap::on_MouseHandle(int event, int x, int y, int flags, void * parm)
{
	GenshinImpact_AutoMap& gi = *(giam::GenshinImpact_AutoMap*) parm;

	switch (event)	
	{
	case EVENT_MOUSEMOVE: 
	{
		//!< indicates that the mouse pointer has moved over the window.

		break;
	}
	case EVENT_LBUTTONDOWN: 
	{
		//!< indicates that the left mouse button is pressed.
		gi.giMEF.x0 = x;
		gi.giMEF.y0 = y;
		gi.giMEF.p0 = gi.zerosMinMap;
		break;
	}
	case EVENT_RBUTTONDOWN:
	{
		//!< indicates that the right mouse button is pressed.

		break;
	}
	case EVENT_MBUTTONDOWN: 
	{
		//!< indicates that the middle mouse button is pressed.

		break;
	}
	case EVENT_LBUTTONUP: 
	{
		//!< indicates that left mouse button is released.

		break;
	}
	case EVENT_RBUTTONUP: 
	{
		//!< indicates that right mouse button is released.

		break;
	}
	case EVENT_MBUTTONUP: 
	{
		//!< indicates that middle mouse button is released.

		break;
	}
	case EVENT_LBUTTONDBLCLK: 
	{
		//!< indicates that left mouse button is double clicked.

		break;
	}
	case EVENT_RBUTTONDBLCLK: 
	{
		//!< indicates that right mouse button is double clicked.

		break;
	}
	case EVENT_MBUTTONDBLCLK:
	{
		//!< indicates that middle mouse button is double clicked.

		break;
	}
	case EVENT_MOUSEWHEEL:

	{
		//!< positive and negative values mean forward and backward scrolling, respectively.

		break;
	}
	case EVENT_MOUSEHWHEEL:
	{
		//!< positive and negative values mean right and left scrolling, respectively.

		break;
	}
	default:
		break;
	}

	switch (flags)
	{
	case EVENT_FLAG_LBUTTON:
	{
		//!< indicates that the left mouse button is down.
		gi.giMEF.dx = x - gi.giMEF.x0;
		gi.giMEF.dy = y - gi.giMEF.y0;

		gi.zerosMinMap = gi.giMEF.p0 - Point(gi.giMEF.dx, gi.giMEF.dy);

		break;
	}
	case EVENT_FLAG_RBUTTON:
	{
		//!< indicates that the right mouse button is down.

		break;
	}
	case EVENT_FLAG_MBUTTON:
	{
		//!< indicates that the middle mouse button is down.

		break;
	}
	case EVENT_FLAG_CTRLKEY:
	{
		//!< indicates that CTRL Key is pressed.

		break;
	}
	case EVENT_FLAG_SHIFTKEY:
	{
		//!< indicates that SHIFT Key is pressed.

		break;
	}
	case EVENT_FLAG_ALTKEY:
	{
		//!< indicates that ALT Key is pressed.

		break;
	}
	default:
		break;
	}
}

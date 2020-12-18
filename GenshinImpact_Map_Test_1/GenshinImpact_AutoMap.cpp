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
	
	autoMapMat = Mat(autoMapSize, CV_8UC3, Scalar(200, 200, 200));

	namedWindow(autoMapWindowsName);
	imshow(autoMapWindowsName, autoMapMat);
	return false;
}

bool giam::GenshinImpact_AutoMap::run()
{
	if (!isInit) { init(); }
	while (isRun)
	{
		zerosMinMap.x++;
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
	circle(img, Point(12, 12), 8, giHUD.displayFlagColor, -1);
	putText(img, giHUD.runState, Point(28, 20), FONT_HERSHEY_COMPLEX_SMALL, 1, giHUD.runTextColor, 1);
	circle(img, autoMapSize / 2, 3, Scalar(0, 0, 255));
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
	imshow(autoMapWindowsName, autoMapMat);
	FRL.Wait();
}

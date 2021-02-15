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
	MET.zerosMinMap = zerosMinMap;
	getGiHandle();
	getThisHandle(mapWindowsHandle);


	getGiState();
	setThisState();
	//多线程初始化
	/**/
}

void AutomaticTrackingMap::Exit()
{
}

void AutomaticTrackingMap::FrontEndUpdata()
{
	MainMat = getViewMap();
	Mat2QImage();
}

void AutomaticTrackingMap::BackEndUpdata()
{
	getGiState();
	setThisOffset();
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
}

void AutomaticTrackingMap::setThisState()
{
	//设置窗口位置
	setWindowsPos();
	ShowWindow(thisHandle, SW_SHOW);
}

void AutomaticTrackingMap::setThisOffset()
{
	if (GIS.giRectMode > 0)
	{
		offGiMinMap = GIS.getOffset();
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
	zerosMinMap = MET.zerosMinMap;
}

void AutomaticTrackingMap::setMouseMovePos(int x, int y)
{
	MET.setMouseMovePos(x, y);
	zerosMinMap = MET.zerosMinMap;
	
}

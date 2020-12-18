#include "GenshinImpact_AutoMap.h"

giam::GenshinImpact_AutoMap::GenshinImpact_AutoMap()
{
}

giam::GenshinImpact_AutoMap::~GenshinImpact_AutoMap()
{
}

bool giam::GenshinImpact_AutoMap::init()
{
	//AT.on();
	
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
		handle = FindWindow(NULL, "Ô­Éñ");
		if (handle != NULL)
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
		if (handle != NULL)
		{
			giIsDisplayFlag= !IsIconic(handle);
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
		if (handle != NULL)
		{
			//WindowFromPoint();
			giIsZoomedFlag=IsZoomed(handle);
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

void giam::GenshinImpact_AutoMap::mapUpdata()
{
	giCheckWindows();

}

void giam::GenshinImpact_AutoMap::mapShow()
{
	imshow(autoMapWindowsName, autoMapMat);
	FRL.Wait();
}

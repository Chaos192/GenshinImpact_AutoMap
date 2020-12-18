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
		if (giIsRunning())
		{
			putText(autoMapMat, "Game Running", Point(10, 100), 1, 1, Scalar(0, 255, 0));
			//genshin is Running
			if (giIsTop())
			{
				//genshin is Top Windows
				if (giIsZoomed())
				{
					//
				}
				else
				{

				}
			}
			else
			{
				//genshin is Iconic
			}
		}
		else
		{
			//genshin not Run
			putText(autoMapMat, "Not Run!", Point(10, 100), 1, 1, Scalar(0, 0, 255));
		}
		mapShow();
		waitKey(33);
	}
	exit();
	return false;
}

bool giam::GenshinImpact_AutoMap::exit()
{
	return false;
}

bool giam::GenshinImpact_AutoMap::giIsRunning()
{
	if (AT.s())
	{
		//AutoTest Work Is On
		return AT.t;
	}
	else
	{
		handle = FindWindow(NULL, "Ô­Éñ");
		if (handle == NULL)
			return false;
		else
			return true;
	}
	return false;
}

bool giam::GenshinImpact_AutoMap::giIsTop()
{
	if (AT.s())
	{
		//AutoTest Work Is On
		return AT.t;
	}
	else
	{
		//
	}
	return false;
}

bool giam::GenshinImpact_AutoMap::giIsZoomed()
{
	if (AT.s())
	{
		//AutoTest Work Is On
		return AT.f;
	}
	else
	{
		//
	}
	return false;
}

void giam::GenshinImpact_AutoMap::mapShow()
{
	imshow(autoMapWindowsName, autoMapMat);

}

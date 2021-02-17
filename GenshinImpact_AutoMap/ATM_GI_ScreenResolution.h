#pragma once
#include <opencv2/opencv.hpp>
class ATM_GI_SR;
class ATM_GI_ScreenResolution
{
public:
	virtual cv::Size giSize() = 0;
	virtual int giRectMode(ATM_GI_SR gisr) = 0;
};

class GISR_Undefinde :public ATM_GI_ScreenResolution
{
public:
	cv::Size giSize()
	{
		return cv::Size(0, 0);
	}
	int giRectMode()
	{
		return 1;
	}
};

class ATM_GI_SR
{
public:
	void giRevtMode()
	{

	}
};


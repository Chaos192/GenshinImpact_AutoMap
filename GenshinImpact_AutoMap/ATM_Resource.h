#pragma once
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include "resource.h"
using namespace cv;

class ATM_Resource
{
	//HBITMAP gHmp = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1));
public:
	ATM_Resource();
	~ATM_Resource();
public:
	Mat GIMAP;
	Mat MAINMASK;
	Mat *GIOBJICON;

private:
	HBITMAP hGIMAP;
	HBITMAP hMAINMASK;
	HBITMAP *hGIOBJICON;

	bool HBitmap2Mat(HBITMAP& _hBmp, cv::Mat& _mat);
};


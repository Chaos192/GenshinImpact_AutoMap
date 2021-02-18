#pragma once
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include "resource.h"
using namespace cv;

class ATM_Resource
{
	//HBITMAP gHmp = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_MAINMASK));
public:
	ATM_Resource();
	~ATM_Resource();
public:
	Mat GIMAP;
	Mat MAINMASK;
	Mat *GIOBJICON;
	Mat *GIPAIMON;

private:
	HBITMAP hGIMAP;
	HBITMAP hMAINMASK;
	HBITMAP *hGIOBJICON;
	HBITMAP *hGIPAIMON;

	void loadGiMap();
	void loadMainMask();
	void loadGiPaimon();

	bool HBitmap2Mat(HBITMAP& _hBmp, cv::Mat& _mat);
};


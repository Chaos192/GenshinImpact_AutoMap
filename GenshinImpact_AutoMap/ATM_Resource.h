#pragma once
#include <vector>
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
	Mat GIAVATAR;
	Mat *GIOBJICON;
	Mat *GIOBJICONMASK;
	Mat *GIOBJFLAGICON;
	Mat *GIOBJFLAGICONMASK;
	Mat *GIPAIMON;

private:
	HBITMAP hGIMAP;
	HBITMAP hMAINMASK;
	HBITMAP hGIAVATAR;
	HBITMAP *hGIOBJICON;
	HBITMAP *hGIOBJICONMASK;
	HBITMAP *hGIOBJFLAGICON;
	HBITMAP *hGIOBJFLAGICONMASK;
	HBITMAP *hGIPAIMON;

	void loadGiMap();
	void loadMainMask();
	void loadGiAvatar();
	void loadGiPaimon();
	void loadGiObjIcon();
	void loadGiObjIconMask();
	void loadGiObjFlagIcon();
	void loadGiObjFlagIconMask();

	bool HBitmap2Mat(HBITMAP& _hBmp, cv::Mat& _mat);
	bool Mat2MaskMat(Mat &in, Mat &out);
};


// Test2Project1.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "framework.h"
#include "Test2Project1.h"
#include "resource.h"

#include<Windows.h>
#include<opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include<opencv2/xfeatures2d.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>

//using namespace cv;

// 这是导出变量的一个示例
TEST2PROJECT1_API int nTest2Project1=0;

// 这是导出函数的一个示例。
TEST2PROJECT1_API int fnTest2Project1(void)
{
    return 0;
}

BOOL HBitmap2Mat(HBITMAP& _hBmp, cv::Mat& _mat)
{
	//BITMAP操作
	BITMAP bmp;
	GetObject(_hBmp, sizeof(BITMAP), &bmp);
	if (1 == 1);
	int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel / 8;
	int depth = bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;
	//mat操作
	cv::Mat v_mat;
	v_mat.create(cvSize(bmp.bmWidth, bmp.bmHeight), CV_MAKETYPE(CV_8UC3, nChannels));
	//v_mat.create(cvSize(bmp.bmWidth, bmp.bmHeight), CV_MAKETYPE(CV_8UC3, nChannels));
	GetBitmapBits(_hBmp, bmp.bmHeight*bmp.bmWidth*nChannels, v_mat.data);
	_mat = v_mat;
	if (nChannels == 4)
	{
		cv::cvtColor(v_mat, _mat, CV_RGBA2RGB);
		return TRUE;
	}
	return FALSE;
}

// 这是已导出类的构造函数。
GGenshinImpactMatch::GGenshinImpactMatch(void)
{
	testMat = new cv::Mat;
	if (!gLoadSource())throw "Dll Resource Image Load Faile!";
	

}

GGenshinImpactMatch::~GGenshinImpactMatch(void)
{
	delete testMat;
}

bool GGenshinImpactMatch::setSource(void * _source)
{
	cv::Mat& source = *(cv::Mat*)_source;


	return false;
}

bool GGenshinImpactMatch::setTarget(void * _target)
{
	cv::Mat& target = *(cv::Mat*)_target;

	return false;
}


GPoint GGenshinImpactMatch::getPosition()
{
	return gPosition;
}

bool GGenshinImpactMatch::gLoadSource()
{
	HBITMAP test = LoadBitmap(GetModuleHandle(L"TEST2PROJECT1.dll"), MAKEINTRESOURCE(IDB_BITMAP1));
	//testMat = new cv::Mat();
	cv::Mat out;
	if(!HBitmap2Mat(test, *(cv::Mat*)testMat))throw"HBITMAP to cv::Mat Faile!";
	//testMat = &out;
	
	if (testMat != NULL)return true;
	return false;
}

GSize::GSize():GSize(0,0){}

GSize::GSize(int _x, int _y):x(_x),y(_y){}

void GSize::toArray(int _array[2])
{
	_array[0] = x;
	_array[1] = y;
}


//int * GSize::toArray()
//{
//	int _array[2] = { x,y };
//	return _array;
//}

GPoint::GPoint() :GPoint(0, 0) {}

GPoint::GPoint(int _x, int _y) :x(_x), y(_y) {}

void GPoint::toArray(int _array[2])
{
	_array[0] = x;
	_array[1] = y;
}


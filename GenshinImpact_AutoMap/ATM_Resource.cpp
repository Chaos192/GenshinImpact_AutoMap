#include "ATM_Resource.h"

ATM_Resource::ATM_Resource()
{
	hGIMAP= LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_GIMAP));
	HBitmap2Mat(hGIMAP, GIMAP);
	hMAINMASK = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1));
	HBitmap2Mat(hMAINMASK, MAINMASK);
}

ATM_Resource::~ATM_Resource()
{
}

bool ATM_Resource::HBitmap2Mat(HBITMAP & _hBmp, cv::Mat & _mat)
{
	//BITMAP²Ù×÷
	BITMAP bmp;
	GetObject(_hBmp, sizeof(BITMAP), &bmp);
	int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel / 8;
	int depth = bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;
	//mat²Ù×÷
	cv::Mat v_mat;
	v_mat.create(cvSize(bmp.bmWidth, bmp.bmHeight), CV_MAKETYPE(CV_8UC3, nChannels));
	GetBitmapBits(_hBmp, bmp.bmHeight*bmp.bmWidth*nChannels, v_mat.data);
	_mat = v_mat;
	if (nChannels == 4)
	{
		cv::cvtColor(v_mat, _mat, CV_RGBA2RGB);
		return true;
	}
	return false;
}

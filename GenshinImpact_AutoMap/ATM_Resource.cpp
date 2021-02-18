#include "ATM_Resource.h"

ATM_Resource::ATM_Resource()
{
	hGIPAIMON = new HBITMAP[4];
	GIPAIMON = new Mat[4];

	loadGiMap();
	loadMainMask();
	loadGiPaimon();
}

ATM_Resource::~ATM_Resource()
{
	delete[] hGIPAIMON;
	delete[] GIPAIMON;
}

void ATM_Resource::loadGiMap()
{
	hGIMAP = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_GIMAP));
	HBitmap2Mat(hGIMAP, GIMAP);
}

void ATM_Resource::loadMainMask()
{
	hMAINMASK = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_MAINMASK));
	HBitmap2Mat(hMAINMASK, MAINMASK);
}

void ATM_Resource::loadGiPaimon()
{
	hGIPAIMON[0]= LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_PAIMON1920X1080));
	HBitmap2Mat(hGIPAIMON[0], GIPAIMON[0]);
	hGIPAIMON[1] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_PAIMON1680X1050));
	HBitmap2Mat(hGIPAIMON[1], GIPAIMON[1]);
	hGIPAIMON[2] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_PAIMON1440X900));
	HBitmap2Mat(hGIPAIMON[2], GIPAIMON[2]);
	hGIPAIMON[3] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_PAIMON1366X768));
	HBitmap2Mat(hGIPAIMON[3], GIPAIMON[3]);
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

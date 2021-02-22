#include "ATM_Resource.h"

ATM_Resource::ATM_Resource()
{
	hGIOBJICON = new HBITMAP[4];
	hGIOBJICONMASK = new HBITMAP[4];
	hGIOBJFLAGICON = new HBITMAP[1];
	hGIOBJFLAGICONMASK = new HBITMAP[1];
	hGIPAIMON = new HBITMAP[4];


	GIOBJICON = new Mat[4];
	GIOBJICONMASK = new Mat[4];
	GIOBJFLAGICON = new Mat[1];
	GIOBJFLAGICONMASK = new Mat[1];
	GIPAIMON = new Mat[4];

	loadGiMap();
	loadMainMask();
	loadGiPaimon();
	loadGiObjIcon();
	loadGiObjIconMask();
	loadGiObjFlagIcon();
	loadGiObjFlagIconMask();

}

ATM_Resource::~ATM_Resource()
{
	delete[] hGIOBJICON;
	delete[] hGIOBJICONMASK;
	delete[] hGIOBJFLAGICON;
	delete[] hGIOBJFLAGICONMASK;
	delete[] hGIPAIMON;

	delete[] GIOBJICON;
	delete[] GIOBJICONMASK;
	delete[] GIOBJFLAGICON;
	delete[] GIOBJFLAGICONMASK;
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

void ATM_Resource::loadGiObjIcon()
{
	hGIOBJICON[0] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_OBJICON0));
	HBitmap2Mat(hGIOBJICON[0], GIOBJICON[0]);
	hGIOBJICON[1] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_OBJICON1));
	HBitmap2Mat(hGIOBJICON[1], GIOBJICON[1]);
	hGIOBJICON[2] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_OBJICON2));
	HBitmap2Mat(hGIOBJICON[2], GIOBJICON[2]);
	hGIOBJICON[3] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_OBJICON999));
	HBitmap2Mat(hGIOBJICON[3], GIOBJICON[3]);
}

void ATM_Resource::loadGiObjIconMask()
{
	hGIOBJICONMASK[0] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_OBJICON0MASK));
	HBitmap2Mat(hGIOBJICONMASK[0], GIOBJICONMASK[0]);
	Mat2MaskMat(GIOBJICONMASK[0], GIOBJICONMASK[0]);
	hGIOBJICONMASK[1] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_OBJICON1MASK));
	HBitmap2Mat(hGIOBJICONMASK[1], GIOBJICONMASK[1]);
	Mat2MaskMat(GIOBJICONMASK[1], GIOBJICONMASK[1]);
	hGIOBJICONMASK[2] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_OBJICON2MASK));
	HBitmap2Mat(hGIOBJICONMASK[2], GIOBJICONMASK[2]);
	Mat2MaskMat(GIOBJICONMASK[2], GIOBJICONMASK[2]);
	hGIOBJICONMASK[3] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_OBJICON999MASK));
	HBitmap2Mat(hGIOBJICONMASK[3], GIOBJICONMASK[3]);
	Mat2MaskMat(GIOBJICONMASK[3], GIOBJICONMASK[3]);
}

void ATM_Resource::loadGiObjFlagIcon()
{
	hGIOBJFLAGICON[0] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_OBJFLAGICON0));
	HBitmap2Mat(hGIOBJFLAGICON[0], GIOBJFLAGICON[0]);
}

void ATM_Resource::loadGiObjFlagIconMask()
{
	hGIOBJFLAGICONMASK[0] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_OBJFLAGICON0MASK));
	HBitmap2Mat(hGIOBJFLAGICONMASK[0], GIOBJFLAGICONMASK[0]);
	Mat2MaskMat(GIOBJFLAGICONMASK[0], GIOBJFLAGICONMASK[0]);
}

bool ATM_Resource::HBitmap2Mat(HBITMAP & _hBmp, cv::Mat & _mat)
{
	//BITMAP操作
	BITMAP bmp;
	GetObject(_hBmp, sizeof(BITMAP), &bmp);
	int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel / 8;
	int depth = bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;
	//mat操作
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

bool ATM_Resource::Mat2MaskMat(Mat & in, Mat & out)
{
	std::vector<Mat> mv0;
	//通道分离
	split(in, mv0);
	out = mv0[0];

	return false;
}

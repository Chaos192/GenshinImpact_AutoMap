#include "ATM_Resource.h"

ATM_Resource::ATM_Resource()
{
	hGIOBJICON = new HBITMAP[4];
	hGIOBJICONMASK = new HBITMAP[4];
	hGIOBJFLAGICON = new HBITMAP[2];
	hGIOBJFLAGICONMASK = new HBITMAP[2];
	hGIPAIMON = new HBITMAP[4];
	hGINUMUID = new HBITMAP[11];


	GIOBJICON = new Mat[4];
	GIOBJICONMASK = new Mat[4];
	GIOBJFLAGICON = new Mat[2];
	GIOBJFLAGICONMASK = new Mat[2];
	GIPAIMON = new Mat[4];
	GINUMUID = new Mat[11];

	loadGiMap();
	loadMainMask();
	loadGiAvatar();
	loadGiAvatarMask();
	loadGiStar();
	loadGiStarMask();
	loadGiPaimon();
	loadGiObjIcon();
	loadGiObjIconMask();
	loadGiObjFlagIcon();
	loadGiObjFlagIconMask();
	loadGiNumUID();
}

ATM_Resource::~ATM_Resource()
{
	delete[] hGIOBJICON;
	delete[] hGIOBJICONMASK;
	delete[] hGIOBJFLAGICON;
	delete[] hGIOBJFLAGICONMASK;
	delete[] hGIPAIMON;
	delete[] hGINUMUID;

	delete[] GIOBJICON;
	delete[] GIOBJICONMASK;
	delete[] GIOBJFLAGICON;
	delete[] GIOBJFLAGICONMASK;
	delete[] GIPAIMON;
	delete[] GINUMUID;
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

void ATM_Resource::loadGiAvatar()
{
	hGIAVATAR = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_GIAVATAR));
	HBitmap2Mat(hGIAVATAR, GIAVATAR);
}

void ATM_Resource::loadGiAvatarMask()
{
	hGIAVATARMASK = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_GIAVATARMASK));
	HBitmap2MatAlpha(hGIAVATARMASK, GIAVATARMASK);
}

void ATM_Resource::loadGiStar()
{
	hGISTAR = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_GISTAR));
	HBitmap2Mat(hGISTAR, GISTAR);
}

void ATM_Resource::loadGiStarMask()
{
	hGISTARMASK = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_GISTARMASK));
	HBitmap2Mat(hGISTARMASK, GISTARMASK);
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
	hGIOBJFLAGICON[1] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_OBJFLAGICON1));
	HBitmap2Mat(hGIOBJFLAGICON[1], GIOBJFLAGICON[1]);
}

void ATM_Resource::loadGiObjFlagIconMask()
{
	hGIOBJFLAGICONMASK[0] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_OBJFLAGICON0MASK));
	HBitmap2Mat(hGIOBJFLAGICONMASK[0], GIOBJFLAGICONMASK[0]);
	Mat2MaskMat(GIOBJFLAGICONMASK[0], GIOBJFLAGICONMASK[0]);
	hGIOBJFLAGICONMASK[1] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_OBJFLAGICON1MASK));
	HBitmap2Mat(hGIOBJFLAGICONMASK[1], GIOBJFLAGICONMASK[1]);
	Mat2MaskMat(GIOBJFLAGICONMASK[1], GIOBJFLAGICONMASK[1]);
}

void ATM_Resource::loadGiNumUID()
{
	hGINUMUID[0] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_GINUMUID0_ARGB));
	HBitmap2MatAlpha(hGINUMUID[0], GINUMUID[0]);
	hGINUMUID[1] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_GINUMUID1_ARGB));
	HBitmap2MatAlpha(hGINUMUID[1], GINUMUID[1]);
	hGINUMUID[2] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_GINUMUID2_ARGB));
	HBitmap2MatAlpha(hGINUMUID[2], GINUMUID[2]);
	hGINUMUID[3] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_GINUMUID3_ARGB));
	HBitmap2MatAlpha(hGINUMUID[3], GINUMUID[3]);
	hGINUMUID[4] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_GINUMUID4_ARGB));
	HBitmap2MatAlpha(hGINUMUID[4], GINUMUID[4]);
	hGINUMUID[5] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_GINUMUID5_ARGB));
	HBitmap2MatAlpha(hGINUMUID[5], GINUMUID[5]);
	hGINUMUID[6] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_GINUMUID6_ARGB));
	HBitmap2MatAlpha(hGINUMUID[6], GINUMUID[6]);
	hGINUMUID[7] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_GINUMUID7_ARGB));
	HBitmap2MatAlpha(hGINUMUID[7], GINUMUID[7]);
	hGINUMUID[8] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_GINUMUID8_ARGB));
	HBitmap2MatAlpha(hGINUMUID[8], GINUMUID[8]);
	hGINUMUID[9] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_GINUMUID9_ARGB));
	HBitmap2MatAlpha(hGINUMUID[9], GINUMUID[9]);
	hGINUMUID[10] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_GINUMUID_ARGB));
	HBitmap2MatAlpha(hGINUMUID[10], GINUMUID[10]);
}

void ATM_Resource::loadFromResource()
{
	//:/png/resource/ItemsPng/UIObjList0.png
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

//带Alpha通道的32位Bmp图片
bool ATM_Resource::HBitmap2MatAlpha(HBITMAP & _hBmp, cv::Mat & _mat)
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
	return true;
}

bool ATM_Resource::Mat2MaskMat(Mat & in, Mat & out)
{
	std::vector<Mat> mv0;
	//通道分离
	split(in, mv0);
	out = mv0[0];

	return false;
}

QPixmap ATM_Resource::QImage2QPixmap(QImage & in)
{
	QPixmap out;
	return out.fromImage(in);
}

QImage ATM_Resource::QPixmap2QImage(QPixmap & in)
{
	return in.toImage();
}

Mat ATM_Resource::QImage2Mat(QImage & in)
{
	return Mat(in.height(), in.width(), CV_8UC4, (uchar*)in.bits(), in.bytesPerLine());
}

QImage ATM_Resource::Mat2QImage(Mat & in)
{
	Mat rgb;
	cvtColor(in, rgb, CV_BGR2RGB);
	return QImage((const unsigned char*)(rgb.data), rgb.cols, rgb.rows, QImage::Format_RGB888);
}

#pragma once
#include <QtWidgets/QMainWindow>
#include <vector>
#include <string>
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
	Mat GIAVATARMASK;
	Mat GISTAR;
	Mat GISTARMASK;
	Mat *GIOBJICON;
	Mat *GIOBJICONMASK;
	Mat *GIOBJFLAGICON;
	Mat *GIOBJFLAGICONMASK;
	Mat *GIPAIMON;
	Mat *GINUMUID;

private:
	HBITMAP hGIMAP;
	HBITMAP hMAINMASK;
	HBITMAP hGIAVATAR;
	HBITMAP hGIAVATARMASK;
	HBITMAP hGISTAR;
	HBITMAP hGISTARMASK;
	HBITMAP *hGIOBJICON;
	HBITMAP *hGIOBJICONMASK;
	HBITMAP *hGIOBJFLAGICON;
	HBITMAP *hGIOBJFLAGICONMASK;
	HBITMAP *hGIPAIMON;
	HBITMAP *hGINUMUID;

	void loadGiMap();
	void loadMainMask();
	void loadGiAvatar();
	void loadGiAvatarMask();
	void loadGiStar();
	void loadGiStarMask();
	void loadGiPaimon();
	void loadGiObjIcon();
	void loadGiObjIconMask();
	void loadGiObjFlagIcon();
	void loadGiObjFlagIconMask();
	void loadGiNumUID();

	void loadFromResource();

	bool HBitmap2Mat(HBITMAP& _hBmp, cv::Mat& _mat);
	bool HBitmap2MatAlpha(HBITMAP& _hBmp, cv::Mat& _mat);
	bool Mat2MaskMat(Mat &in, Mat &out);

	QPixmap QImage2QPixmap(QImage &in);
	QImage QPixmap2QImage(QPixmap &in);
	Mat QImage2Mat(QImage &in);
	QImage Mat2QImage(Mat &in);
};


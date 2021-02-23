#pragma once
#include <thread>
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/xfeatures2d/cuda.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/imgproc/imgproc_c.h>
using namespace std;
using namespace cv;


class ATM_TM_SurfMap
{
	Mat _mapMat;
	Mat _minMapMat;

	int minHessian = 400;
	float ratio_thresh = 0.66f;

	Ptr<cv::xfeatures2d::SURF> detector, detectorSomeMap;
	std::vector<KeyPoint> Kp_MinMap, Kp_Map, Kp_SomeMap;
	Mat Dp_MinMap, Dp_Map, Dp_SomeMap;

	//static Point hisP[3];
	Point hisP[3];

	Point pos;
public:
	bool isInit = false;
	bool isContinuity = false;
	void setMap(Mat mapMat);
	void setMinMap(Mat minMapMat);

	void Init();
	void SURFMatch();
	Point SURFMatch(Mat minMapMat);
	Point getLocalPos();
	bool getIsContinuity();
private:
	double dis(Point &p);
};

class ATM_TM_TemplatePaimon
{
	Mat _paimonTemplate;
	Mat _paimonMat;
	bool isPaimonVisible = false;
public:
	void setPaimonTemplate(Mat paimonTemplateMat);
	void setPaimonMat(Mat paimonMat);
	void TemplatePaimon();
	bool getPaimonVisible();

};

class ATM_TM_ORBAvatar
{
	
	Mat _avatarTemplate;
	Mat _avatarMat;
	double rotationAngle = 0;

	Ptr<ORB> orb;
	vector<KeyPoint> Kp_Template, Kp_Avatar;
	Mat Dp_Template, Dp_Avatar;

public:
	bool isInit = false;

	void setAvatarTemplate(Mat avatarTemplateMat);
	void setAvatarMat(Mat avatarMat);
	void Init();
	void ORBMatch();
	double getRotationAngle();
};

class ATM_TM_TemplateMatch
{

};

class ATM_ThreadMatch
{
	Mat mapGray;
	Mat objMinMap;

	Mat templateAvatar;
	Mat objAvatar;

	Mat templatePaimon;
	Mat objPaimon;

	Mat objUID;



	ATM_TM_SurfMap surfMap;
	ATM_TM_TemplatePaimon tempPaimon;
	ATM_TM_ORBAvatar orbAvatar;
public:
	~ATM_ThreadMatch();

	Point pos;
	bool isPaimonVisial = false;
	bool isContinuity = false;
	double rotationAngle = 0;

	bool isExistObjMinMap = false;
	bool isExistObjPaimon = false;
	bool isExistObjUID = false;

	bool tIsEndSurfMapInit = false;
	bool tIsEndSurfMapMatch = false;
	bool tIsEndTemplatePaimonMatch = false;
	bool tIsEndOrbAvatarInit = false;
	bool tIsEndOrbAvatarMatch = false;

	thread * tSurfMapInit = nullptr;
	thread * tSurfMapMatch = nullptr;
	thread * tTemplatePaimonMatch = nullptr;
	thread * tOrbAvatarInit = nullptr;
	thread * tOrbAvatarMatch = nullptr;

	thread * tMatchStar = nullptr;
	thread * tMatchTarget = nullptr;

	void cThreadSurfMapInit(Mat &Map);
	void cThreadSurfMapMatch();
	void setSurfMap(Mat mapMat);

	void cThreadTemplatePaimonMatch(Mat &Template);
	void setTemplatePaimon(Mat TemplatePaimonMat);
	void setPaimon(Mat PaimonMat);

	void cThreadOrbAvatarInit(Mat &TemplatAvatar);
	void cThreadOrbAvatarMatch();
	void setAvatat(Mat AvatarMat);

	void getObjMinMap(Mat &obj);
	void getObjPaimon(Mat &obj);
	void getObjUID(Mat &obj);

	void CheckThread();

	void CheckThread_SurfMapInit();
	void thread_SurfMapInit(Mat& tar);

	void CheckThread_SurfMapMatch();
	void thread_SurfMapMatch(Mat& Obj);

	void CheckThread_TemplatePaimonMatch();
	void thread_TemplatePaimonMatch(Mat &Template, Mat& Obj);

	void CheckThread_OrbAvatarInit();
	void thread_OrbAvatarInit(Mat& tar);

	void CheckThread_OrbAvatarMatch();
	void thread_OrbAvatarMatch(Mat& Obj);

	void thread_MatchMap(Mat& tar, Mat& Obj);
	void thread_MatchStar(Mat& tar, Mat& Obj);
	void thread_MatchTarget(Mat& tar, Mat& Obj);

	void GetMatchResults();
};


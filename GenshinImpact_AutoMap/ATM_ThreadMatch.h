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

class ATM_TM_TemplateUID
{
	struct ATM_TM_Template_NumUID
	{
		Mat UID;
		Mat n[10];
		int max = 10;
	}giNumUID;

	Mat _uidMat;

	int _NumBit[9] = { 0 };
	int _uid = 0;

	int getMaxID(double lis[], int len);

public:
	bool isInit = false;

	void Init();
	void setUIDTemplate(Mat *uidTemplateMat);
	void setUIDMat(Mat uidMat);
	void TemplateUID();
	int getUID();
};

//class ATM_TM_Thread
//{
//	Mat workInput;
//	thread *tLoopWork = nullptr;
//	void(*ptr)(Mat &inMat) = nullptr;
//	bool isExitThread = false;
//	bool isExistFunction = false;
//	bool isRunWork = false;
//	bool isEndWork = false;
//
//	void run();
//
//public:
//	ATM_TM_Thread();
//	~ATM_TM_Thread();
//	ATM_TM_Thread(void(*funPtr)(Mat &inMat));
//	void setFunction(void(*funPtr)(Mat &inMat));
//
//	void start(Mat & inMat);
//	bool isEnd();
//};

class ATM_ThreadMatch
{
	Mat mapGray;
	Mat objMinMap;

	Mat templateAvatar;
	Mat objAvatar;

	Mat templatePaimon;
	Mat objPaimon;

	Mat *templateUID;
	Mat objUID;

	ATM_TM_SurfMap surfMap;
	ATM_TM_TemplatePaimon tempPaimon;
	ATM_TM_ORBAvatar orbAvatar;
	ATM_TM_TemplateUID tempUID;
	//ATM_TM_Thread tempUID;
public:
	~ATM_ThreadMatch();

	Point pos;
	bool isPaimonVisial = false;
	bool isContinuity = false;
	double rotationAngle = 0;
	int uid = 0;

	bool isExistObjMinMap = false;
	bool isExistObjPaimon = false;
	bool isExistObjUID = false;

	bool tIsEndSurfMapInit = false;
	bool tIsEndSurfMapMatch = false;
	bool tIsEndTemplatePaimonMatch = false;
	bool tIsEndOrbAvatarInit = false;
	bool tIsEndOrbAvatarMatch = false;
	bool tIsEndTemplateUIDInit = false;
	bool tIsEndTemplateUIDMatch = false;

	thread * tSurfMapInit = nullptr;
	thread * tSurfMapMatch = nullptr;
	thread * tTemplatePaimonMatch = nullptr;
	thread * tOrbAvatarInit = nullptr;
	thread * tOrbAvatarMatch = nullptr;	
	thread * tTemplateUIDInit = nullptr;
	thread * tTemplateUIDMatch = nullptr;

	//SURF Match Map
	void cThreadSurfMapInit(Mat &Map);
	void cThreadSurfMapMatch();
	void setSurfMap(Mat mapMat);

	//Template Match Paimon
	void cThreadTemplatePaimonMatch(Mat &Template);
	void setTemplatePaimon(Mat TemplatePaimonMat);
	void setPaimon(Mat PaimonMat);

	//ORB Match Avatar
	void cThreadOrbAvatarInit(Mat &TemplatAvatar);
	void cThreadOrbAvatarMatch();
	void setAvatat(Mat AvatarMat);

	//Template Match UID
	void cThreadTemplateUIDInit(Mat * TemplateUID);
	void cThreadTemplateUIDMatch();
	void setUID(Mat UIDMat);

	//Set Some Mat
	void getObjMinMap(Mat &obj);
	void getObjPaimon(Mat &obj);
	void getObjUID(Mat &obj);

	//Check Thread End
	void CheckThread();

	//SURF Init
	void CheckThread_SurfMapInit();
	void thread_SurfMapInit(Mat& tar);

	//SURF Match
	void CheckThread_SurfMapMatch();
	void thread_SurfMapMatch(Mat& Obj);

	//Template Match
	void CheckThread_TemplatePaimonMatch();
	void thread_TemplatePaimonMatch(Mat &Template, Mat& Obj);

	//ORB Init
	void CheckThread_OrbAvatarInit();
	void thread_OrbAvatarInit(Mat& tar);

	//ORB Match
	void CheckThread_OrbAvatarMatch();
	void thread_OrbAvatarMatch(Mat& Obj);

	//Template UID Init
	void CheckThread_TemplateUIDInit();
	void thread_TemplateUIDInit(Mat * tar);

	//Template UID Match
	void CheckThread_TemplateUIDMatch();
	void thread_TemplateUIDMatch(Mat& Obj);


	void GetMatchResults();
};


#pragma once
#include <thread>
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/xfeatures2d/cuda.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/core/cuda.hpp>

#include <opencv2/imgproc/imgproc_c.h>
using namespace std;
using namespace cv;


class ATM_TM_SurfMap
{
	Mat _mapMat;
	Mat _minMapMat;

	int minHessian = 400;
	float ratio_thresh = 0.66f;
	float mapScale = 1.3;//1.3;
	int someSizeR = 106;
	float MatchMatScale = 2.0;

	Ptr<cv::xfeatures2d::SURF> detector, detectorSomeMap;
	std::vector<KeyPoint> Kp_MinMap, Kp_Map, Kp_SomeMap;
	Mat Dp_MinMap, Dp_Map, Dp_SomeMap;

	//static Point hisP[3];
	Point hisP[3];

	Point pos;
public:
	ATM_TM_SurfMap();
	~ATM_TM_SurfMap();

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

class ATM_TM_TemplateStar
{
	Mat _starTemplate;
	Mat _starMat;
	bool isStarVisible = false;
	vector<Point> pos;
public:
	bool isInit = false;

	void Init();
	void setStarTemplate(Mat starTemplateMat);
	void setStarMat(Mat starMat);
	void TemplateStar();
	bool getStar();
	vector<Point> getStarPos();
};

//实现线程的单独控制
/*
应对两张图片匹配的过程
应对存在一张目标图像需要在给定源图像中匹配的场景
其中目标图像是固定的，需要使用时前初始化
*/
class ATM_TM_Thread
{
	Mat workInput;
	thread *tLoopWork = nullptr;
	void(*ptr)(Mat &inMat) = nullptr;
	bool isExitThread = false;
	bool isExistFunction = false;
	bool isRunWork = false;
	bool isEndWork = false;

	void run();

public:
	bool isInit = false;
	ATM_TM_Thread();
	~ATM_TM_Thread();
	ATM_TM_Thread(void(*funPtr)(Mat &inMat));
	void setFunction(void(*funPtr)(Mat &inMat));

	void start(Mat & inMat);
	bool isEnd();
};

class ATM_TM_Continuity
{
	bool continuity[3] = { false };
public:
	void setState(bool state);
	bool getIsContinuity();
};

class ATM_ThreadMatch
{
	Mat mapGray;
	Mat objMinMap;

	Mat templateAvatar;
	Mat objAvatar;

	Mat templatePaimon;
	Mat objPaimon;

	Mat templateStar;
	Mat objStar;

	Mat *templateUID;
	Mat objUID;

	ATM_TM_SurfMap surfMap;
	ATM_TM_TemplatePaimon tempPaimon;
	ATM_TM_ORBAvatar orbAvatar;
	ATM_TM_TemplateUID tempUID;
	ATM_TM_TemplateStar tempStar;
	//ATM_TM_Thread tempUID;
public:
	~ATM_ThreadMatch();
	ATM_TM_Continuity continuityState;
	Point pos = Point(1466, 3272);
	bool isPaimonVisial = false;
	bool isContinuity = false;
	double rotationAngle = 0;
	int uid = 0;
	bool isStarExist = false;
	bool isStarVisible = false;
	vector<Point> starPos;


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
	bool tIsEndTemplateStarInit = false;
	bool tIsEndTemplateStarMatch = false;

	thread * tSurfMapInit = nullptr;
	thread * tSurfMapMatch = nullptr;
	thread * tTemplatePaimonMatch = nullptr;
	thread * tOrbAvatarInit = nullptr;
	thread * tOrbAvatarMatch = nullptr;	
	thread * tTemplateUIDInit = nullptr;
	thread * tTemplateUIDMatch = nullptr;
	thread * tTemplateStarInit = nullptr;
	thread * tTemplateStarMatch = nullptr;

	//Init
	void cThreadInit();

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

	//Template Match Star
	void cThreadTemplateStarInit(Mat &TemplateStar);
	void cThreadTemplateStarMatch();
	void setTemplateStar(Mat TemplateStarMat);
	void setStar(Mat StarMat);

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

	//Template Star Init
	void CheckThread_TemplateStarInit();
	void thread_TemplateStarInit(Mat & tar);

	//Template Star Match
	void CheckThread_TemplateStarMatch();
	void thread_TemplateStarMatch(Mat& Obj);

	void GetMatchResults();
};


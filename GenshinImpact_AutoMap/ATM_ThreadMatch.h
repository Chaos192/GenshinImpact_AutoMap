#pragma once
#include <thread>
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/imgproc/imgproc_c.h>
using namespace std;
using namespace cv;


class ATM_TM_SurfMap
{
	bool isInit = false;
	Mat _mapMat;
	Mat _minMapMat;

	int minHessian = 400;
	float ratio_thresh = 0.66f;

	Ptr<cv::xfeatures2d::SURF> detector, detectorSomeMap;
	std::vector<KeyPoint> Kp_MinMap, Kp_Map, Kp_SomeMap;
	Mat Dp_MinMap, Dp_Map, Dp_SomeMap;

	//static Point hisP[3];

	Point pos;
public:
	void setMap(Mat mapMat);
	void setMinMap(Mat minMapMat);

	void Init();
	void SURFMatch();
	Point SURFMatch(Mat minMapMat);
	Point getLocalPos();
private:

	double dis(Point &p);
};


class ATM_TM_SurfMatch
{

};

class ATM_TM_TemplateMatch
{

};

class ATM_ThreadMatch
{
	Mat mapGray;

	Mat objMinMap;
	Mat objPaimon;
	Mat objUID;



	ATM_TM_SurfMap surfMap;
public:
	~ATM_ThreadMatch();

	Point pos;

	bool isExistObjMinMap = false;
	bool isExistObjPaimon = false;
	bool isExistObjUID = false;

	bool tIsEndSurfMapInit = false;
	bool tIsEndSurfMapMatch = false;
	bool tIsEndMap = false;
	bool tIsEndStar = false;
	bool tIsEndTarget = false;

	thread * tSurfMapInit = nullptr;
	thread * tSurfMapMatch = nullptr;
	thread * tMatchStar = nullptr;
	thread * tMatchTarget = nullptr;

	void cThreadSurfMapInit(Mat &Map);

	void cThreadSurfMapMatch();
	void setSurfMap(Mat mapMat);

	void getObjMinMap(Mat &obj);
	void getObjPaimon(Mat &obj);
	void getObjUID(Mat &obj);

	void CheckThread();

	void CheckThread_SurfMapInit();
	void thread_SurfMapInit(Mat& tar);
	void CheckThread_SurfMapMatch();
	void thread_SurfMapMatch(Mat& Obj);

	void thread_MatchMap(Mat& tar, Mat& Obj);
	void thread_MatchStar(Mat& tar, Mat& Obj);
	void thread_MatchTarget(Mat& tar, Mat& Obj);

	void GetMatchResults();


};


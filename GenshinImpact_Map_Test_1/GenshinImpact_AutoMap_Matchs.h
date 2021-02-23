#pragma once
#include<iostream>
#include<Windows.h>
#include<opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include<opencv2/xfeatures2d.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>

using namespace cv;
using namespace std;

class GenshinImpact_AutoMap_Matchs
{
public:
	GenshinImpact_AutoMap_Matchs();
	~GenshinImpact_AutoMap_Matchs();
public:
	GenshinImpact_AutoMap_Matchs(Mat _target);

public:
	void init();
	void setMode(int flag);

	//匹配对象，包含要匹配的的图像
	void setObject(Mat img);
	//匹配目标，在该图像中匹配
	void setTarget(Mat img);
	//UID区域
	void setRectUID(Mat img);

	void getKeyPoints();
	void onMatch();
	Point getLocation();

	void testSURF();
	void testSURF2();
	void test();
	void test2();
	void test3();
	void getUID();

	void testORB();
	bool keySave();
	bool keyLoad();

	void setCout(bool _isCout);

	bool getIsCanGet();
	bool getIsFindStar();
	Point getFindStar();

	bool isFinishMatchTarget = false;

	int UID = 0;
	//bool getIsFinishMatchTarget();
private:
	bool isGetUID = false;
	int uid = 0;
	bool isInit = false;
	bool isCout = false;
	bool isObjectExist = false;
	bool isTargetExist = false;
	bool isRectUIDExist = false;

	bool isFindStar = false;
	Point isStarPoint;

	Mat object;
	Mat target;
	Mat rectUID;
	//0:SURF
	int mode = 0;
	Point p;
	bool isCanGet = false;
	double t = 0;
	//int minHessian = 200;
	//float ratio_thresh = 0.7f;
	//Ptr<cv::xfeatures2d::SURF> detector;
	//std::vector<KeyPoint> keypoints_object;
	//std::vector<KeyPoint> keypoints_target;
	//Mat descriptors_object;
	//Mat descriptors_target;

	//vector<Point2d> off_obj;
	//vector<Point2d> off_sce;
	int minHessian = 400;
	float ratio_thresh = 0.66f;

	Ptr<cv::xfeatures2d::SURF> detector;
	Ptr<cv::xfeatures2d::SURF> detectorTmp;
	std::vector<KeyPoint> keypoints_object, keypoints_scene, keypoints_sceneTmp;
	Mat descriptors_object, descriptors_scene, descriptors_sceneTmp;

	Ptr<ORB> orb;
	vector<KeyPoint> keyPoints_tem, keyPoints_test;
	Mat descriptors_2, descriptors_test;
private:
	void getObjectKeyPoints();
	void getTargetKeyPoints();
};

typedef GenshinImpact_AutoMap_Matchs giAMM;

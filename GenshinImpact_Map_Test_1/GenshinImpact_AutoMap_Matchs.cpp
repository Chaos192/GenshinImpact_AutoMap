#include "GenshinImpact_AutoMap_Matchs.h"

GenshinImpact_AutoMap_Matchs::GenshinImpact_AutoMap_Matchs()
{
}

GenshinImpact_AutoMap_Matchs::~GenshinImpact_AutoMap_Matchs()
{
}

void GenshinImpact_AutoMap_Matchs::setMode(int flag)
{
	mode = flag;
}

void GenshinImpact_AutoMap_Matchs::setObject(Mat img)
{
	object = img;
	isObjectExist = true;
}

void GenshinImpact_AutoMap_Matchs::setTarget(Mat img)
{
	target = img;
	isTargetExist = true;
}

void GenshinImpact_AutoMap_Matchs::getKeyPoints()
{
	getObjectKeyPoints();
	getTargetKeyPoints();
}

void GenshinImpact_AutoMap_Matchs::onMatch()
{
}

Point GenshinImpact_AutoMap_Matchs::getLocation()
{
	return Point();
}

void GenshinImpact_AutoMap_Matchs::getObjectKeyPoints()
{

}

void GenshinImpact_AutoMap_Matchs::getTargetKeyPoints()
{
	if (!isTargetExist)return;
	switch (mode)
	{
	case 0:
	{
		detector = cv::xfeatures2d::SURF::create(minHessian);
		detector->detectAndCompute(target, noArray(), keypoints_target, descriptors_target);

		break;
	}
	default:
		break;
	}
}

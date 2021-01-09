#include "GenshinImpact_AutoMap_Matchs.h"

GenshinImpact_AutoMap_Matchs::GenshinImpact_AutoMap_Matchs()
{

}

GenshinImpact_AutoMap_Matchs::~GenshinImpact_AutoMap_Matchs()
{
}

GenshinImpact_AutoMap_Matchs::GenshinImpact_AutoMap_Matchs(Mat _target)
{
	target = _target;
	detector = cv::xfeatures2d::SURF::create(minHessian);

	detector->detectAndCompute(target, noArray(), keypoints_scene, descriptors_scene);
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
	return p;
}

void GenshinImpact_AutoMap_Matchs::test()
{
	Mat img_scene = target;
	Mat img_object = object;


	detector->detectAndCompute(img_object, noArray(), keypoints_object, descriptors_object);


	//-- Step 2: Matching descriptor vectors with a FLANN based matcher
	// Since SURF is a floating-point descriptor NORM_L2 is used
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
	std::vector< std::vector<DMatch> > knn_matches;
	matcher->knnMatch(descriptors_object, descriptors_scene, knn_matches, 2);



	//-- Filter matches using the Lowe's ratio test
	//const float ratio_thresh = 0.8f;
	std::vector<DMatch> good_matches;
	for (size_t i = 0; i < knn_matches.size(); i++)
	{
		if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
		{
			good_matches.push_back(knn_matches[i][0]);

		}
	}
	int k = good_matches.size();
	static double x = 0;
	static double y = 0;
	for (size_t i = 0; i < k; i++)
	{
		//size/2-obj+sce
		if (i == 0) 
		{
			x = 0;
			y = 0;
		}
		x = x + (92.5 - keypoints_object[good_matches[i].queryIdx].pt.x + keypoints_scene[good_matches[i].trainIdx].pt.x) / k;
		y = y + (92.5 - keypoints_object[good_matches[i].queryIdx].pt.y + keypoints_scene[good_matches[i].trainIdx].pt.y) / k;
	}
	
	p = Point(x, y);
	//-- Draw matches

	//Mat img_matches;
	//drawMatches(img_object, keypoints_object, target, keypoints_scene, good_matches, img_matches, Scalar::all(-1),
	//	Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	//namedWindow("1", WINDOW_FREERATIO);
	//imshow("1", img_matches);
}

void GenshinImpact_AutoMap_Matchs::test()
{
	Mat img_scene = target;
	Mat img_object = object;


	detector->detectAndCompute(img_object, noArray(), keypoints_object, descriptors_object);


	//-- Step 2: Matching descriptor vectors with a FLANN based matcher
	// Since SURF is a floating-point descriptor NORM_L2 is used
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
	std::vector< std::vector<DMatch> > knn_matches;
	matcher->knnMatch(descriptors_object, descriptors_scene, knn_matches, 2);



	//-- Filter matches using the Lowe's ratio test
	//const float ratio_thresh = 0.8f;
	std::vector<DMatch> good_matches;
	for (size_t i = 0; i < knn_matches.size(); i++)
	{
		if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
		{
			good_matches.push_back(knn_matches[i][0]);
		}
	}

	//-- Draw matches
	Mat img_matches;
	drawMatches(img_object, keypoints_object, target, keypoints_scene, good_matches, img_matches, Scalar::all(-1),
		Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	namedWindow("1", WINDOW_FREERATIO);
	imshow("1", img_matches);
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
		//detector->detectAndCompute(target, noArray(), keypoints_target, descriptors_target);

		break;
	}
	default:
		break;
	}
}

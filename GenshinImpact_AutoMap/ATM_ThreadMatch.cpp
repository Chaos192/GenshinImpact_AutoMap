#include "ATM_ThreadMatch.h"

ATM_ThreadMatch::~ATM_ThreadMatch()
{
	if (tSurfMapInit != nullptr)
	{
		tSurfMapInit->join();
		delete tSurfMapInit;
	}
	if (tSurfMapMatch != nullptr)
	{
		tSurfMapMatch->join();
		delete tSurfMapMatch;
	}
	if (tTemplatePaimonMatch != nullptr)
	{
		tTemplatePaimonMatch->join();
		delete tTemplatePaimonMatch;
	}
	if (tOrbAvatarInit != nullptr)
	{
		tOrbAvatarInit->join();
		delete tOrbAvatarInit;
	}
	if (tOrbAvatarMatch != nullptr)
	{
		tOrbAvatarMatch->join();
		delete tOrbAvatarMatch;
	}

	if (tMatchStar != nullptr)
	{
		tMatchStar->join();
		delete tMatchStar;
	}
	if (tMatchTarget != nullptr)
	{
		tMatchTarget->join();
		delete tMatchTarget;
	}
}

void ATM_ThreadMatch::cThreadSurfMapInit(Mat &Map)
{
	if (tSurfMapInit == nullptr && surfMap.isInit == false)
	{
		cvtColor(Map, mapGray, CV_RGB2GRAY);

		tSurfMapInit = new thread(&ATM_ThreadMatch::thread_SurfMapInit, this, ref(mapGray));
		tIsEndSurfMapInit = false;
	}
}

void ATM_ThreadMatch::cThreadSurfMapMatch()
{
	if (tSurfMapMatch == nullptr && tIsEndSurfMapInit && isExistObjMinMap && isPaimonVisial)
	{
		tSurfMapMatch = new thread(&ATM_ThreadMatch::thread_SurfMapMatch, this, ref(objMinMap));
		tIsEndSurfMapMatch = false;
	}
}

void ATM_ThreadMatch::setSurfMap(Mat mapMat)
{
	surfMap.setMap(mapMat);
}

void ATM_ThreadMatch::cThreadTemplatePaimonMatch(Mat & Template)
{
	if (tTemplatePaimonMatch == nullptr && isExistObjPaimon)
	{
		cvtColor(Template, templatePaimon, CV_RGB2GRAY);
		tTemplatePaimonMatch = new thread(&ATM_ThreadMatch::thread_TemplatePaimonMatch, this, ref(templatePaimon), ref(objPaimon));
		tIsEndTemplatePaimonMatch = false;
	}
}

void ATM_ThreadMatch::setTemplatePaimon(Mat TemplatePaimonMat)
{
	TemplatePaimonMat.copyTo(templatePaimon);
}

void ATM_ThreadMatch::setPaimon(Mat PaimonMat)
{
	PaimonMat.copyTo(objPaimon);
}

void ATM_ThreadMatch::cThreadOrbAvatarInit(Mat & TemplatAvatar)
{
	if (tOrbAvatarInit == nullptr && orbAvatar.isInit == false)
	{
		cvtColor(TemplatAvatar, templateAvatar, CV_RGB2GRAY);
		resize(templateAvatar, templateAvatar, Size(150, 150), 0, 0, INTER_LANCZOS4);//INTER_CUBIC INTER_AREAz
		tOrbAvatarInit = new thread(&ATM_ThreadMatch::thread_OrbAvatarInit, this, ref(templateAvatar));
		tIsEndOrbAvatarInit = false;
	}
}

void ATM_ThreadMatch::cThreadOrbAvatarMatch()
{
	if (tOrbAvatarMatch == nullptr && tIsEndOrbAvatarInit && isExistObjMinMap && isPaimonVisial)
	{
		resize(objAvatar, objAvatar, Size(150, 150), 0, 0, INTER_LANCZOS4);//INTER_CUBIC INTER_AREAz
		tOrbAvatarMatch = new thread(&ATM_ThreadMatch::thread_OrbAvatarMatch, this, ref(objAvatar));
		tIsEndOrbAvatarMatch = false;
	}
}

void ATM_ThreadMatch::setAvatat(Mat AvatarMat)
{
	AvatarMat.copyTo(objAvatar);
}

void ATM_ThreadMatch::getObjMinMap(Mat & obj)
{
	obj.copyTo(objMinMap);
	obj(Rect(obj.cols / 2 - 24, obj.rows / 2 - 24, 48, 48)).copyTo(objAvatar);
	isExistObjMinMap = true;
}

void ATM_ThreadMatch::getObjPaimon(Mat & obj)
{
	obj.copyTo(objPaimon);
	isExistObjPaimon = true;
}

void ATM_ThreadMatch::getObjUID(Mat & obj)
{
	obj.copyTo(objUID);
	isExistObjUID = true;
}

void ATM_ThreadMatch::CheckThread()
{
	if (tIsEndSurfMapInit == false)
	{
		CheckThread_SurfMapInit();
	}
	if (tIsEndSurfMapMatch == false)
	{
		CheckThread_SurfMapMatch();
	}
	if (tIsEndTemplatePaimonMatch == false)
	{
		CheckThread_TemplatePaimonMatch();
	}
	if (tIsEndOrbAvatarInit == false)
	{
		CheckThread_OrbAvatarInit();
	}
	if (tIsEndOrbAvatarMatch == false)
	{
		CheckThread_OrbAvatarMatch();
	}
}

void ATM_ThreadMatch::CheckThread_SurfMapInit()
{
	DWORD exitCode;
	if (tSurfMapInit != nullptr)
	{
		GetExitCodeThread(tSurfMapInit->native_handle(), &exitCode);
		if (exitCode == 0)
		{
			tSurfMapInit->join();
			delete tSurfMapInit;
			tSurfMapInit = nullptr;
			tIsEndSurfMapInit = true;
		}
	}
}

void ATM_ThreadMatch::thread_SurfMapInit(Mat & tar)
{
	surfMap.setMap(tar);
	surfMap.Init();
}

void ATM_ThreadMatch::CheckThread_SurfMapMatch()
{
	DWORD exitCode;
	if (tSurfMapMatch != nullptr)
	{
		GetExitCodeThread(tSurfMapMatch->native_handle(), &exitCode);
		if (exitCode == 0)
		{
			tSurfMapMatch->join();
			delete tSurfMapMatch;
			tSurfMapMatch = nullptr;
			tIsEndSurfMapMatch = true;
		}
	}
}

void ATM_ThreadMatch::thread_SurfMapMatch(Mat & Obj)
{
	//surfMap.setMinMap(Obj);
	if (isExistObjMinMap)
	{
		//surfMap.setMinMap(objMinMap);
		surfMap.setMinMap(Obj);
		surfMap.SURFMatch();
	}
}

void ATM_ThreadMatch::CheckThread_TemplatePaimonMatch()
{
	DWORD exitCode;
	if (tTemplatePaimonMatch != nullptr)
	{
		GetExitCodeThread(tTemplatePaimonMatch->native_handle(), &exitCode);
		if (exitCode == 0)
		{
			tTemplatePaimonMatch->join();
			delete tTemplatePaimonMatch;
			tTemplatePaimonMatch = nullptr;
			tIsEndTemplatePaimonMatch = true;
		}
	}
}

void ATM_ThreadMatch::thread_TemplatePaimonMatch(Mat &Template, Mat & Obj)
{
	if (isExistObjPaimon)
	{
		tempPaimon.setPaimonTemplate(Template);
		tempPaimon.setPaimonMat(Obj);
		tempPaimon.TemplatePaimon();
	}
}

void ATM_ThreadMatch::CheckThread_OrbAvatarInit()
{
	DWORD exitCode;
	if (tOrbAvatarInit != nullptr)
	{
		GetExitCodeThread(tOrbAvatarInit->native_handle(), &exitCode);
		if (exitCode == 0)
		{
			tOrbAvatarInit->join();
			delete tOrbAvatarInit;
			tOrbAvatarInit = nullptr;
			tIsEndOrbAvatarInit = true;
		}
	}
}

void ATM_ThreadMatch::thread_OrbAvatarInit(Mat & tar)
{
	orbAvatar.setAvatarTemplate(templateAvatar);
	orbAvatar.Init();
}

void ATM_ThreadMatch::CheckThread_OrbAvatarMatch()
{
	DWORD exitCode;
	if (tOrbAvatarMatch != nullptr)
	{
		GetExitCodeThread(tOrbAvatarMatch->native_handle(), &exitCode);
		if (exitCode == 0)
		{
			tOrbAvatarMatch->join();
			delete tOrbAvatarMatch;
			tOrbAvatarMatch = nullptr;
			tIsEndOrbAvatarMatch = true;
		}
	}
}

void ATM_ThreadMatch::thread_OrbAvatarMatch(Mat & Obj)
{
	if (isExistObjMinMap)
	{
		orbAvatar.setAvatarMat(Obj);
		orbAvatar.ORBMatch();
	}
}

void ATM_ThreadMatch::thread_MatchMap(Mat & tar, Mat & Obj)
{
}

void ATM_ThreadMatch::thread_MatchStar(Mat & tar, Mat & Obj)
{
}

void ATM_ThreadMatch::thread_MatchTarget(Mat & tar, Mat & Obj)
{
}

void ATM_ThreadMatch::GetMatchResults()
{
	pos = surfMap.getLocalPos();
	isContinuity = surfMap.getIsContinuity();
	isPaimonVisial = tempPaimon.getPaimonVisible();
	rotationAngle = orbAvatar.getRotationAngle();
}

void ATM_TM_SurfMap::setMap(Mat mapMat)
{
	_mapMat = mapMat;
}

void ATM_TM_SurfMap::setMinMap(Mat minMapMat)
{
	_minMapMat = minMapMat;
}

void ATM_TM_SurfMap::Init()
{
	if (isInit)return;
	detector = cv::xfeatures2d::SURF::create(minHessian);
	detector->detectAndCompute(_mapMat, noArray(), Kp_Map, Dp_Map);
	isInit = true;
}

void ATM_TM_SurfMap::SURFMatch()
{
	//static Point hisP[3];

	Mat img_scene(_mapMat);
	Mat img_object(_minMapMat);

	isContinuity = false;

	if ((dis(hisP[1] - hisP[0]) + dis(hisP[2] - hisP[1])) < 2000)
	{
		if (hisP[2].x > 150 && hisP[2].x < img_scene.cols - 150 && hisP[2].y>150 && hisP[2].y < img_scene.rows - 150)
		{
			isContinuity = true;
			if (isContinuity)
			{
				Mat someMap(img_scene(Rect(hisP[2].x - 150, hisP[2].y - 150, 300, 300)));
				detectorSomeMap = cv::xfeatures2d::SURF::create(minHessian);
				detectorSomeMap->detectAndCompute(someMap, noArray(), Kp_SomeMap, Dp_SomeMap);
				detectorSomeMap->detectAndCompute(img_object, noArray(), Kp_MinMap, Dp_MinMap);
				Ptr<DescriptorMatcher> matcherTmp = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
				std::vector< std::vector<DMatch> > KNN_mTmp;
				//std::vector<DMatch> good_matchesTmp;
				matcherTmp->knnMatch(Dp_MinMap, Dp_SomeMap, KNN_mTmp, 2);
				std::vector<double> lisx;
				std::vector<double> lisy;
				double sumx = 0;
				double sumy = 0;
				for (size_t i = 0; i < KNN_mTmp.size(); i++)
				{
					if (KNN_mTmp[i][0].distance < ratio_thresh * KNN_mTmp[i][1].distance)
					{
						//good_matchesTmp.push_back(KNN_mTmp[i][0]);
						lisx.push_back(((img_object.cols / 2 - Kp_MinMap[KNN_mTmp[i][0].queryIdx].pt.x)*1.3 + Kp_SomeMap[KNN_mTmp[i][0].trainIdx].pt.x));
						lisy.push_back(((img_object.rows / 2 - Kp_MinMap[KNN_mTmp[i][0].queryIdx].pt.y)*1.3 + Kp_SomeMap[KNN_mTmp[i][0].trainIdx].pt.y));
						sumx += lisx.back();
						sumy += lisy.back();
					}
				}

				if (min(lisx.size(), lisy.size()) < 2)
				{
					isContinuity = false;
				}

				double meanx = sumx / lisx.size(); //均值
				double meany = sumy / lisy.size(); //均值
				int x = (int)meanx;
				int y = (int)meany;
				pos = Point(x + hisP[2].x - 150, y + hisP[2].y - 150);

			}
		}
	}
	if (!isContinuity)
	{
		detector->detectAndCompute(img_object, noArray(), Kp_MinMap, Dp_MinMap);
		Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
		std::vector< std::vector<DMatch> > KNN_m;
		//std::vector<DMatch> good_matches;
		matcher->knnMatch(Dp_MinMap, Dp_Map, KNN_m, 2);

		std::vector<double> lisx;
		std::vector<double> lisy;
		double sumx = 0;
		double sumy = 0;
		for (size_t i = 0; i < KNN_m.size(); i++)
		{
			if (KNN_m[i][0].distance < ratio_thresh * KNN_m[i][1].distance)
			{
				//good_matches.push_back(KNN_m[i][0]);
				lisx.push_back(((img_object.cols / 2 - Kp_MinMap[KNN_m[i][0].queryIdx].pt.x)*1.3 + Kp_Map[KNN_m[i][0].trainIdx].pt.x));
				lisy.push_back(((img_object.rows / 2 - Kp_MinMap[KNN_m[i][0].queryIdx].pt.y)*1.3 + Kp_Map[KNN_m[i][0].trainIdx].pt.y));
				sumx += lisx.back();
				sumy += lisy.back();
			}
		}
		if (min(lisx.size(), lisy.size()) == 0)
		{
			cout << "SURF Match Fail" << endl;
			return;
		}
		cout << "SURF Match Point Number: " << lisx.size() << "," << lisy.size() << endl;


		double meanx = sumx / lisx.size(); //均值
		double meany = sumy / lisy.size(); //均值
		int x = (int)meanx;
		int y = (int)meany;
		if (min(lisx.size(), lisy.size()) > 15)
		{
			double accumx = 0.0;
			double accumy = 0.0;
			for (int i = 0; i < min(lisx.size(), lisy.size()); i++)
			{
				accumx += (lisx[i] - meanx)*(lisx[i] - meanx);
				accumy += (lisy[i] - meany)*(lisy[i] - meany);
			}

			double stdevx = sqrt(accumx / (lisx.size() - 1)); //标准差
			double stdevy = sqrt(accumy / (lisy.size() - 1)); //标准差

			sumx = 0;
			sumy = 0;
			int numx = 0;
			int numy = 0;
			for (int i = 0; i < min(lisx.size(), lisy.size()); i++)
			{
				if (abs(lisx[i] - meanx) < 3 * stdevx)
				{
					sumx += lisx[i];
					numx++;
				}
				if (abs(lisy[i] - meany) < 3 * stdevy)
				{
					sumy += lisy[i];
					numy++;
				}
			}
			int x = (int)(sumx / numx);
			int y = (int)(sumy / numy);
			pos = Point(x, y);
		}
		else
		{
			pos = Point(x, y);
		}
	}

	hisP[0] = hisP[1];
	hisP[1] = hisP[2];
	hisP[2] = pos;
}

Point ATM_TM_SurfMap::SURFMatch(Mat minMapMat)
{
	return Point();
}

Point ATM_TM_SurfMap::getLocalPos()
{
	return pos;
}

bool ATM_TM_SurfMap::getIsContinuity()
{
	return isContinuity;
}

double ATM_TM_SurfMap::dis(Point & p)
{
	return sqrt(p.x*p.x + p.y*p.y);
}

void ATM_TM_TemplatePaimon::setPaimonTemplate(Mat paimonTemplateMat)
{
	_paimonTemplate = paimonTemplateMat;
}

void ATM_TM_TemplatePaimon::setPaimonMat(Mat paimonMat)
{
	_paimonMat = paimonMat;
}

void ATM_TM_TemplatePaimon::TemplatePaimon()
{
	Mat tmp;
	cv::matchTemplate(_paimonTemplate, _paimonMat, tmp, cv::TM_CCOEFF_NORMED);

	double minVal, maxVal;
	cv::Point minLoc, maxLoc;
	//寻找最佳匹配位置
	cv::minMaxLoc(tmp, &minVal, &maxVal, &minLoc, &maxLoc);
	cout <<"Match Template MinVal & MaxVal" <<minVal << " , "<< maxVal<<endl;
	if (minVal < 0.51 || maxVal == 1)
	{
		isPaimonVisible = false;

	}
	else
	{
		isPaimonVisible = true;
	}
}

bool ATM_TM_TemplatePaimon::getPaimonVisible()
{
	return isPaimonVisible;
}

void ATM_TM_ORBAvatar::setAvatarTemplate(Mat avatarTemplateMat)
{
	_avatarTemplate = avatarTemplateMat;
}

void ATM_TM_ORBAvatar::setAvatarMat(Mat avatarMat)
{
	_avatarMat = avatarMat;
}

void ATM_TM_ORBAvatar::Init()
{
	if (isInit)return;
	orb = ORB::create();//(36, 1.2, 3, 31, 0, 2, ORB::HARRIS_SCORE);
	orb->detectAndCompute(_avatarTemplate, Mat(), Kp_Template, Dp_Template, false);
	isInit = true;
}

bool GreaterSort(DMatch a, DMatch b)
{
	return (a.distance > b.distance);
}

void ATM_TM_ORBAvatar::ORBMatch()
{
	orb->detectAndCompute(_avatarMat, Mat(), Kp_Avatar, Dp_Avatar, false);

	//BruteForceMatcher<HammingLUT> matcher;
	//vector<DMatch> matches;
	//matcher.match(Dp_Template, Dp_Avatar, matches);

	//特征匹配是通过使用合适的相似度度量比较特征描述子来执行的。
   //定义特征描述子匹配器
	//Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::MatcherType::BRUTEFORCE);
	////参数MatcherType：匹配器类型，这里使用MatcherType::BRUTEFORCE（暴力匹配算法）

	//vector<DMatch> matches;
	////通过描述子匹配器，对两幅图像的描述子进行匹配，也就是将两幅图像中的对应特征点进行匹配；输出的是一个DMatch结构体向量，其每一个DMatch结构体包含一组对应特征点的信息。
	//matcher->match(Dp_Template, Dp_Avatar, matches);

	//double max_dist = 0; double min_dist = 1000;
	////-- Quick calculation of max and min distances between keypoints     
	//for (int i = 0; i < Dp_Template.rows; i++)
	//{
	//	double dist = matches[i].distance;
	//	if (dist < min_dist) min_dist = dist;
	//	if (dist > max_dist) max_dist = dist;
	//}
	//printf("-- Max dist : %f \n", max_dist);
	//printf("-- Min dist : %f \n", min_dist);
	////-- Draw only "good" matches (i.e. whose distance is less than 0.6*max_dist )     
	////-- PS.- radiusMatch can also be used here.     
	//std::vector< DMatch > good_matches;
	//for (int i = 0; i < Dp_Template.rows; i++)
	//{
	//	if (matches[i].distance < 0.6*max_dist)
	//	{
	//		good_matches.push_back(matches[i]);
	//	}
	//}

	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
	std::vector< std::vector<DMatch> > KNN_m;
	vector<DMatch> KNN_m2;
	std::vector<DMatch> good_matches;
	matcher->knnMatch(Dp_Template, Dp_Avatar, KNN_m,1);

	double max_dist = 0; double min_dist = 1000;
	std::vector<double> angle;
	//-- Quick calculation of max and min distances between keypoints     
	for (int i = 0; i < Dp_Template.rows; i++)
	{
		double dist = KNN_m[i][0].distance;
		KNN_m2.push_back( KNN_m[i][0]);
		
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	sort(KNN_m2.begin(), KNN_m2.end(), GreaterSort);

	double res = 0;
	for (size_t i = 0; i < KNN_m.size(); i++)
	{
		if (KNN_m[i][0].distance < 0.66 * max_dist)
		{
			good_matches.push_back(KNN_m[i][0]);
			angle.push_back(Kp_Avatar[KNN_m[i][0].trainIdx].angle - Kp_Template[KNN_m[i][0].queryIdx].angle);
			res =res+ angle[angle.size()-1];
		}
	}

	Mat img_matches;
	drawMatches(_avatarTemplate, Kp_Template, _avatarMat, Kp_Avatar,
		good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
		vector<char>());
	if (good_matches.size() != 0)
	{
		rotationAngle = -res/ good_matches.size();
	}
	
}

double ATM_TM_ORBAvatar::getRotationAngle()
{
	return rotationAngle;
}

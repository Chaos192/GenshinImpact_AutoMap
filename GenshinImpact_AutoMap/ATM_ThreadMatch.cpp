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
	if (tTemplateUIDInit != nullptr)
	{
		tTemplateUIDInit->join();
		delete tTemplateUIDInit;
	}
	if (tTemplateUIDMatch != nullptr)
	{
		tTemplateUIDMatch->join();
		delete tTemplateUIDMatch;
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

void ATM_ThreadMatch::cThreadTemplateUIDInit(Mat * TemplateUID)
{
	if (tTemplateUIDInit == nullptr && tempUID.isInit == false)
	{
		templateUID = TemplateUID;
		tTemplateUIDInit = new thread(&ATM_ThreadMatch::thread_TemplateUIDInit, this, templateUID);
		tIsEndTemplateUIDInit = false;
	}
}

void ATM_ThreadMatch::cThreadTemplateUIDMatch()
{
	if (tTemplateUIDMatch == nullptr && isExistObjUID)
	{
		tTemplateUIDMatch = new thread(&ATM_ThreadMatch::thread_TemplateUIDMatch, this, ref(objUID));
		tIsEndTemplateUIDMatch = false;
	}
}

void ATM_ThreadMatch::setUID(Mat UIDMat)
{
	UIDMat.copyTo(objUID);
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
	if (tIsEndTemplateUIDInit == false)
	{
		CheckThread_TemplateUIDInit();
	}
	if (tIsEndTemplateUIDMatch == false)
	{
		CheckThread_TemplateUIDMatch();
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

void ATM_ThreadMatch::CheckThread_TemplateUIDInit()
{
	DWORD exitCode;
	if (tTemplateUIDInit != nullptr)
	{
		GetExitCodeThread(tTemplateUIDInit->native_handle(), &exitCode);
		if (exitCode == 0)
		{
			tTemplateUIDInit->join();
			delete tTemplateUIDInit;
			tTemplateUIDInit = nullptr;
			tIsEndTemplateUIDInit = true;
		}
	}
}

void ATM_ThreadMatch::thread_TemplateUIDInit(Mat * tar)
{
	tempUID.setUIDTemplate(tar);
	tempUID.Init();
}

void ATM_ThreadMatch::CheckThread_TemplateUIDMatch()
{
	DWORD exitCode;
	if (tTemplateUIDMatch != nullptr)
	{
		GetExitCodeThread(tTemplateUIDMatch->native_handle(), &exitCode);
		if (exitCode == 0)
		{
			tTemplateUIDMatch->join();
			delete tTemplateUIDMatch;
			tTemplateUIDMatch = nullptr;
			tIsEndTemplateUIDMatch = true;
		}
	}
}

void ATM_ThreadMatch::thread_TemplateUIDMatch(Mat & Obj)
{
	if (isExistObjUID)
	{
		//surfMap.setMinMap(objMinMap);
		tempUID.setUIDMat(Obj);
		tempUID.TemplateUID();
	}
}

void ATM_ThreadMatch::GetMatchResults()
{
	if (tIsEndSurfMapMatch)
	{
		if (surfMap.getLocalPos().x > 0 && surfMap.getLocalPos().y > 0)
		{
			pos = surfMap.getLocalPos();
		}
	}
	if (tIsEndSurfMapMatch)
	{
		isContinuity = surfMap.getIsContinuity();
	}	
	if (tIsEndTemplatePaimonMatch)
	{
		isPaimonVisial = tempPaimon.getPaimonVisible();
	}	
	if (tIsEndOrbAvatarMatch)
	{
		rotationAngle = orbAvatar.getRotationAngle();
	}	
	if (tIsEndTemplateUIDMatch)
	{
		uid = tempUID.getUID();
	}
}

ATM_TM_SurfMap::ATM_TM_SurfMap()
{
	hisP[0] = Point();
	hisP[1] = Point();
	hisP[2] = Point();
}

ATM_TM_SurfMap::~ATM_TM_SurfMap()
{
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

				if (min(lisx.size(), lisy.size()) <= 2)
				{
					isContinuity = false;
				}
				else
				{
					double meanx = sumx / lisx.size(); //均值
					double meany = sumy / lisy.size(); //均值
					int x = (int)meanx;
					int y = (int)meany;
					pos = Point(x + hisP[2].x - 150, y + hisP[2].y - 150);
				}
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
		else
		{
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
	if(Kp_Avatar.size()==0)
	{
		return;
	}
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

//void ATM_TM_Thread::run()
//{
//	while (isExitThread == false)
//	{
//		if (isRunWork && (*ptr) != nullptr)
//		{
//			ptr(workInput);
//			isRunWork = false;
//			isEndWork = true;
//		}
//		else
//		{
//			std::this_thread::sleep_for(std::chrono::milliseconds(1));
//		}
//	}
//}
//
//ATM_TM_Thread::ATM_TM_Thread()
//{
//	tLoopWork = new thread(&ATM_TM_Thread::run, this);
//}
//
//ATM_TM_Thread::~ATM_TM_Thread()
//{
//	if (tLoopWork != nullptr)
//	{
//		isExitThread = true;
//		tLoopWork->join();
//		delete tLoopWork;
//	}
//}
//
//ATM_TM_Thread::ATM_TM_Thread(void(*funPtr)(Mat &inMat))
//{
//	setFunction(funPtr);
//	tLoopWork = new thread(&ATM_TM_Thread::run, this);
//}
//
//void ATM_TM_Thread::setFunction(void(*funPtr)(Mat &inMat))
//{
//	ptr = funPtr;
//	isExistFunction = true;
//}
//
//void ATM_TM_Thread::start(Mat & inMat)
//{
//	if (isExistFunction == false)
//	{
//		throw"Not Found Work Function";
//	}
//	workInput = inMat;
//	isRunWork = true;
//	isEndWork = false;
//}
//
//bool ATM_TM_Thread::isEnd()
//{
//	return isEndWork;
//}

int ATM_TM_TemplateUID::getMaxID(double lis[], int len)
{
	int maxId = 0;
	for (int i = 1; i < len; i++)
	{
		if (lis[i] > lis[maxId])
		{
			maxId = i;
		}
	}
	return maxId;
}

void ATM_TM_TemplateUID::Init()
{
	if (isInit)return;

	isInit = true;
}

void ATM_TM_TemplateUID::setUIDTemplate(Mat * uidTemplateMat)
{
	for (int i = 0; i < 10; i++)
	{
		uidTemplateMat[i].copyTo(giNumUID.n[i]);
	}
	uidTemplateMat[10].copyTo(giNumUID.UID);

}

void ATM_TM_TemplateUID::setUIDMat(Mat uidMat)
{
	if (uidMat.channels() == 4)
	{
		uidMat.copyTo(_uidMat);
	}
	else
	{
		cvtColor(uidMat, _uidMat, CV_RGB2RGBA);
	}
	
}

void ATM_TM_TemplateUID::TemplateUID()
{
	int bitCount = 1;
	Mat tmp;
	Mat checkUID = giNumUID.UID;
	Mat Roi(_uidMat);

	cv::matchTemplate(Roi, checkUID, tmp, cv::TM_CCOEFF_NORMED);

	double minVal, maxVal;
	cv::Point minLoc, maxLoc;
	//寻找最佳匹配位置
	cv::minMaxLoc(tmp, &minVal, &maxVal, &minLoc, &maxLoc);
	if (maxVal > 0.75)
	{
		int x = maxLoc.x + checkUID.cols + 7;
		int y = 0;
		double tmplis[10] = { 0 };
		int tmplisx[10] = { 0 };
		for (int p = 8; p >= 0; p--)
		{
			_NumBit[p] = 0;
 			for (int i = 0; i < giNumUID.max; i++)
			{
				Rect r(x, y, giNumUID.n[i].cols + 2, giNumUID.n[i].rows);//180-46/9->140/9->16->16*9=90+54=144
				if (x + r.width > _uidMat.cols)
				{
					r = Rect(_uidMat.cols - giNumUID.n[i].cols - 2, 0, giNumUID.n[i].cols + 2, giNumUID.n[i].rows);
				}

				Mat numCheckUID = giNumUID.n[i];
				Roi = _uidMat(r);

				cv::matchTemplate(Roi, numCheckUID, tmp, cv::TM_CCOEFF_NORMED);

				double minVali, maxVali;
				cv::Point minLoci, maxLoci;
				//寻找最佳匹配位置
				cv::minMaxLoc(tmp, &minVali, &maxVali, &minLoci, &maxLoci);

				tmplis[i] = maxVali;
				tmplisx[i] = maxLoci.x + numCheckUID.cols - 1;
				if (maxVali > 0.85)
				{
					_NumBit[p] = i;
					x = x + maxLoci.x + numCheckUID.cols - 1;
					break;
				}
				if (i == giNumUID.max - 1)
				{
					_NumBit[p] = getMaxID(tmplis, 10);
					x = x + tmplisx[_NumBit[p]];
				}
			}
			//if (p == 0)
			//{
			//	break;
			//}

		}
	}
	_uid = 0;
	for (int i = 0; i < 9; i++)
	{
		_uid += _NumBit[i] * bitCount;
		bitCount = bitCount * 10;
	}

}

int ATM_TM_TemplateUID::getUID()
{
	return _uid;
}

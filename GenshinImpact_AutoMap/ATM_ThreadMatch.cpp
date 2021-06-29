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

void ATM_ThreadMatch::cThreadInit()
{
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

void ATM_ThreadMatch::cThreadOrbAvatarInit(Mat & TemplateAvatar)
{
	if (tOrbAvatarInit == nullptr && orbAvatar.isInit == false)
	{
		//templateAvatar = Mat(300, 300, CV_8UC1,Scalar(0,0,0));
		//cvtColor(TemplateAvatar(Rect(TemplateAvatar.cols/2-16, TemplateAvatar.rows/2-16,32,32)), templateAvatar(Rect(134,134,32,32)), CV_RGB2GRAY);
		//threshold(templateAvatar, templateAvatar, 185, 255, THRESH_TOZERO);
		////resize(templateAvatar, templateAvatar, Size(0, 0), 1, 1, 3);//INTER_CUBIC INTER_AREAz
		resize(TemplateAvatar, templateAvatar, Size(150, 150), 0, 0, INTER_LANCZOS4);//INTER_CUBIC INTER_AREAz
		tOrbAvatarInit = new thread(&ATM_ThreadMatch::thread_OrbAvatarInit, this, ref(templateAvatar));
		tIsEndOrbAvatarInit = false;
	}
}

void ATM_ThreadMatch::cThreadOrbAvatarMatch()
{
	if (tOrbAvatarMatch == nullptr && tIsEndOrbAvatarInit && isExistObjMinMap && isPaimonVisial)
	{
		//Mat temp = Mat(300, 300, CV_8UC1, Scalar(0, 0, 0));
		//objAvatar.copyTo(temp(Rect(138, 138, 24, 24)));
		//objAvatar = temp;
		//threshold(objAvatar, objAvatar, 185, 255, THRESH_TOZERO);
		////resize(objAvatar, objAvatar, Size(0, 0), 1*1.3, 1*1.3, 3);//INTER_CUBIC INTER_AREAz

		//resize(objAvatar, objAvatar, Size(150, 150), 0, 0, INTER_LANCZOS4);//INTER_CUBIC INTER_AREAz
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

void ATM_ThreadMatch::cThreadTemplateStarInit(Mat & TemplateStar)
{
	if (tTemplateStarInit == nullptr && tempStar.isInit == false)
	{
		//templateStar = TemplateStar;
		cvtColor(TemplateStar, templateStar, CV_RGB2GRAY);
		tTemplateStarInit = new thread(&ATM_ThreadMatch::thread_TemplateStarInit, this, templateStar);
		tIsEndTemplateStarInit = false;
	}
}

void ATM_ThreadMatch::cThreadTemplateStarMatch()
{
	if (tTemplateStarMatch == nullptr && isExistObjMinMap && isStarExist)
	{
		tTemplateStarMatch = new thread(&ATM_ThreadMatch::thread_TemplateStarMatch, this, ref(objStar));
		tIsEndTemplateStarMatch = false;
	}
}

void ATM_ThreadMatch::setTemplateStar(Mat TemplateStarMat)
{
	TemplateStarMat.copyTo(templateStar);
}

void ATM_ThreadMatch::setStar(Mat StarMat)
{
	StarMat.copyTo(objStar);
}

void ATM_ThreadMatch::getObjMinMap(Mat & obj)
{
	//obj.copyTo(objMinMap);
	cvtColor(obj, objMinMap, CV_RGB2GRAY);
	int Avatar_Rect_x = cvRound(obj.cols*0.4);
	int Avatar_Rect_y = cvRound(obj.rows*0.4);
	int Avatar_Rect_w = cvRound(obj.cols*0.2);
	int Avatar_Rect_h = cvRound(obj.rows*0.2);

	obj(cv::Rect(Avatar_Rect_x, Avatar_Rect_y, Avatar_Rect_w, Avatar_Rect_h)).copyTo(objAvatar);

	//obj(Rect(obj.cols / 2 - 14, obj.rows / 2 - 14, 28, 28)).copyTo(objAvatar);
	//obj(Rect(36, 36, obj.cols - 72, obj.rows - 72)).copyTo(objStar);
	cvtColor(obj(Rect(36, 36, obj.cols - 72, obj.rows - 72)), objStar, CV_RGBA2GRAY);
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
	if (tIsEndTemplateStarInit == false)
	{
		CheckThread_TemplateStarInit();
	}
	if (tIsEndTemplateStarMatch == false)
	{
		CheckThread_TemplateStarMatch();
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

void ATM_ThreadMatch::CheckThread_TemplateStarInit()
{
	DWORD exitCode;
	if (tTemplateStarInit != nullptr)
	{
		GetExitCodeThread(tTemplateStarInit->native_handle(), &exitCode);
		if (exitCode == 0)
		{
			tTemplateStarInit->join();
			delete tTemplateStarInit;
			tTemplateStarInit = nullptr;
			tIsEndTemplateStarInit = true;
		}
	}
}

void ATM_ThreadMatch::thread_TemplateStarInit(Mat & tar)
{
	tempStar.setStarTemplate(tar);
	tempStar.Init();
}

void ATM_ThreadMatch::CheckThread_TemplateStarMatch()
{
	DWORD exitCode;
	if (tTemplateStarMatch != nullptr)
	{
		GetExitCodeThread(tTemplateStarMatch->native_handle(), &exitCode);
		if (exitCode == 0)
		{
			tTemplateStarMatch->join();
			delete tTemplateStarMatch;
			tTemplateStarMatch = nullptr;
			tIsEndTemplateStarMatch = true;
		}
	}
}

void ATM_ThreadMatch::thread_TemplateStarMatch(Mat & Obj)
{
	if (isExistObjMinMap)
	{
		tempStar.setStarMat(Obj);
		tempStar.TemplateStar();
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
	if (tIsEndTemplateStarMatch)
	{
		isStarVisible = tempStar.getStar();
		//if (isStarVisible)
		//{
			starPos = tempStar.getStarPos();
		//}
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
	detector = xfeatures2d::SURF::create(minHessian);
	detector->detectAndCompute(_mapMat, noArray(), Kp_Map, Dp_Map);
	isInit = true;
}

void ATM_TM_SurfMap::SURFMatch()
{
	//static Point hisP[3];

	Mat img_scene(_mapMat);
	Mat img_object(_minMapMat(Rect(30,30, _minMapMat.cols-60, _minMapMat.rows-60)));

	//someSizeR = cvCeil(img_object.rows / 2);

	if (img_object.empty())
	{
		return;
	}

	isContinuity = false;

	if ((dis(hisP[1] - hisP[0]) + dis(hisP[2] - hisP[1])) < 2000)
	{
		if (hisP[2].x > someSizeR && hisP[2].x < img_scene.cols - someSizeR && hisP[2].y>someSizeR && hisP[2].y < img_scene.rows - someSizeR)
		{
			isContinuity = true;
			if (isContinuity)
			{
				Mat someMap(img_scene(Rect(hisP[2].x - someSizeR, hisP[2].y - someSizeR, someSizeR*2, someSizeR*2)));
				Mat minMap(img_object);
				//resize(someMap, someMap, Size(), MatchMatScale, MatchMatScale, 1);
				//resize(minMap, minMap, Size(), MatchMatScale, MatchMatScale, 1);

				detectorSomeMap = xfeatures2d::SURF::create(minHessian);
				detectorSomeMap->detectAndCompute(someMap, noArray(), Kp_SomeMap, Dp_SomeMap);
				detectorSomeMap->detectAndCompute(minMap, noArray(), Kp_MinMap, Dp_MinMap);
				Ptr<DescriptorMatcher> matcherTmp = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
				std::vector< std::vector<DMatch> > KNN_mTmp;
				std::vector<DMatch> good_matchesTmp;
				matcherTmp->knnMatch(Dp_MinMap, Dp_SomeMap, KNN_mTmp, 2);
				std::vector<double> lisx;
				std::vector<double> lisy;
				double sumx = 0;
				double sumy = 0;
				for (size_t i = 0; i < KNN_mTmp.size(); i++)
				{
					if (KNN_mTmp[i][0].distance < ratio_thresh * KNN_mTmp[i][1].distance)
					{
						good_matchesTmp.push_back(KNN_mTmp[i][0]);
						// 这里有个bug回卡进来，进入副本或者切换放大招时偶尔触发
						lisx.push_back(((minMap.cols / 2 - Kp_MinMap[KNN_mTmp[i][0].queryIdx].pt.x)*mapScale + Kp_SomeMap[KNN_mTmp[i][0].trainIdx].pt.x));
						lisy.push_back(((minMap.rows / 2 - Kp_MinMap[KNN_mTmp[i][0].queryIdx].pt.y)*mapScale + Kp_SomeMap[KNN_mTmp[i][0].trainIdx].pt.y));
						sumx += lisx.back();
						sumy += lisy.back();
					}
				}
				Mat img_matches, imgmap, imgminmap;
				drawKeypoints(someMap, Kp_SomeMap, imgmap, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
				drawKeypoints(img_object, Kp_MinMap, imgminmap, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

				drawMatches(img_object, Kp_MinMap, someMap, Kp_SomeMap, good_matchesTmp, img_matches, Scalar::all(-1), Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

				if (min(lisx.size(), lisy.size()) <= 4)
				{
					isContinuity = false;
				}
				else
				{
					double meanx = sumx / lisx.size(); //均值
					double meany = sumy / lisy.size(); //均值
					Point p = SPC(lisx, sumx, lisy, sumy);

					int x = (int)meanx;
					int y = (int)meany;

					x = p.x;
					y = p.y;

 					pos = Point(x + hisP[2].x - someSizeR, y + hisP[2].y - someSizeR);
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
				lisx.push_back(((img_object.cols / 2 - Kp_MinMap[KNN_m[i][0].queryIdx].pt.x)*mapScale + Kp_Map[KNN_m[i][0].trainIdx].pt.x));
				lisy.push_back(((img_object.rows / 2 - Kp_MinMap[KNN_m[i][0].queryIdx].pt.y)*mapScale + Kp_Map[KNN_m[i][0].trainIdx].pt.y));
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

			pos=SPC(lisx, sumx, lisy, sumy);
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

Point ATM_TM_SurfMap::SPC(vector<double> lisx, double sumx, vector<double> lisy, double sumy)
{
	Point pos;
	double meanx = sumx / lisx.size(); //均值
	double meany = sumy / lisy.size(); //均值
	int x = (int)meanx;
	int y = (int)meany;
	if (min(lisx.size(), lisy.size()) > 3)
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
			if (abs(lisx[i] - meanx) < 1 * stdevx)
			{
				sumx += lisx[i];
				numx++;
			}

			if (abs(lisy[i] - meany) < 1 * stdevy)
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
	return pos;
}

Point ATM_TM_SurfMap::SPC2(vector<double> lisx, double sumx, vector<double> lisy, double sumy)
{
	Point p;

	return Point();
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
	matchTemplate(_paimonTemplate, _paimonMat, tmp, TM_CCOEFF_NORMED);

	double minVal, maxVal;
	Point minLoc, maxLoc;
	//寻找最佳匹配位置
	minMaxLoc(tmp, &minVal, &maxVal, &minLoc, &maxLoc);
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
	Mat giAvatarRef = _avatarMat;

	resize(giAvatarRef, giAvatarRef, Size(), 2, 2);
	std::vector<Mat> lis;
	split(giAvatarRef, lis);

	Mat gray0;
	Mat gray1;
	Mat gray2;

	threshold(lis[0], gray0, 240, 255, THRESH_BINARY);
	threshold(lis[1], gray1, 212, 255, THRESH_BINARY);
	threshold(lis[2], gray2, 25, 255, THRESH_BINARY_INV);

	Mat and12;
	bitwise_and(gray1, gray2, and12, gray0);
	resize(and12, and12, Size(), 2, 2, 3);
	Canny(and12, and12, 20, 3 * 20, 3);
	circle(and12, Point(cvCeil(and12.cols / 2), cvCeil(and12.rows / 2)), cvCeil(and12.cols / 4.5), Scalar(0, 0, 0), -1);
	Mat dilate_element = getStructuringElement(MORPH_RECT, Size(2, 2));
	dilate(and12, and12, dilate_element);
	Mat erode_element = getStructuringElement(MORPH_RECT, Size(2, 2));
	erode(and12, and12, erode_element);

	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarcy;

	findContours(and12, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	std::vector<Rect> boundRect(contours.size());  //定义外接矩形集合
	//std::vector<RotatedRect> box(contours.size()); //定义最小外接矩形集合
	Point2f rect[4];

	std::vector<Point2d> AvatarKeyPoint;
	double AvatarKeyPointLine[3] = { 0 };
	std::vector<Point2f> AvatarKeyLine;
	Point2f KeyLine;

	if (contours.size() != 3)
	{
		return ;
	}

	for (int i = 0; i < 3; i++)
	{
		//box[i] = minAreaRect(Mat(contours[i]));  //计算每个轮廓最小外接矩形
		boundRect[i] = boundingRect(Mat(contours[i]));
		AvatarKeyPoint.push_back(Point(cvRound(boundRect[i].x + boundRect[i].width / 2), cvRound(boundRect[i].y + boundRect[i].height / 2)));
	}

	AvatarKeyPointLine[0] = dis(AvatarKeyPoint[2] - AvatarKeyPoint[1]);
	AvatarKeyPointLine[1] = dis(AvatarKeyPoint[2] - AvatarKeyPoint[0]);
	AvatarKeyPointLine[2] = dis(AvatarKeyPoint[1] - AvatarKeyPoint[0]);



	if (AvatarKeyPointLine[0] >= AvatarKeyPointLine[2] && AvatarKeyPointLine[1] >= AvatarKeyPointLine[2])
	{
		AvatarKeyLine.push_back(AvatarKeyPoint[2] - AvatarKeyPoint[1]);
		AvatarKeyLine.push_back(AvatarKeyPoint[2] - AvatarKeyPoint[0]);
	}
	if (AvatarKeyPointLine[0] >= AvatarKeyPointLine[1] && AvatarKeyPointLine[2] >= AvatarKeyPointLine[1])
	{
		AvatarKeyLine.push_back(AvatarKeyPoint[1] - AvatarKeyPoint[0]);
		AvatarKeyLine.push_back(AvatarKeyPoint[1] - AvatarKeyPoint[2]);
	}
	if (AvatarKeyPointLine[1] >= AvatarKeyPointLine[0] && AvatarKeyPointLine[2] >= AvatarKeyPointLine[0])
	{
		AvatarKeyLine.push_back(AvatarKeyPoint[0] - AvatarKeyPoint[1]);
		AvatarKeyLine.push_back(AvatarKeyPoint[0] - AvatarKeyPoint[2]);
	}

	AvatarKeyLine = Vector2UnitVector(AvatarKeyLine);
	KeyLine = AvatarKeyLine[0] + AvatarKeyLine[1];
	rotationAngle = Line2Angle(KeyLine);
}

double ATM_TM_ORBAvatar::getRotationAngle()
{
	return rotationAngle;
}

double ATM_TM_ORBAvatar::dis(Point p)
{
	return sqrt(p.x*p.x + p.y*p.y);
}
std::vector<Point2f> ATM_TM_ORBAvatar::Vector2UnitVector(std::vector<Point2f> pLis)
{
	double length = 1;
	std::vector<Point2f> res;
	for (int i = 0; i < pLis.size(); i++)
	{
		length = sqrt(pLis[i].x*pLis[i].x + pLis[i].y*pLis[i].y);
		res.push_back(Point2f((float)(pLis[i].x / length), (float)(pLis[i].y / length)));
	}
	return res;
}

double ATM_TM_ORBAvatar::Line2Angle(Point2f p)
{
	const double rad2degScale = 180 / CV_PI;
	double res = atan2(-p.y, p.x)*rad2degScale;
	res = res - 90; //从屏幕空间左侧水平线为0度转到竖直向上为0度
	return res;
}

void ATM_TM_Thread::run()
{
	while (isExitThread == false)
	{
		if (isRunWork && (*ptr) != nullptr)
		{
			ptr(workInput);
			isRunWork = false;
			isEndWork = true;
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
}

ATM_TM_Thread::ATM_TM_Thread()
{
	tLoopWork = new thread(&ATM_TM_Thread::run, this);
}

ATM_TM_Thread::~ATM_TM_Thread()
{
	if (tLoopWork != nullptr)
	{
		isExitThread = true;
		tLoopWork->join();
		delete tLoopWork;
	}
}

ATM_TM_Thread::ATM_TM_Thread(void(*funPtr)(Mat &inMat))
{
	setFunction(funPtr);
	tLoopWork = new thread(&ATM_TM_Thread::run, this);
}

void ATM_TM_Thread::setFunction(void(*funPtr)(Mat &inMat))
{
	ptr = funPtr;
	isExistFunction = true;
}

void ATM_TM_Thread::start(Mat & inMat)
{
	if (isExistFunction == false)
	{
		throw"Not Found Work Function";
	}
	workInput = inMat;
	isRunWork = true;
	isEndWork = false;
}

bool ATM_TM_Thread::isEnd()
{
	return isEndWork;
}

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

	matchTemplate(Roi, checkUID, tmp, TM_CCOEFF_NORMED);

	double minVal, maxVal;
	Point minLoc, maxLoc;
	//寻找最佳匹配位置
	minMaxLoc(tmp, &minVal, &maxVal, &minLoc, &maxLoc);
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

				matchTemplate(Roi, numCheckUID, tmp, TM_CCOEFF_NORMED);

				double minVali, maxVali;
				Point minLoci, maxLoci;
				//寻找最佳匹配位置
				minMaxLoc(tmp, &minVali, &maxVali, &minLoci, &maxLoci);

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

void ATM_TM_TemplateStar::Init()
{
	if (isInit)return;

	isInit = true;
}

void ATM_TM_TemplateStar::setStarTemplate(Mat starTemplateMat)
{
	_starTemplate = starTemplateMat;
}

void ATM_TM_TemplateStar::setStarMat(Mat starMat)
{
	_starMat = starMat;
}

void ATM_TM_TemplateStar::TemplateStar()
{
	int MAXLOOP = 0;
	bool isLoopMatch = false;
	Mat tmp;
	double minVal, maxVal;
	Point minLoc, maxLoc;

	pos.clear();
	
	matchTemplate(_starTemplate, _starMat, tmp, TM_CCOEFF_NORMED);
	minMaxLoc(tmp, &minVal, &maxVal, &minLoc, &maxLoc);
	cout << "Match Star MinVal & MaxVal : " << minVal << " , " << maxVal << endl;

	if (maxVal < 0.66)
	{
		isStarVisible = false;
	}
	else
	{
		isLoopMatch = true;
		isStarVisible = true;
		pos.push_back(maxLoc - Point(_starMat.cols / 2, _starMat.rows / 2) + Point(_starTemplate.cols / 2, _starTemplate.rows / 2));
	}

	while (isLoopMatch)
	{
		_starMat(Rect(maxLoc.x, maxLoc.y, _starTemplate.cols, _starTemplate.rows)) = Scalar(0, 0, 0);
		matchTemplate(_starTemplate, _starMat, tmp, TM_CCOEFF_NORMED);
		minMaxLoc(tmp, &minVal, &maxVal, &minLoc, &maxLoc);
		cout << "Match Star MinVal & MaxVal : " << minVal << " , " << maxVal << endl;
		if (maxVal < 0.66)
		{
			isLoopMatch = false;
		}
		else
		{
			pos.push_back(maxLoc - Point(_starMat.cols / 2, _starMat.rows / 2) + Point(_starTemplate.cols / 2, _starTemplate.rows / 2));
		}

		MAXLOOP > 10 ? isLoopMatch = false : MAXLOOP++;
	}
}

bool ATM_TM_TemplateStar::getStar()
{
	return isStarVisible;
}

vector<Point> ATM_TM_TemplateStar::getStarPos()
{
	return pos;
}

void ATM_TM_Continuity::setState(bool state)
{
	continuity[0] = continuity[1];
	continuity[1] = continuity[2];
	continuity[2] = state;
}

bool ATM_TM_Continuity::getIsContinuity()
{
	return continuity[0] && continuity[1] && continuity[2];
}

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
	if (surfMap.isInit == false)
	{
		cvtColor(Map, mapGray, CV_RGB2GRAY);
		if (tSurfMapInit == nullptr)
		{
			tSurfMapInit = new thread(&ATM_ThreadMatch::thread_SurfMapInit, this, ref(mapGray));
			tIsEndSurfMapInit = false;
		}
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
	cvtColor(Template, templatePaimon, CV_RGB2GRAY);

	if (tTemplatePaimonMatch == nullptr && isExistObjPaimon)
	{
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

void ATM_ThreadMatch::getObjMinMap(Mat & obj)
{
	obj.copyTo(objMinMap);
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
	isPaimonVisial = tempPaimon.getPaimonVisible();
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

	bool isContinuity = false;

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

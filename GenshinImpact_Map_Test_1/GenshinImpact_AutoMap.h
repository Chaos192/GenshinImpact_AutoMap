#include<iostream>
#include<Windows.h>
#include<opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include<opencv2/xfeatures2d.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>

using namespace cv;
using namespace std;

class AutoTest
{
public:
	AutoTest() :AutoTest(false) {};
	~AutoTest() {};
public:
	AutoTest(bool flag) :state(flag) {};
	bool operator==(const AutoTest& AT) { return AT.state; };
	operator bool() { return state; };
public:
	//公共变量
	bool state=false;
private:
	//私有变量
public:
	//框架类函数
	void on() { state = true; };
	void off() { state = false; };

};

class FrameRateLock
{
public:
	FrameRateLock():FrameRateLock(30){};
	~FrameRateLock() {};
public:
	FrameRateLock(int f) :_fps(f){};
public:
	//公共变量
	double runningTime=0;
	double absClock0 = (double)getTickCount();
	double absClock1 = (double)getTickCount();
private:
	//私有变量
	int _fps = 30;
	double _s = 0.0323f;
public:
	//框架类函数
	void fps(int f) { _fps = f; _s = 1.0 / _fps-0.001; };
	int fps() { return _fps; };
	void Wait()
	{
		absClock1 = (double)getTickCount();
		runningTime = (absClock1 - absClock0) / getTickFrequency();
		if (runningTime < _s)
		{
			if (runningTime >= 0)
			{
				waitKey((int)((_s - runningTime)*1000)+1);
			}
			else
			{
				waitKey((int)(_s*1000));
			}
		}
		absClock0 = absClock1;
	};
};


namespace giam
{
	class GenshinImpact_AutoMap
	{
	public:
		//构造与析构函数
		GenshinImpact_AutoMap();
		~GenshinImpact_AutoMap();
	public:
		//公共变量
		AutoTest AT;
		FrameRateLock FRL;

	private:
		//私有变量
		bool isInit = false;
		bool isRun = false;

		HWND giHandle;

		bool giIsRunningFlag = false;
		bool giIsDisplayFlag = false;
		bool giIsZoomedFlag = false;

		struct HUD
		{
			string runState = "";
			Scalar runTextColor=Scalar(255,0,0);
			Scalar displayFlagColor = Scalar(255, 0, 0);

		}giHUD;

		Mat mapMat=imread("Map.bmp");
		Mat autoMapMat;
		String autoMapWindowsName = "Genshin Impact Auto Map";

		Size autoMapSize = Size(450, 400);
		Size mapSize= Size(mapMat.cols, mapMat.rows);
		Point zerosMinMap = mapSize/2;

		Mat giFrame;
	public:
		//框架类函数
		bool init();
		bool run();
		bool exit();
	public:
		//实现类函数
		Mat getMinMap();
	private:
		//类内实现函数
		void giIsRunning();
		void giIsDisplay();
		void giIsZoomed();
		void giCheckWindows();
		void giGetScreen();
		void setHUD();
		void addHUD(Mat img);

		void mapUpdata();
		void mapShow();

	};

	typedef GenshinImpact_AutoMap giAM;
}



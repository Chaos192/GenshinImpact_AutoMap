#include<iostream>
#include<Windows.h>
#include<opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include<opencv2/xfeatures2d.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>

using namespace cv;
using namespace std;

//自动测试
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

//帧率锁定
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
		HWND thisHandle;

		bool giIsRunningFlag = false;
		bool giIsDisplayFlag = false;
		bool giIsZoomedFlag = false;

		struct HUD
		{
			
			String runState = "";
			Scalar runTextColor=Scalar(255,0,0);
			Scalar displayFlagColor = Scalar(255, 0, 0);
			Scalar minBackgroundColo = Scalar(255, 255, 0, 0);
			Scalar minStarColor = Scalar(255, 255, 0, 128);

		}giHUD;

		struct MEF
		{
			int x0 = 0;
			int y0 = 0;
			int dx = 0;
			int dy = 0;
			Point p0 = Point(0, 0);
			Point p1 = Point(0, 0);
			Point dp = Point(0, 0);

		}giMEF;

		Mat mapMat=imread("Map.png", IMREAD_UNCHANGED);
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

		void customProcess();

		void mapUpdata();
		void mapShow();

		static void on_MouseHandle(int event, int x, int y, int flags, void *parm);

		void mapMouseE_MM();
		void mapMouseE_LBD();
		void mapMouseE_RBD();
		void mapMouseE_MBD();
		void mapMouseE_LBU();
		void mapMouseE_RBU();
		void mapMouseE_MBU();
		void mapMouseE_LBB();
		void mapMouseE_RBB();
		void mapMouseE_MBB();
		void mapMouseE_MW();
		void mapMouseE_MHW();
		void mapMouseF_L();
		void mapMouseF_R();
		void mapMouseF_M();
		void mapMouseF_CK();
		void mapMouseF_SK();
		void mapMouseF_AK();


	};

	typedef GenshinImpact_AutoMap giAM;
}



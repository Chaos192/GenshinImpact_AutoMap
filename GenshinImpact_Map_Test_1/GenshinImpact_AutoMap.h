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
	bool t = true;
	bool f = false;
private:
	//私有变量
public:
	//框架类函数
	void on() { state = true; };
	void off() { state = false; };
	bool _is() { return true; };
	bool _isn() { return false; };
	bool s() { return state; };
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
	private:
		//私有变量
		bool isInit = false;
		bool isRun = false;

		HWND handle;

		Size autoMapSize=Size(250,200);
		Mat autoMapMat;
		String autoMapWindowsName = "Genshin Impact Auto Map";
	public:
		//框架类函数
		bool init();
		bool run();
		bool exit();
	public:
		//实现类函数
		bool giIsRunning();
		bool giIsDisplay();
		bool giIsZoomed();
	private:
		//类内实现函数
		void mapShow();

	};

	typedef GenshinImpact_AutoMap giAM;
}



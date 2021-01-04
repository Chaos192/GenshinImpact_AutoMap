#include<iostream>
#include<Windows.h>
#include<opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include<opencv2/xfeatures2d.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>

#include "GenshinImpact_AutoMap_Objects.h"

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
	void fps(int f) { _fps = f; _s = 1.0 / _fps - 0.001; };
	int fps() { return _fps; };
	void Wait()
	{
		absClock1 = (double)getTickCount();
		runningTime = (absClock1 - absClock0) / getTickFrequency();
		if (runningTime < _s)
		{
			if (runningTime >= 0)
			{
				waitKey((int)((_s - runningTime) * 1000) + 1);
			}
			else
			{
				waitKey((int)(_s * 1000));
			}
		}
		absClock0 = absClock1;
	};

};

class MessBox
{

};

class Popup
{
public:
	Popup():Popup(""){};
	~Popup() {};
public:
	Popup(std::string text) :Popup("", text) {};
	Popup(std::string title,std::string text):Popup(title,text,false){};
	Popup(std::string title, std::string text,bool isReturn) {};
	

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

		//测试用
		//AutoTest AT;

		//图像更新帧率锁定
		FrameRateLock FRL;

	private:
		//私有变量

		//是否初始化
		bool isInit = true;
		//是否运行
		bool isRun = false;
		//原神游戏窗口句柄
		HWND giHandle;
		//自动悬浮窗句柄
		HWND thisHandle;
		//原神窗口区域
		RECT giRect;
		//原神窗口区域保存对比用
		RECT giRectTmp;

		//原神是否正在运行标志
		bool giIsRunningFlag = false;
		//原神是否可见标志
		bool giIsDisplayFlag = false;
		//原神是否最大化标志
		bool giIsZoomedFlag = false;

		//HUD参数
		struct HUD
		{
			
			String runState = "";
			Scalar runTextColor=Scalar(255,0,0);
			Scalar displayFlagColor = Scalar(255, 0, 0);
			Scalar minBackgroundColo = Scalar(255, 255, 0, 0);
			Scalar minStarColor = Scalar(255, 255, 0, 128);

		}giHUD;

		//鼠标回调传递参数
		struct MEF
		{
			int x0 = 0;
			int y0 = 0;
			int dx = 0;
			int dy = 0;
			int x1 = 0;
			int y1 = 0;
			Point p0 = Point(0, 0);
			Point p1 = Point(0, 0);
			double value = 0.0;
			double scale = 1.0;

			bool bLCD = false;
			bool bLCU = false;
		}giMEF;

		//地图标记对应图标
		struct TAB
		{
			//string pngA = "f_t_c_1_1.png";
			Mat pngA = imread("C:/Users/GengG/source/repos/GenshinImpact_AutoMap/GenshinImpact_Map_Test_1/f_t_c_1_1.png", IMREAD_UNCHANGED);
			Mat pngAMask = imread("C:/Users/GengG/source/repos/GenshinImpact_AutoMap/GenshinImpact_Map_Test_1/f_t_c_1_1_mask.bmp", IMREAD_UNCHANGED);
			Mat pngB = imread("C:/Users/GengG/source/repos/GenshinImpact_AutoMap/GenshinImpact_Map_Test_1/f_t_c_1_1.png", IMREAD_UNCHANGED);
			Mat pngC = imread("C:/Users/GengG/source/repos/GenshinImpact_AutoMap/GenshinImpact_Map_Test_1/f_t_c_1_1.png", IMREAD_UNCHANGED);
			Mat sysIcon1 = imread("C:/Users/GengG/source/repos/GenshinImpact_AutoMap/GenshinImpact_Map_Test_1/sysIcon_1.png", IMREAD_UNCHANGED);
			Mat sysIcon1Mask = imread("C:/Users/GengG/source/repos/GenshinImpact_AutoMap/GenshinImpact_Map_Test_1/sysIcon_1_mask.bmp", IMREAD_UNCHANGED);
			Mat sysIcon2 = imread("C:/Users/GengG/source/repos/GenshinImpact_AutoMap/GenshinImpact_Map_Test_1/sysIcon_2.png", IMREAD_UNCHANGED);
			Mat sysIcon2Mask = imread("C:/Users/GengG/source/repos/GenshinImpact_AutoMap/GenshinImpact_Map_Test_1/sysIcon_2_mask.bmp", IMREAD_UNCHANGED);
			Rect pngARect = Rect(30, 0, pngA.cols, pngA.rows);
		}giTab;

		//地图标记相关记录
		struct FLAG
		{
			bool isUpdata = true;
			int max;
			bool *isShow;
			int numFlag[3] = {73,10,19};//[66,131,80];

			FLAG() :FLAG(3) {};
			FLAG(int n) 
			{
				max = n;
				isShow = new bool[n] { false };

			}
			~FLAG() { delete isShow; };

		}giFlag;

		struct Location2d
		{
			int x;
			int y;
			Location2d() :Location2d(0, 0) {}
			Location2d(int _x, int _y) :x(_x), y(_y) {}
		};

		struct OBJECT
		{
			string name;
			unsigned char klass;
			int orderNum;
			Location2d p;
			OBJECT(){}
			OBJECT(string _name, unsigned char _klass, int _orderNum, int _x, int _y) :OBJECT(_name, _klass, _orderNum, Location2d(_x, _y)) {}
			OBJECT(string _name, unsigned char _klass, int _orderNum, Location2d _p) :name(_name), klass(_klass), orderNum(_orderNum), p(_p) {}
		};
		struct OBJECTS :OBJECT
		{

		};

		struct FLAG_ICON_T_1
		{

		};

		struct obj
		{
			giAMO obj1;
			obj()
			{
				obj1.initCSD();
			}
		}OBJ;

		//完整地图源备份
		//Mat mapMatSource = imread("Map.png", IMREAD_UNCHANGED);
		//完整地图 应用
		Mat mapMat = imread("C:/Users/GengG/source/repos/GenshinImpact_AutoMap/GenshinImpact_Map_Test_1/Map.png", IMREAD_UNCHANGED);
		//悬浮窗显示窗口
		Mat autoMapMat;
		//悬浮窗窗口标题
		String autoMapWindowsName = "Genshin Impact Auto Map";
		//悬浮窗大小
		Size autoMapSize = Size(250, 200);
		//完整地图大小
		Size mapSize= Size(mapMat.cols, mapMat.rows);
		//悬浮窗中心所对大地图位置
		Point zerosMinMap = Point(1466,3272);
		//悬浮窗相对原神窗口位置
		Point offGiMinMap = Point(250, 100);
		//悬浮窗相对原神窗口位置对比用
		Point offGiMinMapTmp = Point(250, 100);
		//
		Rect minMapRect;
		//原神游戏窗口截图
		Mat giFrame;

	public:
		//框架类函数

		//初始化
		bool init();
		//运行
		bool run();
		//退出
		bool exit();
	public:
		//实现类函数

		//从大地图中截取显示区域
		Mat getMinMap();
		//判断RECT是否相等
		bool isEqual(RECT &r1, RECT &r2);
		bool isContains(RECT &r, Point &p);
		bool isContains(Rect &r, Point &p);

	private:
		//类内实现函数

		//原神是否运行
		void giIsRunning();
		//原神是否可见
		void giIsDisplay();
		//原神是否最大化
		void giIsZoomed();
		//检查原神窗口状态
		void giCheckWindows();
		//获取原神画面
		void giGetScreen();

		//设置HUD
		void setHUD();
		//绘制HUD
		void addHUD(Mat img);
		//设置标记是否显示
		void setFLAG();
		//在地图上绘制标记
		void addFLAG(Mat img);

		//测试用
		void customProcess();

		//地图数据状态更新
		void mapUpdata();
		//地图显示刷新
		void mapShow();

		//鼠标回调
		static void on_MouseHandle(int event, int x, int y, int flags, void *parm);
	};

	typedef GenshinImpact_AutoMap giAM;
}



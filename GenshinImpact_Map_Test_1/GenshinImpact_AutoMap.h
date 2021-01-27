#include <mutex> 
#include <thread>
#include <iostream>
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include "resource.h"
#include "GenshinImpact_AutoMap_LoadUID.h"
#include "GenshinImpact_AutoMap_Objects.h"
#include "GenshinImpact_AutoMap_Matchs.h"

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
	double runningTime = 1;
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
		if (runningTime < _s - 0.001)
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
		else
		{
			waitKey(1);
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

		//循环计数
		long int _count = 0;
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
		//原神是否全屏标志
		bool giIsFullScreenFlag = false;
		//原神是否派蒙可见，即在主画面
		bool giIsPaimonVisibleFlag = false;

		//
		bool thisIsIconicFlag = false;

		//HUD参数
		struct HUD
		{
			
			String runState = "";
			Scalar runTextColor = Scalar(255, 0, 0);
			Scalar displayFlagColor = Scalar(255, 0, 0);
			Scalar minBackgroundColo = Scalar(255, 255, 0);
			Scalar minStarColor = Scalar(255, 255, 0);
			Scalar paimonFlagColor = Scalar(255, 255, 0);
			Scalar autoMoveFlagColor = Scalar(255, 255, 0);
			Scalar isEndMatchInit = Scalar(255, 255, 0);

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
			
			HBITMAP aa;// = (HBITMAP)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP4), IDB_BITMAP4, 0, 0, LR_LOADFROMFILE);//LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_PNG1));;
			BITMAP bb;
																																  //string pngA = "f_t_c_1_1.png";
			Mat png;
			Mat pngA = imread("./Res/FST.png", IMREAD_UNCHANGED);
			Mat pngAMask = imread("./Res/FST_mask.bmp", IMREAD_UNCHANGED);
			Mat pngB = imread("./Res/YST.png", IMREAD_UNCHANGED);
			Mat pngBMask = imread("./Res/YST_mask.bmp", IMREAD_UNCHANGED);
			Mat pngC = imread("./Res/f_t_c_1_1.png", IMREAD_UNCHANGED);
			Mat pngCMask = imread("./Res/f_t_c_1_1_mask.bmp", IMREAD_UNCHANGED);
			Mat sysIcon1 = imread("./Res/sysIcon_1.png", IMREAD_UNCHANGED);
			Mat sysIcon1Mask = imread("./Res/sysIcon_1_mask.bmp", IMREAD_UNCHANGED);

			Rect pngARect = Rect(30, 0, pngA.cols, pngA.rows);
			Rect pngBRect = Rect(52, 0, pngB.cols, pngB.rows);
			Rect pngCRect = Rect(72, 0, pngC.cols, pngC.rows);

			Mat *lis = new Mat[3];
			Mat *lisMask = new Mat[3];
			Rect *lisRect = new Rect[3];
			Point *lisPoint = new Point[3];
			TAB()
			{
				lis[0] = pngA;
				lis[1] = pngB;
				lis[2] = pngC;
				lisMask[0] = pngAMask;
				lisMask[1] = pngBMask;
				lisMask[2] = pngCMask;
				lisRect[0] = pngARect;
				lisRect[1] = pngBRect;
				lisRect[2] = pngCRect;
				lisPoint[0] = Point(pngA.cols / 2, pngA.rows/2);
				lisPoint[1] = Point(pngB.cols / 2, pngB.rows/2);
				lisPoint[2] = Point(pngC.cols / 2, pngC.rows/2);

				//aa = LoadBitmap(, MAKEINTRESOURCE(IDB_BITMAP1));
				//aa = LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP4), IDB_BITMAP4, 0, 0, LR_LOADFROMFILE);
				//aa = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP6));
			}
			~TAB()
			{
				delete[] lis;
				delete[] lisMask;
				delete[] lisRect;
				delete[] lisPoint;
			}
			TAB(HWND handle)
			{
				//HBITMAP hBitmap = (HBITMAP)LoadImage(GetModuleHandle(0),m_SPath + _T("top_btn.bmp"),IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				png=HBitmap2Mat(aa);
				//HBitmap2Mat(aa, png);
			}
			BITMAP HBitmap2Bitmap(HBITMAP hBitmap)
			{
				BITMAP bm;
				::GetObject(hBitmap, sizeof(bm), &bm);
				return bm;
			}
			Mat HBitmap2Mat(HBITMAP& _hBmp)
			{
				//BITMAP操作
				BITMAP bmp;
				GetObject(_hBmp, sizeof(BITMAP), &bmp);
				int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel / 8;
				int depth = bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;
				//mat操作
				Mat v_mat;
				v_mat.create(cvSize(bmp.bmWidth, bmp.bmHeight), CV_MAKETYPE(CV_8UC3, nChannels));
				GetBitmapBits(_hBmp, bmp.bmHeight*bmp.bmWidth*nChannels, v_mat.data);
				return v_mat;
			}
			IplImage* hBitmap2Ipl(HBITMAP hBmp)
			{
				
				BITMAP bmp;
				::GetObject(hBmp, sizeof(BITMAP), &bmp);//hBmp-->bmp
				int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel / 8;
				int depth = bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;
				IplImage* img = cvCreateImage(cvSize(bmp.bmWidth, bmp.bmHeight), depth, nChannels); //cvCreateImageHeader
				//pBuffer = (char*)malloc(bmp.bmHeight*bmp.bmWidth*nChannels*sizeof(char));
				memcpy(img->imageData, (char*)(bmp.bmBits), bmp.bmHeight*bmp.bmWidth*nChannels);
				IplImage *dst = cvCreateImage(cvGetSize(img), img->depth, 3);
				//cv(img, dst, CV_BGRA2BGR);
				cvReleaseImage(&img);
				return dst;
	
			}
			Mat Ipl2Mat(IplImage iplImg)
			{
				/*IplImage *iplImg = ("greatwave.jpg", 1);
				Mat mtx(,);*/
			}
			void te()
			{
				//图片可见
				typedef HWND(WINAPI *PROCGETCONSOLEWINDOW)();
				PROCGETCONSOLEWINDOW GetConsoleWindow;

				HMODULE hKernel32 = GetModuleHandle("kernel32");
				//HMODULE hKernel32 = GetModuleHandle((LPCWSTR)"kernel32");
				GetConsoleWindow = (PROCGETCONSOLEWINDOW)GetProcAddress(hKernel32, "GetConsoleWindow");
				HWND cmd = GetConsoleWindow();
				HDC dc = GetDC(cmd);
				HBITMAP hBitmap;
				hBitmap = aa;
				HDC cmdmem = CreateCompatibleDC(dc);
				SelectObject(cmdmem, hBitmap);
				BitBlt(dc, 250, 250, 500, 500, cmdmem, 0, 0, SRCCOPY);
				ReleaseDC(cmd, dc);
				ReleaseDC(cmd, cmdmem);
			}
		}giTab;

		//地图标记相关记录
		struct FLAG
		{
			bool isUpdata = true;
			bool isGetMap = true;
			bool isUpHUD = true;
			int max = 0;
			bool *isShow = nullptr;
			bool isAutoMove=false;
			int numFlag[3] = {73,10,19};//[66,131,80];

			FLAG() :FLAG(3) {};
			FLAG(int n) 
			{
				max = n;
				isShow = new bool[n] { false };

			}
			~FLAG() 
			{
				delete[] isShow;
			}

		}giFlag;

		struct ObjTable
		{
			int num = 0;
			giAMO *obj;
			giAMO at;
			ObjTable(int k)
			{
				num = k;
				obj = new giAMO[k];
				obj[0].initFST();
				obj[1].initYST();
				obj[2].initFHYS();

				//at.initALL();
			}
			~ObjTable()
			{
				delete[] obj;
			}
		}giObjTable=ObjTable(3);

		//完整地图源备份
		//Mat mapMatSource = imread("Map.png", IMREAD_UNCHANGED);
		//完整地图 应用
		Mat matMap = imread("./Res/Map.png", IMREAD_UNCHANGED);
		//
		Mat matMatchMap;// = imread("./Res/MatchMap.bmp", IMREAD_UNCHANGED);
		//Paimon
		Mat matPaimon1 = imread("./Res/Paimon1.bmp", IMREAD_UNCHANGED);
		Mat matPaimon2 = imread("./Res/Paimon2.bmp", IMREAD_UNCHANGED);
		//悬浮窗显示窗口
		Mat autoMapMat;
		//悬浮窗窗口标题
		String autoMapWindowsName = "Genshin Impact Auto Map";
		//悬浮窗大小
		Size autoMapSize = Size(250, 200);
		//完整地图大小
		Size mapSize= Size(matMap.cols, matMap.rows);
		//完整地图世界中心，相对原点
		Point mapWorldCenter = Point(1416, 3306);
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
		//原神游戏窗口截图有效区域
		Mat giFrameROI;
		//
		Mat giFrameRect;
		//
		Mat giFramePaimon;
		//
		Mat giFrameMap;

		giAMM giMatch;

		Size giSize;

		giAML giConfig;

		//多线程相关
		mutex tMuMatch;

		bool tIsEndInit = false;
		bool tIsEndMap = false;
		bool tIsEndStar = false;
		bool tIsEndTarget = false;

		thread * tMatchInit = nullptr;
		thread * tMatchMap = nullptr;
		thread * tMatchStar = nullptr;
		thread * tMatchTarget = nullptr;

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
		int dis2(Point& p);
		int dis2(int x, int y);
	private:
		//类内实现函数

		//原神是否运行
		bool giIsRunning();

		//原神是否可见
		bool giIsDisplay();

		//原神是否最大化
		//bool giIsZoomed();

		//原神是否全屏
		bool giIsFullScreen();

		//原神是否派蒙可见，即在主画面
		bool giIsPaimonVisible();
		//检查原神窗口状态
		void giCheckWindows();
		//获取原神画面
		void giGetScreen();
		//原神画面处理
		void giScreenROI();
		//
		void giGetPaimon();
		//
		void giGetMap();
		
		bool thisIsIconic();
		
		bool isNeedFindStar();

		bool isNeedFindStar(int& id, Point &p);

		bool isNeedFindStar(vector<int>& id, vector<Point> &lisP);

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

		//地图跟踪
		void mapTrack();

		void mapStar();

		//地图数据状态更新
		void mapUpdata();
		//地图显示刷新
		void mapShow();

		//多线程
		void thisCheckThread();

		//鼠标回调
		static void on_MouseHandle(int event, int x, int y, int flags, void *parm);
		//多线程
		 void thread_MatchInit(giAMM& match, mutex& mu);
		 void thread_MatchMap(giAMM& match, mutex& mu);
		 void thread_MatchStar(giAMM& match, mutex& mu);
		 void thread_MatchTarget(giAMM& match, mutex& mu);
	};

	typedef GenshinImpact_AutoMap giAM;
}



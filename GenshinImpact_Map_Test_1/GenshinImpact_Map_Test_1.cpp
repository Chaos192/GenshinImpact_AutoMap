#include<iostream>
#include<Windows.h>
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<opencv2/xfeatures2d.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>

#include"GenshinImpact_AutoMap.h"

//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
int main()
{
	//创建地图对象
	giam::giAM Amap;
	//运行地图
	Amap.run();
	//system("pause");
	return 0;
}


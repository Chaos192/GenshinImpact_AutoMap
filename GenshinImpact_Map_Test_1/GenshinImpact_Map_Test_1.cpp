#include<iostream>
#include<Windows.h>

#include"GenshinImpact_AutoMap.h"
//
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


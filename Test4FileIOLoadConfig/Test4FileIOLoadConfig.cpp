// Test4FileIOLoadConfig.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	string path1 = "C:\\Users\\GengG\\source\\repos\\GenshinImpact_AutoMap\\x64\\Out\\file.dat";
	string path2 = "C:\\Users\\GengG\\source\\repos\\GenshinImpact_AutoMap\\x64\\Out\\load.ini";
	//char data[100];
	//ofstream   afile;
	//afile.open("C:\\Users\\GengG\\source\\repos\\GenshinImpact_AutoMap\\x64\\Out\\file.dat");
	////FILE *fp = open("Config.ini","r");
	//int k = 123;
	//afile << k << endl;

	//ifstream load;
	//load.open("C:\\Users\\GengG\\source\\repos\\GenshinImpact_AutoMap\\x64\\Out\\load.ini");
	//load >> data;

	//// 在屏幕上写入数据
	//cout << data << endl;

 //   std::cout << "Hello World!\n";
	//afile.close();
	FILE *fp;

	fopen_s(&fp,"C:\\Users\\GengG\\source\\repos\\GenshinImpact_AutoMap\\x64\\Out\\load.ini", "r");

	int absID, numID, typeID, x=0, y=0;
	char type[100],info[100];

	fscanf_s(fp, "%d %d %d", &absID, &numID, &typeID);// type, 6, &x, 4, &y, 4, info, 100);
	fscanf_s(fp, "%s", type, 100);
	fscanf_s(fp, "%d %d", &x, &y);
	fscanf_s(fp, "%s", info, 100);

	cout << absID << numID << typeID << type << x << y << info << endl;

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

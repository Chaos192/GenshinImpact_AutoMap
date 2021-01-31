// Test5MatchUID.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <opencv.hpp>
using namespace std;
using namespace cv;

struct Num
{
	Mat * n = new Mat[9];
	int max = 9;
	Mat UID = imread("./uid/UID_.png", IMREAD_UNCHANGED);
	Mat uid0 = imread("./uid/uid0.png", IMREAD_UNCHANGED);
	Mat uid1 = imread("./uid/uid1.png", IMREAD_UNCHANGED);
	Mat uid2 = imread("./uid/uid2.png", IMREAD_UNCHANGED);
	Mat uid3 = imread("./uid/uid3.png", IMREAD_UNCHANGED);
	Mat uid4 = imread("./uid/uid4.png", IMREAD_UNCHANGED);
	Mat uid5 = imread("./uid/uid5.png", IMREAD_UNCHANGED);
	Mat uid6 = imread("./uid/uid6.png", IMREAD_UNCHANGED);
	Mat uid7 = imread("./uid/uid7.png", IMREAD_UNCHANGED);
	Mat uid8 = imread("./uid/uid8.png", IMREAD_UNCHANGED);
	Num()
	{
		n[0] = uid0;
		n[1] = uid1;
		n[2] = uid2;
		n[3] = uid3;
		n[4] = uid4;
		n[5] = uid5;
		n[6] = uid6;
		n[7] = uid7;
		n[8] = uid8;
		//n[9] = uid9;
	}
	~Num()
	{
		//delete n;
	}
};

int getMaxId(double lis[], int len)
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

int getUid(Num num,Mat img)
{
	int res = 0;
	int k[9] = { 0 };
	int c = 1;

	Mat tmp;
	{
		Mat checkUID = num.UID;
		Mat Roi = img;

		cv::matchTemplate(Roi, checkUID, tmp, cv::TM_CCOEFF_NORMED);

		double minVal, maxVal;
		cv::Point minLoc, maxLoc;
		//寻找最佳匹配位置
		cv::minMaxLoc(tmp, &minVal, &maxVal, &minLoc, &maxLoc);
		if (maxVal > 0.85)
		{
			int x = maxLoc.x + checkUID.cols + 7;
			int y = 0;
			double tmplis[9] = { 0 };
			int tmplisx[9] = { 0 };
			for (int p = 8; p >= 0; p--)
			{
				for (int i = 0; i < num.max; i++)
				{
					Rect r(x, y, num.n[i].cols + 2, num.n[i].rows);//180-46/9->140/9->16->16*9=90+54=144
					if (x + r.width > img.cols)
					{
						r = Rect(img.cols - num.n[i].cols - 2, 0, num.n[i].cols + 2, num.n[i].rows);
					}

					Mat numCheckUID = num.n[i];
					Roi = img(r);

					cv::matchTemplate(Roi, numCheckUID, tmp, cv::TM_CCOEFF_NORMED);

					double minVali, maxVali;
					cv::Point minLoci, maxLoci;
					//寻找最佳匹配位置
					cv::minMaxLoc(tmp, &minVali, &maxVali, &minLoci, &maxLoci);

					tmplis[i] = maxVali;
					tmplisx[i] = maxLoci.x + numCheckUID.cols - 1;
					if (maxVali > 0.85)
					{
						k[p] = i;
						x = x + maxLoci.x + numCheckUID.cols - 1;
						break;
					}
					if (i == num.max - 1)
					{
						k[p] = getMaxId(tmplis, 9);
						x = x + tmplisx[k[p]];
					}
				}

			}
		}

	}

	for (int i = 0; i < 9; i++)
	{
		res += k[i] * c;
		c = c * 10;
	}
	return res;
}

int main()
{
	Num num;

	Mat test1 = imread(".\\uid\\test1.png", IMREAD_UNCHANGED);
	Mat test2 = imread(".\\uid\\test2.png", IMREAD_UNCHANGED);
	Mat test3 = imread(".\\uid\\test3.png", IMREAD_UNCHANGED);
	int ans1 = 145588000;
	int ans2 = 145147062;
	int ans3 = 100437381;

	double t = getTickCount();

	int res1 = getUid(num, test1);
	int res2 = getUid(num, test2);
	int res3 = getUid(num, test3);
	t = (getTickCount() - t) / getTickFrequency();

	cout << t*1000 << " ms"<<endl;

	cout << "UID:" << "145588000 || " << res1 << endl;
	if (ans1 != res1)
	{
		cout << "Match ERROR" << endl;
	}
	cout << "UID:" << "145147062 || " << res2 << endl;
	if (ans2 != res2)
	{
		cout << "Match ERROR" << endl;
	}
	cout << "UID:" << "100437381 || " << res3 << endl;
	if (ans3 != res3)
	{
		cout << "Match ERROR" << endl;
	}

	cv::imshow("test1", test1);
	cv::imshow("test2", test2);
	cv::imshow("test3", test3);

	waitKey(1000);
    std::cout << "Hello World!\n";
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

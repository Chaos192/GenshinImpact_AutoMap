#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;
class ATM_ObjectList
{
	int _maxNumber=0;
	int *_x = nullptr;
	int *_y = nullptr;
	int _orderPtr = 0;
public:
	ATM_ObjectList();
	ATM_ObjectList(int maxNumber);
	~ATM_ObjectList();
	//ATM_ObjectList(const ATM_ObjectList &objlist) = delete;
	ATM_ObjectList& operator=(const ATM_ObjectList& objList);

	void append(int x, int y);

	int x(int i);
	int y(int i);
	cv::Point p(int i);
};

class ATM_ObjectFlag
{
	int _maxNumber = 0;
	vector<int> _x;
	vector<int> _y;
	int _orderPtr = 0;
public:
	ATM_ObjectFlag();
	~ATM_ObjectFlag();

	void append(int x, int y);

	int x(int i);
	int y(int i);
	cv::Point p(int i);
};

class ATM_ObjectLists
{
	int _objectListsNumber = 4;
	int _objectMaxNumbers[4] = { 65,131,80,120 };
	bool _isShow[4] = { false };
	ATM_ObjectList *_objList = nullptr;
	ATM_ObjectFlag objFlag;

public:
	ATM_ObjectLists();
	~ATM_ObjectLists();
	void Init();
	int x(int klass, int i);
	int y(int klass, int i);
	cv::Point p(int klass, int i);
	int objectListsNumber();
	int objectsNumber(int klass);
	bool isShow(int klass);
	void setShow(int klass);
	void setShow(int klass,bool isShow);


private:
	void Init0();
	void Init1();
	void Init2();
	void Init3();
	void append(int i, int x, int y);
};

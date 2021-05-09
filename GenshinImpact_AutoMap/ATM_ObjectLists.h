#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include "ATM_Matrix.h"

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
	void deleteId(int id);

	int x(int i);
	int y(int i);
	cv::Point p(int i);

	int getSize();
	void clear();
};

class ATM_ObjectLists
{
	// 在此：添加新的物品需改数量
	int _objectListsNumber = 11;
	int _objectMaxNumbers[11] = { 65,131,80,120 };
	bool _isShow[11] = { false };
	bool _isShowFlag = false;
	ATM_ObjectList *_objList = nullptr;
	ATM_ObjectFlag _objFlag;


public:
	ATM_Matrix _collectionStateFST = ATM_Matrix(1, 65);
	ATM_Matrix _collectionStateYST = ATM_Matrix(1, 131);
	ATM_Matrix _collectionStateFHYS = ATM_Matrix(1, 80);
	ATM_Matrix _collectionStateFlag;
	ATM_Matrix *collectionState[4];
	vector<int> visualStarKlassList;
	vector<int> visualStarIdList;
	vector<double> visualStarDisList;

	bool isSelect = false;
	int selectID = -1;

	bool isSelectObj = false;
	int selectObjKlass = -1;
	int selectObjID = -1;

	ATM_ObjectLists();
	~ATM_ObjectLists();
	void Init();
	int x(int klass, int i);
	int y(int klass, int i);
	cv::Point p(int klass, int i);
	cv::Point fp(int i);
	int objectListsNumber();
	int objectsNumber(int klass);
	int flagNumber();
	bool isShow(int klass);
	bool isShowFlag();
	void setShow(int klass);
	void setShowFlag();
	void setShow(int klass, bool isShow);
	void setShowFlag(bool isShow);

	void appendFlag(int x, int y);
	void deleteFlag(int id);
	void reAppendFlag();
	void reDeleteFlag();

	//0 未发现 1 未发现即已收集 2 已发现未收集  
	void setCollectionState(int klass, int i, int state);
	//0 未发现 1 未发现即已收集 2 已发现未收集  
	int getCollectionState(int klass, int i);
	void copyFrom(int klass, ATM_Matrix &mat);
	void copyTo(int klass, ATM_Matrix *mat);

private:
	void Init0();
	void Init1();
	void Init2();
	void Init3();
	void append(int i, int x, int y);
};

#pragma once
#include <iostream>
#include <vector>

struct Location2d
{
	int x;
	int y;
	Location2d();
	Location2d(int _x, int _y);
};

class GenshinImpact_AutoMap_Object
{
public:
	GenshinImpact_AutoMap_Object();
	~GenshinImpact_AutoMap_Object();

public:
	GenshinImpact_AutoMap_Object(std::string str,int k,int max);

public:

private:
	std::string name = "";
	int klass = 0;
	int order = 0;
	int number = 0;
	Location2d *p = nullptr;

public:
	void add(Location2d p0);
	void add(int x,int y);
	//void del(int n);
	Location2d at(int n);
	int size();
};

class GenshinImpact_AutoMap_Objects
{
public:
	GenshinImpact_AutoMap_Objects();
	~GenshinImpact_AutoMap_Objects();

public:
	GenshinImpact_AutoMap_Object *object = nullptr;
	GenshinImpact_AutoMap_Object **objptr = nullptr;
private:
	bool isLock = false;
	int classNum = 0;
public:
	void initALL();
	//传送点
	//void initCSD();

	//风神瞳
	void initFST();
	//岩神瞳
	void initYST();

	//绯红玉髓
	void initFHYS();
	Location2d at(int n);

	void add(int x,int y);
	int size();
	int size(int i);



	void fun(int absID, int numID, int TypeID, std::string Type, int X, int Y, std::string Info);
	void fun(int numID, int TypeID, int X, int Y);

};

typedef GenshinImpact_AutoMap_Objects giAMO;

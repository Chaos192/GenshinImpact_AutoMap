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
	GenshinImpact_AutoMap_Object *object;

private:
	bool isLock = false;

public:
	//传送点
	void initCSD();
	//风神瞳
	void initFST();

	//绯红玉髓
	void initFHYS();
	Location2d at(int n);

	void add(int x,int y);
	int size();
};

typedef GenshinImpact_AutoMap_Objects giAMO;

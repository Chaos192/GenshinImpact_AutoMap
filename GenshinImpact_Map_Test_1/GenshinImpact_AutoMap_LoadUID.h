#pragma once
#include<iostream>
#include<Windows.h>
#include <shlobj.h>
#include<direct.h>    
#include<io.h>
using namespace std;

#define UIDCONFIGFILEPATH 

class GenshinImpact_AutoMap_LoadUID
{
public:
	GenshinImpact_AutoMap_LoadUID();
	~GenshinImpact_AutoMap_LoadUID();

public:
	GenshinImpact_AutoMap_LoadUID(unsigned int _UID);
	GenshinImpact_AutoMap_LoadUID(char *_name);

public:
	int getUID();
	string getStrUID();
	void setUID(int _uid);
	void getAppConfigPath();
	//char* getAppConfigPath();

	int data[200][10] = { 0 };
	void save();
	void load();
private:
	char uidstr[10] = { "000000000" };
	unsigned int uid = 0;

	

	FILE *fp;

	string appTempPath;
	string uidFile;
	string giIndex = "GenshinImpactAutoMap\\";
	string fileName = "UID";
	char appConfigPath[MAX_PATH];

	void uid2str();
	void uid2str(int _uid);
	string getUIDFileName();

	int openConfig();
	int loadFileHeader();
	int loadData();
	int saveFileHeader();
	int saveData();
};

typedef GenshinImpact_AutoMap_LoadUID giAML;

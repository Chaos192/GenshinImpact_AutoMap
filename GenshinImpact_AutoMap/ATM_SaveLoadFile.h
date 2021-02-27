#pragma once
#include <io.h>
#include <time.h>
#include <direct.h>    
#include <iostream>
#include "ATM_Matrix.h"
using namespace std;
class ATM_SaveLoadFile
{
	int _uid = 0;
	ATM_Matrix _stateFST = ATM_Matrix(1, 65);
	ATM_Matrix _stateYST = ATM_Matrix(1, 131);
	ATM_Matrix _stateFHYS = ATM_Matrix(1, 80);
	ATM_Matrix _stateFlag;
	string _uidStr = "000000000";

	string _saveIndex = "";
	char _lastSaveTimeChars[60] = {'\0'};
	string _uidFilePath = "";
	const string _uid_ = "UID-";
public:
	ATM_SaveLoadFile();
	~ATM_SaveLoadFile();
	void setIndex(string index);
	void setUID(int uid);
	void save();
	void load();
private:
	bool tryLoad();

	void getUIDStr();
	void getFilePath();
	string getSystemTime();

	void saveMatrix(FILE * fpSave,ATM_Matrix &mat);
	void loadMatrix(FILE * fpLoad,ATM_Matrix &mat);

};


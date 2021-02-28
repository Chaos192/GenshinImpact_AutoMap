#include "ATM_SaveLoadFile.h"

#include<Windows.h>
ATM_SaveLoadFile::ATM_SaveLoadFile()
{
}

ATM_SaveLoadFile::~ATM_SaveLoadFile()
{
}

void ATM_SaveLoadFile::setIndex(string index)
{
	if (_access(index.c_str(), 0) == -1)
	{
		int e= _mkdir(index.c_str());//error 3
		if (e == -1 && GetLastError() == 3)
		{
			int i = 0;
			string _index(index);
			i = index.rfind("\\",index.size()-2);
			_index.erase(_index.begin()+ i,_index.end());
			_mkdir(_index.c_str());
			_mkdir(index.c_str());
		}
	}
	_saveIndex = index;
	getFilePath();
}

void ATM_SaveLoadFile::setUID(int uid)
{
	if (_uid == uid)
	{
		return;
	}
	_uid = uid;
	getUIDStr();
	getFilePath();
	if (tryLoad())
	{
		load();
	}
	else
	{
		save();
	}
}

void ATM_SaveLoadFile::save()
{
	FILE *fpSave;
	errno_t err;
	err = fopen_s(&fpSave, _uidFilePath.c_str(), "w");
	if (fpSave == NULL)
	{
		return;
	}
	
	fprintf_s(fpSave, "%s\n", _uidStr.c_str());
	fprintf_s(fpSave, "%s\n", getSystemTime().c_str());

	saveMatrix(fpSave, _stateFST);
	saveMatrix(fpSave, _stateYST);
	saveMatrix(fpSave, _stateFHYS);
	saveMatrix(fpSave, _stateFlag);

	fclose(fpSave);
}

void ATM_SaveLoadFile::load()
{
	FILE *fpLoad;
	errno_t err;
	err = fopen_s(&fpLoad, _uidFilePath.c_str(), "r");
	if (fpLoad == NULL)
	{
		return;
	}

	fscanf_s(fpLoad, "%d\n", &_uid);
	//fscanf_s(fpLoad, "%[^\n]s", &_lastSaveTimeChars, 60);
	fgets(_lastSaveTimeChars, 60, fpLoad);

	loadMatrix(fpLoad, _stateFST);
	loadMatrix(fpLoad, _stateYST);
	loadMatrix(fpLoad, _stateFHYS);
	loadMatrix(fpLoad, _stateFlag);

	fclose(fpLoad);
}

//ATM_Matrix * ATM_SaveLoadFile::StateClass(int klass)
//{
//	//switch (klass)
//	//{
//	//	case 0:
//	//	{
//	//		return _stateFST;
//	//	}
//	//	default:
//	//		break;
//	//}
//	return nullptr;
//}

bool ATM_SaveLoadFile::tryLoad()
{
	if (_access(_uidFilePath.c_str(), 0) == -1)
	{
		return false;
	}
	else
	{
		return true;
	}
	return false;
}

void ATM_SaveLoadFile::getUIDStr()
{
	char uidBuff[10];
	sprintf_s(uidBuff, "%09d", _uid);
	_uidStr = uidBuff;
}

void ATM_SaveLoadFile::getFilePath()
{
	getUIDStr();
	_uidFilePath = _saveIndex + _uid_ + _uidStr + ".ini";
}

string ATM_SaveLoadFile::getSystemTime()
{
	time_t nowTime = time(NULL);
	char nowTimeChars[64] = { 0 };
	strftime(nowTimeChars, sizeof(nowTimeChars) - 1, "%Y-%m-%d %H:%M:%S", localtime(&nowTime));     //年-月-日 时-分-秒

	return string(nowTimeChars);
}

void ATM_SaveLoadFile::saveMatrix(FILE * fpSave, ATM_Matrix & mat)
{
	fprintf_s(fpSave, "%d %d\n", mat.col(), mat.row());
	for (int i = 0; i < mat.col(); i++)
	{
		for (int ii = 0; ii < mat.row(); ii++)
		{
			fprintf_s(fpSave, "%d ", mat[i][ii]);
		}
		fprintf_s(fpSave, "\n");
	}
}

void ATM_SaveLoadFile::loadMatrix(FILE * fpLoad, ATM_Matrix & mat)
{
	int x = 0, y = 0;
	fscanf_s(fpLoad, "%d %d", &x, &y);
	mat.reSet(x, y);
	for (int i = 0; i < mat.col(); i++)
	{
		for (int ii = 0; ii < mat.row(); ii++)
		{
			fscanf_s(fpLoad, "%d", &mat[i][ii]);
		}
	}
}

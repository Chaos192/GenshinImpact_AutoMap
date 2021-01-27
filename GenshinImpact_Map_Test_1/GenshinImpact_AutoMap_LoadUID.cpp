#include "GenshinImpact_AutoMap_LoadUID.h"

GenshinImpact_AutoMap_LoadUID::GenshinImpact_AutoMap_LoadUID()
{
	getAppConfigPath();
	appTempPath = string(appConfigPath);

	appTempPath.append(giIndex);
	strcat_s(appConfigPath, giIndex.c_str());

	cout << appConfigPath << endl;
	cout << appTempPath.c_str() << endl;

	if (_access(appConfigPath, 0) == -1)
	{
		_mkdir(appConfigPath);
	}
	uidFile = string(appTempPath);
	uidFile.append(getUIDFileName());

	if (_access(uidFile.c_str(), 0) == -1)
	{
		//File not Found
		if (fopen_s(&fp, uidFile.c_str(), "w+") == 0)
		{
			saveFileHeader();
			saveData();
		}
		else
		{
			throw"file Open Faile";
		}
		fclose(fp);
	}
	else
	{
		fopen_s(&fp, uidFile.c_str(), "r+");
		if (loadFileHeader())
		{
			loadData();
		}
		else
		{
			saveFileHeader();
			saveData();
		}
		fclose(fp);
	}
}

GenshinImpact_AutoMap_LoadUID::~GenshinImpact_AutoMap_LoadUID()
{
	fclose(fp);
}

GenshinImpact_AutoMap_LoadUID::GenshinImpact_AutoMap_LoadUID(unsigned int _UID)
{
	setUID(_UID);

	getAppConfigPath();
	appTempPath = string(appConfigPath);

	appTempPath.append(giIndex);
	strcat_s(appConfigPath, giIndex.c_str());

	cout << appConfigPath << endl;
	cout << appTempPath.c_str() << endl;

	if (_access(appConfigPath, 0) == -1)
	{
		_mkdir(appConfigPath);
	}
	uidFile = string(appTempPath);
	uidFile.append(getUIDFileName());

	if (_access(uidFile.c_str(), 0) == -1)
	{
		//File not Found
		if (fopen_s(&fp, uidFile.c_str(), "w+") == 0)
		{
			saveFileHeader();
			saveData();
		}
		else
		{
			throw"file Open Faile";
		}
		fclose(fp);
	}
	else
	{
		fopen_s(&fp, uidFile.c_str(), "r+");
		if (loadFileHeader())
		{
			loadData();
		}
		else
		{
			saveFileHeader();
			saveData();
		}
		fclose(fp);
	}
}

GenshinImpact_AutoMap_LoadUID::GenshinImpact_AutoMap_LoadUID(char * _name)
{
	getAppConfigPath();
	appTempPath = string(appConfigPath);

	appTempPath.append(giIndex);
	strcat_s(appConfigPath, giIndex.c_str());

	cout << appConfigPath << endl;
	cout << appTempPath.c_str() << endl;

	if (_access(appConfigPath, 0) == -1)
	{
		_mkdir(appConfigPath);
	}
	uidFile = string(appTempPath);
	uidFile.append(_name);
	uidFile.append(".ini");

	if (_access(uidFile.c_str(), 0) == -1)
	{
		//File not Found
		if (fopen_s(&fp, uidFile.c_str(), "w+") == 0)
		{
			saveFileHeader();
			saveData();
		}
		else
		{
			throw"file Open Faile";
		}
		fclose(fp);
	}
	else
	{
		fopen_s(&fp, uidFile.c_str(), "r+");
		if (loadFileHeader())
		{
			loadData();
		}
		else
		{
			saveFileHeader();
			saveData();
		}
		fclose(fp);
	}
}

int GenshinImpact_AutoMap_LoadUID::getUID()
{
	return uid;
}

void GenshinImpact_AutoMap_LoadUID::setUID(int _uid)
{
	uid = _uid;
	uid2str(_uid);
}

void GenshinImpact_AutoMap_LoadUID::getAppConfigPath()
{
	GetTempPath(_MAX_PATH, appConfigPath);
}

void GenshinImpact_AutoMap_LoadUID::save()
{
	fopen_s(&fp, uidFile.c_str(), "w");
	loadFileHeader();
	loadData();
	fclose(fp);
}

void GenshinImpact_AutoMap_LoadUID::load()
{
	fopen_s(&fp, uidFile.c_str(), "r");
	loadFileHeader();
	loadData();
	fclose(fp);
}

//char * GenshinImpact_AutoMap_LoadUID::getAppConfigPath()
//{
//	char *tmp=new char[MAX_PATH];
//	return tmp;
//}

void GenshinImpact_AutoMap_LoadUID::uid2str()
{
	uid2str(uid);
}

void GenshinImpact_AutoMap_LoadUID::uid2str(int _uid)
{
	sprintf_s(uidstr, "%9d", _uid);
}

string GenshinImpact_AutoMap_LoadUID::getUIDFileName()
{
	string name(fileName);
	name.append(uidstr);
	name.append(".ini");
	return name;
}

int GenshinImpact_AutoMap_LoadUID::openConfig()
{
	return fopen_s(&fp, uidFile.c_str(), "a");
}

int GenshinImpact_AutoMap_LoadUID::loadFileHeader()
{
	int tmp = 0;
	fscanf_s(fp, "%d\n", &tmp);
	return tmp;
}

int GenshinImpact_AutoMap_LoadUID::loadData()
{
	for (int i = 0; i < 100;i++)
	{
		for (int j = 0; j < 10; j++)
		{
			fscanf_s(fp, "%d", &data[i][j]);
		}
	}
	return 0;
}

int GenshinImpact_AutoMap_LoadUID::saveFileHeader()
{
	fprintf(fp, "1\n");
	return 0;
}

int GenshinImpact_AutoMap_LoadUID::saveData()
{
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			fprintf(fp, "%d ", data[i][j]);
		}
		fprintf(fp, "\n");
	}
	return 0;
}

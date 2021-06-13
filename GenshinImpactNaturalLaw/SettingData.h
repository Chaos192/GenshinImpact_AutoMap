#pragma once

#include <QDir>
#include <QSettings>
//#include <String>
//using namespace std;

class SettingData
{
	QSettings *IniSettingFile = nullptr;

public:
	// [General]
	bool is_start_pupowindows = false;
	QString launcher_install_path = "E:/Genshin Impact/";
	QString game_dynamic_bg_name = "c4b0adcdaa7afebdffa0a4d4d661dc43_7732044710342326225.png";
	QString game_install_path = "E:/Genshin Impact/Genshin Impact Game/";
	QString game_start_name = "yuanshen.exe";
	QString parm_borderless = " -popupwindow";
	bool is_first_exit = false;

public:
	SettingData();
	~SettingData();

	QString gamepath();
	QString Command_NoBorderStartGame();
	QString Command_StartGame();

};


#pragma once
#include <QSettings>
//#include <String>
//using namespace std;

class SettingData
{
	QSettings *IniSettingFile = nullptr;

	// [General]
	bool is_start_pupowindows = false;
	QString launcher_install_path = "";
	QString game_dynamic_bg_name = "";
	QString game_install_path = "";
	QString game_start_name = "";
	bool is_first_exit = false;
public:
	SettingData();
	~SettingData();

};


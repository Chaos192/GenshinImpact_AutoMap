#include "SettingData.h"

SettingData::SettingData()
{
	IniSettingFile = new QSettings("config.ini", QSettings::IniFormat);
	is_start_pupowindows = IniSettingFile->value("General/is_start_pupowindows").toBool();
	launcher_install_path = IniSettingFile->value("General/launcher_install_path").toString();
	game_dynamic_bg_name = IniSettingFile->value("General/game_dynamic_bg_name").toString();
	game_install_path = IniSettingFile->value("General/game_install_path").toString();
	game_start_name = IniSettingFile->value("General/game_start_name").toString();
	is_first_exit = IniSettingFile->value("General/is_first_exit").toBool();
}

SettingData::~SettingData()
{
}

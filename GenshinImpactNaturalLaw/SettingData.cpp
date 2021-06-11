#include "SettingData.h"

SettingData::SettingData()
{
	QString tmp = QDir::currentPath();
	IniSettingFile = new QSettings(QDir::currentPath() + "/config.ini", QSettings::IniFormat);
	is_start_pupowindows = IniSettingFile->value("General/is_start_pupowindows").toBool();
	launcher_install_path = IniSettingFile->value("General/launcher_install_path").toString();
	game_dynamic_bg_name = IniSettingFile->value("General/game_dynamic_bg_name").toString();
	game_install_path = IniSettingFile->value("General/game_install_path").toString();
	game_start_name = IniSettingFile->value("General/game_start_name").toString();
	is_first_exit = IniSettingFile->value("General/is_first_exit").toBool();
}

SettingData::~SettingData()
{
	IniSettingFile->setValue("General/is_start_pupowindows", is_start_pupowindows);
	IniSettingFile->setValue("General/launcher_install_path", launcher_install_path);
	IniSettingFile->setValue("General/game_dynamic_bg_name", game_dynamic_bg_name);
	IniSettingFile->setValue("General/game_install_path", game_install_path);
	IniSettingFile->setValue("General/game_start_name", game_start_name);
	IniSettingFile->setValue("General/is_first_exit", is_first_exit);
	IniSettingFile->sync();
}

QString SettingData::gamepath()
{
	return game_install_path;
}

QString SettingData::Command_NoBorderStartGame()
{
	QString res(game_install_path);
	res.append(game_start_name);
	res.append(parm_borderless);
	return res.replace(QRegExp("/"), "\\");;// game_install_path + game_start_name + parm_borderless;
}

QString SettingData::Command_StartGame()
{
	return game_install_path + game_start_name;
}
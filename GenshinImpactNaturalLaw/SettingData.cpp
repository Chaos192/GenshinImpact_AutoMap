#include "SettingData.h"

SettingData::SettingData()
{
	IniSettingFile = new QSettings(QDir::currentPath() + "/config.ini", QSettings::IniFormat);
	
	is_auto_run = IniSettingFile->value("General/is_auto_run").toBool();
	is_start_pupowindows = IniSettingFile->value("General/is_start_pupowindows").toBool();
	is_start_module = IniSettingFile->value("General/is_start_module").toBool();
	is_exit_ismini = IniSettingFile->value("General/is_exit_ismini").toBool();
	
	launcher_install_path = IniSettingFile->value("Launcher/launcher_install_path").toString();
	game_dynamic_bg_name = IniSettingFile->value("Launcher/game_dynamic_bg_name").toString();
	
	game_install_path = IniSettingFile->value("Game/game_install_path").toString();
	game_start_name = IniSettingFile->value("Game/game_start_name").toString();
	
	is_first_exit = IniSettingFile->value("Module/is_first_exit").toBool();
}

SettingData::~SettingData()
{
	IniSettingFile->setValue("General/is_auto_run", is_auto_run);
	IniSettingFile->setValue("General/is_start_pupowindows", is_start_pupowindows);
	IniSettingFile->setValue("General/is_start_module", is_start_module);
	IniSettingFile->setValue("General/is_exit_ismini", is_exit_ismini);

	IniSettingFile->setValue("Launcher/launcher_install_path", launcher_install_path);
	IniSettingFile->setValue("Launcher/game_dynamic_bg_name", game_dynamic_bg_name);
	
	IniSettingFile->setValue("Game/game_install_path", game_install_path);
	IniSettingFile->setValue("Game/game_start_name", game_start_name);
	
	IniSettingFile->setValue("Module/is_first_exit", is_first_exit);
	
	IniSettingFile->sync();
}

bool SettingData::tryGetGamePath()
{
	if (launcher_install_path != "")
	{
		return false;
	}
	else
	{
		QSettings *launcherIniFile;
		launcherIniFile = new QSettings(launcher_install_path + "/config.ini", QSettings::IniFormat);
		game_install_path = launcherIniFile->value("launcher/game_install_path").toString();
		game_dynamic_bg_name = launcherIniFile->value("launcher/game_dynamic_bg_name").toString();
		game_start_name = launcherIniFile->value("launcher/game_start_name").toString();
	}
	return true;
}

QString SettingData::gamepath()
{
	return game_install_path;
}

QString SettingData::Command_NoBorderStartGame()
{
	QString res(game_install_path);
	res.append("/" + game_start_name);
	res.append(parm_borderless);
	return res.replace(QRegExp("/"), "\\");// game_install_path + game_start_name + parm_borderless;
}

QString SettingData::Command_StartGame()
{
	QString res(game_install_path);
	res.append("/" + game_start_name);
	if (is_start_pupowindows)
	{
		res.append(parm_borderless);
	}
	return res.replace(QRegExp("/"), "\\");
}
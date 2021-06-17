#if defined(_MSC_VER) && (_MSC_VER >= 1600)    
# pragma execution_character_set("utf-8")    
#endif

#include "QtWidgetsSetting.h"

QtWidgetsSetting::QtWidgetsSetting(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint|Qt::SubWindow);

	uiConnectButton();
	connect(ui.pushButton_Exit, SIGNAL(clicked()), this, SLOT(CloseSelf()));
	connect(ui.pushButton_Cancel, SIGNAL(clicked()), this, SLOT(Cancel()));
	connect(ui.pushButton_OK, SIGNAL(clicked()), this, SLOT(OK()));

	connect(ui.radioButton_Setting_0, SIGNAL(clicked()), this, SLOT(RadioButton_SettingExitOrMini()));
	connect(ui.radioButton_Setting_1, SIGNAL(clicked()), this, SLOT(RadioButton_SettingExitOrMini()));
	
	connect(ui.checkBox_Setting_0, SIGNAL(stateChanged(int)), this, SLOT(CheckBox_SettingAutoRun(int)));
	connect(ui.checkBox_Setting_1, SIGNAL(stateChanged(int)), this, SLOT(CheckBox_SettingPupoGame(int)));
	connect(ui.checkBox_Setting_2, SIGNAL(stateChanged(int)), this, SLOT(CheckBox_SettingRunModule(int)));
	
	connect(ui.pushButton_Check_1, SIGNAL(clicked()), this, SLOT(CheckOptions_CheckGameLauncher()));
	connect(ui.pushButton_Check_2, SIGNAL(clicked()), this, SLOT(CheckOptions_CheckGame()));
	connect(ui.pushButton_Check_3, SIGNAL(clicked()), this, SLOT(CheckOptions_CheckModule()));
	connect(ui.pushButton_Check_4, SIGNAL(clicked()), this, SLOT(CheckOptions_RefreshModule()));
	connect(ui.pushButton_Check_5, SIGNAL(clicked()), this, SLOT(CheckOptions_UpdataLauncher()));
	connect(ui.pushButton_Check_6, SIGNAL(clicked()), this, SLOT(CheckOptions_UpdataGameLauncher()));
	connect(ui.pushButton_Check_7, SIGNAL(clicked()), this, SLOT(CheckOptions_UpdataGame()));
}

QtWidgetsSetting::~QtWidgetsSetting()
{
}

void QtWidgetsSetting::uiConnectButton()
{
	UIButtonList.clear();
	UIButtonList.push_back(ui.pushButton_UI_GeneralSetting);
	UIButtonList.push_back(ui.pushButton_UI_GameSetting);
	UIButtonList.push_back(ui.pushButton_UI_ModuleSetting);
	UIButtonList.push_back(ui.pushButton_UI_ModuleResource);
	UIButtonList.push_back(ui.pushButton_UI_VersionInformation);

	ScrollLabelList.clear();
	ScrollLabelList.push_back(ui.label_Title_0);
	ScrollLabelList.push_back(ui.label_Title_1);
	ScrollLabelList.push_back(ui.label_Title_2);
	/************************************************************************************************************************************/
	ScrollLabelList.push_back(ui.label_Title_2);
	/************************************************************************************************************************************/
	ScrollLabelList.push_back(ui.label_Title_3);

	for (int i = 0; i < UIButtonList.size(); i++)
	{
		connect(UIButtonList[i], SIGNAL(clicked()), this, SLOT(SwitchOptions()));
	}
}

void QtWidgetsSetting::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton &&
		ui.TitleLabelRect->frameRect().contains(event->globalPos() - this->frameGeometry().topLeft())) {
		m_Press = event->globalPos();
		leftBtnClk = true;
	}
	event->ignore();
}

void QtWidgetsSetting::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		leftBtnClk = false;
	}
	event->ignore();
}
void QtWidgetsSetting::mouseMoveEvent(QMouseEvent *event)
{
	if (leftBtnClk) {
		m_Move = event->globalPos();
		this->move(this->pos() + m_Move - m_Press);
		m_Press = m_Move;
	}
	event->ignore();
}
void QtWidgetsSetting::SetSetting(SettingData *setting)
{
	this->setting = setting;

	emit UpdataShowOptions();
}

void QtWidgetsSetting::UpdataShowOptions()
{
	ui.checkBox_Setting_0->setChecked(setting->is_auto_run);
	ui.checkBox_Setting_1->setChecked(setting->is_start_pupowindows);
	ui.checkBox_Setting_2->setChecked(setting->is_start_module);
	ui.radioButton_Setting_0->setChecked(setting->is_exit_ismini);
	ui.radioButton_Setting_1->setChecked(!setting->is_exit_ismini);
	ui.lineEdit_Path_1->setText(setting->launcher_install_path.replace(QRegExp("/"), "\\"));
	ui.lineEdit_Path_2->setText(setting->game_install_path.replace(QRegExp("/"), "\\"));
}

void QtWidgetsSetting::CloseSelf()
{
	this->SendCloseSelfSignalToMainWidgets();
	this->close();
}

void QtWidgetsSetting::Cancel()
{
	this->SendCloseSelfSignalToMainWidgets();
	this->close();
}

void QtWidgetsSetting::OK()
{
	this->SendCloseSelfSignalToMainWidgets();
	this->close();
}

void QtWidgetsSetting::SwitchOptions()
{
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	for (int i = 0; i < UIButtonList.size(); i++)
	{
		if (btn == UIButtonList[i])
		{
			QScrollBar *scrBar = ui.scrollArea->verticalScrollBar();
			QPropertyAnimation *scrBarAni = new QPropertyAnimation(scrBar, "value");
			scrBarAni->setStartValue(scrBar->value());
			scrBarAni->setEndValue(ScrollLabelList[i]->y());
			scrBarAni->setDuration(150);
			scrBarAni->start();
		}
	}
}

void QtWidgetsSetting::ShowMessageBox()
{
	if (WidgetsMessageBox == nullptr)
	{
		WidgetsMessageBox = new QtWidgetsMessageBox();
		connect(WidgetsMessageBox, SIGNAL(SendCloseSelfSignalToSettingWidgets()), this, SLOT(ReceiveCloseSelfSignalFromWidgetsMessageBox()));

		WidgetsMessageBox->setWindowModality(Qt::ApplicationModal);
		WidgetsMessageBox->move(this->x() + 145, this->y() + 85);
		WidgetsMessageBox->show();
	}
	else
	{
		WidgetsMessageBox->move(this->x() + 145, this->y() + 85);
		WidgetsMessageBox->show();
	}
	if (MainMaskLabel == nullptr)
	{
		MainMaskLabel = new QLabel(this);
		MainMaskLabel->setText("");
		MainMaskLabel->setGeometry(QRect(0, 0, 820, 524));
		MainMaskLabel->setStyleSheet("background-color:rgba(0, 0, 0, 120);");
		MainMaskLabel->show();
	}
	else
	{
		MainMaskLabel->show();
	}
}

void QtWidgetsSetting::CheckBox_SettingAutoRun(int arg)
{
	if (arg == 2)
	{
		setting->is_auto_run = true;
	}
	else if (arg == 0)
	{
		setting->is_auto_run = false;
	}
}

void QtWidgetsSetting::CheckBox_SettingPupoGame(int arg)
{
	if (arg == 2)
	{
		setting->is_start_pupowindows = true;
	}
	else if (arg == 0)
	{
		setting->is_start_pupowindows = false;
	}
}

void QtWidgetsSetting::CheckBox_SettingRunModule(int arg)
{
	if (arg == 2)
	{
		setting->is_start_module = true;
	}
	else if (arg == 0)
	{
		setting->is_start_module = false;
	}
}

void QtWidgetsSetting::RadioButton_SettingExitOrMini()
{
	QRadioButton *btn = qobject_cast<QRadioButton*>(sender());
	if (btn == ui.radioButton_Setting_0)
	{
		if (btn->isChecked() == true)
		{
			setting->is_exit_ismini = true;
		}
	}
	if (btn == ui.radioButton_Setting_1)
	{
		if (btn->isChecked() == true)
		{
			setting->is_exit_ismini = false;
		}
	}
}

void QtWidgetsSetting::CheckOptions_CheckGameLauncher()
{
	QString FileDialogPath = "./";
	if (setting->launcher_install_path != "")
	{
		FileDialogPath = setting->launcher_install_path;
	}
	QString GameLauncherPath = QFileDialog::getExistingDirectory(this, "选择原神启动器所在目录", FileDialogPath, QFileDialog::ShowDirsOnly);
	
	if (!GameLauncherPath.isEmpty())
	{
		QFileInfo file(GameLauncherPath+"/launcher.exe");
		if (file.exists() == false)
		{
			emit ShowMessageBox();//未能找到游戏本体，请重新选择游戏本体路径
			return;
		}
		else
		{
			setting->launcher_install_path = GameLauncherPath;
			if (!setting->tryGetGamePath())
			{
				emit ShowMessageBox();//未能找到游戏本体，请手动选择游戏本体路径
				return;
			}
		}
	}
	else
	{
		return;
	}
	emit UpdataShowOptions();
}

void QtWidgetsSetting::CheckOptions_CheckGame()
{
	QString FileDialogPath = "./";
	if (setting->game_install_path != "")
	{
		FileDialogPath = setting->game_install_path;
	}
	QString GamePath = QFileDialog::getOpenFileName(this, "选择原神所在目录", FileDialogPath, "应用程序 (*.exe);;");
	if (!GamePath.isEmpty()) 
	{
		setting->game_start_name = GamePath.section('/', -1);
		setting->game_install_path = GamePath.section('/', 0, -2);
	}
	else
	{
		return;
	}

	emit UpdataShowOptions();
}

void QtWidgetsSetting::CheckOptions_CheckModule()
{

}

void QtWidgetsSetting::CheckOptions_RefreshModule()
{

}

void QtWidgetsSetting::CheckOptions_UpdataLauncher()
{

}

void QtWidgetsSetting::CheckOptions_UpdataGameLauncher()
{

}

void QtWidgetsSetting::CheckOptions_UpdataGame()
{

}

void QtWidgetsSetting::ReceiveCloseSelfSignalFromWidgetsMessageBox()
{
	MainMaskLabel->hide();
}


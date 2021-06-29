#include "GenshinImpactNaturalLaw.h"
#pragma execution_character_set("utf-8")

GenshinImpactNaturalLaw::GenshinImpactNaturalLaw(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	
	uiConnectButton();
	uiConnectButtonLabel();

	Tray = new QSystemTrayIcon(this);
	Tray->setIcon(QIcon(QPixmap(":/icon/resource/icon/ICON.png")));
	Tray->setToolTip("天理");
	QString title = "天理";
	QString text = "原神天理系统";
	Tray->show();
	connect(Tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(TrayMenuClickEvent(QSystemTrayIcon::ActivationReason)));

	ShowMainAction = new QAction("显示主界面", this);
	connect(ShowMainAction, SIGNAL(triggered()), this, SLOT(show()));
	ExitAction = new QAction("退出", this);
	connect(ExitAction, SIGNAL(triggered()), this, SLOT(close()));

	TrayMenu = new QMenu(this);
	TrayMenu->addAction(ShowMainAction);
	TrayMenu->addAction(ExitAction);
	Tray->setContextMenu(TrayMenu);

	QGraphicsDropShadowEffect *Shadow_LabelPage = new QGraphicsDropShadowEffect();
	Shadow_LabelPage->setBlurRadius(5);
	Shadow_LabelPage->setColor(QColor(0, 0, 0, 120));
	Shadow_LabelPage->setOffset(0.0);
	ui.label_Page_Rect->setGraphicsEffect(Shadow_LabelPage);

	connect(ui.pushButton_TitleSet, SIGNAL(clicked()), this, SLOT(NewWidgetsSetting()));
	connect(ui.pushButton_TitleExit, SIGNAL(clicked()), this, SLOT(CloseEvent()));
	connect(ui.pushButton_StartGame, SIGNAL(clicked()), this, SLOT(StartGame()));
	
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(OpenPageLinkeUrl()));
}
GenshinImpactNaturalLaw::~GenshinImpactNaturalLaw()
{

}
void GenshinImpactNaturalLaw::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton &&
		ui.TitleLabelRect->frameRect().contains(event->globalPos() - this->frameGeometry().topLeft())) {
		m_Press = event->globalPos();
		leftBtnClk = true;
	}
	event->ignore();
}

void GenshinImpactNaturalLaw::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		leftBtnClk = false;
	}
	event->ignore();
}

void GenshinImpactNaturalLaw::mouseMoveEvent(QMouseEvent *event)
{
	if (leftBtnClk) {
		m_Move = event->globalPos();
		this->move(this->pos() + m_Move - m_Press);
		m_Press = m_Move;
	}
	event->ignore();
}

void GenshinImpactNaturalLaw::NewWidgetsSetting()
{
	if (WidgetsSetting == nullptr)
	{
		WidgetsSetting = new QtWidgetsSetting();
		connect(WidgetsSetting, SIGNAL(SendSettingToMainWidgets()), this, SLOT(ReceiveSettingFromWidgetsSetting()));
		connect(WidgetsSetting, SIGNAL(SendCloseSelfSignalToMainWidgets()), this, SLOT(ReceiveCloseSelfSignalFromWidgetsSetting()));
		WidgetsSetting->SetSetting(&setting);

		WidgetsSetting->setWindowModality(Qt::ApplicationModal);
		WidgetsSetting->move(this->x()+230, this->y()+103);
		WidgetsSetting->show();
	}
	else
	{
		WidgetsSetting->move(this->x() + 230, this->y() + 103);
		WidgetsSetting->show();
	}
	if (MainMaskLabel == nullptr)
	{
		MainMaskLabel = new QLabel(this);
		MainMaskLabel->setText("");
		MainMaskLabel->setGeometry(QRect(0, 0, 1280, 730));
		MainMaskLabel->setStyleSheet("background-color:rgba(0, 0, 0, 120);");
		MainMaskLabel->show();
	}
	else
	{
		MainMaskLabel->show();
	}
}
void GenshinImpactNaturalLaw::uiConnectButton()
{
	LinkeButtonList.clear();
	LinkeButtonList.push_back(ui.pushButton_Linke_1);
	LinkeButtonList.push_back(ui.pushButton_Linke_2);
	LinkeButtonList.push_back(ui.pushButton_Linke_3);
	LinkeButtonList.push_back(ui.pushButton_Linke_4);
	LinkeButtonList.push_back(ui.pushButton_Linke_5);

	LinkeButtonUrlList.clear();
	LinkeButtonUrlList.push_back(QUrl(QLatin1String("https://space.bilibili.com/135774602")));
	LinkeButtonUrlList.push_back(QUrl(QLatin1String("https://qm.qq.com/cgi-bin/qm/qr?k=3bd3tolWoA9vX-AdYzo-ynX_zUUB18oX&jump_from=webapi")));
	LinkeButtonUrlList.push_back(QUrl(QLatin1String("https://github.com/GengGode/GenshinImpact_AutoMap")));
	LinkeButtonUrlList.push_back(QUrl(QLatin1String("")));
	LinkeButtonUrlList.push_back(QUrl(QLatin1String("https://yuanshen.site/")));

	for (int i = 0; i < LinkeButtonList.size(); i++)
	{
		connect(LinkeButtonList[i], SIGNAL(clicked()), this, SLOT(OpenLinkeUrl()));
	}
}

void GenshinImpactNaturalLaw::uiConnectButtonLabel()
{
	LinkeButtonLabelList.clear();
	LinkeButtonLabelList.push_back(ui.pushButton_Page_1);
	LinkeButtonLabelList.push_back(ui.pushButton_Page_2);
	LinkeButtonLabelList.push_back(ui.pushButton_Page_3);
	LinkeButtonLabelList.push_back(ui.pushButton_Page_4);
	LinkeButtonLabelList.push_back(ui.pushButton_Page_5);
	LinkeButtonLabelList.push_back(ui.pushButton_Page_6);

	LinkeButtonLabelUrlList.clear();
	LinkeButtonLabelUrlList.push_back(QUrl(QLatin1String("https://www.bilibili.com/read/cv11018357")));
	LinkeButtonLabelUrlList.push_back(QUrl(QLatin1String("https://www.bilibili.com/read/cv11803430")));
	LinkeButtonLabelUrlList.push_back(QUrl(QLatin1String("")));
	LinkeButtonLabelUrlList.push_back(QUrl(QLatin1String("")));
	LinkeButtonLabelUrlList.push_back(QUrl(QLatin1String("")));
	LinkeButtonLabelUrlList.push_back(QUrl(QLatin1String("")));

	for (int i = 0; i < LinkeButtonLabelList.size(); i++)
	{
		connect(LinkeButtonLabelList[i], SIGNAL(clicked()), this, SLOT(OpenButtonLabelLinkeUrl()));
	}
}
void GenshinImpactNaturalLaw::CloseEvent()
{
	if (setting.is_exit_ismini)
	{
		this->hide();
	}
	else
	{
		close();
	}
}
void GenshinImpactNaturalLaw::StartGame()
{
	QString command = setting.Command_StartGame();
	//TCHAR szCmdLine[] = { TEXT("E:\\Genshin Impact\\Genshin Impact Game\\yuanshen.exe -popupwindow") };
	TCHAR szCmdLine[1024] = {};

	command.toWCharArray(szCmdLine);
	STARTUPINFO si;
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi;

	bool res = CreateProcess(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);




	if (!res)
	{
		DWORD err = GetLastError();
		if (err != 0)
		{
			res = 0;
		}
	}
	else
	{
		this->hide();
	}
}
void GenshinImpactNaturalLaw::OpenLinkeUrl()
{
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	for (int i = 0; i < LinkeButtonList.size(); i++)
	{
		if (btn == LinkeButtonList[i])
		{
			QDesktopServices::openUrl(LinkeButtonUrlList[i]);
		}
	}
}

void GenshinImpactNaturalLaw::OpenPageLinkeUrl()
{
QDesktopServices::openUrl(QUrl(QLatin1String("https://www.bilibili.com/video/BV1ar4y1A7c5")));
}

void GenshinImpactNaturalLaw::OpenButtonLabelLinkeUrl()
{
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	for (int i = 0; i < LinkeButtonLabelList.size(); i++)
	{
		if (btn == LinkeButtonLabelList[i])
		{
			QDesktopServices::openUrl(LinkeButtonLabelUrlList[i]);
		}
	}
}
void GenshinImpactNaturalLaw::TrayMenuClickEvent(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
	case QSystemTrayIcon::Trigger://单击托盘图标
		break;
	case QSystemTrayIcon::DoubleClick://双击托盘图标
		this->showNormal();
		break;
	default:
		break;
	}
}
void GenshinImpactNaturalLaw::ReceiveSettingFromWidgetsSetting()
{
	
}
void GenshinImpactNaturalLaw::ReceiveCloseSelfSignalFromWidgetsSetting()
{
	MainMaskLabel->hide();
}
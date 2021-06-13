#pragma once
#include <windows.h>
#include <vector>
#include <QDesktopServices>
#include <QTextCodec>
#include <QSystemTrayIcon>
#include <QDesktopServices>
#include <QAction>
#include <QMenu>
#include <QProcess>
#include <QMouseEvent>
#include <QtWidgets/QMainWindow>
#include "ui_GenshinImpactNaturalLaw.h"
#include "QtWidgetsSetting.h"
#include "SettingData.h"

class GenshinImpactNaturalLaw : public QMainWindow
{
    Q_OBJECT

public:
    GenshinImpactNaturalLaw(QWidget *parent = Q_NULLPTR);
	~GenshinImpactNaturalLaw();

private:
    Ui::GenshinImpactNaturalLawClass ui;

private:
	SettingData setting;

private:
	QPoint m_Press;
	QPoint m_Move;
	bool leftBtnClk = false;
	QtWidgetsSetting *WidgetsSetting = nullptr;
	QLabel *MainMaskLabel = nullptr;
	QMenu *TrayMenu;//托盘菜单
	QSystemTrayIcon *Tray;//托盘图标添加成员
	QAction *ShowMainAction;//托盘图标右键点击时弹出选项
	QAction *ExitAction;//托盘图标右键点击时弹出选项
private:
	std::vector<QPushButton*> LinkeButtonList;
	std::vector<QUrl> LinkeUrlList;
private:
	void uiConnectButton();
private:
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private slots:
	void NewWidgetsSetting();
	void StartGame();
	void OpenLinkeUrl();
	
	void TrayMenuClickEvent(QSystemTrayIcon::ActivationReason reason);
	// Receive Setting From WidgetsSetting
	void ReceiveSettingFromWidgetsSetting(SettingData *setting);
	void ReceiveCloseSelfSignalFromWidgetsSetting();
// signals:
};

#pragma once
//#include <qfont.h>
#include <qfontdatabase.h>
#include <qtimer.h>
#include <qpainter.h>
#include <QMouseEvent>
#include <QtWidgets/QMainWindow>
#include "ui_GenshinImpact_AutoMap.h"
#include "AutomaticTrackingMap.h"
#include "QtClassMyHotKeyObject.h"
#include "QtWidgetsClassMySelectGenshinImpactHandle.h"

////
#include <QDebug>

class GenshinImpact_AutoMap : public QMainWindow
{
    Q_OBJECT

public:
    GenshinImpact_AutoMap(QWidget *parent = Q_NULLPTR);
	~GenshinImpact_AutoMap();

private:
    Ui::GenshinImpact_AutoMapClass ui;

private:
	//×Ô¶¯×·×ÙµØÍ¼
	ATmap map;
	QCursor *myCursor;
	QtClassMyHotKeyObject *hotKeyAutoMode;
	QtClassMyHotKeyObject *hotKeyAddFlag;
	QtClassMyHotKeyObject *hotKeyActivationKongYingJiuGuan;
	QtClassMyHotKeyObject *hotKeyActivationSelectGenshinImpact;
	QtWidgetsClassMySelectGenshinImpactHandle *widgetsSelectGI = nullptr;
	vector<QPushButton*> UIObjList;
	void mapInit();

protected:
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void paintEvent(QPaintEvent *event);

private:
	void displayUID(int uid);

private:
	void uiHideButton();
	void uiShowButton();
	void uiConnectButton();
	void uiButtonToMap();
private:
	int Fps = 42;//ms
	QTimer *mapMessageLoopTimer;
	QTimer *uiObjListSleepTimer;
private slots:
	void runMap();

	void updataFrontEnd();
	void updataBackEnd();

	void setAutoMode();
	void setAddFlag();
	void setActivationKongYingJiuGuan();
	void setActivationSelectGenshinImpact();

	void setUIObjListShow();
	void setUIObjListHide();
	void setUIObjListToMapData();

	void getGenshinImpactWndHandleFromWidgets(HWND giHandle);
signals:

	void mapUpdata();
	void mapUpdataFrontEnd();
	void mapUpdataBackEnd();

};

#include "GenshinImpact_AutoMap.h"

GenshinImpact_AutoMap::GenshinImpact_AutoMap(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	uiHideButton();
	uiConnectButton();

	//创建刷新定时器
	mapMessageLoopTimer = new QTimer(this);
	mapMessageLoopTimer->start(Fps);//1000/30=33.3,1000/24=42
	connect(mapMessageLoopTimer, SIGNAL(timeout()), this, SLOT(runMap()));
	//创建UIObjList激活定时器
	uiObjListSleepTimer = new QTimer(this);
	uiObjListSleepTimer->setSingleShot(true);
	connect(uiObjListSleepTimer, SIGNAL(timeout()), this, SLOT(setUIObjListHide()));

	//添加全局快捷键
	hotKeyAutoMode = new QtClassMyHotKeyObject("Alt+T", this);
	connect(hotKeyAutoMode, SIGNAL(Activated()), this, SLOT(setAutoMode()));
	hotKeyAddFlag = new QtClassMyHotKeyObject("Alt+F", this);
	connect(hotKeyAddFlag, SIGNAL(Activated()), this, SLOT(setAddFlag()));
	hotKeyActivationKongYingJiuGuan = new QtClassMyHotKeyObject("Alt+M", this);
	connect(hotKeyActivationKongYingJiuGuan, SIGNAL(Activated()), this, SLOT(setActivationKongYingJiuGuan()));
	hotKeyActivationSelectGenshinImpact = new QtClassMyHotKeyObject("Alt+F8", this);
	connect(hotKeyActivationSelectGenshinImpact, SIGNAL(Activated()), this, SLOT(setActivationSelectGenshinImpact()));

	connect(ui.UIButton, SIGNAL(clicked()), this, SLOT(setUIObjListShow()));
	connect(ui.ExitButton, SIGNAL(mouseDoubleClickExitExe()), this, SLOT(close()));
	connect(this, &GenshinImpact_AutoMap::mapUpdataFrontEnd, this, &GenshinImpact_AutoMap::updataFrontEnd);
	connect(this, &GenshinImpact_AutoMap::mapUpdataBackEnd, this, &GenshinImpact_AutoMap::updataBackEnd);

	//设置鼠标指针
	myCursor = new QCursor(QPixmap(":/CurMain/resource/GenshinImpactCur.cur"), 2, 2);
	this->setCursor(*myCursor);

	//设置半透明无边框窗口
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	//ui.MainView->setAttribute(Qt::WA_TranslucentBackground);
	ui.MainView->setVisible(false);

	//设置UID字体
	int UIDFontId = QFontDatabase::addApplicationFont(":/UIDFont/resource/UIDFont.ttf");
	QString UIDFontName = QFontDatabase::applicationFontFamilies(UIDFontId).at(0);
	QFont UIDFont(UIDFontName,12);
	ui.UIDLabel->setFont(UIDFont);

	mapInit();
}

GenshinImpact_AutoMap::~GenshinImpact_AutoMap()
{
	delete myCursor;
	delete hotKeyAutoMode;
	delete hotKeyAddFlag;
	delete hotKeyActivationKongYingJiuGuan;
	delete hotKeyActivationSelectGenshinImpact;
	delete widgetsSelectGI;
}

void GenshinImpact_AutoMap::mapInit()
{
	map.Init((HWND)this->winId());
}

void GenshinImpact_AutoMap::mouseMoveEvent(QMouseEvent * event)
{
	if (map.MET.bLCD)
	{
		map.setMoveMapMovePos(event->x(), event->y());
		update();
	}
	if (map.MET.bMCD)
	{
		map.setOffsetMovePos(event->globalX(), event->globalY());
		map.setWindowsPos();
	}
}

void GenshinImpact_AutoMap::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		// 左键按下
		map.MET.bLCD = true;
		map.setMoveMapDownPos(event->x(), event->y());
	}
	if (event->button() == Qt::MidButton)
	{
		map.MET.bMCD = true;
		map.setOffsetDownPos(event->globalPos().x(), event->globalPos().y());
		map.CustomProcess(0);
	}
}

void GenshinImpact_AutoMap::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		// 左键按下
		map.MET.bLCD = false;
	}
	if (event->button() == Qt::MidButton)
	{
		map.MET.bMCD = false;
	}
}

void GenshinImpact_AutoMap::mouseDoubleClickEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		emit this->setAutoMode();
	}
}

void GenshinImpact_AutoMap::wheelEvent(QWheelEvent * event)
{
	map.setScaleMapDelta(event->x(), event->y(), event->delta());
	update();
}

void GenshinImpact_AutoMap::paintEvent(QPaintEvent * event)
{
	//设置画面为地图
	QPainter painter(this);
	painter.drawImage(0, 0, map.MainImg);
}

void GenshinImpact_AutoMap::displayUID(int uid)
{
	static int uidTmp = 0;
	static bool isInitDrawFinish = false;
	if (uidTmp != uid)
	{
		ui.UIDLabel->setText(QString::QString("UID: %1").arg(uid));
		uidTmp = uid;
	}
	if (!isInitDrawFinish)
	{
		if (map.isAutoMode)
		{
			if (map.isAutoInitFinish)
			{
				ui.MainView->setVisible(false);
				isInitDrawFinish = true;
			}
			else
			{
				ui.MainView->setVisible(true);
			}
		}
	}
}

void GenshinImpact_AutoMap::uiHideButton()
{
	ui.UIObjFlagButton->setVisible(false);
	ui.UIObjList0Button->setVisible(false);
	ui.UIObjList1Button->setVisible(false);
	ui.UIObjList2Button->setVisible(false);
	ui.UIObjList93Button->setVisible(false);
	ui.UIObjList94Button->setVisible(false);
	ui.UIObjList101Button->setVisible(false);
	ui.UIObjList102Button->setVisible(false);
	ui.UIObjList103Button->setVisible(false);
	ui.UIObjList104Button->setVisible(false);
	ui.UIObjList105Button->setVisible(false);
	ui.UIObjList205Button->setVisible(false);
	ui.UIDLabel->setVisible(true);
}

void GenshinImpact_AutoMap::uiShowButton()
{
	ui.UIObjFlagButton->setVisible(true);
	ui.UIObjList0Button->setVisible(true);
	ui.UIObjList1Button->setVisible(true);
	ui.UIObjList2Button->setVisible(true);
	ui.UIObjList93Button->setVisible(true);
	ui.UIObjList94Button->setVisible(true);
	ui.UIObjList101Button->setVisible(true);
	ui.UIObjList102Button->setVisible(true);
	ui.UIObjList103Button->setVisible(true);
	ui.UIObjList104Button->setVisible(true);
	ui.UIObjList105Button->setVisible(true);
	ui.UIObjList205Button->setVisible(true);
	ui.UIDLabel->setVisible(false);
}

void GenshinImpact_AutoMap::uiConnectButton()
{
	//UIObjList = new QPushButton*[11];
	//UIObjList[0] = ui.UIObjList0Button;
	//UIObjList[1] = ui.UIObjList1Button;
	//UIObjList[2] = ui.UIObjList2Button;
	//UIObjList[3] = ui.UIObjList93Button;
	//UIObjList[4] = ui.UIObjList94Button;
	//UIObjList[0] = ui.UIObjList101Button;
	//UIObjList[0] = ui.UIObjList6Button;
	//UIObjList[0] = ui.UIObjList0Button;
	//UIObjList[0] = ui.UIObjList0Button;
	//UIObjList[0] = ui.UIObjList0Button;
	//UIObjList[0] = ui.UIObjList0Button;
	UIObjList.clear();
	UIObjList.push_back(ui.UIObjList0Button);
	UIObjList.push_back(ui.UIObjList1Button);
	UIObjList.push_back(ui.UIObjList2Button);
	UIObjList.push_back(ui.UIObjList93Button);
	UIObjList.push_back(ui.UIObjList94Button);
	UIObjList.push_back(ui.UIObjList101Button);
	UIObjList.push_back(ui.UIObjList102Button);
	UIObjList.push_back(ui.UIObjList103Button);
	UIObjList.push_back(ui.UIObjList104Button);
	UIObjList.push_back(ui.UIObjList105Button);
	UIObjList.push_back(ui.UIObjList205Button);

	connect(ui.UIObjFlagButton, SIGNAL(clicked()), this, SLOT(setUIObjListToMapData()));
	connect(ui.UIObjList0Button, SIGNAL(clicked()), this, SLOT(setUIObjListToMapData()));
	connect(ui.UIObjList1Button, SIGNAL(clicked()), this, SLOT(setUIObjListToMapData()));
	connect(ui.UIObjList2Button, SIGNAL(clicked()), this, SLOT(setUIObjListToMapData()));
	connect(ui.UIObjList93Button, SIGNAL(clicked()), this, SLOT(setUIObjListToMapData()));
	connect(ui.UIObjList94Button, SIGNAL(clicked()), this, SLOT(setUIObjListToMapData()));
	connect(ui.UIObjList101Button, SIGNAL(clicked()), this, SLOT(setUIObjListToMapData()));
	connect(ui.UIObjList102Button, SIGNAL(clicked()), this, SLOT(setUIObjListToMapData()));
	connect(ui.UIObjList103Button, SIGNAL(clicked()), this, SLOT(setUIObjListToMapData()));
	connect(ui.UIObjList104Button, SIGNAL(clicked()), this, SLOT(setUIObjListToMapData()));
	connect(ui.UIObjList105Button, SIGNAL(clicked()), this, SLOT(setUIObjListToMapData()));
	connect(ui.UIObjList205Button, SIGNAL(clicked()), this, SLOT(setUIObjListToMapData()));
}

void GenshinImpact_AutoMap::runMap()
{
	static bool isUpdataEnd = true;
	//更新是否已结束
	if (isUpdataEnd)
	{
		isUpdataEnd = false;
		emit this->mapUpdataFrontEnd();
		emit this->mapUpdataBackEnd();
		isUpdataEnd = true;
		//启动下一帧
		mapMessageLoopTimer->start(Fps);
	}
	else
	{
		//启动下一帧
		mapMessageLoopTimer->start(Fps);
	}


}

void GenshinImpact_AutoMap::updataFrontEnd()
{
	//更新绘制图像
	map.FrontEndUpdata();
	displayUID(map.getUID());
	//绘制到窗口
	update();
}

void GenshinImpact_AutoMap::updataBackEnd()
{
	map.BackEndUpdata();
}

void GenshinImpact_AutoMap::setAutoMode()
{
	map.setAutoMode();
	if (map.isAutoMode)
	{
		ui.UIButton->setIcon(QIcon(":/IconUI/resource/UI0.ico"));
	}
	else
	{
		ui.UIButton->setIcon(QIcon(":/IconUI/resource/UI.ico"));
	}

}

void GenshinImpact_AutoMap::setAddFlag()
{
	//map.zerosMinMap;
	map.setAddFlagOnPos();
}

void GenshinImpact_AutoMap::setActivationKongYingJiuGuan()
{
	map.testSaveScreen();
	map.setKongYingJiuGuanState();
}

void GenshinImpact_AutoMap::setActivationSelectGenshinImpact()
{
	if (widgetsSelectGI == nullptr)
	{
		widgetsSelectGI = new QtWidgetsClassMySelectGenshinImpactHandle();
		connect(widgetsSelectGI, SIGNAL(SendGenshinImpactWndHandleToATM(HWND)), this, SLOT(getGenshinImpactWndHandleFromWidgets(HWND)));
		widgetsSelectGI->show();

	}
	else
	{
		widgetsSelectGI->show();

	}
}

void GenshinImpact_AutoMap::setUIObjListShow()
{
	ui.UIButton->setIcon(QIcon(":/IconUI/resource/UI1.ico"));

	uiShowButton();

	uiObjListSleepTimer->start(2000);
}

void GenshinImpact_AutoMap::setUIObjListHide()
{
	uiHideButton();

	if (map.isAutoMode)
	{
		ui.UIButton->setIcon(QIcon(":/IconUI/resource/UI0.ico"));
	}
	else
	{
		ui.UIButton->setIcon(QIcon(":/IconUI/resource/UI.ico"));
	}
}

void GenshinImpact_AutoMap::setUIObjListToMapData()
{
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	if (btn == ui.UIObjFlagButton) 
	{
		map.setObjFlagIsShow();
	}
	for (int i = 0; i < UIObjList.size(); i++)
	{
		if (btn == UIObjList[i])
		{
			map.setObjIsShow(i);
		}
	}
	//if (btn == ui.UIObjList0Button) 
	//{
	//	map.setObjIsShow(0);
	//}
	//if (btn == ui.UIObjList1Button) 
	//{
	//	map.setObjIsShow(1);
	//}
	//if (btn == ui.UIObjList2Button) 
	//{
	//	map.setObjIsShow(2);
	//}
	//if (btn == ui.UIObjList101Button)
	//{
	//	map.setObjIsShow(3);
	//}
}

void GenshinImpact_AutoMap::getGenshinImpactWndHandleFromWidgets(HWND giHandle)
{
	map.setGenshinImpactWndHandle(giHandle);
}



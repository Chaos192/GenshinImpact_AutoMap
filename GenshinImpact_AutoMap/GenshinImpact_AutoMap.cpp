#include "GenshinImpact_AutoMap.h"

GenshinImpact_AutoMap::GenshinImpact_AutoMap(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	uiConnectButton();
	uiHideButton();


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
	for (int i = 0; i < UIObjList.size(); i++)
	{
		UIObjList[i]->setVisible(false);
	}
	ui.UIDLabel->setVisible(true);
}

void GenshinImpact_AutoMap::uiShowButton()
{
	ui.UIObjFlagButton->setVisible(true);
	for (int i = 0; i < UIObjList.size(); i++)
	{
		UIObjList[i]->setVisible(true);
	}
	ui.UIDLabel->setVisible(false);
}

void GenshinImpact_AutoMap::uiConnectButton()
{
	UIObjList.clear();

	// 在此：添加新的按钮
	UIObjList.push_back(ui.UIObjList0Button); // 风神瞳
	UIObjList.push_back(ui.UIObjList1Button); // 岩神瞳
	UIObjList.push_back(ui.UIObjList2Button); // 绯红玉髓
	UIObjList.push_back(ui.UIObjList93Button); // 水晶矿
	UIObjList.push_back(ui.UIObjList94Button); // 石珀
	UIObjList.push_back(ui.UIObjList101Button); // 琉璃百合
	UIObjList.push_back(ui.UIObjList102Button); // 清心
	UIObjList.push_back(ui.UIObjList103Button); // 琉璃袋
	UIObjList.push_back(ui.UIObjList104Button); // 钩钩果
	UIObjList.push_back(ui.UIObjList105Button); // 小灯草
	UIObjList.push_back(ui.UIObjList205Button); // 星螺

	connect(ui.UIObjFlagButton, SIGNAL(clicked()), this, SLOT(setUIObjListToMapData()));
	for (int i = 0; i < UIObjList.size(); i++)
	{
		connect(UIObjList[i], SIGNAL(clicked()), this, SLOT(setUIObjListToMapData()));
	}
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

	uiObjListSleepTimer->start(2000);

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
}

void GenshinImpact_AutoMap::getGenshinImpactWndHandleFromWidgets(HWND giHandle)
{
	map.setGenshinImpactWndHandle(giHandle);
}



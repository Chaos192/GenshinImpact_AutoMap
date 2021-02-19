#include "GenshinImpact_AutoMap.h"

GenshinImpact_AutoMap::GenshinImpact_AutoMap(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	//刷新定时器
	mapMessageLoopTimer = new QTimer(this);
	mapMessageLoopTimer->start(16);//1000/30=33.3
	//mapMessageLoopTimer->setSingleShot(true);
	connect(mapMessageLoopTimer, SIGNAL(timeout()), this, SLOT(runMap()));
	connect(ui.ExitButton, SIGNAL(mouseDoubleClickExitExe()), this, SLOT(close()));
	connect(ui.AutoButton, SIGNAL(clicked()), this, SLOT(setAutoMode()));
	connect(this, &GenshinImpact_AutoMap::mapUpdataFrontEnd, this, &GenshinImpact_AutoMap::updataFrontEnd);
	connect(this, &GenshinImpact_AutoMap::mapUpdataBackEnd, this, &GenshinImpact_AutoMap::updataBackEnd);

	//设置鼠标指针
	myCursor = new QCursor(QPixmap(":/CurMain/resource/GenshinImpactCur.cur"), 2, 2);
	this->setCursor(*myCursor);

	//设置半透明无边框窗口
	//setWindowFlags(Qt::CustomizeWindowHint);
	//this->setWindowOpacity(0.9);
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	ui.MainView->setAttribute(Qt::WA_TranslucentBackground);

	mapInit();
}

void GenshinImpact_AutoMap::mapInit()
{
	map.Init((HWND)this->winId());
}

void GenshinImpact_AutoMap::mouseMoveEvent(QMouseEvent * event)
{
	if (map.MET.bLCD)
	{
		qDebug() << "mouse move " << event->x() << "," << event->y();
		map.setMouseMovePos(event->x(), event->y());
	}
}

void GenshinImpact_AutoMap::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton /*&& (event->buttons() & Qt::LeftButton)*/)
	{
		// 左键按下
		map.MET.bLCD = true;
		map.setMouseDownPos(event->x(), event->y());
		qDebug() << "mouse move setMouseDownPos" << event->x() << "," << event->y();
	}
}

void GenshinImpact_AutoMap::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton /*&& (event->buttons() & Qt::LeftButton)*/)
	{
		// 左键按下
		map.MET.bLCD = false;
		//map.setMouseUpPos(event->x(), event->y());
		qDebug() << "mouse move res" << event->x() << "," << event->y();
	}
}

void GenshinImpact_AutoMap::mouseDoubleClickEvent(QMouseEvent * event)
{
	static int i = 0;
	if (event->button() == Qt::LeftButton)
	{
		qDebug() << "mouse move double" << event->x() << "," << event->y();
		map.CustomProcess(i);
		i++;
	}
}

void GenshinImpact_AutoMap::wheelEvent(QWheelEvent * event)
{
	if (event->delta() > 0) {
		if (map.MET.scale > 0.5)
		{
			map.MET.scale /= 1.2;
		}
	}
	else {
		if (map.MET.scale < 6)
		{
			map.MET.scale *= 1.2;
		}
	}
}

void GenshinImpact_AutoMap::paintEvent(QPaintEvent * event)
{
	//设置画面为地图
	QPainter painter(this);
	painter.drawImage(0, 0, map.MainImg);
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
		mapMessageLoopTimer->start(16);
	}
	else
	{
		//启动下一帧
		mapMessageLoopTimer->start(16);
	}


}

void GenshinImpact_AutoMap::updataFrontEnd()
{
	//static int count = 0;
	//qDebug() << "Updata Front-End " << count++ << " ";
	
	//更新绘制图像
	map.FrontEndUpdata();
	//绘制到窗口
	update();
}

void GenshinImpact_AutoMap::updataBackEnd()
{
	//static int count = 0;
	//qDebug() << "Updata Back-End " << count++ << " ";
	map.BackEndUpdata();
}

void GenshinImpact_AutoMap::setAutoMode()
{
	map.setAutoMode();
	if (map.getAutoMode())
	{
		ui.AutoButton->setIcon(QIcon(":/IconAutoMode/resource/AutoModeSwitchOn.ico"));
		//ui.AutoButton->setIcon();
	}
	else
	{
		ui.AutoButton->setIcon(QIcon(":/IconAutoMode/resource/AutoModeSwitchOff.ico"));
	}
}


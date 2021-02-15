#include "GenshinImpact_AutoMap.h"

GenshinImpact_AutoMap::GenshinImpact_AutoMap(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	mapMessageLoopTimer = new QTimer(this);
	mapMessageLoopTimer->start(16);//1000/30=33.3
	//mapMessageLoopTimer->setSingleShot(true);
	connect(mapMessageLoopTimer, SIGNAL(timeout()), this, SLOT(runMap()));
	connect(this, &GenshinImpact_AutoMap::mapUpdataFrontEnd, this, &GenshinImpact_AutoMap::updataFrontEnd);
	connect(this, &GenshinImpact_AutoMap::mapUpdataBackEnd, this, &GenshinImpact_AutoMap::updataBackEnd);


	//设置无边框
	//setWindowFlags(Qt::CustomizeWindowHint);
	setWindowFlags(Qt::FramelessWindowHint);
	myCursor = new QCursor(QPixmap(":/CurMain/resource/cur3.cur"), 2,2);
	this->setCursor(*myCursor);
	//setWindowOpacity(0.7);

	setWindowFlag(Qt::FramelessWindowHint); /* 注意：如果单纯开启窗口透明层效果，在Windows系统中必须设置, 其他系统可忽略。*/
	setAttribute(Qt::WA_TranslucentBackground);

	this->setAttribute(Qt::WA_TranslucentBackground, true);

	map.Mat2QImage();
	//ui.MainView->setPixmap(QPixmap::fromImage(map.MainImg));

	ui.MainView->setAttribute(Qt::WA_TranslucentBackground);

	//label->setAttribute(Qt::WA_TranslucentBackground);

	//label->setStyleSheet("background:transparent");

	//map.getGiHandle();
	//map.getThisHandle((HWND)this->winId());
	//map.setWindowsPos();

	//connect(this, &GenshinImpact_AutoMap::mapUpdata, this, &GenshinImpact_AutoMap::runMap);
	//emit this->mapUpdata();
	qDebug() << "Init finish";

}

//bool GenshinImpact_AutoMap::eventFilter(QObject * watched, QEvent * event)
//{
//	switch (event->type())
//	{
//		case QEvent::MouseButtonPress:
//		{
//			if (watched == ui.MainView)
//			{
//
//			}
//			break;
//		}
//	}
//
//	return QWidget::eventFilter(watched, event);
//}

void GenshinImpact_AutoMap::mapinit()
{
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
		map.setMouseUpPos(event->x(), event->y());
		qDebug() << "mouse move setMouseUpPos" << event->x() << "," << event->y();
	}
}

void GenshinImpact_AutoMap::mouseDoubleClickEvent(QMouseEvent * event)
{
}

void GenshinImpact_AutoMap::wheelEvent(QWheelEvent * event)
{
}

void GenshinImpact_AutoMap::paintEvent(QPaintEvent * event)
{
	//设置画面为地图
	QPainter painter(this);
	painter.drawImage(0, 0, map.MainImg);

	//QPainter painter(this);
	///* 0x20为透明层颜色，可自定义设置为0x0到0xff */
	//painter.fillRect(this->rect(), QColor(0, 0, 0, 0x20));

	//QPainter p(this);
	//p.setCompositionMode(QPainter::CompositionMode_Clear);
	//p.fillRect(10, 10, 300, 300, Qt::SolidPattern);
}

void GenshinImpact_AutoMap::EventClickMove()
{
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


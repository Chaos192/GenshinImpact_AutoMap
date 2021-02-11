#include "GenshinImpact_AutoMap.h"

GenshinImpact_AutoMap::GenshinImpact_AutoMap(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	//ÉèÖÃÎÞ±ß¿ò
	//setWindowFlags(Qt::CustomizeWindowHint);
	setWindowFlags(Qt::FramelessWindowHint);
	myCursor = new QCursor(QPixmap(":/CurMain/resource/cur3.cur"), 2,2);
	this->setCursor(*myCursor);
}

void GenshinImpact_AutoMap::doubleClickExit()
{

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

void GenshinImpact_AutoMap::mouseMoveEvent(QMouseEvent * e)
{
	qDebug() << "mouse move "<<e->x()<<","<< e->y();
}

void GenshinImpact_AutoMap::EventClickMove()
{
}

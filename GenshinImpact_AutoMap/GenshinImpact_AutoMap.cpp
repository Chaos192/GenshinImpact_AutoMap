#include "GenshinImpact_AutoMap.h"

GenshinImpact_AutoMap::GenshinImpact_AutoMap(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	//设置无边框
	//setWindowFlags(Qt::CustomizeWindowHint);
	setWindowFlags(Qt::FramelessWindowHint);
	myCursor = new QCursor(QPixmap(":/CurMain/resource/cur3.cur"), 2,2);
	this->setCursor(*myCursor);
	//setWindowOpacity(0.7);
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	map.Mat2QImage();
	//ui.MainView->setPixmap(QPixmap::fromImage(map.MainImg));
	ui.MainView->setAttribute(Qt::WA_TranslucentBackground);
	//label->setAttribute(Qt::WA_TranslucentBackground);

	//label->setStyleSheet("background:transparent");
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

void GenshinImpact_AutoMap::paintEvent(QPaintEvent * event)
{
	QPixmap covert_pixmap(":/BackGroundImage/resource/bg1.png");// = QPixmap::fromImage(map.MainImg);// 
	QPixmap pixmap(covert_pixmap.width(), covert_pixmap.height());
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	QPoint start_point(0, 0);
	QPoint end_point(0, pixmap.height());
	//QLinearGradient进行渐变色设置
	QLinearGradient linear_gradient(start_point, end_point);
	linear_gradient.setColorAt(0, QColor(255, 255, 255, 100));
	linear_gradient.setColorAt(0.5, QColor(255, 255, 255, 150));
	linear_gradient.setColorAt(1, QColor(255, 255, 255, 255));
	painter.fillRect(this->rect(), QBrush(linear_gradient));
	painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
	painter.drawPixmap(0, 0, covert_pixmap);
	painter.end();

	QPainter painter2(this);
	painter2.drawPixmap(0, 0, pixmap);
}

void GenshinImpact_AutoMap::EventClickMove()
{
}

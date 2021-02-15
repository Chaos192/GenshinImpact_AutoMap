#pragma once
#include <qtimer.h>
#include <qpainter.h>
#include <QMouseEvent>
#include <QtWidgets/QMainWindow>
#include "ui_GenshinImpact_AutoMap.h"
#include "AutomaticTrackingMap.h"

////
#include <QDebug>

class GenshinImpact_AutoMap : public QMainWindow
{
    Q_OBJECT

public:
    GenshinImpact_AutoMap(QWidget *parent = Q_NULLPTR);

private:
    Ui::GenshinImpact_AutoMapClass ui;

private:
	//×Ô¶¯×·×ÙµØÍ¼
	ATmap map;
	QCursor *myCursor;
	//void eventMouseMove();
	//void updataMap();

protected:
	//bool eventFilter(QObject * watched, QEvent * event)override;
	void mouseMoveEvent(QMouseEvent *e);
	void paintEvent(QPaintEvent *event);

private:
	//timer = new QTimer(this);
	//connect(timer, SIGNAL(timeout()), this, SLOT(DrawLine()));
	QTimer *mapMessageLoopTimer;

private slots:
	void doubleClickExit();
	void EventClickMove();

	void runMap();

	void updataFrontEnd();
	void updataBackEnd();

signals:

	void mapUpdata();
	void mapUpdataFrontEnd();
	void mapUpdataBackEnd();

};

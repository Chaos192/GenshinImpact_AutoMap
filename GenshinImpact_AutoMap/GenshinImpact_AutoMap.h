#pragma once
#include <qtimer.h>
#include <qpainter.h>
#include <QMouseEvent>
#include <QtWidgets/QMainWindow>
#include "ui_GenshinImpact_AutoMap.h"
#include "AutomaticTrackingMap.h"
#include "QtClassMyHotKeyObject.h"

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
	//�Զ�׷�ٵ�ͼ
	ATmap map;
	QCursor *myCursor;
	QtClassMyHotKeyObject *hotKeyAutoMode;

	void mapInit();

protected:
	//bool eventFilter(QObject * watched, QEvent * event)override;
	//bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);


	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void paintEvent(QPaintEvent *event);

private:
	//timer = new QTimer(this);
	//connect(timer, SIGNAL(timeout()), this, SLOT(DrawLine()));
	QTimer *mapMessageLoopTimer;

private slots:
	void runMap();

	void updataFrontEnd();
	void updataBackEnd();

	void setAutoMode();
signals:

	void mapUpdata();
	void mapUpdataFrontEnd();
	void mapUpdataBackEnd();

};

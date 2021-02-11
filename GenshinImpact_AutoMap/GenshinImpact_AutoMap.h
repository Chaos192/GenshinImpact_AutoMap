#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GenshinImpact_AutoMap.h"
#include "AutomaticTrackingMap.h"

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

	void eventMouseMove();
	//void updataMap();

protected:
	bool eventFilter(QObject * watched, QEvent * event)override;

private:
	//timer = new QTimer(this);
	//connect(timer, SIGNAL(timeout()), this, SLOT(DrawLine()));

private slots:
	void doubleClickExit();
	void EventClickMove();
};

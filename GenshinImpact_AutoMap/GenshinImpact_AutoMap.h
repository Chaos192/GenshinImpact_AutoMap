#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GenshinImpact_AutoMap.h"

class GenshinImpact_AutoMap : public QMainWindow
{
    Q_OBJECT

public:
    GenshinImpact_AutoMap(QWidget *parent = Q_NULLPTR);

private:
    Ui::GenshinImpact_AutoMapClass ui;

private slots:
	void doubleClickExit();
	void EventClickMove();
};

#pragma once

#include <QWidget>
#include "ui_QtWidgetsClassMySelectGenshinImpactHandle.h"

class QtWidgetsClassMySelectGenshinImpactHandle : public QWidget
{
	Q_OBJECT

public:
	QtWidgetsClassMySelectGenshinImpactHandle(QWidget *parent = Q_NULLPTR);
	~QtWidgetsClassMySelectGenshinImpactHandle();

private:
	Ui::QtWidgetsClassMySelectGenshinImpactHandle ui;
};

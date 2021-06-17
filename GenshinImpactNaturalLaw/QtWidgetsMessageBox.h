#pragma once
#include <QWidget>
#include "ui_QtWidgetsMessageBox.h"

class QtWidgetsMessageBox : public QWidget
{
	Q_OBJECT

public:
	QtWidgetsMessageBox(QWidget *parent = Q_NULLPTR);
	~QtWidgetsMessageBox();

private:
	Ui::QtWidgetsMessageBox ui;

private slots:
	void CloseSelf();
signals:
	void SendCloseSelfSignalToSettingWidgets();
};

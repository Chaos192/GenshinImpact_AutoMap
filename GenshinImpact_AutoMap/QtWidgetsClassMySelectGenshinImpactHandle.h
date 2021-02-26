#pragma once

#include <QWidget>
#include <QMouseEvent>
#include "ui_QtWidgetsClassMySelectGenshinImpactHandle.h"
#include <iostream>
#include <Windows.h>
using namespace std;

class QtWidgetsClassMySelectGenshinImpactHandle : public QWidget
{
	Q_OBJECT

public:
	QtWidgetsClassMySelectGenshinImpactHandle(QWidget *parent = Q_NULLPTR);
	~QtWidgetsClassMySelectGenshinImpactHandle();

private:
	Ui::QtWidgetsClassMySelectGenshinImpactHandle ui;

private:
	string giName="";
	HWND giHandle = NULL;
	string giClass="";
	POINT pos;
	bool isStartSelect = false;

private:
	void displayWndInfo();
protected:
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
private slots:
	void SelectGenshinImpactWndStart();
	void SelectGenshinImpactWndOk();

signals:
	void SendGenshinImpactWndHandleToATM(HWND giHandle);
};

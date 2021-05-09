#include "QtWidgetsClassMySelectGenshinImpactHandle.h"

QtWidgetsClassMySelectGenshinImpactHandle::QtWidgetsClassMySelectGenshinImpactHandle(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	pos.x = 0;
	pos.y = 0;
}

QtWidgetsClassMySelectGenshinImpactHandle::~QtWidgetsClassMySelectGenshinImpactHandle()
{
}

void QtWidgetsClassMySelectGenshinImpactHandle::displayWndInfo()
{
	long long int nHandle = (long long int)giHandle;
	ui.lineEditName->setText(QString::fromLocal8Bit(giName.data()));
	ui.lineEditHandle->setText(QString::number(nHandle));
	ui.lineEditClass->setText(QString::fromLocal8Bit(giClass.data()));
}

void QtWidgetsClassMySelectGenshinImpactHandle::mouseMoveEvent(QMouseEvent * event)
{
	if (isStartSelect)
	{
		char classNameLis[256];
		char nameLis[256];

		pos.x = event->globalPos().x();
		pos.y = event->globalPos().y();

		giHandle = WindowFromPoint(pos);

		GetClassNameA(giHandle, classNameLis, 256);
		giClass = classNameLis;

		GetWindowTextA(giHandle, nameLis, 256);
		giName = nameLis;

		displayWndInfo();
	}
}

void QtWidgetsClassMySelectGenshinImpactHandle::mousePressEvent(QMouseEvent * event)
{
}

void QtWidgetsClassMySelectGenshinImpactHandle::mouseReleaseEvent(QMouseEvent * event)
{
	isStartSelect = false;
}

void QtWidgetsClassMySelectGenshinImpactHandle::SelectGenshinImpactWndStart()
{
	isStartSelect = true;
}

void QtWidgetsClassMySelectGenshinImpactHandle::SelectGenshinImpactWndOk()
{
	if (giHandle != NULL)
	{
		emit this->SendGenshinImpactWndHandleToATM(giHandle);
	}
	close();
}

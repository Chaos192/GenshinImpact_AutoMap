#include "QtWidgetsClassMySelectGenshinImpactHandle.h"

QtWidgetsClassMySelectGenshinImpactHandle::QtWidgetsClassMySelectGenshinImpactHandle(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//setAttribute(Qt::WA_DeleteOnClose);
	ui.ButtonSelect->setAttribute(Qt::WA_TransparentForMouseEvents, true);;
}

QtWidgetsClassMySelectGenshinImpactHandle::~QtWidgetsClassMySelectGenshinImpactHandle()
{
}

void QtWidgetsClassMySelectGenshinImpactHandle::displayWndInfo()
{
	ui.lineEditName->setText(QString::fromLocal8Bit(giName.data()));
	ui.lineEditHandle->setText(QString::number((unsigned int)giHandle));
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

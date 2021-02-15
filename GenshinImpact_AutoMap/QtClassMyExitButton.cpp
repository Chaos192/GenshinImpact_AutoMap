#include "QtClassMyExitButton.h"

QtClassMyExitButton::QtClassMyExitButton(QWidget *parent)
	: QPushButton(parent)
{

}

QtClassMyExitButton::~QtClassMyExitButton()
{
}

void QtClassMyExitButton::mouseDoubleClickEvent(QMouseEvent * ev)
{
	emit this->mouseDoubleClickExitExe();
}

#include "QtWidgetsMessageBox.h"

QtWidgetsMessageBox::QtWidgetsMessageBox(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);

	connect(ui.pushButton_OK, SIGNAL(clicked()), this, SLOT(CloseSelf()));
}

QtWidgetsMessageBox::~QtWidgetsMessageBox()
{
}

void QtWidgetsMessageBox::CloseSelf()
{
	this->SendCloseSelfSignalToSettingWidgets();
	this->close();
}

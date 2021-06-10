#include "QtWidgetsSetting.h"

QtWidgetsSetting::QtWidgetsSetting(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint|Qt::SubWindow);
	connect(ui.pushButton_Exit, SIGNAL(clicked()), this, SLOT(CloseSelf()));
}

QtWidgetsSetting::~QtWidgetsSetting()
{
}

void QtWidgetsSetting::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton &&
		ui.TitleLabelRect->frameRect().contains(event->globalPos() - this->frameGeometry().topLeft())) {
		m_Press = event->globalPos();
		leftBtnClk = true;
	}
	event->ignore();
}

void QtWidgetsSetting::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		leftBtnClk = false;
	}
	event->ignore();
}

void QtWidgetsSetting::mouseMoveEvent(QMouseEvent *event)
{
	if (leftBtnClk) {
		m_Move = event->globalPos();
		this->move(this->pos() + m_Move - m_Press);
		m_Press = m_Move;
	}
	event->ignore();
}

void QtWidgetsSetting::CloseSelf()
{
	this->SendCloseSelfSignalToMainWidgets();
	this->close();
}
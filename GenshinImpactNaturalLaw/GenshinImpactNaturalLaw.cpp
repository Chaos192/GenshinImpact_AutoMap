#include "GenshinImpactNaturalLaw.h"

GenshinImpactNaturalLaw::GenshinImpactNaturalLaw(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	connect(ui.pushButton_TitleSet, SIGNAL(clicked()), this, SLOT(NewWidgetsSetting()));
}

void GenshinImpactNaturalLaw::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton &&
		ui.TitleLabelRect->frameRect().contains(event->globalPos() - this->frameGeometry().topLeft())) {
		m_Press = event->globalPos();
		leftBtnClk = true;
	}
	event->ignore();
}

void GenshinImpactNaturalLaw::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		leftBtnClk = false;
	}
	event->ignore();
}

void GenshinImpactNaturalLaw::mouseMoveEvent(QMouseEvent *event)
{
	if (leftBtnClk) {
		m_Move = event->globalPos();
		this->move(this->pos() + m_Move - m_Press);
		m_Press = m_Move;
	}
	event->ignore();
}

void GenshinImpactNaturalLaw::NewWidgetsSetting()
{
	if (WidgetsSetting == nullptr)
	{
		WidgetsSetting = new QtWidgetsSetting();
		connect(WidgetsSetting, SIGNAL(SendSettingToMainWidgets(SettingData)), this, SLOT(ReceiveSettingFromWidgetsSetting(SettingData)));
		connect(WidgetsSetting, SIGNAL(SendCloseSelfSignalToMainWidgets()), this, SLOT(ReceiveCloseSelfSignalFromWidgetsSetting()));
		WidgetsSetting->setWindowModality(Qt::ApplicationModal);
		WidgetsSetting->move(this->x()+230, this->y()+103);
		WidgetsSetting->show();
	}
	else
	{
		WidgetsSetting->move(this->x() + 230, this->y() + 103);
		WidgetsSetting->show();
	}
	if (MainMaskLabel == nullptr)
	{
		MainMaskLabel = new QLabel(this);
		MainMaskLabel->setText("");
		MainMaskLabel->setGeometry(QRect(0, 0, 1280, 730));
		MainMaskLabel->setStyleSheet("background-color:rgb(0, 0, 0,120);");
		MainMaskLabel->show();
	}
	else
	{
		MainMaskLabel->show();
	}
}

void GenshinImpactNaturalLaw::ReceiveSettingFromWidgetsSetting(SettingData * setting)
{
}
void GenshinImpactNaturalLaw::ReceiveCloseSelfSignalFromWidgetsSetting()
{
	MainMaskLabel->hide();

}
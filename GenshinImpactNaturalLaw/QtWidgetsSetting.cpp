#include "QtWidgetsSetting.h"

QtWidgetsSetting::QtWidgetsSetting(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint|Qt::SubWindow);

	uiConnectButton();
	connect(ui.pushButton_Exit, SIGNAL(clicked()), this, SLOT(CloseSelf()));
	connect(ui.pushButton_Cancel, SIGNAL(clicked()), this, SLOT(Cancel()));
	connect(ui.pushButton_OK, SIGNAL(clicked()), this, SLOT(OK()));


}

QtWidgetsSetting::~QtWidgetsSetting()
{
}

void QtWidgetsSetting::uiConnectButton()
{
	UIButtonList.clear();
	UIButtonList.push_back(ui.pushButton_UI_GeneralSetting);
	UIButtonList.push_back(ui.pushButton_UI_GameSetting);
	UIButtonList.push_back(ui.pushButton_UI_ModuleSetting);
	UIButtonList.push_back(ui.pushButton_UI_ModuleResource);
	UIButtonList.push_back(ui.pushButton_UI_VersionInformation);

	ScrollLabelList.clear();
	ScrollLabelList.push_back(ui.label_Title_0);
	ScrollLabelList.push_back(ui.label_Title_1);
	ScrollLabelList.push_back(ui.label_Title_2);
	/************************************************************************************************************************************/
	ScrollLabelList.push_back(ui.label_Title_2);
	/************************************************************************************************************************************/
	ScrollLabelList.push_back(ui.label_Title_3);

	for (int i = 0; i < UIButtonList.size(); i++)
	{
		connect(UIButtonList[i], SIGNAL(clicked()), this, SLOT(SwitchOptions()));
	}
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
void QtWidgetsSetting::SetSetting(SettingData *setting)
{
	this->setting = setting;
	ui.lineEdit_Path_1->setText(setting->launcher_install_path.replace(QRegExp("/"), "\\"));
}
void QtWidgetsSetting::CloseSelf()
{
	this->SendCloseSelfSignalToMainWidgets();
	this->close();
}

void QtWidgetsSetting::Cancel()
{
	this->SendCloseSelfSignalToMainWidgets();
	this->close();
}
void QtWidgetsSetting::OK()
{
	this->SendCloseSelfSignalToMainWidgets();
	this->close();
}
void QtWidgetsSetting::SwitchOptions()
{
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	for (int i = 0; i < UIButtonList.size(); i++)
	{
		if (btn == UIButtonList[i])
		{
			QScrollBar *scrBar = ui.scrollArea->verticalScrollBar();
			QPropertyAnimation *scrBarAni = new QPropertyAnimation(scrBar, "value");
			scrBarAni->setStartValue(scrBar->value());
			scrBarAni->setEndValue(ScrollLabelList[i]->y());
			scrBarAni->setDuration(150);
			scrBarAni->start();
		}
	}
}


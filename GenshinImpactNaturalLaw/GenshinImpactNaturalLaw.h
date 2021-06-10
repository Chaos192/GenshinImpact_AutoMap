#pragma once
#include <QMouseEvent>
#include <QtWidgets/QMainWindow>
#include "ui_GenshinImpactNaturalLaw.h"
#include "QtWidgetsSetting.h"
#include "SettingData.h"

class GenshinImpactNaturalLaw : public QMainWindow
{
    Q_OBJECT

public:
    GenshinImpactNaturalLaw(QWidget *parent = Q_NULLPTR);

private:
    Ui::GenshinImpactNaturalLawClass ui;

private:
	SettingData setting;
private:
	QPoint m_Press;
	QPoint m_Move;
	bool leftBtnClk = false;
	QtWidgetsSetting *WidgetsSetting = nullptr;
	QLabel *MainMaskLabel = nullptr;
private:
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private slots:
	void NewWidgetsSetting();
	// Receive Setting From WidgetsSetting
	void ReceiveSettingFromWidgetsSetting(SettingData *setting);
	void ReceiveCloseSelfSignalFromWidgetsSetting();
// signals:
};

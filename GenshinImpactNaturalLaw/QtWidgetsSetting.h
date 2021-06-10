#pragma once
#include <QMouseEvent>
#include <QWidget>
#include "ui_QtWidgetsSetting.h"
#include "SettingData.h"

class QtWidgetsSetting : public QWidget
{
	Q_OBJECT

public:
	QtWidgetsSetting(QWidget *parent = Q_NULLPTR);
	~QtWidgetsSetting();

private:
	Ui::QtWidgetsSetting ui;

private:
	QPoint m_Press;
	QPoint m_Move;
	bool leftBtnClk = false;

private:
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
private slots:
	void CloseSelf();
signals:
	void SendSettingToMainWidgets(SettingData *setting);
	void SendCloseSelfSignalToMainWidgets();
};

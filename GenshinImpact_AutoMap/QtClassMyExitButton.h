#pragma once
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>

class QtClassMyExitButton : public QPushButton
{
	Q_OBJECT

public:
	QtClassMyExitButton(QWidget  *parent);
	~QtClassMyExitButton();

protected:
	void mouseDoubleClickEvent(QMouseEvent *ev); /*双击事件响应函数*/

signals:
	void mouseDoubleClickExitExe();
};

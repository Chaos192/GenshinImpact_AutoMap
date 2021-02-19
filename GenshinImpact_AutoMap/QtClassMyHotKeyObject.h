#pragma once
#include <QApplication>
#include <windows.h>
#include <QKeySequence>
#include <QHash>
#include "QtClassMyHotKayNativeEventFilter.h"

class QtClassMyHotKayNativeEventFilter;
class QtClassMyHotKeyObject :
	public QObject
{
	Q_OBJECT
public:
	QtClassMyHotKeyObject(QString key, QObject* app);
	~QtClassMyHotKeyObject();
	void ActivateHotKey();
	bool mRegisterHotKey();
	bool mUnregisterHotKey();
	QHash<QPair<quint32, quint32>, QtClassMyHotKeyObject*> hotKeyObject;
private:
	QApplication *hotKeyApp;
	QtClassMyHotKayNativeEventFilter *hotKeyEventFilter;
	QKeySequence hotKey;
	Qt::Key key;
	Qt::KeyboardModifiers mods;
	static quint32 nativeKeycode(Qt::Key keyCode);
	static quint32 nativeModifiers(Qt::KeyboardModifiers modifiers);
signals:
	void Activated();
};


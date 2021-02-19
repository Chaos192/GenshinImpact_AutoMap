#pragma once
#include <Windows.h>
#include <QApplication>
#include <QAbstractNativeEventFilter>
#include "QtClassMyHotKeyObject.h"
class QtClassMyHotKeyObject;
class QtClassMyHotKayNativeEventFilter :
	public QAbstractNativeEventFilter
{
public:
	QtClassMyHotKayNativeEventFilter(QtClassMyHotKeyObject *hotKeyObject);
	~QtClassMyHotKayNativeEventFilter();
	virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);
private:
	QtClassMyHotKeyObject *_hotKeyObject;
};

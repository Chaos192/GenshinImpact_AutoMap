#include "QtClassMyHotKayNativeEventFilter.h"

QtClassMyHotKayNativeEventFilter::QtClassMyHotKayNativeEventFilter(QtClassMyHotKeyObject * hotKeyObject)
	:_hotKeyObject(hotKeyObject)
{
}

QtClassMyHotKayNativeEventFilter::~QtClassMyHotKayNativeEventFilter()
{
}

bool QtClassMyHotKayNativeEventFilter::nativeEventFilter(const QByteArray & eventType, void * message, long * result)
{
	if (eventType == "windows_generic_MSG")
	{
		MSG *msg = static_cast<MSG *>(message);
		if (msg->message == WM_HOTKEY)
		{
			const quint32 keycode = HIWORD(msg->lParam);
			const quint32 modifiers = LOWORD(msg->lParam);
			bool res = _hotKeyObject->hotKeyObject.value(qMakePair(keycode, modifiers));
			if (res)
			{
				_hotKeyObject->ActivateHotKey();
				return true;
			}
		}

	}
	return false;
}

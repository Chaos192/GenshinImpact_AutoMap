#include "GenshinImpact_AutoMap.h"

GenshinImpact_AutoMap::GenshinImpact_AutoMap(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	//…Ë÷√Œﬁ±ﬂøÚ
	//setWindowFlags(Qt::CustomizeWindowHint);
	setWindowFlags(Qt::FramelessWindowHint);
}

void GenshinImpact_AutoMap::doubleClickExit()
{

}

void GenshinImpact_AutoMap::EventClickMove()
{
}

#include "GenshinImpact_AutoMap.h"

GenshinImpact_AutoMap::GenshinImpact_AutoMap(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	//ÉèÖÃÎÞ±ß¿ò
	//setWindowFlags(Qt::CustomizeWindowHint);
	setWindowFlags(Qt::FramelessWindowHint);
	map.Mat2QImage();
	ui.MainView->setPixmap(QPixmap::fromImage(map.MainImg));
}

void GenshinImpact_AutoMap::doubleClickExit()
{

}

void GenshinImpact_AutoMap::EventClickMove()
{
}

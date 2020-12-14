#include "GenshinImpact_AutoMap.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GenshinImpact_AutoMap w;
    w.show();
    return a.exec();
}

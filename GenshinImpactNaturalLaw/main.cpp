#include "GenshinImpactNaturalLaw.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GenshinImpactNaturalLaw w;
    w.show();
    return a.exec();
}

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGenshinImpactNaturalLaw.h"

class QtGenshinImpactNaturalLaw : public QMainWindow
{
    Q_OBJECT

public:
    QtGenshinImpactNaturalLaw(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtGenshinImpactNaturalLawClass ui;
};

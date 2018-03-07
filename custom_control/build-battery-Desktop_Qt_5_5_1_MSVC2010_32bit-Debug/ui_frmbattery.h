/********************************************************************************
** Form generated from reading UI file 'frmbattery.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMBATTERY_H
#define UI_FRMBATTERY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "battery.h"

QT_BEGIN_NAMESPACE

class Ui_frmBattery
{
public:
    QVBoxLayout *verticalLayout;
    Battery *widget;
    QSlider *horizontalSlider;

    void setupUi(QWidget *frmBattery)
    {
        if (frmBattery->objectName().isEmpty())
            frmBattery->setObjectName(QStringLiteral("frmBattery"));
        frmBattery->resize(500, 300);
        verticalLayout = new QVBoxLayout(frmBattery);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new Battery(frmBattery);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setValue(0);

        verticalLayout->addWidget(widget);

        horizontalSlider = new QSlider(frmBattery);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMaximum(100);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setInvertedControls(false);

        verticalLayout->addWidget(horizontalSlider);


        retranslateUi(frmBattery);
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), widget, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(frmBattery);
    } // setupUi

    void retranslateUi(QWidget *frmBattery)
    {
        frmBattery->setWindowTitle(QApplication::translate("frmBattery", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class frmBattery: public Ui_frmBattery {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMBATTERY_H

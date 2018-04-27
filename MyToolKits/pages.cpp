/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "pages.h"
#include <QDebug>
#include <string>
#include <stdio.h>
using namespace std;

ConfigurationPage::ConfigurationPage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *configGroup = new QGroupBox(tr("Server configuration"));

    QLabel *serverLabel = new QLabel(tr("Server:"));
    QComboBox *serverCombo = new QComboBox;
    serverCombo->addItem(tr("Qt (Australia)"));
    serverCombo->addItem(tr("Qt (Germany)"));
    serverCombo->addItem(tr("Qt (Norway)"));
    serverCombo->addItem(tr("Qt (People's Republic of China)"));
    serverCombo->addItem(tr("Qt (USA)"));

    QHBoxLayout *serverLayout = new QHBoxLayout;
    serverLayout->addWidget(serverLabel);
    serverLayout->addWidget(serverCombo);

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addLayout(serverLayout);
    configGroup->setLayout(configLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(configGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

UpdatePage::UpdatePage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *updateGroup = new QGroupBox(tr("Package selection"));
    QCheckBox *systemCheckBox = new QCheckBox(tr("Update system"));
    QCheckBox *appsCheckBox = new QCheckBox(tr("Update applications"));
    QCheckBox *docsCheckBox = new QCheckBox(tr("Update documentation"));

    QGroupBox *packageGroup = new QGroupBox(tr("Existing packages"));

    QListWidget *packageList = new QListWidget;
    QListWidgetItem *qtItem = new QListWidgetItem(packageList);
    qtItem->setText(tr("Qt"));
    QListWidgetItem *qsaItem = new QListWidgetItem(packageList);
    qsaItem->setText(tr("QSA"));
    QListWidgetItem *teamBuilderItem = new QListWidgetItem(packageList);
    teamBuilderItem->setText(tr("Teambuilder"));

    QPushButton *startUpdateButton = new QPushButton(tr("Start update"));

    QVBoxLayout *updateLayout = new QVBoxLayout;
    updateLayout->addWidget(systemCheckBox);
    updateLayout->addWidget(appsCheckBox);
    updateLayout->addWidget(docsCheckBox);
    updateGroup->setLayout(updateLayout);

    QVBoxLayout *packageLayout = new QVBoxLayout;
    packageLayout->addWidget(packageList);
    packageGroup->setLayout(packageLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(updateGroup);
    mainLayout->addWidget(packageGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(startUpdateButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

QueryPage::QueryPage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *packagesGroup = new QGroupBox(tr("Look for packages"));

    QLabel *nameLabel = new QLabel(tr("Name:"));
    QLineEdit *nameEdit = new QLineEdit;

    QLabel *dateLabel = new QLabel(tr("Released after:"));
    QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate());

    QCheckBox *releasesCheckBox = new QCheckBox(tr("Releases"));
    QCheckBox *upgradesCheckBox = new QCheckBox(tr("Upgrades"));

    QSpinBox *hitsSpinBox = new QSpinBox;
    hitsSpinBox->setPrefix(tr("Return up to "));
    hitsSpinBox->setSuffix(tr(" results"));
    hitsSpinBox->setSpecialValueText(tr("Return only the first result"));
    hitsSpinBox->setMinimum(1);
    hitsSpinBox->setMaximum(100);
    hitsSpinBox->setSingleStep(10);

    QPushButton *startQueryButton = new QPushButton(tr("Start query"));

    QGridLayout *packagesLayout = new QGridLayout;
    packagesLayout->addWidget(nameLabel, 0, 0);
    packagesLayout->addWidget(nameEdit, 0, 1);
    packagesLayout->addWidget(dateLabel, 1, 0);
    packagesLayout->addWidget(dateEdit, 1, 1);
    packagesLayout->addWidget(releasesCheckBox, 2, 0);
    packagesLayout->addWidget(upgradesCheckBox, 3, 0);
    packagesLayout->addWidget(hitsSpinBox, 4, 0, 1, 2);
    packagesGroup->setLayout(packagesLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(packagesGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(startQueryButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

FloatConvertionPage::FloatConvertionPage(QWidget *parent)
    : QWidget(parent)
{
    packagesGroup = new QGroupBox(QStringLiteral("单精度浮点数转换"));
    packagesGroup->setStyleSheet(
                                 "QGroupBox"
                                            "{"
                                            "border: 3px solid white;"//边框3px是粗细。white是颜色
                                            "border-radius:8px;"
                                            "margin-top:6px;"
                                            "font-size: 18px;"
                                            "font-weight: bold;"
                                            "}"
                                            "QGroupBox:title"
                                            "{"
                                            "color:black;"
                                            "subcontrol-origin: margin;"
                                            "subcontrol-position: top center;"
                                            "}"
                                   );

    resultTextEdit = new QTextEdit;

    nameLabel = new QLabel(QStringLiteral("请输入数值:"));
    nameLabel->setStyleSheet("font:bold;font-size:18px");
    inputEdit = new QLineEdit;
    lengthtipLabel = new QLabel(QStringLiteral("长度(1~25)"));

    convertiontipLabel = new QLabel(QStringLiteral("转换类型:"));
    convertiontipLabel->setStyleSheet("font:bold;font-size:18px");

    // 说明标签
    commentsLabel = new QLabel(QStringLiteral("\n【说明】\n* 单精度浮点数用来表示带有小数部分的实数,IEEE754规定，单精度浮点数用4个字节存储，包括符号位1位，阶码8位，尾数23位。其数值范围为-3.4E-38～3.4E+38，单精度浮点数最多有7位有效小数；\n* 字节在内存中的排列顺序，intel的cpu按little endian顺序(低字节在前)，motorola的cpu按big endian顺序（高字节在前）排列。"));
    commentsLabel->setWordWrap(true);
    commentsLabel->setStyleSheet("background-color: rgb(240, 240, 240);font-size:18px;color:black");

    // 转换类型选择 radiobutton
    convertionGroup = new QButtonGroup(this);
    Decimal2FloatCheckBox = new QRadioButton(QStringLiteral("十进制转十六进制单精度浮点数"));
    Float2DecimalCheckBox = new QRadioButton(QStringLiteral("十六进制单精度浮点数转十进制"));
    convertionGroup->addButton(Decimal2FloatCheckBox);
    convertionGroup->addButton(Float2DecimalCheckBox);
    Decimal2FloatCheckBox->setChecked(true);

    startConvertButton = new QPushButton(QStringLiteral("开始转换"));

    packagesLayout = new QGridLayout;
    packagesLayout->addWidget(resultTextEdit, 0, 0, 1 , 3);
    packagesLayout->addWidget(nameLabel, 1, 0);
    packagesLayout->addWidget(inputEdit, 1, 1);
    packagesLayout->addWidget(lengthtipLabel, 1, 2);
    packagesLayout->addWidget(convertiontipLabel , 2, 0);
    packagesLayout->addWidget(Decimal2FloatCheckBox, 3, 0);
    packagesLayout->addWidget(Float2DecimalCheckBox, 4, 0);
    packagesGroup->setLayout(packagesLayout);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(packagesGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(startConvertButton);
    mainLayout->addWidget(commentsLabel);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    // 连接信号
    connect(startConvertButton , SIGNAL(clicked(bool)) , this , SLOT(startConvert()));
}

void FloatConvertionPage::startConvert()
{
    resultTextEdit->clear(); // 清空
    resultTextEdit->setStyleSheet("background-color: rgb(255, 255, 255);font-size:20px;color:black"); // 设置格式

    QString strText = inputEdit->text();

    // 选择了 十进制转16进制单精度浮点数
    if(Decimal2FloatCheckBox->isChecked())
    {
        flh =strText.toFloat();
        memcpy(&(floatToHex[0]) , &flh , 4); //浮点数转为十六进制

        char str1[256] , str2[256];

        qDebug("\n倒序十六进制：\n%f=%02x %02x %02x %02x\n",flh,floatToHex[0],floatToHex[1],floatToHex[2],floatToHex[3]);//低位在前
        sprintf(str1 , "%f = %02x %02x %02x %02x\n",flh,floatToHex[0],floatToHex[1],floatToHex[2],floatToHex[3] );

        resultTextEdit->append(QStringLiteral("倒序十六进制(低字节在前，小端模式)：\n"));
        resultTextEdit->append(str1);

        qDebug("\n正序十六进制：\n%f=%02x %02x %02x %02x\n",flh,floatToHex[3],floatToHex[2],floatToHex[1],floatToHex[0] );//高位在前
        sprintf(str2 , "%f = %02x %02x %02x %02x\n",flh,floatToHex[3],floatToHex[2],floatToHex[1],floatToHex[0] );//高位在前

        resultTextEdit->append(QStringLiteral("正序十六进制(高字节在前，大端模式)：\n"));
        resultTextEdit->append(str2);
    }

    // 选择了 16进制单精度浮点数转十进制
    if(Float2DecimalCheckBox->isChecked())
    {         
        char str1[256] , str2[256];

        int length = strText.toLocal8Bit().length();
        if( length != 8)
        {
          qDebug("length error : %d !=8\n" , length);
          sprintf(str1 , "%d != 8\n", length);
          resultTextEdit->append(QStringLiteral("输入字符长度错误:\n"));
          resultTextEdit->append(str1);
          resultTextEdit->append(QStringLiteral("请重新输入8位16进制字符！\n"));

          return ;
        }

        int n = strText.toInt( 0 , 16);
        qDebug("%x" , n);

        float *f = (float *)&n; // 16进制浮点数转十进制
        qDebug("%f",*f);

        sprintf(str2 , "%s = %f\n", qPrintable(strText) , *f);
        resultTextEdit->append(QStringLiteral("十六进制转换为浮点数：\n"));
        resultTextEdit->append(str2);
    }
}

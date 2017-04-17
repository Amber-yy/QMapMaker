/********************************************************************************
** Form generated from reading UI file 'qmapmaker.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMAPMAKER_H
#define UI_QMAPMAKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QMapMakerClass
{
public:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;

    void setupUi(QWidget *QMapMakerClass)
    {
        if (QMapMakerClass->objectName().isEmpty())
            QMapMakerClass->setObjectName(QStringLiteral("QMapMakerClass"));
        QMapMakerClass->resize(980, 620);
        scrollArea = new QScrollArea(QMapMakerClass);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(0, 0, 700, 620));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 698, 618));
        scrollArea->setWidget(scrollAreaWidgetContents);
        scrollArea_2 = new QScrollArea(QMapMakerClass);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(705, 5, 270, 350));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 268, 348));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        pushButton_2 = new QPushButton(QMapMakerClass);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(800, 575, 75, 23));
        pushButton_3 = new QPushButton(QMapMakerClass);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(710, 575, 75, 23));
        pushButton_4 = new QPushButton(QMapMakerClass);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(890, 575, 75, 23));
        label = new QLabel(QMapMakerClass);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(705, 370, 54, 20));
        label_2 = new QLabel(QMapMakerClass);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(705, 420, 54, 20));
        label_3 = new QLabel(QMapMakerClass);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(705, 520, 54, 20));
        label_4 = new QLabel(QMapMakerClass);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(705, 470, 54, 20));
        lineEdit = new QLineEdit(QMapMakerClass);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(770, 370, 150, 20));
        lineEdit_2 = new QLineEdit(QMapMakerClass);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(770, 420, 150, 20));
        lineEdit_3 = new QLineEdit(QMapMakerClass);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(770, 470, 150, 20));
        lineEdit_4 = new QLineEdit(QMapMakerClass);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(770, 520, 150, 20));
        pushButton_5 = new QPushButton(QMapMakerClass);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(925, 370, 50, 20));
        pushButton_6 = new QPushButton(QMapMakerClass);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(925, 420, 50, 20));
        pushButton_7 = new QPushButton(QMapMakerClass);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(925, 470, 50, 20));
        pushButton_8 = new QPushButton(QMapMakerClass);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(925, 520, 50, 20));

        retranslateUi(QMapMakerClass);

        QMetaObject::connectSlotsByName(QMapMakerClass);
    } // setupUi

    void retranslateUi(QWidget *QMapMakerClass)
    {
        QMapMakerClass->setWindowTitle(QApplication::translate("QMapMakerClass", "QMapMaker", 0));
        pushButton_2->setText(QApplication::translate("QMapMakerClass", "\345\212\240\350\275\275\345\234\260\345\233\276", 0));
        pushButton_3->setText(QApplication::translate("QMapMakerClass", "\346\226\260\345\273\272\345\234\260\345\233\276", 0));
        pushButton_4->setText(QApplication::translate("QMapMakerClass", "\346\267\273\345\212\240\350\247\246\345\217\221", 0));
        label->setText(QApplication::translate("QMapMakerClass", "\350\270\251\350\270\217\350\247\246\345\217\221", 0));
        label_2->setText(QApplication::translate("QMapMakerClass", "\346\243\200\346\237\245\350\247\246\345\217\221", 0));
        label_3->setText(QApplication::translate("QMapMakerClass", "\350\247\246\347\242\260\350\247\246\345\217\221", 0));
        label_4->setText(QApplication::translate("QMapMakerClass", "\345\256\232\346\227\266\350\247\246\345\217\221", 0));
        pushButton_5->setText(QApplication::translate("QMapMakerClass", "\344\277\256\346\224\271", 0));
        pushButton_6->setText(QApplication::translate("QMapMakerClass", "\344\277\256\346\224\271", 0));
        pushButton_7->setText(QApplication::translate("QMapMakerClass", "\344\277\256\346\224\271", 0));
        pushButton_8->setText(QApplication::translate("QMapMakerClass", "\344\277\256\346\224\271", 0));
    } // retranslateUi

};

namespace Ui {
    class QMapMakerClass: public Ui_QMapMakerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMAPMAKER_H

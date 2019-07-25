/********************************************************************************
** Form generated from reading UI file 'qtgui_test.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUI_TEST_H
#define UI_QTGUI_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTGUI_TestClass
{
public:
    QWidget *centralWidget;
    QPushButton *start_button;
    QGroupBox *groupBox;
    QLabel *label;
    QLineEdit *a_text;
    QLabel *label_2;
    QLineEdit *b_text;
    QGroupBox *groupBox_2;
    QLabel *label_3;
    QLineEdit *c_text;
    QGroupBox *groupBox_3;
    QLabel *label_4;
    QLineEdit *c_text_2;
    QPushButton *stop_button;
    QPushButton *start_receive_image_button;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTGUI_TestClass)
    {
        if (QTGUI_TestClass->objectName().isEmpty())
            QTGUI_TestClass->setObjectName(QStringLiteral("QTGUI_TestClass"));
        QTGUI_TestClass->resize(449, 517);
        centralWidget = new QWidget(QTGUI_TestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        start_button = new QPushButton(centralWidget);
        start_button->setObjectName(QStringLiteral("start_button"));
        start_button->setGeometry(QRect(50, 350, 120, 40));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 381, 121));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 30, 72, 21));
        a_text = new QLineEdit(groupBox);
        a_text->setObjectName(QStringLiteral("a_text"));
        a_text->setGeometry(QRect(70, 20, 221, 31));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 80, 72, 21));
        b_text = new QLineEdit(groupBox);
        b_text->setObjectName(QStringLiteral("b_text"));
        b_text->setGeometry(QRect(70, 70, 221, 31));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 140, 381, 80));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 40, 72, 21));
        c_text = new QLineEdit(groupBox_2);
        c_text->setObjectName(QStringLiteral("c_text"));
        c_text->setGeometry(QRect(70, 30, 221, 31));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 240, 381, 80));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 40, 72, 21));
        c_text_2 = new QLineEdit(groupBox_3);
        c_text_2->setObjectName(QStringLiteral("c_text_2"));
        c_text_2->setGeometry(QRect(70, 30, 221, 31));
        stop_button = new QPushButton(centralWidget);
        stop_button->setObjectName(QStringLiteral("stop_button"));
        stop_button->setGeometry(QRect(230, 350, 120, 40));
        start_receive_image_button = new QPushButton(centralWidget);
        start_receive_image_button->setObjectName(QStringLiteral("start_receive_image_button"));
        start_receive_image_button->setGeometry(QRect(50, 400, 191, 40));
        QTGUI_TestClass->setCentralWidget(centralWidget);
        groupBox->raise();
        start_button->raise();
        groupBox_2->raise();
        groupBox_3->raise();
        stop_button->raise();
        start_receive_image_button->raise();
        menuBar = new QMenuBar(QTGUI_TestClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 449, 26));
        QTGUI_TestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QTGUI_TestClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QTGUI_TestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QTGUI_TestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QTGUI_TestClass->setStatusBar(statusBar);

        retranslateUi(QTGUI_TestClass);

        QMetaObject::connectSlotsByName(QTGUI_TestClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTGUI_TestClass)
    {
        QTGUI_TestClass->setWindowTitle(QApplication::translate("QTGUI_TestClass", "QTGUI_Test", nullptr));
        start_button->setText(QApplication::translate("QTGUI_TestClass", "\345\220\257\345\212\250\346\234\215\345\212\241\345\231\250", nullptr));
        groupBox->setTitle(QApplication::translate("QTGUI_TestClass", "\345\256\242\346\210\267\347\253\257\346\217\220\344\272\244\347\232\204\346\225\260\346\215\256\357\274\210A,B\357\274\211", nullptr));
        label->setText(QApplication::translate("QTGUI_TestClass", "A:", nullptr));
        label_2->setText(QApplication::translate("QTGUI_TestClass", "B:", nullptr));
        groupBox_2->setTitle(QApplication::translate("QTGUI_TestClass", "\346\234\215\345\212\241\347\253\257\345\244\204\347\220\206\347\232\204\347\273\223\346\236\234\357\274\210C= A + B\357\274\211", nullptr));
        label_3->setText(QApplication::translate("QTGUI_TestClass", "C\357\274\232", nullptr));
        c_text->setText(QString());
        groupBox_3->setTitle(QApplication::translate("QTGUI_TestClass", "\350\256\276\347\275\256\346\234\200\345\244\247\350\277\236\346\216\245\346\225\260", nullptr));
        label_4->setText(QApplication::translate("QTGUI_TestClass", "M\357\274\232", nullptr));
        c_text_2->setText(QApplication::translate("QTGUI_TestClass", "Not implement yet", nullptr));
        stop_button->setText(QApplication::translate("QTGUI_TestClass", "\345\201\234\346\255\242\346\234\215\345\212\241\345\231\250", nullptr));
        start_receive_image_button->setText(QApplication::translate("QTGUI_TestClass", "\345\220\257\345\212\250\350\216\267\345\217\226\345\233\276\345\203\217\346\234\215\345\212\241\345\231\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QTGUI_TestClass: public Ui_QTGUI_TestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUI_TEST_H

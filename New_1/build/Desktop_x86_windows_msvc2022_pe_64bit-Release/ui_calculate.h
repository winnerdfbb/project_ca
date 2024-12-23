/********************************************************************************
** Form generated from reading UI file 'calculate.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATE_H
#define UI_CALCULATE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Calculate
{
public:
    QAction *import_file;
    QAction *exit;
    QWidget *parameter;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_start;
    QPushButton *pushButton_stop;
    QPushButton *pushButton_end;
    QTableWidget *tableWidget;
    QProgressBar *progressBar;
    QFrame *frame_2;
    QPushButton *export_csv;
    QPushButton *export_excel;
    QPushButton *pushButton_clear;
    QMenuBar *menubar;
    QMenu *menu_pz;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Calculate)
    {
        if (Calculate->objectName().isEmpty())
            Calculate->setObjectName("Calculate");
        Calculate->resize(605, 383);
        import_file = new QAction(Calculate);
        import_file->setObjectName("import_file");
        exit = new QAction(Calculate);
        exit->setObjectName("exit");
        parameter = new QWidget(Calculate);
        parameter->setObjectName("parameter");
        frame = new QFrame(parameter);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 310, 41));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_start = new QPushButton(frame);
        pushButton_start->setObjectName("pushButton_start");

        horizontalLayout->addWidget(pushButton_start);

        pushButton_stop = new QPushButton(frame);
        pushButton_stop->setObjectName("pushButton_stop");

        horizontalLayout->addWidget(pushButton_stop);

        pushButton_end = new QPushButton(frame);
        pushButton_end->setObjectName("pushButton_end");

        horizontalLayout->addWidget(pushButton_end);

        tableWidget = new QTableWidget(parameter);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 39, 500, 281));
        progressBar = new QProgressBar(parameter);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(340, 10, 141, 23));
        progressBar->setValue(24);
        frame_2 = new QFrame(parameter);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(500, 40, 91, 281));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        export_csv = new QPushButton(frame_2);
        export_csv->setObjectName("export_csv");
        export_csv->setGeometry(QRect(10, 77, 71, 21));
        export_excel = new QPushButton(frame_2);
        export_excel->setObjectName("export_excel");
        export_excel->setGeometry(QRect(10, 37, 71, 21));
        pushButton_clear = new QPushButton(frame_2);
        pushButton_clear->setObjectName("pushButton_clear");
        pushButton_clear->setGeometry(QRect(10, 140, 71, 21));
        Calculate->setCentralWidget(parameter);
        menubar = new QMenuBar(Calculate);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 605, 18));
        menu_pz = new QMenu(menubar);
        menu_pz->setObjectName("menu_pz");
        Calculate->setMenuBar(menubar);
        statusbar = new QStatusBar(Calculate);
        statusbar->setObjectName("statusbar");
        Calculate->setStatusBar(statusbar);

        menubar->addAction(menu_pz->menuAction());
        menu_pz->addAction(import_file);
        menu_pz->addSeparator();
        menu_pz->addAction(exit);

        retranslateUi(Calculate);

        QMetaObject::connectSlotsByName(Calculate);
    } // setupUi

    void retranslateUi(QMainWindow *Calculate)
    {
        Calculate->setWindowTitle(QCoreApplication::translate("Calculate", "MainWindow", nullptr));
        import_file->setText(QCoreApplication::translate("Calculate", "\345\257\274\345\205\245\346\226\207\344\273\266", nullptr));
        exit->setText(QCoreApplication::translate("Calculate", "\351\200\200\345\207\272", nullptr));
        pushButton_start->setText(QCoreApplication::translate("Calculate", "\345\220\257\345\212\250", nullptr));
        pushButton_stop->setText(QCoreApplication::translate("Calculate", "\346\232\202\345\201\234", nullptr));
        pushButton_end->setText(QCoreApplication::translate("Calculate", "\347\273\223\346\235\237", nullptr));
        export_csv->setText(QCoreApplication::translate("Calculate", "\345\257\274\345\207\272(csv)", nullptr));
        export_excel->setText(QCoreApplication::translate("Calculate", "\345\257\274\345\207\272(excel)", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("Calculate", "\346\270\205\347\251\272", nullptr));
        menu_pz->setTitle(QCoreApplication::translate("Calculate", "\350\217\234\345\215\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Calculate: public Ui_Calculate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATE_H

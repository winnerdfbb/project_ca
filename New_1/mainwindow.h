#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calculate.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

//
extern QString db_name;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    Calculate *ca = new Calculate();
    void create_database();
    static QString inputval;

    ~MainWindow();


private slots:
    void new_window();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

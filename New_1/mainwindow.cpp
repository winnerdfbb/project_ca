#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculate.h"
#include<QDebug>
#include<QInputDialog>
#include<QTimer>

#include <QSqlDatabase>
#include <QSqlError>
#include<QSqlQuery>

#include <QCoreApplication>
#include <QSqlError>
#include<QMessageBox>
#include<QSqlTableModel>
#include<QSqlDatabase>
#include<QTableView>
#include<QSqlQueryModel>
QString MainWindow::inputval;   //inputval：作为自定义数据库名字

//
QString db_name = QString('a');

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //连接信号:点击新建弹出窗口
    connect(ui->action_new,&QAction::triggered,this,&MainWindow::new_window);

}

MainWindow::~MainWindow()
{
    delete ui;
}


//弹出新建窗口
void MainWindow::new_window()
{
    bool ok = false;
    // 获取字符串
    QLineEdit::EchoMode echoMode = QLineEdit::Normal;

    inputval = QInputDialog::getText(this, tr("新建"), tr("请输入文件名"), echoMode, tr("unknow"), &ok);
    if(ok)
    {
        //创建Inputval名字的数据库
        create_database();
        db_name=inputval;
        //延迟效果
        QTimer::singleShot(500,this,[=](){
            //设置场景的位置_0
            ca->setGeometry(this->geometry());
            //进入Caculate页面
            this->hide();
            ca->show();
        });
    }

}


void MainWindow::create_database()
{
    // 添加 SQLite 数据库连接
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    // 设置数据库连接属性
    db.setDatabaseName(inputval+".db");  // 设置数据库文件名

    // 打开数据库连接
    if (db.open()) {
        qDebug() << "Database connected successfully";

            // 创建数据表
            QSqlQuery createTableQuery;
            if (createTableQuery.exec("CREATE TABLE IF NOT EXISTS users_info (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, age INTEGER)")) {
                qDebug() << "Table created successfully";

                // 插入数据
                QSqlQuery insertDataQuery;
                if (insertDataQuery.exec("INSERT INTO users_info (name, age) VALUES ('John', 30), ('Alice', 25), ('Bob', 35),('John', 30), ('Alice', 25), ('Bob', 35),('John', 30), ('Alice', 25), ('Bob', 35),('John', 30), ('Alice', 25), ('Bob', 35),('John', 30), ('Alice', 25), ('Bob', 35),('John', 30), ('Alice', 25), ('Bob', 35),('John', 30), ('Alice', 25), ('Bob', 35),('John', 30), ('Alice', 25), ('Bob', 35),('John', 30), ('Alice', 25), ('Bob', 35)"
                )) {
                    qDebug() << "Data inserted successfully";
                } else {
                    qDebug() << "Data insertion error:" << insertDataQuery.lastError().text();

                }
            } else {
                qDebug() << "Table creation error:" << createTableQuery.lastError().text();
            }
            // 关闭数据库连接
            db.close();
        }
    else{
        qDebug() << "Database connection error:" << db.lastError().text();
    }

    //生成的地址在：E:\Qt_project\New_1\build\Desktop_x86_windows_msvc2022_pe_64bit-Release
}






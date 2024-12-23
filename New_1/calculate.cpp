#include "calculate.h"
#include "ui_calculate.h"

#include<QDebug>
#include<QTableView>
#include<QFileDialog>

#include <QMessageBox>
#include<QAxObject>

#include <QString>
#include <QTextStream>

#include<QSqlDatabase>
#include<QSqlQuery>
#include <QSqlError>
int Calculate::count = 0;
bool Calculate::flag = true;
bool Calculate::quit_show = false;
Calculate::Calculate(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculate)
{
    ui->setupUi(this);

    //一开始，进度条是隐藏的
    ui->progressBar->hide();

    //链接信号：导入配置文件
    connect(ui->import_file,&QAction::triggered,this,&Calculate::import_file);



}


Calculate::~Calculate()
{
    delete ui;
}

//开始启动按钮功能
void Calculate::on_pushButton_start_clicked()
{
    qDebug() << "启动！！！";
    //flag:检测是否按了暂停
    flag = true;
    qDebug() << flag;
        //显示表格
    // ui->tableWidget->show();

        //进度条显示:一开始进度为0
    progressBar_change(0);
        //数据显示
    while(flag==true&&count<=100)
    {
        //row：数据库中数据条数————————————————————————————
        count++;
        show_database();
        Delay(1000);
            //显示表格
            // create_table(row,5);
            //表格内显示数据
            create_data();
            // show_database();
            //进度条百分比进行计算！！！——————————————————
        progressBar_change(count);

    }

}

void Calculate::show_database(){
    //1.链接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    extern QString db_name;
    qDebug()<<"db_name:"<<db_name;
    QString base_name = db_name;
    qDebug() << base_name;
    db.setDatabaseName(base_name+".db");
        //判断是否打开链接上数据库
    if(db.open()){
        QSqlQuery query;
        int row =0;
        int columns = 0;
        //初始化行数
        QString sql = QString("select count(*) as row from users_info");
        query.exec(sql);
        if(query.first())
        {
            row =  query.value("row").toInt();
            count = row;    //设置进度条现在的进度
            qDebug()<<"row:"<<row;
            ui->tableWidget->setRowCount(row);
        }
        //默认列数为5；
        ui->tableWidget->setColumnCount(3);
    //2.设置表头
        ui->tableWidget->setHorizontalHeaderLabels({"项目名称","项目状态","当前模块"});
    //3.设置表格属性
        //点击选中一整行
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        //充满 横向
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        //不可编辑
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        sql = QString("select * from users_info ");
        query.exec(sql);
        for(int i = 0; query.next(); i++)
        {
            for(int j = 1; j < 4; j++)
            {
                ui->tableWidget->setItem(i,j-1, new QTableWidgetItem(query.value(j-1).toString()));

                qDebug() << query.value(j).toString();
            }
        }

    }
}

//暂停按钮
void Calculate::on_pushButton_stop_clicked()
{
    flag = false;
}

//终止按钮
void Calculate::on_pushButton_end_clicked()
{
    //终止：禁用开始 和 暂停 按钮
    ui->pushButton_start->setEnabled(false);
    ui->pushButton_stop->setEnabled(false);
}

//以表格的形式显示数据
void Calculate::create_table(int rows,int columns) {
    //设置几行几列
    ui->tableWidget->setRowCount(rows);
    ui->tableWidget->setColumnCount(columns);

    //表头标题
    QStringList headers;
    headers << "发射站" << "接收站" << "角度1" << "角度2" << "角度3";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    //点击选中一整行
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //充满 横向
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //不可编辑
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

//打开文件夹，并选择文件导入
void Calculate::import_file(){
    // 打开文件夹对话框，并设置初始路径和过滤器
    QString filePath = QFileDialog::getOpenFileName(this, "选择文件夹", "");
    QFile file(filePath);
    if(file.open(QFile::ReadOnly))
    {
        QMessageBox::information(this,"提示信息","文件已导入");
    }
    else{
        QMessageBox::warning(this,tr("警告信息"),tr("文件导入失败"));
    }
}

//显示数据（将数据库中的数据显示到表格中）————————————————————————————————————
void Calculate::create_data(){
    // qDebug()<<"show_data";
    // for(int i=0;i<rows;i++){
    //     for(int j=0;j<columns;j++)
    //         ui->tableWidget->setItem(i, j, new QTableWidgetItem(tr("abc_%1").arg(row)));
    // }
    //1.链接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    extern QString db_name;
    qDebug()<<"db_name:"<<db_name;
    QString base_name = db_name;
    qDebug() << base_name;
    db.setDatabaseName(base_name+".db");
    //2.插入数据
    if (db.open()) {
        qDebug() << "open db";
        // 插入数据
        QSqlQuery insertDataQuery;
        if (insertDataQuery.exec("INSERT INTO users_info (name, age) VALUES ('lily', 30)"
        )) {
            qDebug() << "Data inserted successfully";
        } else {
            qDebug() << "Data insertion error:" << insertDataQuery.lastError().text();

        }
        // 关闭数据库连接
        db.close();
    }
    else{
        qDebug() << "Database connection error:" << db.lastError().text();
    }

}

//导出excel、csv文件
void Calculate::on_export_excel_clicked()
{
    qDebug() << "excel";
    //获取保存路径
    QString filepath=QFileDialog::getSaveFileName(this,tr("Save"),".",tr(" (*.xlsx)"));
    if(!filepath.isEmpty())
    {
        qDebug() << "excel1";
        statusBar()->showMessage(tr("正在导出数据。。。。。。"));
        QAxObject *excel = new QAxObject(this);
        //连接Excel控件
        excel->setControl("Excel.Application");
        //不显示窗体
        excel->dynamicCall("SetVisible (bool Visible)","false");
        //不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
        excel->setProperty("DisplayAlerts", false);
        //获取工作簿集合
        QAxObject *workbooks = excel->querySubObject("WorkBooks");
        //新建一个工作簿
        workbooks->dynamicCall("Add");
        //获取当前工作簿
        QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
        //获取工作表集合
        QAxObject *worksheets = workbook->querySubObject("Sheets");
        //获取工作表集合的工作表1，即sheet1
        QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);

        //设置表头值
        for(int i=1;i<ui->tableWidget->columnCount()+1;i++)
        {
            //设置设置某行某列
            QAxObject *Range = worksheet->querySubObject("Cells(int,int)", 1, i);
            Range->dynamicCall("SetValue(const QString &)",ui->tableWidget->horizontalHeaderItem(i-1)->text());
            qDebug()<<ui->tableWidget->horizontalHeaderItem(i-1)->text();
        }

        //设置表格数据
        for(int i = 1;i<ui->tableWidget->rowCount()+1;i++)
        {
            qDebug()<<"excel here1";
            qDebug()<<ui->tableWidget->rowCount();
            qDebug()<<"excel here2";
            qDebug()<<ui->tableWidget->columnCount();
            qDebug()<<"excel here3";
            for(int j = 1;j<ui->tableWidget->columnCount()+1;j++)
            {

                QAxObject *Range = worksheet->querySubObject("Cells(int,int)", i+1, j);
                Range->dynamicCall("SetValue(const QString &)",ui->tableWidget->item(i-1,j-1)->text());
                qDebug()<<ui->tableWidget->item(i-1,j-1)->text();
                qDebug()<<"excel here_"<< j;
            }
            qDebug()<<"excel here4";
        }
        qDebug()<<"excel here";
        workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(filepath));//保存至filepath
        workbook->dynamicCall("Close()");//关闭工作簿
        excel->dynamicCall("Quit()");//关闭excel
        delete excel;
        excel=NULL;
        statusBar()->showMessage(tr("导出成功"));
        qDebug() << "\n导出成功啦！！！";
    }
}


void Calculate::on_export_csv_clicked()
{
    //1.选择导出的csv文件保存路径
    // QString csvFile = QFileDialog::getExistingDirectory(this);
    QString csvFile=QFileDialog::getSaveFileName(this,tr("Save"),".",tr(" (*.csv)"));
    if(csvFile.isEmpty())
        return;

    //3.用QFile打开.csv文件 如果不存在则会自动新建一个新的文件
    QFile file(csvFile);
    if ( file.exists())
    {
        //如果文件存在执行的操作，此处为空，因为文件不可能存在
    }
    file.open( QIODevice::ReadWrite | QIODevice::Text );
    statusBar()->showMessage(tr("正在导出数据。。。。。。"));
    // QTextStream out(&file);

    QString conTents;
    QTextStream stream(&file);
    QHeaderView * header = ui->tableWidget->horizontalHeader() ;
    if (header)
    {
        for ( int i = 0; i < header->count(); i++ )
            {
                QTableWidgetItem *item = ui->tableWidget->horizontalHeaderItem(i);
                if (!item)
                {
                    continue;
                }
                conTents += item->text() + ",";
            }
            conTents += "\n";
    }

    // QTextStream stream(&file);
    qDebug() << ui->tableWidget->rowCount();
                qDebug() << ui->tableWidget->columnCount();
        for ( int i = 0 ; i < ui->tableWidget->rowCount(); i++ )
        {
            for ( int j = 0; j < ui->tableWidget->columnCount(); j++ )
            {

                QTableWidgetItem* item = ui->tableWidget->item(i, j);
                if ( !item )
                    continue;
                QString str = item->text();
                str.replace(","," ");
                conTents += str + ",";
            }
            conTents += "\n";
        }
        stream << conTents;



    //5.写完数据需要关闭文件
    file.close();
    statusBar()->showMessage(tr("导出完成"));
    qDebug() << "\n导出成功啦！！！";
}


//清空数据
void Calculate::on_pushButton_clear_clicked()
{
    ui->tableWidget->clear();
    // ui->tableWidget->hide();
    // ui->tableWidget->setShowGrid(false);
    ui->progressBar->hide();
    for(int i=0;i<count;++i){
        ui->tableWidget->removeRow(0);
    }
    count=0;
}

//进度条
void Calculate::progressBar_change(int now_count)
{
    ui->progressBar->show();
    ui->progressBar->setValue(now_count);
}

//延迟函数
void Calculate::Delay(int mesc)
{
    QTime _Timer = QTime::currentTime().addMSecs(mesc);
    while( QTime::currentTime() < _Timer )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

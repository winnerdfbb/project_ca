#ifndef CALCULATE_H
#define CALCULATE_H

#include <QMainWindow>

namespace Ui {
class Calculate;
}

class Calculate : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculate(QWidget *parent = nullptr);

    void create_table(int rows,int columns);
    void create_data();
    void show_database();
    void progressBar_change(int now_count);
    void Delay(int mesc);
    ~Calculate();

    static int count;
    static bool flag;
    static bool quit_show;

    // MainWindow *mw = new MainWindow();


private slots:

    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_end_clicked();

    void import_file();

    void on_export_excel_clicked();

    void on_export_csv_clicked();

    void on_pushButton_clear_clicked();

private:
    Ui::Calculate *ui;

};


#endif // CALCULATE_H

#ifndef WORKWITHDATABASE_H
#define WORKWITHDATABASE_H

#include <QDialog>
#include "addinfo.h"
namespace Ui {
class WorkWithDatabase;
}

class WorkWithDatabase : public QDialog
{
    Q_OBJECT

public:
    explicit WorkWithDatabase(QWidget *parent = nullptr);
    ~WorkWithDatabase();

private slots:
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();
    void refreshData();

    void on_pushButton_4_clicked();

private:
    Ui::WorkWithDatabase *ui;
    AddInfo *  win1;
};

#endif // WORKWITHDATABASE_H

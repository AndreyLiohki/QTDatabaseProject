#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->resize(800, 600);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(205, 92, 92));
    this->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LoginButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Order.db");
    if(!db.open()){
        QMessageBox::warning(this, "Database error", "Troubles with your database"+ QString(db.lastError().text()));
        return;
    }
    QSqlQuery qry;
    QString login = ui->LoginLine->text();
    QString password = ui->passwordLine->text();
    qry.prepare("SELECT COUNT(*) FROM User WHERE login = :login AND password = :password");
    qry.bindValue(":login", login);
    qry.bindValue(":password", password);
    qry.exec();

    if(qry.next()){
        int count = qry.value(0).toInt();
        if(count>0){
            hide();
            workingwindow = new WorkWithDatabase(this);
            workingwindow->show();

        }else{
            QMessageBox::warning(this, "login", "login or passwords is wrong");
        }
    }

}


void MainWindow::on_pushButton_clicked()
{
    registrationdialog = new registrationform(this);
    registrationdialog->show();
}


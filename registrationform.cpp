#include "registrationform.h"
#include "ui_registrationform.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include "Validator.h"
registrationform::registrationform(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registrationform)
{
    ui->setupUi(this);
    this->resize(800, 600);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(113, 75, 92));
    this->setPalette(palette);
}

registrationform::~registrationform()
{
    delete ui;
}

void registrationform::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Order.db");
    if(!db.open()){
        QMessageBox::critical(this, "Database error", "Troubles with your database "+ QString(db.lastError().text()));
        return;
    }
    QSqlQuery qry;
    QString newlogin = "";
    QString newpassword = "";
    QString newid = "";
    qry.prepare("SELECT MAX(id) FROM User");
    if(!qry.exec()){
        QMessageBox::critical(this, "Database error", qry.lastError().text());
        return;
    }
    if(qry.next()){
        newid = QString::number(qry.value(0).toInt() + 1);
    }

    bool isLoginValid = false;
    bool isPasswordValid = false;
    validator password;
    validator login;
    newlogin = ui->lineEdit->text();
    newpassword = ui->lineEdit_2->text();
    if (!isLoginValid || !isPasswordValid) {

        isLoginValid = login.validlogin(newlogin);
        isPasswordValid = password.validpassword(newpassword);

        if (!isLoginValid || !isPasswordValid) {
            QMessageBox::critical(this, "Validation error", "Non-valid login or password");
            hide();
            return;
        }
    }
    qry.prepare("SELECT COUNT(*) FROM User WHERE login = :login");
    qry.bindValue(":login", newlogin);
    qry.exec();
    if(qry.next()){
        int count = qry.value(0).toInt();
        if(count>0){
            QMessageBox::warning(this, "login", "User with such login has already registered");
        }else{
            qry.prepare("INSERT INTO User (id, Login, Password) VALUES(:val1, :val2, :val3)");
            qry.bindValue(":val1", newid);
            qry.bindValue(":val2", newlogin);
            qry.bindValue(":val3", newpassword);
            if(!qry.exec()){
                QMessageBox::critical(this, "Database error", qry.lastError().text());
                return;
            }
            QMessageBox::warning(this, "Registration", "Registration successful");
            db.close();

            hide();
        }
    }


}


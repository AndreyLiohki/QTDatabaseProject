#include "workwithdatabase.h"
#include "ui_workwithdatabase.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>
bool type1 = false;
bool type2 = false;
WorkWithDatabase::WorkWithDatabase(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WorkWithDatabase)
{
    ui->setupUi(this);
    this->resize(800, 600);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(113, 75, 234));
    this->setPalette(palette);
}

WorkWithDatabase::~WorkWithDatabase()
{
    delete ui;
}

void WorkWithDatabase::on_radioButton_clicked()
{
    type1 = true;
    type2 = false;
    ui->textEdit_2->setVisible(true);
    ui->textEdit_3->setVisible(true);
    ui->textEdit_4->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
}

void WorkWithDatabase::on_radioButton_2_clicked()
{
    type1 = false;
    type2 = true;
    ui->textEdit_2->setVisible(true);
    ui->textEdit_3->setVisible(true);
    ui->textEdit_4->setVisible(false);
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(false);
}

void WorkWithDatabase::on_pushButton_2_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Order.db");
    if(!db.open()){
        QMessageBox::warning(this, "Database error", "Troubles with your database"+ QString(db.lastError().text()));
        return;
    }
    QSqlQuery qry;
    QString final ="";
    if(!qry.exec("SELECT * FROM Flower")){
        ui->textEdit->setText("Error with query");
    }else{

        while(qry.next()){
            final+=(QString(qry.value(1).toString()) + " " + QString(qry.value(2).toString()) + " " + QString(qry.value(3).toString()) + "\n");
        }
        final += "------------------------------------------------------------------------------------";
        final +="\n";

    }
    if(!qry.exec("SELECT * FROM Composition")){
        ui->textEdit->setText("Error with query");
    }else{

        while(qry.next()){
            final+=(QString(qry.value(1).toString()) + " " + QString(qry.value(2).toString()) + " " + "\n");
        }
        final += "------------------------------------------------------------------------------------";
        final +="\n";

    }
    if(!qry.exec("SELECT * FROM User")){
        ui->textEdit->setText("Error with query");
    }else{

        while(qry.next()){
            final+=(QString(qry.value(1).toString()) + " " + QString(qry.value(2).toString()) + " "+ "\n");
        }
        final += "------------------------------------------------------------------------------------";

    }
    ui->textEdit->setText(final);
}

void WorkWithDatabase::refreshData()
{
    on_pushButton_2_clicked();
}
void WorkWithDatabase::on_pushButton_clicked()
{
    connect(win1, &AddInfo::databaseUpdated, this, &WorkWithDatabase::refreshData);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Order.db");
    if(!db.open()){
        ui->textEdit->setText("Error: " + db.lastError().text());
        return;
    }

    QSqlQuery qry;
    QString name="";
    QString type="";
    QString cost="";
    QString id="";
    if(type1){
        name = ui->textEdit_2->toPlainText();
        cost = ui->textEdit_3->toPlainText();
        type = ui->textEdit_4->toPlainText();
        qry.prepare("SELECT COUNT(*) FROM Flower WHERE Name = :name AND Type = :type");
        qry.bindValue(":name", name);
        qry.bindValue(":type", type);
        if(!qry.exec()){
            QMessageBox::critical(this, "Database error", qry.lastError().text());
            return;
        }
        qry.next();
        int count = qry.value(0).toInt();
        if(count>0){
            QMessageBox::critical(this, "Slot error", "There is already such slot");
            return;
        }
        qry.prepare("SELECT MAX(id) FROM Flower");
        if(!qry.exec()){
            QMessageBox::critical(this, "Database error", qry.lastError().text());
            return;
        }
        if(qry.next()){
            id = QString::number(qry.value(0).toInt() + 1);
        }
        qry.prepare("INSERT INTO Flower (id, Name, Type, Cost) VALUES (:id, :name, :type, :cost)");
        qry.bindValue(":id", id);
        qry.bindValue(":name", name);
        qry.bindValue(":type", type);
        qry.bindValue(":cost", cost);
        if(!qry.exec()){
            qDebug() << "Error:" << qry.lastError().text();
        } else {
            qDebug()<<"Successes";
            db.commit();
            db.close();
            on_pushButton_2_clicked();
        }
    }
    if(type2){
        name = ui->textEdit_2->toPlainText();
        cost = ui->textEdit_3->toPlainText();
        qry.prepare("SELECT COUNT(*) FROM Composition WHERE Name = :name");
        qry.bindValue(":name", name);
        if(!qry.exec()){
            QMessageBox::critical(this, "Database error", qry.lastError().text());
            return;
        }
        qry.next();
        int count = qry.value(0).toInt();
        if(count>0){
            QMessageBox::critical(this, "Slot error", "There is already such slot");
            return;
        }
        qry.prepare("SELECT MAX(id) FROM Composition");
        if(!qry.exec()){
            QMessageBox::critical(this, "Database error", qry.lastError().text());
            return;
        }
        if(qry.next()){
            id = QString::number(qry.value(0).toInt() + 1);
        }
        qry.prepare("INSERT INTO Composition (id, Name, Cost) VALUES (:id, :name, :cost)");
        qry.bindValue(":id", id);
        qry.bindValue(":name", name);
        qry.bindValue(":cost", cost);
        if(!qry.exec()){
            qDebug() << "Error:" << qry.lastError().text();
        } else {
            qDebug()<<"Successes";
            db.commit();
            db.close();
            on_pushButton_2_clicked();
        }
    }

}

void WorkWithDatabase::on_pushButton_3_clicked()
{
    win1 = new AddInfo(this);
    win1->show();
}


void WorkWithDatabase::on_pushButton_4_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Order.db");
    if(!db.open()){
        ui->textEdit->setText("Error: " + db.lastError().text());
        return;
    }
    QSqlQuery qry;
    qry.prepare("DELETE FROM Flower");
    qry.exec();
    qry.prepare("DELETE FROM Composition");
    qry.exec();
    qry.prepare("DELETE FROM User");
    qry.exec();
    db.commit();

}


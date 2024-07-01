#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include <QDialog>

namespace Ui {
class registrationform;
}

class registrationform : public QDialog
{
    Q_OBJECT

public:
    explicit registrationform(QWidget *parent = nullptr);
    ~registrationform();

private slots:
    void on_pushButton_clicked();

private:
    Ui::registrationform *ui;
};

#endif // REGISTRATIONFORM_H

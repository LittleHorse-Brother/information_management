#ifndef DIALOG_ADD_H
#define DIALOG_ADD_H

#include <QDialog>
#include "student.h"

namespace Ui {
class Dialog_Add;
}

class Dialog_Add : public QDialog
{
    Q_OBJECT


public:
    explicit Dialog_Add(QWidget *parent = nullptr);
    ~Dialog_Add();
public:
    Student information;

private slots:
    void on_pushButton_clicked();


private:
    Ui::Dialog_Add *ui;

};

#endif // DIALOG_ADD_H

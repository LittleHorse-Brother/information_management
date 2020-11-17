#include "dialog_add.h"
#include "ui_dialog_add.h"

Dialog_Add::Dialog_Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Add)
{
    ui->setupUi(this);
}

Dialog_Add::~Dialog_Add()
{
    delete ui;
}

void Dialog_Add::on_pushButton_clicked()
{
    information.name=(ui->lineEdit->text().toStdString());
    information.id=(ui->lineEdit_2->text().toStdString());
    information.cellphone=(ui->lineEdit_3->text().toStdString());
    accept();

}


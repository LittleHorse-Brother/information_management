#include "cellwidget.h"
#include "ui_cellwidget.h"

cellwidget::cellwidget(QTreeWidgetItem* rowid, QWidget *parent) :
    QWidget(parent),rowid(rowid),
    ui(new Ui::cellwidget)
{
    ui->setupUi(this);
}

cellwidget::~cellwidget()
{
    delete ui;
}


void cellwidget::on_toolButton_clicked()
{
      emit userDelete(rowid);
}

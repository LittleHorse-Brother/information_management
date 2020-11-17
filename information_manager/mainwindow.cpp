#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_add.h"
#include "cellwidget.h"
#include <algorithm>
#include <QAxObject>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnWidth(0,200);
    ui->treeWidget->setColumnWidth(1,200);
    ui->treeWidget->setColumnWidth(2,200);
    ui->treeWidget->setColumnWidth(3,100);

    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);  //右键菜单的信号连接

    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(OnListContextMenu(const QPoint&)));

    connect(ui->action, SIGNAL(triggered()),
        this, SLOT(OnMenuAdd()));
    connect(ui->action_2, SIGNAL(triggered()),
        this, SLOT(OnMenuRemove()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_info(Student information)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    info.push_back(information);
    item->setText(0, QString::fromStdString(information.name));
    item->setText(1, QString::fromStdString(information.id));
    item->setText(2, QString::fromStdString(information.cellphone));
    ui->treeWidget->addTopLevelItem(item);

    cellwidget* widget = new cellwidget(item); //构建行内删除按钮
    ui->treeWidget->setItemWidget(item, 3, widget);
    widget->setAutoFillBackground(true);
    connect(widget, SIGNAL(userDelete(QTreeWidgetItem*)),
            this, SLOT(onDeleteRow(QTreeWidgetItem* )));

}



void MainWindow::on_toolButton_clicked()  //增加功能
{
    Dialog_Add dlg;
    if(QDialog::Accepted==dlg.exec()){
        add_info(dlg.information);
    }

}

void MainWindow::on_toolButton_2_clicked() //按钮删除功能
{
    QTreeWidgetItem *item=ui->treeWidget->currentItem();
    int index= ui->treeWidget->indexOfTopLevelItem(item);
     delete item;
    info.erase(info.begin()+index);
}

int MainWindow::onDeleteRow(QTreeWidgetItem *item) //行内按键删除功能
{
    int index = ui->treeWidget->indexOfTopLevelItem(item);
    ui->treeWidget->takeTopLevelItem(index);
    delete item;
    info.erase(info.begin()+index);
    return 0;
}

void MainWindow::OnListContextMenu(const QPoint &pt)
{
    QTreeWidgetItem* selected = ui->treeWidget->itemAt(pt);
    int row = ui->treeWidget->currentColumn();

    QMenu menu;
    menu.addAction(ui->action);

    if( selected)    //如果有选中行则菜单中多一个删除键
    {
        menu.addAction(ui->action_2);
    }
    menu.exec(ui->treeWidget->mapToGlobal(pt));

}

void MainWindow::OnMenuAdd()  //菜单添加
{
    Dialog_Add dlg;
    if(QDialog::Accepted==dlg.exec()){
        add_info(dlg.information);
    }

}

void MainWindow::OnMenuRemove() //菜单删除
{
    QTreeWidgetItem *item=ui->treeWidget->currentItem();
    int index= ui->treeWidget->indexOfTopLevelItem(item);
     delete item;
    info.erase(info.begin()+index);
}







void MainWindow::on_pushButton_2_clicked() //返回键则打印出全体信息
{
    ui->treeWidget->clear();
    for(int i=0;i<info.size();i++){
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, QString::fromStdString(info[i].name));
        item->setText(1, QString::fromStdString(info[i].id));
        item->setText(2, QString::fromStdString(info[i].cellphone));
        ui->treeWidget->addTopLevelItem(item);
        cellwidget* widget = new cellwidget(item);
        ui->treeWidget->setItemWidget(item, 3, widget);
        widget->setAutoFillBackground(true);
        connect(widget, SIGNAL(userDelete(QTreeWidgetItem*)),
                this, SLOT(onDeleteRow(QTreeWidgetItem* )));

    }
}

void MainWindow::on_pushButton_clicked()
{
    std::string matched=ui->lineEdit->text().toStdString();
    char matched_c[20];
    strcpy(matched_c,matched.c_str());//将待检索信息转化为char* 以使用strstr函数

    std::vector<int> results_index;//待打印信息
    for(int i=0;i<info.size();i++){
        std::string name=info[i].name;
        char name_c[20];
        strcpy(name_c,name.c_str());
        if(strstr(name_c,matched_c)!=NULL){
           results_index.push_back(i);
        }
    }

     //打印搜索到的结果
        ui->treeWidget->clear();
        int index_print;
        for(int i=0;i<results_index.size();i++){
            QTreeWidgetItem* item = new QTreeWidgetItem();
            index_print=results_index[i];
            item->setText(0, QString::fromStdString(info[index_print].name));
            item->setText(1, QString::fromStdString(info[index_print].id));
            item->setText(2, QString::fromStdString(info[index_print].cellphone));
            ui->treeWidget->addTopLevelItem(item);

        }
    }



void MainWindow::on_toolButton_3_clicked() //保存按键保存入一个excel
{

    QString filepath=QFileDialog::getSaveFileName(this,tr("Save orbit"),".",tr("Microsoft Office 2007 (*.xlsx)"));//获取保存路径
        if(!filepath.isEmpty()){
            QAxObject *excel = new QAxObject(this);
            excel->setControl("Excel.Application");//连接Excel控件
            excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
            excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示

            QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
            workbooks->dynamicCall("Add");//新建一个工作簿
            QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
            QAxObject *worksheets = workbook->querySubObject("Sheets");//获取工作表集合
            QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);//获取工作表集合的工作表1，即sheet1

            QAxObject *cellA,*cellB,*cellC;

            //设置标题
            int cellrow=1;
            QString A="A"+QString::number(cellrow);//设置要操作的单元格，如A1
            QString B="B"+QString::number(cellrow);
            QString C="C"+QString::number(cellrow);

            cellA = worksheet->querySubObject("Range(QVariant, QVariant)",A);//获取单元格
            cellB = worksheet->querySubObject("Range(QVariant, QVariant)",B);
            cellC=worksheet->querySubObject("Range(QVariant, QVariant)",C);

            cellA->dynamicCall("SetValue(const QVariant&)",QVariant("姓名"));//设置各列数字名字
            cellB->dynamicCall("SetValue(const QVariant&)",QVariant("学号"));
            cellC->dynamicCall("SetValue(const QVariant&)",QVariant("电话"));

            cellrow++;

            int rows=info.size();
            for(int i=0;i<rows;i++){
                QString A="A"+QString::number(cellrow);//设置要操作的单元格，如A1
                QString B="B"+QString::number(cellrow);
                QString C="C"+QString::number(cellrow);

                cellA = worksheet->querySubObject("Range(QVariant, QVariant)",A);//获取单元格
                cellB = worksheet->querySubObject("Range(QVariant, QVariant)",B);
                cellC=worksheet->querySubObject("Range(QVariant, QVariant)",C);

                cellA->dynamicCall("SetValue(const QVariant&)",QVariant( QString::fromStdString(info[i].id)));//设置单元格的值
                cellB->dynamicCall("SetValue(const QVariant&)",QVariant( QString::fromStdString(info[i].name)));
                cellC->dynamicCall("SetValue(const QVariant&)",QVariant( QString::fromStdString(info[i].cellphone)));

                cellrow++;
            }

            workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(filepath));//保存至filepath
            workbook->dynamicCall("Close()");//关闭工作簿
            excel->dynamicCall("Quit()");//关闭excel
            delete excel;
            excel=NULL;
        }

}

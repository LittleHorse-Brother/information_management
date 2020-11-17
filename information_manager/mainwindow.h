#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include "student.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void add_info(Student information);

    void on_toolButton_clicked(); //添加键

    void on_toolButton_2_clicked();//删除键

    int onDeleteRow(QTreeWidgetItem* item);//行内删除键

    void OnListContextMenu(const QPoint& pt);//定义右键菜单栏

    void OnMenuAdd();//定义右键菜单栏增加
    void OnMenuRemove();//定义右键菜单栏


    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_toolButton_3_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<Student> info;

};
#endif // MAINWINDOW_H

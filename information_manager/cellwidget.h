#ifndef CELLWIDGET_H
#define CELLWIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>


namespace Ui {
class cellwidget;
}

class cellwidget : public QWidget
{
    Q_OBJECT
signals:
    int userDelete(QTreeWidgetItem* rowid);

public:
    explicit cellwidget(QTreeWidgetItem* rowid, QWidget *parent = nullptr);
    ~cellwidget();

private slots:


    void on_toolButton_clicked();

private:
    Ui::cellwidget *ui;
    QTreeWidgetItem* rowid;
};

#endif // CELLWIDGET_H

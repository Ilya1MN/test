#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qfiledialog.h>
#include <sorts.h>
#include "qdialog.h"
#include "formadd.h"
#include <QAxObject>
#include <QDebug>
#include <QGraphicsScene>
#include "QStandardItemModel"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void sendData(QString, int);
private slots:
    void on_pbOpenFile_released();

    void on_pbAdd_released();
    void guidslot(QString,QString,QString,QPixmap);


    void on_pbSort_released();

    void on_pbDelete_released();

    void on_pbFind_released();

    void on_lEditfind_textChanged(const QString &arg1);

    void on_pbsave_released();

    QList<QStringList> Sorting(QList<QStringList>);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H

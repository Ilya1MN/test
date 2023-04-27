#ifndef FORMADD_H
#define FORMADD_H

#include <QWidget>
#include <qdialog.h>
#include <QDebug>
#include "mainwindow.h"
#include "QMessageBox"
#include <QGraphicsScene>
namespace Ui {
class FormAdd;
}

class FormAdd : public QDialog
{
    Q_OBJECT

public:
    explicit FormAdd(QWidget *parent = 0);
    ~FormAdd();

signals:
        void guid(QString,QString,QString, QByteArray);
   // void guid(QString,QString,QString, QPixmap);
private slots:
    void on_pbadd_released();

    void on_pb_load_photo_released();

private:
    Ui::FormAdd *ui;
    QPixmap px;
    QByteArray imagebyarr;
};

#endif // FORMADD_H

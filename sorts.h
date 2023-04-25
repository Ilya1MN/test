#ifndef SORTS_H
#define SORTS_H

#include <QObject>
#include "qlist.h"
#include "QDebug"
#include "iostream"

class sorts : public QObject
{
    Q_OBJECT
public:
    explicit sorts(QObject *parent = nullptr);
    void bubbleSort(QList<QStringList>* list, int listLength);


    void quickSort(QList<QStringList>* list, int listLength);


    void insertionSort(QList<QStringList>*  list, int listLength);
public slots:

};

#endif // SORTS_H

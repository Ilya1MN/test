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
    QList<QStringList> bubbleSort(QList<QStringList> list, int listLength);

    int findSmallestPosition(QList<QStringList> list, int startPosition, int listLength);
    QList<QStringList> selectionSort(QList<QStringList> list, int listLength);

    QList<QStringList> insertionSort(QList<QStringList> list, int listLength);


    QList<QStringList> shellSort(QList<QStringList> list, int listLength);

    QList<QStringList> heapify(QList<QStringList> list, int listLength, int root);
    QList<QStringList> heapSort(QList<QStringList> list, int listLength);
public slots:

};

#endif // SORTS_H

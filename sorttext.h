#ifndef SORTTEXT_H
#define SORTTEXT_H

#include <QObject>
#include <qdebug.h>
class sorttext : public QObject
{
    Q_OBJECT
public:
    explicit sorttext(QObject *parent = nullptr);
    QStringList bubbleSort(QStringList list, int listLength);

    int findSmallestPosition(QStringList list, int startPosition, int listLength);
    QStringList selectionSort(QStringList list, int listLength);

    QStringList insertionSort(QStringList list, int listLength);

    QStringList shellSort(QStringList list, int listLength);

    QStringList heapify(QStringList list, int listLength, int root);
    QStringList heapSort(QStringList list, int listLength);
signals:

public slots:
};

#endif // SORTTEXT_H

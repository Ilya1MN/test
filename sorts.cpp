#include "sorts.h"


sorts::sorts(QObject *parent) : QObject(parent)
{

}
///////////Сортировка пузырьком
void sorts::bubbleSort(QList<QStringList>* list, int listLength)
{
    while(listLength--)
    {
        for(int i = 0; i < listLength; i++)
        {
                list->swap(i, i + 1);
        }
    }
}


#include "sorttext.h"

sorttext::sorttext(QObject *parent) : QObject(parent)
{

}
////////////////Пузырьковая сортировка//////////////////////////////////////////////////
QStringList sorttext::bubbleSort(QStringList list, int listLength)
{

    while(listLength--)
      {
          for(int i = 0; i < listLength; i++)
          {
                  list.swap(i, i + 1);
          }
      }
    return list;
}

/////////////////////////////////// Сортировка выбором/////////////////////////////////////////////////////////
int sorttext::findSmallestPosition(QStringList list, int startPosition, int listLength)
{
    int smallestPosition = startPosition;

    for(int i = startPosition; i < listLength; i++)
    {
        if(list[i] < list[smallestPosition]) //     if(i > smallestPosition)
            smallestPosition = i;
    }
    return smallestPosition;
}

QStringList sorttext::selectionSort(QStringList list, int listLength)
{
    for(int i = 0; i < listLength; i++)
    {
        int smallestPosition = findSmallestPosition(list, i, listLength);

       list.swap(i, smallestPosition);
    }
    return list;
}

///////////////////////////Сортировка вставками///////////////////////////////////////////////////
QStringList sorttext::insertionSort(QStringList list, int listLength)
{
    for(int i = 1; i < listLength; i++)
        {
            int j = i - 1;
            while(j >= 0 && list[j] > list[j + 1])
            {
                list.swap(j, j + 1);

                j--;
            }
        }
    return list;
}

/////////////////////////////Сортировка Шелла/////////////////////////////////
QStringList sorttext::shellSort(QStringList list, int listLength)
{
    for(int step = listLength/2; step > 0; step /= 2)
    {
        for (int i = step; i < listLength; i += 1)
        {
            int j = i;
            while(j >= step && list[j - step] > list[i])
            {
                list.swap(j, j - step);
                j-=step;
                //cout<<"\ndid";
            }
        }
    }
    return list;
}
/////////////////////////////////Сортировка кучей////////////////////////////////////////
QStringList sorttext::heapify(QStringList list, int listLength, int root)
{
    int largest = root;
    int l = 2*root + 1;
    int r = 2*root + 2;

    if (l < listLength && list[l] > list[largest])
        largest = l;

    if (r < listLength && list[r] > list[largest])
        largest = r;

    if (largest != root)
    {
        list.swap(root, largest);
        list = heapify(list, listLength, largest);
    }
    return list;
}

QStringList sorttext::heapSort(QStringList list, int listLength)
{
    for(int i = listLength / 2 - 1; i >= 0; i--)
         list = heapify(list, listLength, i);

    for(int i = listLength - 1; i >= 0; i--)
    {
        list.swap(0, i);
         list = heapify(list, i, 0);
    }
    return list;
}

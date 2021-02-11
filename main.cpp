/**
* Title : Algorithm Efficiency and Sorting
* Author : Alkim Onen
* Description : Main program to test sorting
*/

#include <iostream>
using namespace std;
#include "sorting.h"

int main()
{
    int compCount, moveCount;
    int *arr;

    cout << "The array" << endl;
    arr = new int[16] {7, 3, 6, 12, 13, 4, 1, 9, 15, 0, 11, 14, 2, 8, 10, 5};
    printArray( arr, 16);
    delete [] arr;

    cout << "Bubble sort" << endl;
    arr = new int[16] {7, 3, 6, 12, 13, 4, 1, 9, 15, 0, 11, 14, 2, 8, 10, 5};
    bubbleSort( arr, 16, compCount, moveCount);
    printArray( arr, 16);
    delete [] arr;

    cout << "Quick sort" << endl;
    arr = new int[16] {7, 3, 6, 12, 13, 4, 1, 9, 15, 0, 11, 14, 2, 8, 10, 5};
    quickSort( arr, 16, compCount, moveCount);
    printArray( arr, 16);
    delete [] arr;

    cout << "Merge sort" << endl;
    arr = new int[16] {7, 3, 6, 12, 13, 4, 1, 9, 15, 0, 11, 14, 2, 8, 10, 5};
    mergeSort( arr, 16, compCount, moveCount);
    printArray( arr, 16);
    delete [] arr;

    cout << "Radix sort" << endl;
    arr = new int[16] {7, 3, 6, 12, 13, 4, 1, 9, 15, 0, 11, 14, 2, 8, 10, 5};
    radixSort( arr, 16);
    printArray( arr, 16);
    delete [] arr;

    performanceAnalysis();

    return 0;
}

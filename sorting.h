/**
* Title : Algorithm Efficiency and Sorting
* Author : Alkim Onen
* Description : Header file for sorting.cpp
*/

#ifndef __SORTING_H
#define __SORTING_H

void bubbleSort(int *arr, int size, int &compCount, int &moveCount);

void quickSort(int *arr, int size, int &compCount, int &moveCount);
void quicksort( int *arr, int first, int last);
void partition( int *arr, int first, int last, int &pivotIndex);

void mergeSort(int *arr, int size, int &compCount, int &moveCount);
void mergesort( int *arr, int first, int last);
void merge( int *arr, int first, int mid, int last);

void radixSort(int *arr, int size);

void printArray(int *arr, int size);

void performanceAnalysis();

#endif

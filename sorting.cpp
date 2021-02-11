/**
* Title : Algorithm Efficiency and Sorting
* Author : Alkim Onen
* Description : Code of sorts and their analysis
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#include "sorting.h"
#include "time.h"

int moves;
int comps;

void swap( int &first, int &second)
{
    int temp;
    temp = first;
    first = second;
    second = temp;
    moves += 3;
}

void bubbleSort(int *arr, int size, int &compCount, int &moveCount)
{
    // zero static variables
    bool sorted = false;
    comps = 0;
    moves = 0;

    for ( int pass = 1; (pass < size) && !sorted; ++pass )
    {
        sorted = true;
        for ( int index = 0; index < size - pass; ++index )
        {
            int nextIndex = index + 1;
            if ( arr[index] > arr[nextIndex] )
            {
                swap( arr[index], arr[nextIndex]);
                sorted = false;
            }
            comps++;
        }
    }
    // zero static variables
    // move static counts to pointers
    moveCount = moves;
    compCount = comps;
}

void quickSort( int *arr, int size, int &compCount, int &moveCount)
{
    // zero static variables
    moves = 0;
    comps = 0;

    quicksort( arr, 0, size-1);

    // move static counts to pointers
    compCount = comps;
    moveCount = moves;
}

void quicksort( int *arr, int first, int last)
{
    int pivotIndex;

    if ( first < last )
    {
        // create the partition: S1, pivot, S2
        partition( arr, first, last, pivotIndex);

        // sort regions S1 and S2
        quicksort( arr, first, pivotIndex-1);
        quicksort( arr, pivotIndex+1, last);
    }
}

void partition( int *arr, int first, int last, int &pivotIndex)
{
    int pivot = arr[first]; // copy pivot
    moves++;

    int lastS1 = first;           // index of last item in S1
    int firstUnknown = first + 1; // index of first item in unknown

	// move one item at a time until unknown region is empty
    for (  ; firstUnknown <= last; ++firstUnknown)
    {
        // move item from unknown to proper region
        if ( arr[firstUnknown] < pivot )
        {  	// belongs to S1
            ++lastS1;
            swap( arr[firstUnknown], arr[lastS1]);
        }	// else belongs to S2
        comps++;
    }
    // place pivot in proper position and mark its location
    swap( arr[first], arr[lastS1]);
    pivotIndex = lastS1;
}


void mergeSort( int *arr, int size, int &compCount, int &moveCount)
{
    // zero static variables
    comps = 0;
    moves = 0;

    mergesort( arr, 0, size-1);

    // move static counts to pointers
    moveCount = moves;
    compCount = comps;
}

void mergesort( int *arr, int first, int last) {

    if (first < last) {

        int mid = (first + last)/2; 	// index of midpoint

        mergesort( arr, first, mid);

        mergesort( arr, mid+1, last);

        // merge the two halves
        merge( arr, first, mid, last);
   }
}  // end mergesqort

void merge( int *arr, int first, int mid, int last) {

	int *tempArray; 	// temporary array
    tempArray = new int[ last + 1];

    int first1 = first; 	// beginning of first subarray
    int last1 = mid; 		// end of first subarray
    int first2 = mid + 1;	// beginning of second subarray
    int last2 = last;		// end of second subarray
    int index = first1; // next available location in tempArray

    for ( ; (first1 <= last1) && (first2 <= last2); ++index)
    {
        if ( arr[first1] < arr[first2])
        {
            tempArray[index] = arr[first1];
            ++first1;
        }
        else
        {
            tempArray[index] = arr[first2];
            ++first2;
        }
        comps++;
        moves++;
    }
    // finish off the first subarray, if necessary
    for (; first1 <= last1; ++first1, ++index)
    {
        tempArray[index] = arr[first1];
        moves++;
    }

    // finish off the second subarray, if necessary
    for (; first2 <= last2; ++first2, ++index)
    {
        tempArray[index] = arr[first2];
        moves++;
    }

    // copy the result back into the original array
    for (index = first; index <= last; ++index)
    {
        arr[index] = tempArray[index];
        moves++;
    }
    delete [] tempArray;
}  // end merge


void radixSort(int *arr, int size)
{
    int n, divider;
    int digit;
    int **groups;
    int *counts;
    bool lastDigit;

    groups = new int*[10];
    divider = 1;    // for index of a number
    lastDigit = false;  // index is at the last digit
    while ( !lastDigit )
    {
        lastDigit = true;

        counts = new int[10];   // number of elements in groups
        // create 10 empty groups
        for ( int i = 0; i < 10; i++)
        {
            groups[i] = new int[size];
            counts[i] = 0;
        }

        // group digits
        for ( int i = 0; i < size; i++ )
        {
            // divide number to divider to remove already scanned digits
            digit = arr[i] / divider;
            if ( digit > 0 )
                lastDigit = false;
            digit = digit % 10;     // get the digit at index

            groups[digit][counts[digit]] = arr[i];  // add it to its group
            counts[digit]++;        // increase group count
        }

        // move arrays to original array
        n = 0;
        for ( digit = 0; digit < 10; digit++)
        {
            for ( int i = 0; i < counts[digit]; i++ )
            {
                arr[n] = groups[digit][i];
                n++;
            }
        }
        divider *= 10;  // multiply divider by 10 so it would point to next index
    }

    // deallocation of dynamic arrays
    for ( int i = 0; i < 10; i++)
    {
        delete [] groups[i];
    }
    delete [] groups;
    delete [] counts;
}

void printArray( int *arr, int size )
{
    if ( size > 0 )
    {
        cout << arr[0];
        for ( int i = 1; i < size; i++ )
        {
            cout << " " << arr[i];
        }
        cout << endl;
    }
    else
        cout << "Array is empty" << endl;
}

void performanceAnalysis()
{
    string names[] = { "Radix sort", "Bubble sort", "Quick sort", "Merge sort"};
    int sizes[] = { 2000, 6000, 10000, 14000, 18000, 22000, 26000, 30000};
    double **durations;
    int ***counts;
    int **arr;
    int moveCount, compCount;
    double duration;
    clock_t startTime;

    // arrays for type of sorts
    counts = new int**[4];
    durations = new double*[4];

    for ( int i = 0; i < 4; i++ )
    {
        // arrays for each size
        durations[i] = new double[8];
        counts[i] = new int*[8];
        // arrays for counts
        for ( int j = 0; j < 8; j++)
            counts[i][j] = new int[2];
    }

    for ( int size = 0; size < 8; size++ )
    {
        // create 4 identical arrays and put random values to them
        arr = new int*[4];
        arr[0] = new int[sizes[size]];
        arr[1] = new int[sizes[size]];
        arr[2] = new int[sizes[size]];
        arr[3] = new int[sizes[size]];

        for ( int i = 0; i < sizes[size]; i++ )
        {
            int value = rand() % (2*sizes[size]);
            arr[0][i] = value;
            arr[1][i] = value;
            arr[2][i] = value;
            arr[3][i] = value;
        }

        // sort first array with radix sort
        startTime = clock();
        radixSort( arr[0], sizes[size]);
        duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
        // record result
        durations[0][size] = duration;

        // sort second array with bubble sort
        startTime = clock();
        bubbleSort( arr[1], sizes[size], compCount, moveCount);
        duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
        // record results
        durations[1][size] = duration;
        counts[1][size][0] = compCount;
        counts[1][size][1] = moveCount;

        // sort third array with quick sort
        startTime = clock();
        quickSort( arr[2], sizes[size], compCount, moveCount);
        duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
        // record results
        durations[2][size] = duration;
        counts[2][size][0] = compCount;
        counts[2][size][1] = moveCount;

        // sort fourth array with merge sort
        startTime = clock();
        mergeSort( arr[3], sizes[size], compCount, moveCount);
        duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
        // record results
        durations[3][size] = duration;
        counts[3][size][0] = compCount;
        counts[3][size][1] = moveCount;
    }

    // print results of radix sort
    cout << "----------------------------------------------------" << endl;
        cout << "Part c - Time analysis of " << names[0] << endl;
    printf( "%-16s%-16s\n", "Array Size", "Time Elapsed");
    for ( int size = 0; size < 8; size++)
        printf( "%-16d%-16f\n", sizes[size], durations[0][size]);

    // print results of other sorts
    for ( int i = 1; i < 4; i++ )
    {
        printf( "----------------------------------------------------\n");
        cout << "Part c - Time analysis of " << names[i] << endl;
        printf( "%-16s%-16s%-12s%-12s\n", "Array Size", "Time Elapsed", "compCount", "moveCount");
        for ( int size = 0; size < 8; size++)
            printf( "%-16d%-16f%-12d%-12d\n", sizes[size], durations[i][size], counts[i][size][0], counts[i][size][1]);
    }

    // deallocate dynamic arrays
    for ( int i = 0; i < 4; i++)
    {
        delete [] durations[i];
        for ( int j = 0; j < 8; j++)
        {
            delete [] counts[i][j];
        }
        delete [] counts[i];
    }
    delete [] counts;
    delete [] durations;
    for ( int i = 0; i < 4; i++)
    {
        delete [] arr[i];
    }
    delete [] arr;
}

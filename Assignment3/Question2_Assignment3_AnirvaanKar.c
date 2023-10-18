#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void checkIfSorted(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            printf("Error in sorting\n");
            exit(0);
        }
    }
}

void bubbleSort(int arr[], int n, int *comparisonCount, int *swapCount) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*comparisonCount)++;//comparing with the next element is counted
            if (arr[j] > arr[j + 1]) {
                (*swapCount)++;//counting swaps in bubble sort
                swap(&arr[j], &arr[j + 1]);
                
            }
        }
    }
}

void insertionSort(int arr[], int n, int *comparisonCount, int *swapCount) {
    for (int i = 1; i < n; i++) {
        int element = arr[i];//considering first element
        int j = i - 1;
        while (j >= 0 && arr[j] > element) {
            (*comparisonCount)++;//comparing with the element we consider
            (*swapCount)++;//swapping the neighbours
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = element;//making the new element to be considered
    }
}

int main() {
    int arr[10000];
    int n = 1000, i, t;
    double cc, sc, cc1, sc1;

    srand(time(NULL));
    printf("For insertion sort and bubble sort\n");
    for (n = 1000; n <= 10000; n = n + 1000) {
        cc = 0.0, sc = 0.0;
        cc1 = 0.0, sc1 = 0.0;
        for (t = 0; t < 100; t++) {
             
             for (i = 0; i < n; i++)
                arr[i] = rand() % 1000;

            int comparisonCount = 0, swapCount = 0;
            insertionSort(arr, n, &comparisonCount, &swapCount);
            cc += (double)comparisonCount;
            sc += (double)swapCount;
            
            for (i = 0; i < n; i++)
                arr[i] = rand() % 1000;
            
            comparisonCount = 0;
            swapCount = 0;
            bubbleSort(arr, n, &comparisonCount, &swapCount);
            cc1 += (double)comparisonCount;
            sc1 += (double)swapCount;
        }
        checkIfSorted(arr, n);
        printf("n = %6d, %lf %lf\n", n, cc / (n * n), sc / (n * n));
        printf("            %lf %lf\n", cc1 / (n * n), sc1 / (n * n));
    }

    return 0;
}

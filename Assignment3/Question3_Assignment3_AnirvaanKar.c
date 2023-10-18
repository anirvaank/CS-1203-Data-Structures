#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//swap function
void swap(int *xp, int *yp)
{   
    int temp;
    temp = *xp; *xp = *yp; *yp = temp;
}
// checking for errors
void checkIfSorted(int arr[], int size){

    int i;
    for (i = 0; i < size-1; i++)
       if (arr[i] > arr[i+1]){
          printf("Error in sorting\n");
          exit(0);
       }
}
// we are doing heapsort by using the combination of insert and delete so we need only those two functions
void heapInsert(int arr[], int n, int elm, int *c1, int *c2)
{
     int i, parent; 

     *c1 = 0; *c2 = 0;
     arr[n] = elm;
     i = n;

     if (i == 0) return;
   
     while (i != 0){
         parent = (i-1)/2;
         (*c1)++;
         if (arr[parent] < arr[i]){ 
           swap(&arr[i], &arr[parent]);
           (*c2)++;
         }
         else break;
         i = parent;
    }
}

int heapDelete(int arr[], int n, int *c1, int *c2)
{
     int i, left, right, largest, val, flag = 1;

     *c1 = 0; *c2 = 0;
     if (n == 0) return -9999;//deleting from empty heap
     val = arr[0];
     arr[0] = arr[n-1];
     i = 0;

     while (flag == 1){
        flag = 0; largest = i;
        left = 2*i+1; right = 2*i+2;
         (*c1)++;
         // to maintain heap condition
        if (left <= n-1 && arr[left] > arr[largest]){
                largest = left; flag = 1;
        }
         (*c1)++;
        if (right <= n-1 && arr[right] > arr[largest]){
                largest = right; flag = 1;
        }
        if (flag == 1){
                 (*c2)++;
                 swap(&arr[i], &arr[largest]); i = largest;
        }
     }
     return val;
}

//merge function to merge the smaller sorted arrays correctly
void merge(int arr[], int l, int m, int r, int *comparisonCount, int *swapCount) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        (*comparisonCount)++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        (*swapCount)++;
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        (*swapCount)++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        (*swapCount)++;
    }
}
//merge sort function to break up the array into smaller chunks and sort them and then merge after base condition that a single element array is sorted
void mergeSort(int arr[], int l, int r, int *comparisonCount, int *swapCount) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, comparisonCount, swapCount);
        mergeSort(arr, m + 1, r, comparisonCount, swapCount);
        merge(arr, l, m, r, comparisonCount, swapCount);
    }
}
// partition function to break the array for quicksort
int partition(int array[], int low, int high, int *comparisonCount, int *swapCount) {
    int pivot = array[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        (*comparisonCount)++;
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
            (*swapCount)++;
        }
    }

    swap(&array[i + 1], &array[high]);
    (*swapCount)++;
    return (i + 1);
}
//quicksorting the smaller arrays
void quickSort(int array[], int low, int high, int *comparisonCount, int *swapCount) {
    if (low < high) {
        int pi = partition(array, low, high, comparisonCount, swapCount);
        quickSort(array, low, pi - 1, comparisonCount, swapCount);
        quickSort(array, pi + 1, high, comparisonCount, swapCount);
    }
}

int main()
{
    int arr[100000];
    int n = 100, i, comparisonCount, swapCount, t;
    int comparisonCount1, swapCount1, elm;
    double cc, sc;
    double cc1, sc1;

    srand(time(NULL));
    printf("For the case of heapsort using insert and then delete \n");
    for (n = 10000; n <= 100000; n = n+10000){// taking arrays of sized 10,000 all the way to 100,000
      cc = 0.0, sc = 0.0;
      cc1 = 0.0, sc1 = 0.0;
      for (t = 0; t < 100; t++){
        for (i = 0; i < n; i++)
	    arr[i] = rand()%10000;//putting in random elements

        for(i = 0; i < n; i++){
            heapInsert(arr, i, arr[i], &comparisonCount, &swapCount);
	    cc += (double) comparisonCount;
	    sc += (double) swapCount;
        }

        for(i = n; i > 0; i--){
            elm = heapDelete(arr, i, &comparisonCount1, &swapCount1);
            arr[i-1] = elm;
	    cc1 += (double) comparisonCount1;
	    sc1 += (double) swapCount1;
        }
   
    
      }
      checkIfSorted(arr, n);
      printf("n = %6d, %lf %lf\n", n, cc/(n*100.0), sc/(n*100.0));
      printf("            %lf %lf\n", cc1/(n*((log(n)/log(2)))*100.0), sc1/(n*((log(n)/log(2)))*100.0));//dividing by nlogn to check the theoretical time complexity of heapDelete
     }
     printf("For quicksort and mergesort\n");
    for (n = 10000; n <= 100000; n = n + 10000) {
        cc = 0.0, sc = 0.0;
        cc1 = 0.0, sc1 = 0.0;
        for (t = 0; t < 100; t++) {
            for (i = 0; i < n; i++)
                arr[i] = rand() % 10000;//putting in random elements

            int comparisonCount = 0, swapCount = 0;
            quickSort(arr, 0, n - 1, &comparisonCount, &swapCount);
            cc += (double)comparisonCount;
            sc += (double)swapCount;

            int comparisonCount1 = 0, swapCount1 = 0;
            mergeSort(arr, 0, n - 1, &comparisonCount1, &swapCount1);
            cc1 += (double)comparisonCount1;
            sc1 += (double)swapCount1;
        }
        checkIfSorted(arr, n);
        printf("n = %6d, %lf %lf\n", n, cc / (n * ((log(n) / log(2))) * 100.0), sc / (n * ((log(n) / log(2))) * 100.0));//checking both with their average theoretical time complexity of nlogn
        printf("            %lf %lf\n", cc1 / (n * ((log(n) / log(2))) * 100.0), sc1 / (n * ((log(n) / log(2))) * 100.0));
    }

    return 0;
}
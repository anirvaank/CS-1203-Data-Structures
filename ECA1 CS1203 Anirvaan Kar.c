#include <stdio.h>
#include <stdbool.h>

// Function to swap two elements in an array
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(int arr[], int start, int end) {
    while (start < end) {
        swap(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

// Function to generate the next lexicographically greater permutation
bool nextPermutation(int arr[], int n) {
    int i = n - 2;

    // Find the first element (from the right) that is smaller than the next element
    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }

    // If no such element is found, all permutations have been generated
    if (i < 0) {
        return false;
    }

    // Find the smallest element to the right of i that is greater than arr[i]
    int j = n - 1;
    while (arr[j] <= arr[i]) {
        j--;
    }

    // Swap arr[i] and arr[j]
    swap(&arr[i], &arr[j]);

    // Reverse the elements to the right of i
    reverse(arr, i + 1, n - 1);

    return true;
}

int main() {
    int n;

    printf("Enter the value of n (<= 8): ");
    scanf("%d", &n);


    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    printf("Permutations of numbers 1 to %d:\n", n);

    // Generate and print permutations using the next permutation algorithm
    do {
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } while (nextPermutation(arr, n));

    return 0;
}
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int arr[50], n;

void SelectionSort() {
    int min, t;
    for (int i = 0; i < (n - 1); i++) {
        min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        t = arr[i];
        arr[i] = arr[min];
        arr[min] = t;
    }
}


int main() {

    printf("Enter the number of elements of the array: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }

    SelectionSort(arr, n);

    printf("\nSorted array: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}

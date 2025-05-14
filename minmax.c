#include <stdio.h>

struct Result {
    int min;
    int max;
};

struct Result maxMin(int A[], int low, int high) {
    struct Result res, left, right;

    // If only one element
    if (low == high) {
        res.min = res.max = A[low];
        return res;
    }
    // If only two elements
    else if (low == high - 1) {
        if (A[low] < A[high]) {
            res.min = A[low];
            res.max = A[high];
        } else {
            res.min = A[high];
            res.max = A[low];
        }
        return res;
    }
    // More than two elements
    else {
        int mid = (low + high) / 2;
        left = maxMin(A, low, mid);
        right = maxMin(A, mid + 1, high);

        // Combine results
        res.min = (left.min < right.min) ? left.min : right.min;
        res.max = (left.max > right.max) ? left.max : right.max;
        return res;
    }
}

int main() {
    int A[100], n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    struct Result final = maxMin(A, 0, n - 1);

    printf("Minimum: %d\n", final.min);
    printf("Maximum: %d\n", final.max);

    return 0;
}
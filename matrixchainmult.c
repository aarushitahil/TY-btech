#include <stdio.h>
#define INF 100000000
#define MAX 100

int dp[MAX][MAX];

// Recursive function with memoization
int matrixChain(int arr[], int i, int j) {
    if (i == j)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    int min = INF;
    for (int k = i; k < j; k++) {
        int cost = matrixChain(arr, i, k) +
                   matrixChain(arr, k + 1, j) +
                   arr[i - 1] * arr[k] * arr[j];

        if (cost < min)
            min = cost;
    }

    dp[i][j] = min;
    return min;
}

int main() {
    int arr[] = {10, 30, 5, 60, 10};
    int n = 4;  // Number of matrices = 4 → arr size = 5

    // Initialize DP table
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            dp[i][j] = -1;

    int minCost = matrixChain(arr, 1, n);
    printf("Minimum number of multiplications: %d\n", minCost);

    return 0;
}

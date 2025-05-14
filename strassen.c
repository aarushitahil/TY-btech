#include <stdio.h>
#include <stdlib.h>

// Function to allocate memory for an n x n matrix
int** allocateMatrix(int n) {
    int** matrix = (int**) malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        matrix[i] = (int*) malloc(n * sizeof(int));
    return matrix;
}

// Function to free memory
void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}

// Matrix addition
void add(int** A, int** B, int** result, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] + B[i][j];
}

// Matrix subtraction
void subtract(int** A, int** B, int** result, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] - B[i][j];
}

// Strassen's recursive multiplication
void strassen(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    // Allocate submatrices
    int** A11 = allocateMatrix(k);
    int** A12 = allocateMatrix(k);
    int** A21 = allocateMatrix(k);
    int** A22 = allocateMatrix(k);
    int** B11 = allocateMatrix(k);
    int** B12 = allocateMatrix(k);
    int** B21 = allocateMatrix(k);
    int** B22 = allocateMatrix(k);
    int** C11 = allocateMatrix(k);
    int** C12 = allocateMatrix(k);
    int** C21 = allocateMatrix(k);
    int** C22 = allocateMatrix(k);

    int** M1 = allocateMatrix(k);
    int** M2 = allocateMatrix(k);
    int** M3 = allocateMatrix(k);
    int** M4 = allocateMatrix(k);
    int** M5 = allocateMatrix(k);
    int** M6 = allocateMatrix(k);
    int** M7 = allocateMatrix(k);
    int** temp1 = allocateMatrix(k);
    int** temp2 = allocateMatrix(k);

    // Dividing matrices A and B into 4 submatrices
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // M1 = (A11 + A22) * (B11 + B22)
    add(A11, A22, temp1, k);
    add(B11, B22, temp2, k);
    strassen(temp1, temp2, M1, k);

    // M2 = (A21 + A22) * B11
    add(A21, A22, temp1, k);
    strassen(temp1, B11, M2, k);

    // M3 = A11 * (B12 - B22)
    subtract(B12, B22, temp1, k);
    strassen(A11, temp1, M3, k);

    // M4 = A22 * (B21 - B11)
    subtract(B21, B11, temp1, k);
    strassen(A22, temp1, M4, k);

    // M5 = (A11 + A12) * B22
    add(A11, A12, temp1, k);
    strassen(temp1, B22, M5, k);

    // M6 = (A21 - A11) * (B11 + B12)
    subtract(A21, A11, temp1, k);
    add(B11, B12, temp2, k);
    strassen(temp1, temp2, M6, k);

    // M7 = (A12 - A22) * (B21 + B22)
    subtract(A12, A22, temp1, k);
    add(B21, B22, temp2, k);
    strassen(temp1, temp2, M7, k);

    // C11 = M1 + M4 - M5 + M7
    add(M1, M4, temp1, k);
    subtract(temp1, M5, temp2, k);
    add(temp2, M7, C11, k);

    // C12 = M3 + M5
    add(M3, M5, C12, k);

    // C21 = M2 + M4
    add(M2, M4, C21, k);

    // C22 = M1 - M2 + M3 + M6
    subtract(M1, M2, temp1, k);
    add(temp1, M3, temp2, k);
    add(temp2, M6, C22, k);

    // Combine C11, C12, C21, C22 into result matrix C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    // Free all allocated memory
    freeMatrix(A11, k); freeMatrix(A12, k); freeMatrix(A21, k); freeMatrix(A22, k);
    freeMatrix(B11, k); freeMatrix(B12, k); freeMatrix(B21, k); freeMatrix(B22, k);
    freeMatrix(C11, k); freeMatrix(C12, k); freeMatrix(C21, k); freeMatrix(C22, k);
    freeMatrix(M1, k); freeMatrix(M2, k); freeMatrix(M3, k); freeMatrix(M4, k);
    freeMatrix(M5, k); freeMatrix(M6, k); freeMatrix(M7, k);
    freeMatrix(temp1, k); freeMatrix(temp2, k);
}

// Function to print an n x n matrix
void printMatrix(int** M, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%4d ", M[i][j]);
        printf("\n");
    }
}

int main() {
    int n = 4; // Must be a power of 2 (e.g., 2, 4, 8)

    // Allocate and initialize matrices
    int** A = allocateMatrix(n);
    int** B = allocateMatrix(n);
    int** C = allocateMatrix(n);

    // Example: Fill A and B with values
    int count = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A[i][j] = count;
            B[i][j] = count;
            count++;
        }

    // Perform Strassen multiplication
    strassen(A, B, C, n);

    // Print results
    printf("Matrix A:\n");
    printMatrix(A, n);
    printf("\nMatrix B:\n");
    printMatrix(B, n);
    printf("\nMatrix A * B using Strassen:\n");
    printMatrix(C, n);

    // Free memory
    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}

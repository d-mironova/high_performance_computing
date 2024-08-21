#include <iostream>
#include <ctime>

#define N 1000

using namespace std;

// Function to initialize a matrix with random values
void initializeMatrix(double **matrix) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 100; // Random value between 0 and 99
        }
    }
}

// Function to calculate the matrix product C = AB
void matrixProduct(double **A, double **B, double **C) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function to calculate the transpose of a matrix
void transposeMatrix(double **A, double **AT) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            AT[i][j] = A[j][i];
        }
    }
}

// Function to allocate memory for a matrix
double **allocateMatrix() {
    double **matrix = new double*[N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new double[N];
    }
    return matrix;
}

// Function to free memory allocated for a matrix
void freeMatrix(double **matrix) {
    for (int i = 0; i < N; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    double **A = allocateMatrix();
    double **B = allocateMatrix();
    double **C = allocateMatrix();
    double **AT = allocateMatrix();
    double **BT = allocateMatrix();
    double **CT = allocateMatrix();

    // Initialize matrices A and B with random values
    initializeMatrix(A);
    initializeMatrix(B);

    // Calculate the transpose of matrix A
    transposeMatrix(A, AT);
    // Calculate the transpose of matrix B
    transposeMatrix(B, BT);

    clock_t start_time, end_time;

    // Measure CPU time for matrix product C = AB
    start_time = clock();
    matrixProduct(A, B, C);
    end_time = clock();
    cout << "CPU time for matrix product C = AB: " << (double)(end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl;

    // Measure CPU time for matrix product C = A^T * B
    start_time = clock();
    matrixProduct(AT, B, CT);
    end_time = clock();
    cout << "CPU time for matrix product C = A^T * B: " << (double)(end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl;

    // Measure CPU time for matrix product C = A * B^T
    start_time = clock();
    matrixProduct(A, BT, C);
    end_time = clock();
    cout << "CPU time for matrix product C = A * B^T: " << (double)(end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl;

    // Free memory
    freeMatrix(A);
    freeMatrix(B);
    freeMatrix(C);
    freeMatrix(AT);
    freeMatrix(BT);
    freeMatrix(CT);

    return 0;
}


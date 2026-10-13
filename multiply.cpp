#include "matrix.h"
#include "multiply.h"

// Matrix multiplication using no threads
Matrix MultiplyMatricesBasic(Matrix m1, Matrix m2) {
    Matrix result;
    int n = m1.getWidth();
    int m = m1.getHeight();
    int p = m2.getHeight();
    result.createEmptyMatrix(n,p);

    for (int i=0; i<n;++i){
        for (int j=0; j<p;++j){
            int sum = 0;
            for (int k=0; k<m;++k){
                sum += m1.getContents()[i][k] * m2.getContents()[k][j];
            }
            result.setItem(i,j,sum);
        }
    }

    return result;
}

// Matrix multiplication using OpenMP for multi-threading
Matrix MultiplyMatricesUsingOpenMP(Matrix m1, Matrix m2) {
    Matrix result;
    int n = m1.getWidth();
    int m = m1.getHeight();
    int p = m2.getHeight();
    result.createEmptyMatrix(n,p);

    // Only difference is this line, which calls OpenMP library to run for loop in parallel
    #pragma omp parallel for collapse(2)
    for (int i=0; i<n;++i){
        for (int j=0; j<p;++j){
            int sum = 0;
            for (int k=0; k<m;++k){
                sum += m1.getContents()[i][k] * m2.getContents()[k][j];
            }
            result.setItem(i,j,sum);
        }
    }

    return result;
}


void GetSum(int i, int j, int n, int m, int p, Matrix m1, Matrix m2, Matrix& result){
    int sum = 0;
    for (int k=0; k<m;++k){
        sum += m1.getContents()[i][k] * m2.getContents()[k][j];
    }
    result.setItem(i,j,sum);
}

Matrix MultiplyMatricesUsingThreads(Matrix m1, Matrix m2) {
    Matrix result;
    int n = m1.getWidth();
    int m = m1.getHeight();
    int p = m2.getHeight();
    result.createEmptyMatrix(n,p);
    std::vector<std::thread> threads;
    for (int i=0; i<n;++i){
        for (int j=0; j<p;++j){
            threads.emplace_back(GetSum, i, j, n, m, p, m1, m2, std::ref(result));
        }
    }
    for (auto& thread : threads) {
        thread.join();
    }

    return result;
}
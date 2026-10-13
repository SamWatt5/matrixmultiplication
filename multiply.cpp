#include <cmath>
#include "matrix.h"
#include "multiply.h"

// Matrix multiplication using no threads
Matrix MultiplyMatricesBasic(Matrix m1, Matrix m2) {
    Matrix result;
    int n = m1.getHeight();
    int m = m1.getWidth();
    int p = m2.getWidth();
    if ( m != m2.getHeight()) {
        throw std::invalid_argument("invalid matrix dimensions for multiplication");
    }
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
    int n = m1.getHeight();
    int m = m1.getWidth();
    int p = m2.getWidth();
    if ( m != m2.getHeight()) {
        throw std::invalid_argument("invalid matrix dimensions for multiplication");
    }
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

Matrix MultiplyMatricesUsingThreads_OLD(Matrix m1, Matrix m2) {
    Matrix result;
   int n = m1.getHeight();
    int m = m1.getWidth();
    int p = m2.getWidth();
    if ( m != m2.getHeight()) {
        throw std::invalid_argument("invalid matrix dimensions for multiplication");
    }
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

Matrix MultiplyMatricesUsingThreads_NEW(Matrix m1, Matrix m2) {
    Matrix result;
   int n = m1.getHeight();
    int m = m1.getWidth();
    int p = m2.getWidth();
    if ( m != m2.getHeight()) {
        throw std::invalid_argument("invalid matrix dimensions for multiplication");
    }
    result.createEmptyMatrix(n,p);
    std::vector<std::thread> threads;
    unsigned int max_threads = std::thread::hardware_concurrency();

    for (int i=0; i<n;++i){
        for (int j=0; j<p;++j){
            if (threads.size() == max_threads) {
                for (auto& thread : threads) {
                    thread.join();
                }
                threads.clear();
            }
            threads.emplace_back(GetSum, i, j, n, m, p, m1, m2, std::ref(result));
        }
    }
    // std::cout << threads.size();
    if (threads.size() > 0){
        for (auto& thread : threads) {
            thread.join();
        }
    }
    

    return result;
}

void GetSums(int iStart, int jStart, int row_step, int col_step,
             int n, int m, int p, Matrix m1, Matrix m2, Matrix& result) {
    int iEnd = std::min(iStart + row_step, n);
    int jEnd = std::min(jStart + col_step, p);

    for (int i = iStart; i < iEnd; ++i) {
        for (int j = jStart; j < jEnd; ++j) {
            int sum = 0;
            for (int k = 0; k < m; ++k) {
                sum += m1.getContents()[i][k] * m2.getContents()[k][j];
            }
            result.setItem(i, j, sum);
        }
    }
}

Matrix MultiplyMatricesUsingThreads_NEW_NEW(Matrix m1, Matrix m2) {
    Matrix result;
    int n = m1.getHeight();
    int m = m1.getWidth();
    int p = m2.getWidth();

    if (m != m2.getHeight()) {
        throw std::invalid_argument("invalid matrix dimensions for multiplication");
    }

    result.createEmptyMatrix(p, n);

    unsigned int max_threads = std::thread::hardware_concurrency();
    if (max_threads == 0) {
        max_threads = 1;
    }

    int row_step = (n + max_threads - 1) / max_threads;
    int col_step = (p + max_threads - 1) / max_threads;
    std::vector<std::thread> threads;

    for (int i = 0; i < n; i += row_step) {
        for (int j = 0; j < p; j += col_step) {
            threads.emplace_back(GetSums, i, j, row_step, col_step, n, m, p, m1, m2, std::ref(result));
        }
    }

    for (auto& thread : threads) {
        thread.join();
    }
    
    return result;
}

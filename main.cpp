#include <iostream>
#include <vector>
#include <omp.h>
#include "matrix.h"
#include "multiply.h"
#include "timer.h"

std::vector<Matrix> create_random_matrix(int n, int m, int p) {
    Matrix m1;
    Matrix m2;

    m1.createRandomMatrix(n,m);
    m2.createRandomMatrix(m,p);

    return {m1,m2};
}

void test_matrices(std::vector<Matrix> matrices){
// Create resulting matrix using non-threading approach
    Matrix res1;

    Timer timer;

    timer.startTimer();
    res1.setContents(MultiplyMatricesBasic(matrices[0], matrices[1]).getContents());
    timer.endTimer();
    std::cout << "Non-threading approach finished in " << timer.getTime() << " seconds" << std::endl;
    // res1.print();
    std::cout << std::endl;


    // Create resulting matrix using OpenMP approach
    Matrix res2;
    timer.startTimer();
    res2.setContents(MultiplyMatricesUsingOpenMP(matrices[0], matrices[1]).getContents());
    timer.endTimer();
    std::cout << "OpenMP approach finished in " << timer.getTime() << " seconds" << std::endl;
    // res2.print();
    std::cout << std::endl;

    Matrix res3;
    timer.startTimer();
    res3.setContents(MultiplyMatricesUsingThreads_OLD(matrices[0], matrices[1]).getContents());
    timer.endTimer();
    std::cout << "Threads library old approach finished in " << timer.getTime() << " seconds" << std::endl;
    // res3.print();
    std::cout << std::endl;

    Matrix res4;
    timer.startTimer();
    res4.setContents(MultiplyMatricesUsingThreads_NEW_NEW(matrices[0], matrices[1]).getContents());
    timer.endTimer();
    std::cout << "Threads library new approach finished in " << timer.getTime() << " seconds" << std::endl;
    // res4.print();
    std::cout << std::endl;

    std::cout << "Checking all results are equal..." << std::endl;
    if (res1.getContents() == res2.getContents() && res2.getContents() == res3.getContents() && res3.getContents() == res4.getContents()) {
        std::cout << "SUCCESS! all approaches calculated same matrix" << std::endl;
    }else{
        std::cout << "ERR - Calculations differ between approaches" << std::endl;
    }
}

void test_newnew(std::vector<Matrix> matrices) {
    Matrix test;
    test.setContents(MultiplyMatricesUsingThreads_NEW_NEW(matrices[0], matrices[1]).getContents());
}

int main(){
    std::cout << "testing multiplication on small matrices..." << std::endl;
    std::cout << "generating small matrices..." << std::endl;
    std::vector<Matrix> small_matrices = create_random_matrix(3,3,3);
    std::cout << "finished generating matrices.\nmultiplying small matrices..." << std::endl;
    test_matrices(small_matrices);

    std::cout << "testing multiplication on large matrices..." << std::endl;
    std::cout << "generating large matrices..." << std::endl;
    std::vector<Matrix> large_matrices = create_random_matrix(100,100,100);
    std::cout << "finished generating matrices.\nmultiplying large matrices..." << std::endl;
    test_matrices(large_matrices);
    //test_newnew(large_matrices);

    return 0;
}

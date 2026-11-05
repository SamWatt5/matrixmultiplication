#pragma once

#include "matrix.h"

Matrix MultiplyMatricesBasic(const Matrix& m1, const Matrix& m2);
Matrix MultiplyMatricesUsingOpenMP(Matrix& m1, Matrix& m2);
Matrix MultiplyMatricesUsingThreads_OLD(Matrix& m1, Matrix& m2);
Matrix MultiplyMatricesUsingThreads_NEW(Matrix& m1, Matrix& m2);
Matrix MultiplyMatricesUsingThreads_Blocking(const Matrix& m1, const Matrix& m2);
Matrix MultiplyMatricesUsingThreads_RowBlocks(const Matrix& m1, const Matrix& m2);
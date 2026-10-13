#include "matrix.h"
#include <thread>
#pragma once

// Matrix multiplication using no threads
Matrix MultiplyMatricesBasic(Matrix m1, Matrix m2);

// Matrix multiplication using OpenMP for multi-threading
Matrix MultiplyMatricesUsingOpenMP(Matrix m1, Matrix m2);

Matrix MultiplyMatricesUsingThreads(Matrix m1, Matrix m2);
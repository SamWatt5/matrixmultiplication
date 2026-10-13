cmake_minimum_required(VERSION 3.16)
project(matrixmultiplication LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(matrixmultiplication
    main.cpp
    matrix.cpp
    timer.cpp
    multiply.cpp
)

find_package(OpenMP REQUIRED)
target_link_libraries(matrixmultiplication PRIVATE OpenMP::OpenMP_CXX)
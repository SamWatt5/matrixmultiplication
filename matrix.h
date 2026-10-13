#include <vector>
#include <iostream>
#include <omp.h>
#pragma once
class Matrix {

private:
    std::vector<std::vector<int>> contents; 
public:
    std::vector<std::vector<int>> getContents();

    void setContents(std::vector<std::vector<int>> new_contents);

    int getWidth();

    int getHeight();

    std::vector<int> getRow(int index);

    std::vector<int> getCol(int index);

    void setItem(int x, int y, int n);

    void createRandomMatrix(int w, int h);
    void createEmptyMatrix(int w, int h);
    void print();
};


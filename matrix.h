#include <vector>
#include <iostream>
#include <omp.h>
#pragma once
class Matrix {

private:
    std::vector<std::vector<int>> contents; 
public:
    std::vector<std::vector<int>> getContents() const;

    void setContents(std::vector<std::vector<int>> new_contents);

    int getWidth() const;

    int getHeight() const;

    std::vector<int> getRow(int index) const;

    std::vector<int> getCol(int index) const;

    void setItem(int x, int y, int n);

    void createRandomMatrix(int w, int h);
    void createEmptyMatrix(int w, int h);
    void print();
};


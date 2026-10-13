#include "matrix.h"

std::vector<std::vector<int>> Matrix::getContents(){
    return contents;
}

void Matrix::setContents(std::vector<std::vector<int>> new_contents){
    contents = new_contents;
}

int Matrix::getWidth(){
    return contents[0].size();
}

int Matrix::getHeight(){
    return contents.size();
}

std::vector<int> Matrix::getRow(int index) {
    return contents[index];
}

std::vector<int> Matrix::getCol(int index) {
    std::vector<int> col;
    for (std::vector<int> row : contents){
        col.push_back(row[index]);
    }
    return col;
}

void Matrix::setItem(int x, int y, int n){
    contents[x][y] = n;
}

void Matrix::createRandomMatrix(int w, int h) {
    if (w <= 0 || h <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }

    contents.clear();
    contents.resize(h);

    #pragma omp parallel for
    for (int row = 0; row < h; ++row) {
        contents[row].resize(w);
        for (int col = 0; col < w; ++col) {
            contents[row][col] = rand() % 101;
        }
    }
}

void Matrix::createEmptyMatrix(int w, int h){
    if (w <= 0 || h <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }

    contents.clear();
    contents.resize(h);

    #pragma omp parallel for
    for (int row = 0; row < h; ++row) {
        contents[row].resize(w);
        for (int col = 0; col < w; ++col) {
            contents[row][col] = 0;
        }
    }
}

// Prints any given matrix
void Matrix::print() {
    for (std::vector<int> row : contents) {
        for (int item : row) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
}
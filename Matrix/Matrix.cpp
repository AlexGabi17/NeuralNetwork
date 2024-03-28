//
// Created by Alexandru Buzescu on 27.03.2024.
//

#include "Matrix.h"
#include <stdexcept>

template<typename T>
static std::vector<std::vector<T>> Matrix<T>::multiplication(const std::vector<std::vector<T>>& matrix1, const std::vector<std::vector<T>>& matrix2, float activationFunction(float)) {
    if(matrix1[0].size() != matrix2.size()) throw std::runtime_error("Product of matrix can't be performed");

    int numberRows_1 = matrix1.size(), numberCol_1 = matrix1[0].size(), numberRows_2 = matrix2.size(), numberCol_2 = matrix2[0].size();
    std::vector<std::vector<T>> result(numberRows_1, std::vector<T>(numberCol_2, 0));

    for(size_t row = 0; row<numberRows_1; ++row){
        for(size_t col = 0; col<numberCol_2; ++col){
            for(size_t it = 0; it<numberCol_1; ++it){
                result[row][col] += matrix1[row][it]*matrix2[it][col];
            }
//            std::cout<<result[row][col]<<"->";
            result[row][col] = activationFunction(result[row][col]);
//            std::cout<<result[row][col]<<'\n'<<'\n';
        }
    }
    /*
     * [3,3] x [3,1]
     * */

    return result;
}

template<typename T>
std::vector<std::vector<T>> Matrix<T>::transpose(const std::vector<std::vector<T>> &matrix) {
    int numRows = matrix.size(), numCol = matrix[0].size();
    std::vector<std::vector<T>> newMatrix(numCol, std::vector<T>(numRows));
    for(size_t row = 0; row < numRows; row ++){
        for(size_t col = 0; col < numCol; col ++){
            newMatrix[col][row] = matrix[row][col];
        }
    }
    return newMatrix;
}

template<typename T>
T Matrix<T>::defaultMethod(T val) {
    return val;
}

template class Matrix<float>;
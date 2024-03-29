//
// Created by Alexandru Buzescu on 27.03.2024.
//

#include "Matrix.h"
#include <stdexcept>

template<typename T>
static std::vector<std::vector<T>>
Matrix<T>::multiplication(const std::vector<std::vector<T>> &matrix1, const std::vector<std::vector<T>> &matrix2,
                          float activationFunction(float)) {
    if (matrix1[0].size() != matrix2.size()) throw std::runtime_error("Product of matrix can't be performed");

    int numberRows_1 = matrix1.size(), numberCol_1 = matrix1[0].size(), numberRows_2 = matrix2.size(), numberCol_2 = matrix2[0].size();
    std::vector<std::vector<T>> result(numberRows_1, std::vector<T>(numberCol_2, 0));

    for (size_t row = 0; row < numberRows_1; ++row) {
        for (size_t col = 0; col < numberCol_2; ++col) {
            for (size_t it = 0; it < numberCol_1; ++it) {
                result[row][col] += matrix1[row][it] * matrix2[it][col];
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
    for (size_t row = 0; row < numRows; row++) {
        for (size_t col = 0; col < numCol; col++) {
            newMatrix[col][row] = matrix[row][col];
        }
    }
//    std::cout<<"Transpose dimension = "<<newMatrix.size()<<","<<newMatrix[0].size()<<'\n';
    return newMatrix;
}

template<typename T>
T Matrix<T>::defaultMethod(T val) {
    return val;
}

template<typename T>
std::vector<std::vector<T>>
Matrix<T>::add(const std::vector<std::vector<T>> &matrix1, const std::vector<std::vector<T>> &matrix2,
               float sign) {
    if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size())
        throw std::runtime_error("Matrix are not compatible for add operation.");

    std::vector<std::vector<T>> newMatrix(matrix1.size(), std::vector<T>(matrix1[0].size()));
    int rowSize = matrix1.size(), colSize = matrix1[0].size();
    for (size_t row = 0; row < rowSize; row++) {
        for (size_t col = 0; col < colSize; col++) {
            newMatrix[row][col] = matrix1[row][col] + sign * matrix2[row][col];
        }
    }
    return newMatrix;
}

template<typename T>
std::vector<std::vector<T>>
Matrix<T>::multiplyByScalar(const std::vector<std::vector<T>> &matrix, const float &scalar) {
    std::vector<std::vector<T>> res(matrix.size(), std::vector<T>(matrix[0].size()));
    int rowNum = matrix.size(), colNum = matrix[0].size();
    for (size_t row = 0; row < rowNum; row++) {
        for (size_t col = 0; col < colNum; col++) {
            res[row][col] = matrix[row][col] * scalar;
        }
    }
    return res;
}

template<typename T>
std::vector<std::vector<T>>
Matrix<T>::elementWiseMulitply(const std::vector<std::vector<T>> &matrix1, const std::vector<std::vector<T>> &matrix2) {
    if (matrix1.size() != matrix2.size() && matrix1[0].size() != matrix2[0].size())
        throw std::runtime_error("elementWiseMultiply cannot be performed with 2 matrix with different dimensions");
    int rowSize = matrix1.size(), colSize = matrix1[0].size();
    std::vector<std::vector<T>> result(rowSize, std::vector<T>(colSize));
    for (size_t row = 0; row < rowSize; row++) {
        for (size_t col = 0; col < colSize; col++) {
            result[row][col] = matrix1[row][col] * matrix2[row][col];
        }
    }
    return result;
}

template<typename T>
std::vector<std::vector<T>>
Matrix<T>::subtractFromScalar(const std::vector<std::vector<T>> &matrix, const float &scalar) {
    std::vector<std::vector<T>> res(matrix.size(), std::vector<T>(matrix[0].size()));
    int rowNum = matrix.size(), colNum = matrix[0].size();
    for (size_t row = 0; row < rowNum; row++) {
        for (size_t col = 0; col < colNum; col++) {
            res[row][col] = scalar - matrix[row][col];
        }
    }
    return res;
}

template
class Matrix<float>;
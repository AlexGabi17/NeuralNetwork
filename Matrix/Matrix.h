//
// Created by Alexandru Buzescu on 27.03.2024.
//

#ifndef NEURALNETWORK_MATRIX_H
#define NEURALNETWORK_MATRIX_H

#include <vector>
#include <iostream>

template<typename T>
class Matrix {
private:
    static T defaultMethod(T val);

public:
    static std::vector<std::vector<T>>
    multiplication(const std::vector<std::vector<T>> &matrix1, const std::vector<std::vector<T>> &matrix2,
                   float activationFunction(float) = defaultMethod);

    static std::vector<std::vector<T>> multiplyByScalar(const std::vector<std::vector<T>> &matrix, const float &scalar);

    static std::vector<std::vector<T>>
    subtractFromScalar(const std::vector<std::vector<T>> &matrix, const float &scalar);

    static std::vector<std::vector<T>>
    elementWiseMulitply(const std::vector<std::vector<T>> &matrix1, const std::vector<std::vector<T>> &matrix2);

    static std::vector<std::vector<T>> transpose(const std::vector<std::vector<T>> &matrix);

    static std::vector<std::vector<T>>
    add(const std::vector<std::vector<T>> &matrix1, const std::vector<std::vector<T>> &matrix2, float sign = 1);

};


#endif //NEURALNETWORK_MATRIX_H

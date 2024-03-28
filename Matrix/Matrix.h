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
    static std::vector<std::vector<T>> multiplication(const std::vector<std::vector<T>>& matrix1, const std::vector<std::vector<T>>& matrix2, float activationFunction(float) = defaultMethod);
    static std::vector<std::vector<T>> transpose(const std::vector<std::vector<T>>& matrix);
};



#endif //NEURALNETWORK_MATRIX_H

//
// Created by Alexandru Buzescu on 27.03.2024.
//

#include <iostream>
#include "NeuralNetwork.h"
#include "../Matrix/Matrix.h"



NeuralNetwork::NeuralNetwork(std::vector<int> nodes, float learningRate) {
    this->nodes = nodes;
    this->learningRate = learningRate;
    initWeights();
}

float NeuralNetwork::getLearningRate() const {
    return this->learningRate;
}

float NeuralNetwork::getRandomNum(const float& meanValue, const float& standardDeviation) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::normal_distribution<float> dist(meanValue, standardDeviation);
    return dist(mt);
}

void NeuralNetwork::initWeights() {
    for (size_t it = 0; it < nodes.size() - 1; it++) { // Every layer has a weight matrix except the last one
        weights.push_back(std::vector<std::vector<float>>(nodes[it + 1], std::vector<float>(nodes[it], 0)));
        float standardDeviation = (pow(nodes[it + 1], -0.5));
//        std::cout<<standardDeviation<<'\n';
        for (size_t row = 0; row < nodes[it + 1]; row++) {
            for (size_t col = 0; col < nodes[it]; col++) {
                weights[it][row][col] = getRandomNum(MEAN_VALUE, standardDeviation);
            }
        }
    }
}

std::vector<std::vector<float>> NeuralNetwork::getLayerWeights(const size_t& layer) const {
    return weights[layer];
}

std::vector<std::vector<std::vector<float>>> NeuralNetwork::getLayersWeights() const {
    return weights;
}

void NeuralNetwork::displayLayerWeights(const size_t& layer) const {
    std::vector<std::vector<float>> w = this->getLayerWeights(layer);
    for (size_t row = 0; row < w.size(); row++) {
        for (size_t col = 0; col < w[0].size(); col++) {
            std::cout << w[row][col] << " ";
        }
        std::cout << '\n';
    }
}

std::vector<float> NeuralNetwork::query(const std::vector<float>& input) const {
    std::vector<std::vector<float>> queryMatrix;
    queryMatrix.push_back(input);
    queryMatrix = Matrix<float>::transpose(queryMatrix);
//    std::cout<<inputMatrix.size()<< " " <<inputMatrix[0].size();
    int queryMatrixSize;
    for(size_t it = 0; it < weights.size(); it ++) {
        queryMatrix = Matrix<float>::multiplication(weights[it], queryMatrix, &sigmoid);
//        std::cout<<'\n';
        queryMatrixSize = queryMatrix.size();

//        for(size_t row = 0; row<queryMatrixSize; row ++){
//            std::cout<<queryMatrix[row][0]<<" ";
//            queryMatrix[row][0] = sigmoid(queryMatrix[row][0]);
//            std::cout<<queryMatrix[row][0]<<'\n';
//        }
//        for (int i = 0; i < queryMatrix.size(); i++) {
//            for (int j = 0; j < queryMatrix[0].size(); j++) {
//                std::cout << queryMatrix[i][j] << " ";
//            }
//            std::cout << '\n';
//        }
//        std::cout<<'\n';
    }
    return Matrix<float>::transpose(queryMatrix)[0];
}

void NeuralNetwork::train(std::vector<std::vector<float>> input, std::vector<std::vector<float>> target) {
    /* input =       target =
     * [ [1,2,3]        [ [1,4,6]
     *   [2,3,4]          [43,5,6]
     *   [2,4,5]          [3, 3, 5]
     * ]                ]
     * */
    if(input.size() != target.size()) throw std::runtime_error("Input size should be same as target size");
    int numInput = input.size();
    std::vector<float> response;
//    std::cout<<"\n\n\n";
    for(size_t it = 0; it < numInput; it++){
//        std::cout<<"Input = "<<it<<'\n';
        response = query(input[it]);
        for(int i=0; i<response.size(); i++){
            std::cout<<response[i]<<" ";
        }
        std::cout<<"\n\n\n";
    }
}



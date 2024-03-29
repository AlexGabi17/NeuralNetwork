//
// Created by Alexandru Buzescu on 27.03.2024.
//

#include <iostream>
#include "NeuralNetwork.h"
#include "../Matrix/Matrix.h"


NeuralNetwork::NeuralNetwork(std::vector<int> nodes, float learningRate) {
    this->neurons = nodes;
    this->learningRate = learningRate;
    initWeights();
}

float NeuralNetwork::getLearningRate() const {
    return this->learningRate;
}

float NeuralNetwork::getRandomNum(const float &meanValue, const float &standardDeviation) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::normal_distribution<float> dist(meanValue, standardDeviation);
    return dist(mt);
}

void NeuralNetwork::initWeights() {
    for (size_t it = 0; it < neurons.size() - 1; it++) { // Every layer has a weight matrix except the last one
        weights.push_back(std::vector<std::vector<float>>(neurons[it + 1], std::vector<float>(neurons[it], 0)));
        float standardDeviation = (pow(neurons[it + 1], -0.5));
//        std::cout<<standardDeviation<<'\n';
        for (size_t row = 0; row < neurons[it + 1]; row++) {
            for (size_t col = 0; col < neurons[it]; col++) {
                weights[it][row][col] = getRandomNum(MEAN_VALUE, standardDeviation);
            }
        }
    }
}

std::vector<std::vector<float>> NeuralNetwork::getLayerWeights(const size_t &layer) const {
    return weights[layer];
}

std::vector<std::vector<std::vector<float>>> NeuralNetwork::getLayersWeights() const {
    return weights;
}

void NeuralNetwork::displayLayerWeights(const size_t &layer) const {
    std::vector<std::vector<float>> w = this->getLayerWeights(layer);
    for (size_t row = 0; row < w.size(); row++) {
        for (size_t col = 0; col < w[0].size(); col++) {
            std::cout << w[row][col] << " ";
        }
        std::cout << '\n';
    }
}

std::vector<std::vector<float>> NeuralNetwork::query(const std::vector<float> &input) const {
    std::vector<std::vector<float>> queryMatrix;
    queryMatrix.push_back(input);
    queryMatrix = Matrix<float>::transpose(queryMatrix);
//    std::cout<<inputMatrix.size()<< " " <<inputMatrix[0].size();
    int queryMatrixSize;
    for (size_t it = 0; it < weights.size(); it++) {
        queryMatrix = Matrix<float>::multiplication(weights[it], queryMatrix, &sigmoid);
//        std::cout<<'\n';
        queryMatrixSize = queryMatrix.size();

    }
    return queryMatrix;
}

void NeuralNetwork::train(std::vector<std::vector<float>> input, std::vector<std::vector<float>> target) {
    /* input =       target =
     * [ [1,2,3]        [ [1,4,6]
     *   [2,3,4]          [43,5,6]
     *   [2,4,5]          [3, 3, 5]
     * ]                ]
     * */
    if (input.size() != target.size()) throw std::runtime_error("Input size should be same as target size");
    int numInput = input.size();
    std::vector<std::vector<float>> outputError;
    std::vector<std::vector<float>> targetMatrix;
    std::vector<std::vector<float>> queryMatrix;


    //    std::cout<<"\n\n\n";
    for (size_t it = 0; it < numInput; it++) {

        std::cout << "Inputul " << it << '\n';
        std::vector<std::vector<std::vector<float>>> listOutputs;
        std::vector<std::vector<float>> inputMatrix;
        inputMatrix.push_back(input[it]);
        listOutputs.push_back(Matrix<float>::transpose(inputMatrix));
        queryMatrix = listOutputs[0];

        for (size_t layer = 0; layer < weights.size(); layer++) {
            queryMatrix = Matrix<float>::multiplication(weights[layer], queryMatrix, &sigmoid);

            listOutputs.push_back(queryMatrix);
        }



//        finished forward propagating and saving the outputs after every layer;



//         Backpropagating
        targetMatrix = Matrix<float>::transpose({target[it]});
        outputError = Matrix<float>::add(targetMatrix, listOutputs[listOutputs.size() - 1], -1);
        for (int outputIndex = listOutputs.size() - 1; outputIndex > 0; --outputIndex) {
//            iterating from n -> 1
            std::cout << "OutputIndex=" << outputIndex << '\n';
//            std::cout<<"dimensiune listOutputs[" << outputIndex << "] = "<<listOutputs[outputIndex].size()<<", "<<listOutputs[outputIndex][0].size()<<'\n';
            for (int row = 0; row < listOutputs[outputIndex].size(); row++) {
                for (int col = 0; col < listOutputs[outputIndex][0].size(); col++) {
                    std::cout << listOutputs[outputIndex][row][col] << " ";
                }
                std::cout << '\n';
            }
            std::cout << '\n';


//            // Updating weights
            int weightsSize = weights.size();
//            //OutputErrors * finalOutpus * (1.0 - finalOutput)
            std::vector<std::vector<float>> result;

            result = Matrix<float>::elementWiseMulitply(outputError, listOutputs[outputIndex]);
//            // (1.0 - finalOutput)
//
            result = Matrix<float>::elementWiseMulitply(result,
                                                        Matrix<float>::subtractFromScalar(listOutputs[outputIndex], 1));
//            // OutputErrors * finalOutpus * (1.0 - finalOutput) * outputs[index-1]_transpose

//            std::cout<<"result="<<result.size()<<", "<<result[0].size()<<'\n';
            result = Matrix<float>::multiplication(result, Matrix<float>::transpose(listOutputs[outputIndex - 1]));
//
            result = Matrix<float>::multiplyByScalar(result, this->learningRate);
            weights[outputIndex - 1] = Matrix<float>::add(weights[outputIndex - 1], result, 1);

            outputError = Matrix<float>::multiplication(Matrix<float>::transpose(weights[outputIndex - 1]),
                                                        outputError);
//            std::cout << "\n\n\n";

        }
        std::cout << "------------" << '\n';
    }
}



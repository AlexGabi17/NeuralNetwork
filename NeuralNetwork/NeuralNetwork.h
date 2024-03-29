//
// Created by Alexandru Buzescu on 27.03.2024.
//

#ifndef NEURALNETWORK_NEURALNETWORK_H
#define NEURALNETWORK_NEURALNETWORK_H
#define DEFAULT_LEARNING_RATE 0.01
#define MEAN_VALUE 0.0f
#define DEFAULT_STANDARD_DEVIATION 0.5f


#include <vector>
#include <random>

class NeuralNetwork {
private:
    std::vector<int> neurons;
    std::vector<std::vector<std::vector<float>>> weights; // vector of weights matrix
    float learningRate;

    void initWeights();

public:
    NeuralNetwork(std::vector<int> nodes, float learningRate = DEFAULT_LEARNING_RATE);

    float getLearningRate() const;

    static float
    getRandomNum(const float &meanValue = MEAN_VALUE, const float &standardDeviation = DEFAULT_STANDARD_DEVIATION);

    std::vector<std::vector<float>> getLayerWeights(const size_t &layer) const;

    std::vector<std::vector<std::vector<float>>> getLayersWeights() const;

    std::vector<std::vector<float>> query(const std::vector<float> &input) const;

    void train(std::vector<std::vector<float>> input, std::vector<std::vector<float>> target);

    inline static float sigmoid(float num) {
        return 1. / (1. + exp((-1) * num));
    }

    //    Debugging & Research Methods
    void displayLayerWeights(const size_t &layer) const;
};


#endif //NEURALNETWORK_NEURALNETWORK_H

#include <iostream>
#include "NeuralNetwork/NeuralNetwork.h"
#include "Matrix/Matrix.h"


int main() {
    NeuralNetwork *net = new NeuralNetwork({3, 3, 3});
//    std::cout << net->getLearningRate();

//    net->displayLayerWeights(0);
//    std::cout << '\n';
//    net->displayLayerWeights(1);
//    std::cout << '\n';

    std::vector<float> input = {0.1, 0.2, 0.3};
    std::vector<std::vector<float>> train_input = { {0.1, 0.2, 0.3}, {0.2, 0.4, 0.5}, {0.6, 0.2, 0.1} };
    std::vector<std::vector<float>> target = { {0.1, 0.1, 0.9}, {0.3, 0.2, 0.1}, {0.1, 0.5, 0.2} };
    net->train(train_input, target);
//    std::vector<float> q = net->query(input);
//    for(auto x: q){
//        std::cout<<x<<" ";
//    }

    delete net;
    return 0;
}

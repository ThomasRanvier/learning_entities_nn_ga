#ifndef GENERIC_NEURAL_NETWORK_NEURALNETWORK_H
#define GENERIC_NEURAL_NETWORK_NEURALNETWORK_H

#include "Neuron.h"

class NeuralNetwork {
private:
    std::vector<std::vector<Neuron *>> net;

    std::vector<int> layers;
    std::vector<double> getOutputs();

    void setEntries(std::vector<double> vector);
    void runNetwork();
public:

    const std::vector<int> getLayers() const;
    void setWeights(const std::vector<std::vector<std::vector<double>>> weights);
    NeuralNetwork(const std::vector<int>);
    std::vector<double> forward(std::vector<double>);
    const std::vector<std::vector<std::vector<double>>> getWeights();
    void displayNet();
};


#endif
#ifndef GENERIC_NEURAL_NETWORK_NEURON_H
#define GENERIC_NEURAL_NETWORK_NEURON_H

#include "../config.hpp"

class Neuron {
private:
    std::vector<double> weights;
public:
    void setWeights(const std::vector<double> &weights);

private:
    std::vector<Neuron *> entries;
    double output;
public:
    Neuron(std::vector<Neuron *>);
    Neuron(std::vector<Neuron *>, std::vector<double>);
    void compute();
    double getOutput() const;
    void setOutput(double output);
    const std::vector<double> getWeights() const;
    void displayNeuron();
};


#endif
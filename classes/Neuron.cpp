#include <cstdlib>
#include "../headers/Neuron.h"

Neuron::Neuron(std::vector<Neuron *> entries) {
    this->entries = entries;
    for (unsigned int i(0); i < entries.size(); i++) {
        this->weights.push_back(((rand() / double(RAND_MAX)) * 2.0) - 1.0);
    }
}

void Neuron::compute() {
    double sum(0);
    for (unsigned int i(0); i < this->entries.size(); i++) {
        sum += this->entries[i]->output * this->weights[i];
    }
    this->output = sum;
}

Neuron::Neuron(std::vector<Neuron *> entries, std::vector<double> weights) {
    this->entries = entries;
    this->weights = weights;
}

double Neuron::getOutput() const {
    return output;
}

void Neuron::setOutput(double output) {
    this->output = output;
}

const std::vector<double> Neuron::getWeights() const {
    return this->weights;
}

void Neuron::displayNeuron() {
    std::cout << " nb of weights : " << this->weights.size() << std::endl;
    for (unsigned int i(0); i < this->weights.size(); i++) {
        std::cout << "Weight " << i + 1 << " : " << this->weights[i] << std::endl;
    }
    std::cout << std::endl;
}

void Neuron::setWeights(const std::vector<double> &weights) {
    Neuron::weights = weights;
}

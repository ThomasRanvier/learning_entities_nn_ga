#include <vector>
#include "../headers/NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(std::vector<int> layers) : layers(layers){
    std::vector<Neuron *> neurons;
    std::vector<Neuron *> entries;
    for (unsigned int i(0); i < layers.size(); i++) {
        for (unsigned int j(0); j < layers[i]; j++) {
            neurons.push_back(new Neuron(entries));
        }
        this->net.push_back(neurons);
        entries = neurons;
        neurons.clear();
    }
}

void NeuralNetwork::setWeights(const std::vector<std::vector<std::vector<double>>> weights) {
    for (unsigned int i(0); i < net.size(); i++) {
        if (i != 0) {
            for (unsigned int j(0); j < net[i].size(); j++) {
                std::vector<double> neuronWeights;
                for (unsigned int k(0); k < net[i][j]->getWeights().size(); k++) {
                    neuronWeights.push_back(weights[i - 1][j][k]);
                    //MUTATIONS
                }
                net[i][j]->setWeights(neuronWeights);
            }
        }
    }
}


void NeuralNetwork::displayNet() {
    std::cout << "<------NETWORK BRIEF------>\n\nNb of layers : " << this->net.size() << "\n";
    for (unsigned int i(0); i < this->net.size(); i++) {
        std::cout << "\n<---Layer " << i + 1 << ", neurons : " << this->net[i].size() << "--->\n\n";
        for (unsigned int j(0); j < this->net[i].size(); j++) {
            if (i == 0) {
                std::cout << "Entrie " << j + 1 << " : no weights\n";
            } else {
                std::cout << "Neuron " << j + 1;
                this->net[i][j]->displayNeuron();
            }
        }
    }
}

std::vector<double> NeuralNetwork::forward(std::vector<double> entries) {
    std::vector<double> outputs;
    if (entries.size() == this->net[0].size()) {
        setEntries(entries);
        runNetwork();
        outputs = getOutputs();
    }
    return outputs;
}

std::vector<double> NeuralNetwork::getOutputs() {
    std::vector<double> outputs;
    int lastLayer(this->net.size() - 1);
    for (unsigned int i(0); i < this->net[lastLayer].size(); i++) {
        outputs.push_back(this->net[lastLayer][i]->getOutput());
    }
    return outputs;
}

void NeuralNetwork::setEntries(std::vector<double> entries) {
    for (unsigned int i(0); i < this->net[0].size(); i++) {
        this->net[0][i]->setOutput(entries[i]);
    }
}

void NeuralNetwork::runNetwork() {
    for (unsigned int i(1); i < this->net.size(); i++) {
        for (unsigned int j(0); j < this->net[i].size(); j++) {
            this->net[i][j]->compute();
        }
    }
}

const std::vector<int> NeuralNetwork::getLayers() const {
    return layers;
}

const std::vector<std::vector<std::vector<double>>> NeuralNetwork::getWeights() {
    std::vector<std::vector<std::vector<double>>> weights;

    for (unsigned int i(0); i < this->layers.size(); i++) {
        std::vector<std::vector<double>> layerWeights;
        for (unsigned int j(0); j < this->layers[i]; j++) {
            if (i != 0) layerWeights.push_back(this->net[i][j]->getWeights());
        }
        if (i != 0) weights.push_back(layerWeights);
    }

    return weights;
}

#include "neural_net.h"
#include <math>
#include <iostream>
#include <random>

class NeuralNet::Impl {
public:
    // implementation variables
    int ni, no;
    int[] n_layers;
    double[][][] weights;
    double[][][] changes;
    double[][] node_acts;
    // Sigmoid Function
    double sigmoid(double x) {
        return tanh(x)
    }
    // Derivative of sigmoid in terms of output
    double dsigmoid(double y) {
        return 1 - y*y
    }
    // Useful Matrix Functions
    double[][] makeRandMatrix(int rows, int cols) {
        double[rows][cols] m;
        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {
                m[r][c] = ((double) rand() / RAND_MAX) * 2 - 1;
            }
        }
    }
    double[][] makeZeroMatrix(int rows, int cols) {
        double[rows][cols] m;
        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {
                m[r][c] = 0.0;
            }
        }
    }
    // Functions that are meant to be hidden but directly used in the implementation
    double[] update_network(double[] inputs) {
        for(int i = 0; i < ni - 1; i++) {
            node_acts[0][i] = inputs[i]
        }
        for(int k = 1; k < n_layers.length-1; k++) {
            for(int j = 0; j < n_layers[k].length - 1; j++) {
                double total = 0.0
                for(int i = 0; i < n_layers[k-1].length; i++) {
                    total += node_acts[k-1][i] * weights[k][i][j]; // NEED TO CHECK. Indecies are confusing
                }
                node_acts[k][j] = sigmoid(total);
            }
        }
        for(int i = 0; i < no; i++) {
            double total = 0.0;
            for(int j = 0; j < n_layers[n_layers.length-1].length) {
                total += node_acts[n_layers.length-1][j] * weights[n_layers.length][j][i];
            }
            node_acts[n_layers.length + 1][i] = total;
        }
        return node_acts[n_layers.length + 1];
    }
    
    double backPropogate(double[] targets, double N, double M) {
        return NULL;
    }
};

NerualNet::NeuralNet(int nInput, int nOutput, int nLayers) : mImpl(new Impl) {
    mImpl->ni = nInput;
    mImpl->no = nOutput;
    mImpl->n_layers = [nLayers + 1];
    mImpl->weights = double[2];
    weights[0] = mImpl->makeRandMatrix(nInput, nLayers);
    weights[1] = mImpl->makeRandMatrix(nLayers, nOutput);
    mImpl->changes = double[2];
    changes[0] = mImpl->makeZeroMatrix(nInput, nLayers);
    changes[1] = mImpl->makeZeroMatrix(nLayers, nOutput);
    mImpl->node_acts = double[3];
    // Initialize the lengths of node_acts based on the number of neurons
}

NerualNet::NeuralNet(int nInput, int nOutput, int[] nLayers) : nImpl(new Impl) {
    mImpl->ni = nInput + 1; // for bias neuron
    mImpl->no = nOutput;
    mImpl->n_layers = int[nLayers.length];
    for(int i = 0; i < nLayers.length; i++) {
        mImpl->n_layers[i] = nLayers[i] + 1;
    }
    mImpl->weights = double[nLayers.length + 1];
    weights[0] = mImpl->makeRandMatrix(nInput, nLayers[0]);
    weights[nLayers.length] = mImpl->makeRandMatrix(nLayers[nLayers.length - 1], nOutput);
    for(int i = 1; i < nLayers.length ; i++) {
        weights[i] = mImpl->makeRandMatrix(nLayers[i - 1], nLayers[i]);
    }
    mImpl->changes = double[nLayers.length + 1];
    changes[0] = mImpl->makeZeroMatrix(nInput, nLayers[0]);
    changes[nLayers.length] = mImpl->makeZeroMatrix(nLayers[nLayers.length - 1], nOutput);
    for(int i = 1; i < nLayers.length ; i++) {
        changes[i] = mImpl->makeZeroMatrix(nLayers[i - 1], nLayers[i]);
    }
    mImpl->node_acts = double[nLayers.length + 2];
    // Initialize the lengths of node_acts based on the number of neurons
}

NeuralNet::NeuralNet(const NerualNet &other) : mImpl(other.mImpl) {
    mImpl->ni = other.mImpl->ni;
    mImpl->no = other.mImpl->no;
    mImpl->n_layers = other.mImpl->n_layers;
}

NeuralNet& NeuralNet::operator=(const NeuralNet &other) {
    if(this != other) {
        mImpl->ni = other.mImpl->ni;
        mImpl->no = other.mImpl->no;
        mImpl->n_layers = other.mImpl->n_layers;
    }
    return *this
}

NeuralNet::~NeuralNet() {}

double[][] NeuralNet::weights(int layer) {
    return mImpl->weights[0];
}

void NeuralNet::train(double[][][] pattern, int iterations, double learn_rate, double momentum) {
    /*
    * Pattern should be an array with multiple input / output pairings
    */
    double error = 0.0;
    double pair_error = 0.0;
    int update_interval = iterations / 10;
    for(int i = 0; i < iterations; i++) {
        error = 0.0;
        for(double[] &p : pattern) {
            mImpl->update_network(p[0]);
            pair_error = mImpl->backPropogate(p[1], learn_rate, momentum);
            error += pair_error;
        }
        if(i % update_interval == 0) {
            std::cout << "Error Trial " + i + ": " + error << std::endl;
        }
    }
    std::cout << "Final Iteration Error:  " + error << std::endl;
}

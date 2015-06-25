#include "neural_net.h"
#include <math.h>
#include <iostream>
#include <random>
#include <cstddef>

// Unused spare code from when I needed an array size.
// I won't remove it becuase it could be helpful later
template<typename T, std::size_t N>
std::size_t size(T (&)[N]) { return N; }

class NeuralNet::Impl {
public:
    // implementation variables
    int hidden_layers;
    int ni, no;
    int* n_layers;
    double*** weights;
    double*** changes;
    double** node_acts;
    // Sigmoid Function
    double sigmoid(double x) {
        return tanh(x);
    }
    // Derivative of sigmoid in terms of output
    double dsigmoid(double y) {
        return 1 - y*y;
    }
    // Useful Matrix Functions
    double** makeRandMatrix(int rows, int cols) {
        double** m = new double *[rows];
        for(int r = 0; r < rows; r++) {
            m[r] = new double[cols];
            for(int c = 0; c < cols; c++) {
                m[r][c] = ((double) rand() / RAND_MAX) * 2 - 1;
            }
        }
        return m;
    }
    double** makeZeroMatrix(int rows, int cols) {
        double** m = new double*[cols];
        for(int r = 0; r < rows; r++) {
            m[r] = new double[cols];
            for(int c = 0; c < cols; c++) {
                m[r][c] = 0.0;
            }
        }
        return m;
    }
    // Functions that are meant to be hidden but directly used in the implementation
    double* update_network(double* inputs) {
        for(int i = 0; i < ni - 1; i++) {
            node_acts[0][i] = inputs[i];
        }
        for(int k = 1; k < hidden_layers-1; k++) {
            for(int j = 0; j < n_layers[k] - 1; j++) {
                double total = 0.0;
                for(int i = 0; i < n_layers[k-1]; i++) {
                    total += node_acts[k-1][i] * weights[k][i][j]; // NEED TO CHECK. Indecies are confusing
                }
                node_acts[k][j] = sigmoid(total);
            }
        }
        for(int i = 0; i < no; i++) {
            double total = 0.0;
            for(int j = 0; j < n_layers[hidden_layers-1]; j++) {
                total += node_acts[hidden_layers-1][j] * weights[hidden_layers][j][i];
            }
            node_acts[hidden_layers + 1][i] = total;
        }
        return node_acts[hidden_layers + 1];
    }

    double backPropogate(double* targets, double N, double M) {
        double** deltas = new double *[hidden_layers + 1];
        deltas[hidden_layers] = new double [no];
        for(int i = 0; i < no; i++) {
            deltas[hidden_layers][i] = targets[i] - node_acts[hidden_layers + 1][i];
            deltas[hidden_layers][i] *= dsigmoid(node_acts[hidden_layers+1][i]);
        }
        for(int j = hidden_layers-1; j >= 0; j--) {
            deltas[j] = new double [n_layers[j]];
            for(int i = 0; i < n_layers[j]; i++) {
                double error = 0.0;
                for(int k = 0; k < n_layers[j+1]; k++) {
                    error += deltas[j+1][k] * weights[j][i][k];
                }
                deltas[j][i] = dsigmoid(node_acts[j][i]) * error;
            }
        }
        int plen, len;
        for(int k = hidden_layers; k >= 0; k--) {
            if(k==0) { plen = ni; }
            else { plen = n_layers[k-1]; }
            if(k==hidden_layers) { len = no; }
            else { plen = n_layers[k]; }
            for(int j = 0; j < plen; j++) {
                for(int i = 0; i < len; i++) {
                    double change = deltas[k][i] * node_acts[j][i];
                    weights[k][j][i] += N * change + M * changes[k][j][i];
                    changes[k][j][i] = change;
                }
            }
        }
        // Calculate error
        double error = 0.0;
        for(int i = 0; i < no; i++) {
            error += 0.5 * ((targets[i]-node_acts[hidden_layers+1][i]) * (targets[i]-node_acts[hidden_layers+1][i]));
        }
        delete deltas;
        return error;
    }
};

NeuralNet::NeuralNet(int nInput, int nOutput, int nLayers) : mImpl(new Impl) {
    mImpl->hidden_layers = 1;
    mImpl->ni = nInput;
    mImpl->no = nOutput;
    mImpl->n_layers = new int [1];
    mImpl->n_layers[0] = nLayers + 1;
    mImpl->weights = new double **[2];
    mImpl->weights[0] = mImpl->makeRandMatrix(nInput, nLayers);
    mImpl->weights[1] = mImpl->makeRandMatrix(nLayers, nOutput);
    mImpl->changes = new double **[2];
    mImpl->changes[0] = mImpl->makeZeroMatrix(nInput, nLayers);
    mImpl->changes[1] = mImpl->makeZeroMatrix(nLayers, nOutput);
    mImpl->node_acts = new double *[3];
    mImpl->node_acts[0] = new double [nInput];
    mImpl->node_acts[1] = new double [nLayers];
    mImpl->node_acts[2] = new double [nOutput];
}

NeuralNet::NeuralNet(int nInput, int nOutput, int nLayers[]) : mImpl(new Impl) {
    mImpl->hidden_layers = sizeof(*nLayers) / sizeof(nLayers[0]);
    int hidden_layers = mImpl->hidden_layers;
    mImpl->ni = nInput + 1; // for bias neuron
    mImpl->no = nOutput;
    mImpl->n_layers = new int [hidden_layers];
    for(int i = 0; i < hidden_layers; i++) {
        mImpl->n_layers[i] = nLayers[i] + 1;
    }
    mImpl->weights = new double **[hidden_layers + 1];
    mImpl->weights[0] = mImpl->makeRandMatrix(nInput, nLayers[0]);
    mImpl->weights[hidden_layers] = mImpl->makeRandMatrix(nLayers[hidden_layers - 1], nOutput);
    for(int i = 1; i < hidden_layers ; i++) {
        mImpl->weights[i] = mImpl->makeRandMatrix(nLayers[i - 1], nLayers[i]);
    }
    mImpl->changes = new double **[hidden_layers + 1];
    mImpl->changes[0] = mImpl->makeZeroMatrix(nInput, nLayers[0]);
    mImpl->changes[hidden_layers] = mImpl->makeZeroMatrix(nLayers[hidden_layers - 1], nOutput);
    for(int i = 1; i < hidden_layers ; i++) {
        mImpl->changes[i] = mImpl->makeZeroMatrix(nLayers[i - 1], nLayers[i]);
    }
    mImpl->node_acts = new double *[hidden_layers + 2];
    mImpl->node_acts[0] = new double [nInput];
    mImpl->node_acts[hidden_layers + 1] = new double[nOutput];
    for(int i = 1; i < hidden_layers + 1; i++)  {
        mImpl->node_acts[i] = new double [nLayers[i]];
    }
}

NeuralNet::NeuralNet(const NeuralNet &other) : mImpl(other.mImpl) {
    mImpl->ni = other.mImpl->ni;
    mImpl->no = other.mImpl->no;
    mImpl->n_layers = other.mImpl->n_layers;
}

NeuralNet& NeuralNet::operator=(const NeuralNet &other) {
    if(this != &other) {
        mImpl->ni = other.mImpl->ni;
        mImpl->no = other.mImpl->no;
        mImpl->n_layers = other.mImpl->n_layers; // Shallow Copy
    }
    return *this;
}

NeuralNet::~NeuralNet() {
    delete mImpl->n_layers;
    delete mImpl->weights;
    delete mImpl->changes;
    delete mImpl->node_acts;
}

double** NeuralNet::weights(int layer) {
    return mImpl->weights[0];
}

void NeuralNet::train(double ***pattern, int iterations, double learn_rate, double momentum, int num_patterns) {
    /*
    * Pattern should be an array with multiple input / output pairings
    */
    double error = 0.0;
    double pair_error = 0.0;
    int update_interval = iterations / 10;
    for(int i = 0; i < iterations; i++) {
        error = 0.0;
        for(int j = 0; j < num_patterns; j++) {
            mImpl->update_network(pattern[j][0]);
            pair_error = mImpl->backPropogate(pattern[j][1], learn_rate, momentum);
            error += pair_error;
        }
        if(i % update_interval == 0) {
            std::cout << "Error Trial " << i << ": " << error << std::endl;
        }
    }
    std::cout << "Final Iteration Error:  " << error << std::endl;
}
/*
double* NeuralNet::test(double ***patterns) {
    double* tmp = new double [patterns.length]; // Cannot use .length
    int i = 0;
    for(double p : pattern) {
        double* result = mImpl->update(p[0])
        std::cout << p[0] << " -> " << result << std::endl;
        tmp[i] = result;
        i++;
    }
    return tmp;
}*/

void NeuralNet::print_test(double ***patterns, int num_patterns) {
    for(int i = 0; i < num_patterns; i++) {
        double* result = mImpl->update_network(patterns[i][0]);
        std::cout << patterns[i][0] << " -> " << result << std::endl;
    }
}

#include "neural_net.h"
#include <iostream>

int main() {
    NeuralNet nn = NeuralNet(2,2,1);
    double[][][] xor_pat = [[[0,0], [0]],
                            [[0,1], [1]],
                            [[1,0], [1]],
                            [[1,1], [0]]];
    nn.train(xor_pat, 1000, 0.5, 0.2);
    nn.test(xor_pat);
    return 0;
}

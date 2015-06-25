#include "neural_net.h"
#include <iostream>

int main() {
    NeuralNet nn = NeuralNet(2,2,1);
    double ***xor_pat = new double **[4];
    for(int i = 0; i < 4; i++) {
        xor_pat[i] = new double*[2];
        xor_pat[i][0] = new double[2];
        xor_pat[i][0] = new double[1];
    }
    xor_pat[0][0][0] = 0; xor_pat[0][0][1] = 0; xor_pat[0][1][0] = 0;
    xor_pat[1][0][0] = 0; xor_pat[1][0][1] = 1; xor_pat[0][1][0] = 1;
    xor_pat[2][0][0] = 1; xor_pat[2][0][1] = 0; xor_pat[0][1][0] = 1;
    xor_pat[3][0][0] = 1; xor_pat[3][0][1] = 1; xor_pat[0][1][0] = 0;
    nn.train(xor_pat, 1000, 0.5, 0.2, 4);
    nn.print_test(xor_pat, 4);
    return 0;
}

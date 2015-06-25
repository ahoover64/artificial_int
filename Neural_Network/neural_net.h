#ifndef __Neural_Net_H__
#define __Neural_Net_H__
#include <memory>


class NeuralNet {
public:
    NeuralNet(int nInput, int nOutput, int nLayers);
    // Passing an array with multiple values creates a multi-layered network
    NeuralNet(int nInput, int nOutput, int nLayers[]);
    NeuralNet(const NeuralNet &);
    NeuralNet& operator=(const NeuralNet &);
    ~NeuralNet();
    // Other methods for implementation
    double** weights(int layer);
    void train(double ***pattern, int iterations, double learn_rate, double momentum, int num_patterns);
    //double* test(double ***patterns);
    void print_test(double ***patterns, int num_patterns);
private:
    class Impl;
    std::shared_ptr<Impl> mImpl;
};

#endif // __Neural_Net_H__

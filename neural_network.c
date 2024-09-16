#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "neural_network.h"

// Função de ativação Sigmoid
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Função de feedforward para IA CRM
void feedforward(double *input, double *weights, double *output, int input_size, int output_size) {
    for (int i = 0; i < output_size; i++) {
        output[i] = 0.0;
        for (int j = 0; j < input_size; j++) {
            output[i] += input[j] * weights[i * input_size + j];
        }
        output[i] = sigmoid(output[i]);
    }
}

// Função para processamento de dados do CRM usando Sea Learning
void process_crm_data(double *crm_data, int data_size, double *output) {
    // IA aplicando a rede neural aos dados do CRM (simplificado)
    double weights[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6};  // Exemplo de pesos para a rede neural
    feedforward(crm_data, weights, output, data_size, 1);
}

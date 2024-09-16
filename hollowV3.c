#include <stdio.h>
#include <fann.h>

// Função para criar e treinar a rede neural
void create_and_train_neural_network() {
    // Definindo o número de neurônios na rede neural
    const unsigned int num_input = 10;   // Número de entradas (ajuste conforme necessário)
    const unsigned int num_hidden = 20;  // Número de neurônios na camada oculta
    const unsigned int num_output = 1;   // Número de saídas (ajuste conforme necessário)

    // Criando uma rede neural com 3 camadas: entrada, oculta e saída
    struct fann *ann = fann_create_standard(3, num_input, num_hidden, num_output);
    
    // Configurando as funções de ativação
    fann_set_activation_function_hidden(ann, FANN_SIGMOID);
    fann_set_activation_function_output(ann, FANN_SIGMOID);

    // Definindo os dados de treinamento
    struct fann_train_data *train_data = fann_create_train(2, num_input, num_output);

    // Exemplo de dados fictícios para treinamento
    // Cada linha representa um exemplo de treinamento com entrada e saída esperada
    fann_set_input(train_data, 0, (float[]){1, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    fann_set_output(train_data, 0, (float[]){1});
    fann_set_input(train_data, 1, (float[]){0, 1, 0, 0, 0, 0, 0, 0, 0, 0});
    fann_set_output(train_data, 1, (float[]){1});

    // Treinando a rede neural
    fann_train_on_data(ann, train_data, 1000, 10, 0.01);
    
    // Salvando a rede neural treinada em um arquivo
    fann_save(ann, "neural_network.net");

    // Liberando memória dos dados de treinamento e da rede neural
    fann_destroy_train(train_data);
    fann_destroy(ann);
}

// Função para carregar a rede neural e realizar previsões
void predict_with_neural_network() {
    // Carregando a rede neural treinada
    struct fann *ann = fann_create_from_file("neural_network.net");

    // Dados de entrada para previsão
    float input[10] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    float *output;

    // Realizando a previsão
    output = fann_run(ann, input);
    printf("Prediction: %f\n", output[0]);

    // Liberando a memória da rede neural
    fann_destroy(ann);
}

int main() {
    // Criar e treinar a rede neural
    create_and_train_neural_network();

    // Realizar previsões com a rede neural treinada
    predict_with_neural_network();

    return 0;
}

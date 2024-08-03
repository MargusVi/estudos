import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import sys

# Função de ativação sigmoide e sua derivada
def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def sigmoid_derivative(x):
    return x * (1 - x)

# Inicialização dos pesos
def initialize_weights(layers):
    weights = []
    for i in range(len(layers) - 1):
        weights.append(np.random.randn(layers[i], layers[i + 1]) * np.sqrt(2.0 / layers[i]))
    return weights

# Forward pass
def forward_pass(inputs, weights):
    activations = [inputs]
    for w in weights:
        net_inputs = np.dot(activations[-1], w)
        activations.append(sigmoid(net_inputs))
    return activations

# Backpropagation
def back_propag(activations, weights, expected_output):
    deltas = [expected_output - activations[-1]]
    for i in reversed(range(len(weights))):
        deltas.append(deltas[-1].dot(weights[i].T) * sigmoid_derivative(activations[i]))
    deltas.reverse()
    return deltas

# Atualização dos pesos
def update_weights(weights, activations, deltas, learning_rate):
    for i in range(len(weights)):
        weights[i] += activations[i].T.dot(deltas[i + 1]) * learning_rate
    return weights

# Cálculo do erro médio quadrático
def calculate_mean_squared_error(outputs, targets):
    return np.mean(np.square(outputs - targets))

# Treinamento do MLP
def train_mlp(inputs, outputs, layers, learning_rate, precision):
    epochArray = []
    errorArray = []
    weights = initialize_weights(layers)
    previous_error = float('inf')
    epoch = 0
    while True:
        epoch += 1
        activations = forward_pass(inputs, weights)
        deltas = back_propag(activations, weights, outputs)
        weights = update_weights(weights, activations, deltas, learning_rate)
        current_error = calculate_mean_squared_error(activations[-1], outputs)
        print(f'Época {epoch}, Erro Médio Quadrático: {current_error:.6f}')
        if abs(previous_error - current_error) < precision:
            break
        previous_error = current_error
        epochArray.append(epoch)
        errorArray.append(current_error)
        if epoch > 100000:
            break
    return weights, epochArray, errorArray

# Previsão com MLP treinado
def predict(inputs, weights):
    activations = forward_pass(inputs, weights)
    return activations[-1]

# Normalizar os dados
def normalize_data(data):
    return (data - np.min(data, axis=0)) / (np.max(data, axis=0) - np.min(data, axis=0))

# Retornar listas dos inputs e outputs a partir dos arquivos .xls
def load_data(file_path):
    df = pd.read_excel(file_path)
    inputs = df.iloc[:, :4].values
    outputs = df.iloc[:, 4:7].values
    inputs = normalize_data(inputs) # Normalizar os dados de entrada
    return inputs, outputs

# Pós-processamento das saídas
def post_process_output(output):
    return np.where(output >= 0.5, 1, 0)

# Calcular porcentagem de acertos
def calculate_accuracy(predictions, targets):
    correct = np.sum(np.argmax(predictions, axis=1) == np.argmax(targets, axis=1))
    total = targets.shape[0]
    accuracy = (correct / total) * 100
    return correct, total - correct, accuracy

# Mapear classes para A, B, C
def map_classes(index):
    class_map = {0: 'A', 1: 'B', 2: 'C'}
    return class_map[index]

def main():
    # Carregar dados de treinamento e validação
    train_inputs, train_outputs = load_data('PP04_dados_treinamento.xls')
    val_inputs, val_outputs = load_data('PP04_dados_validacao.xls')
    
    # Estrutura da rede: 4 neurônios na entrada, 15 neurônios na camada escondida, 3 neurônio na saída
    layers = [4, 15, 3]

    # Parâmetros de treinamento
    learning_rate = 0.001 # Alterado para que os resultados fiquem mais perto do esperado
    precision = 1e-6

    # Treinamento da rede
    trained_weights, epochArray, errorArray = train_mlp(train_inputs, train_outputs, layers, learning_rate, precision)

    # Testando a rede treinada com dados de validação
    val_predictions = predict(val_inputs, trained_weights)

    # Pós-processamento das saídas para a classificação
    val_predictions_post_processed = post_process_output(val_predictions)
    val_pred_classes = np.argmax(val_predictions_post_processed, axis=1)
    val_true_classes = np.argmax(val_outputs, axis=1)
    
    # Calcular porcentagem de acertos
    correct, incorrect, accuracy = calculate_accuracy(val_predictions_post_processed, val_outputs)
    
    print("\nResultado obtido vs resultado esperado")
    for predicted, expected in zip(val_predictions_post_processed, val_outputs):
        print(f"Obtido: {list(predicted)}, Esperado: {list(expected)}")
    print(f"\nAcertos: {correct}, Erros: {incorrect}, Porcentagem de Acertos: {accuracy:.2f}%")

    print("\nResultado obtido vs resultado esperado")
    for predicted, expected in zip(val_pred_classes, val_true_classes):
        print(f"Obtido: {map_classes(predicted)}, Esperado: {map_classes(expected)}")
    print(f"\nAcertos: {correct}, Erros: {incorrect}, Porcentagem de Acertos: {accuracy:.2f}%")

    plt.scatter(epochArray, errorArray)
    plt.xlabel('Época')
    plt.ylabel('Erro Médio Quadrático')
    plt.title('Erro do treinamento')
    plt.show()

if __name__ == '__main__':
    sys.exit(main())
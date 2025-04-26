import numpy as np
import pandas as pd
import sys
import matplotlib.pyplot as plt

# Função para ler os arquivos de dados de treinamento e validação
def ler_arquivos_de_dados(caminho_treinamento, caminho_validacao):
    dados_treinamento = pd.read_excel(caminho_treinamento)
    dados_validacao = pd.read_excel(caminho_validacao)
    return dados_treinamento, dados_validacao

# Função para calcular a distância euclidiana entre dois pontos
def distancia_euclidiana(x1, x2):
    return np.linalg.norm(x1 - x2)

# Função para calcular o valor da função gaussiana
def gaussiana(x, centro, sigma):
    return np.exp(-distancia_euclidiana(x, centro)**2 / (2 * sigma**2))

# Função para realizar o primeiro estágio de treinamento (K-means)
def primeiro_estagio_treinamento(X, n1):
    # Seleção aleatória dos centros iniciais dos clusters
    centros = X[np.random.choice(X.shape[0], n1, replace=False)]  
    
    # Loop para ajustar os centros até a convergência
    while True:
        grupos = {j: [] for j in range(n1)}
        
        # Atribuição dos pontos de dados aos centros mais próximos
        for k in range(len(X)):
            xk = X[k]
            distancias = [distancia_euclidiana(xk, centros[j]) for j in range(n1)]
            j_min = np.argmin(distancias)
            grupos[j_min].append(xk)
        
        # Cálculo dos novos centros dos clusters
        novos_centros = np.zeros_like(centros)
        for j in range(n1):
            if len(grupos[j]) > 0:
                novos_centros[j] = np.mean(grupos[j], axis=0)
        
        # Verificação de convergência (se os centros não mudaram)
        if np.allclose(centros, novos_centros):
            break
        
        centros = novos_centros
    
    # Cálculo da variância (sigma) de cada cluster
    sigma = np.zeros(n1)
    for j in range(n1):
        if len(grupos[j]) > 0:
            dist_quadrada = [distancia_euclidiana(xk, centros[j])**2 for xk in grupos[j]]
            sigma[j] = np.sqrt(np.mean(dist_quadrada))
    
    return centros, sigma

# Função para realizar o segundo estágio de treinamento (ajuste de pesos)
def segundo_estagio_treinamento(X, d, centros, sigma, taxa_aprendizado=0.01, epsilon=1e-7):
    n1 = len(centros)  # Número de neurônios na camada intermediária
    n2 = 1  # Número de saídas desejadas (nesse caso, uma única saída)
    
    # Inicialização dos pesos e do termo de bias (theta) com valores pequenos aleatórios
    W2 = np.random.randn(n1, n2) * 0.01
    theta = np.random.randn(n2) * 0.01
    
    erro_anterior = float('inf')  # Inicialização do erro anterior como infinito
    epoca = 0
    
    erros_medios = []  # Lista para armazenar o erro médio em cada época
    
    # Loop de treinamento até a convergência (ou seja, quando a mudança no erro for pequena)
    while True:
        erro_total = 0
        
        # Iteração sobre todos os exemplos de treinamento
        for k in range(len(X)):
            # Cálculo da saída da camada intermediária usando a função gaussiana
            g1 = np.array([gaussiana(X[k], centros[j], sigma[j]) for j in range(n1)])
            y = np.dot(g1, W2) - theta  # Cálculo da saída da rede
            erro = d[k] - y  # Cálculo do erro
            
            # Atualização dos pesos e do bias (usando a regra delta)
            W2 += taxa_aprendizado * erro * g1[:, np.newaxis]
            theta -= taxa_aprendizado * erro
            
            erro_total += erro**2  # Acumulação do erro quadrado
        
        # Cálculo do erro médio para a época atual
        erro_atual = erro_total / len(X)
        erros_medios.append(erro_atual)  # Armazenando o erro médio
        
        # Verificação de convergência (diferença de erro muito pequena)
        if abs(erro_anterior - erro_atual) <= epsilon:
            break
        
        erro_anterior = erro_atual  # Atualização do erro anterior
        epoca += 1  # Incremento do contador de épocas
    
    return W2, theta, erros_medios

# Função para a fase de operação (validação do modelo)
def fase_operacao(X, centros, sigma, W2, theta):
    n1 = len(centros)  # Número de neurônios na camada intermediária
    y_pred = np.zeros(X.shape[0])  # Inicialização do vetor de saídas previstas
    
    # Iteração sobre todos os exemplos de validação
    for k in range(len(X)):
        # Cálculo da saída da camada intermediária usando a função gaussiana
        g1 = np.array([gaussiana(X[k], centros[j], sigma[j]) for j in range(n1)])
        y_pred[k] = np.dot(g1, W2) - theta  # Cálculo da saída da rede
    
    return y_pred

# Função principal do programa
def main():
    # Definição dos caminhos dos arquivos de treinamento e validação
    caminho_treinamento = 'PP05_dados_treinamento.xls'
    caminho_validacao = 'PP05_dados_validacao.xls'
    
    # Definição dos hiperparâmetros
    taxa_aprendizado = 0.01
    epsilon = 1e-7
    
    # Leitura dos dados de treinamento e validação
    dados_treinamento, dados_validacao = ler_arquivos_de_dados(caminho_treinamento, caminho_validacao)
    
    # Extração das características (X) e das saídas (y) dos dados
    X_treino = dados_treinamento[['x1', 'x2']].values
    y_treino = dados_treinamento['d'].values
    X_valid = dados_validacao[['x1', 'x2']].values
    y_valid = dados_validacao['d'].values
    
    # Filtrando os padrões com presença de radiação (d == 1)
    X_treino_com_rad = X_treino[y_treino == 1]

    # Número de neurônios na camada intermediária
    n1 = 2

    # Executando o primeiro estágio de treinamento (K-means)
    centros, sigma = primeiro_estagio_treinamento(X_treino_com_rad, n1)
    
    # Exibindo os centros e as variâncias (sigma) dos clusters
    print("Centros dos clusters com presença de radiação:")
    print(centros)
    print("Variância (sigma) de cada cluster:")
    print(sigma)
    
    # Executando o segundo estágio de treinamento e coletando os erros médios
    W2, theta, erros_medios = segundo_estagio_treinamento(X_treino, y_treino, centros, sigma, taxa_aprendizado, epsilon)
    
    # Exibindo os pesos e o bias após o segundo estágio de treinamento
    print("Pesos após o segundo estágio de treinamento:")
    print(W2)
    print("Theta:")
    print(theta)
    
    # Fase de operação (validação do modelo)
    y_pred = fase_operacao(X_valid, centros, sigma, W2, theta)

    # Pós-processamento das saídas para determinar as classes previstas
    y_post = np.where(y_pred >= 0, 1, -1)

    # Calculando a precisão do modelo
    precisao = np.mean(y_post == y_valid) * 100

    # Impressão das saídas
    print("Saída antes do pós-processamento (y):")
    print(y_pred)
    print("Saída após o pós-processamento (y_post):")
    print(y_post)
    print(f'Precisão na validação: {precisao:.2f}%')

    # Comparação lado a lado de y_post e y_valid
    print("\nComparação entre y_post e y_valid:")
    for pred, real in zip(y_post, y_valid):
        print(f"Previsto: {pred}, Esperado: {real}")
    
    # Gráfico do erro médio ao longo das épocas
    plt.plot(erros_medios)
    plt.title('Erro Médio ao Longo das Épocas')
    plt.xlabel('Épocas')
    plt.ylabel('Erro Médio')
    plt.grid(True)
    plt.show()
    
    return 0

# Ponto de entrada do programa
if __name__ == '__main__':
    sys.exit(main())
import random

# Passo 1: Obter o conjunto de amostras de treinamento (x)
amostras = [
    [-0.6508,   0.1097,     4.0009],
    [-1.4492,   0.8896,     4.4005],
    [2.0850,    0.6876,     12.0710],
    [0.2626,    1.1476,     7.7985],
    [0.6418,    1.0234,     7.0427],
    [0.2569,    0.6730,     8.3265],
    [1.1155,    0.6043,     7.4446],
    [0.0914,    0.3399,     7.0677],
    [0.0121,    0.5256,     4.6316],
    [-0.0429,   0.4660,     5.4323],
    [0.4340,    0.6870,     8.2287],
    [0.2735,    1.0287,     7.1934],
    [0.4839,    0.4851,     7.4850],
    [0.4089,    -0.1267,    5.5019],
    [1.4391,    0.1614,     8.5843],
    [-0.9115,   -0.1973,    2.1962],
    [0.3654,    1.0475,     7.4858],
    [0.2144,    0.7515,     7.1699],
    [0.2013,    1.0014,     6.5489],
    [0.6483,    0.2183,     5.8991],
    [-0.1147,   0.2242,     7.2435],
    [-0.7970,   0.8795,     3.8762],
    [-1.0625,   0.6366,     2.4707],
    [0.5307,    0.1285,     5.6883],
    [-1.2200,   0.7777,     1.7252],
    [0.3957,    0.1076,     5.6623],
    [-0.1013,   0.5989,     7.1812],
    [2.4482,    0.9455,     11.2095],
    [2.0149,    0.6192,     10.9263],
    [0.2012,    0.2611,     5.4631]
]

# Passo 2: Associar a saída desejada (d) para cada amostra obtida
resultados = [
    -1.0000,
    -1.0000,
    -1.0000,
    1.0000,
    1.0000,
    -1.0000,
    1.0000,
    -1.0000,
    1.0000,
    1.0000,
    -1.0000,
    1.0000,
    -1.0000,
    -1.0000,
    -1.0000,
    -1.0000,
    1.0000,
    1.0000,
    1.0000,
    1.0000,
    -1.0000,
    1.0000,
    1.0000,
    1.0000,
    1.0000,
    -1.0000,
    -1.0000,
    1.0000,
    -1.0000,
    1.0000
]

# Passo 3: Iniciar o vetor w com valores aleatórios pequenos
w = [random.uniform(-0.01, 0.01) for _ in range(len(amostras[0]))]

# Passo 4: Especificar a taxa de aprendizagem (n)
taxa_aprendizagem = 0.1

# Passo 5: Iniciar o contador de número de épocas
epoca = 0
max_epoca = 100000

# Passo 6: Repetir as instruções até que o erro seja "inexiste"
erro = True
while erro and epoca < max_epoca:
    # Passo 6.1: erro <- "inexiste"
    erro = False
    
    # Passo 6.2: Para todas as amostras de treinamento {x, d}, fazer:
    for i in range(len(amostras)):
        # Passo 6.2.1: u <- w * x
        u = sum(x * y for x, y in zip(w, amostras[i]))
        
        # Passo 6.2.2: y <- sinal(u)
        y = 1 if u >= 0 else -1
        
        # Passo 6.2.3: Se y != d, então:
        if y != resultados[i]:
            # Passo 6.2.3.1: w <- w + n * (d - y) * x
            w = [w[j] + taxa_aprendizagem * (resultados[i] - y) * amostras[i][j] for j in range(len(amostras[0]))]
            erro = True
    
    # Passo 6.3: época <- época + 1
    epoca += 1
    print(epoca)

# Fim do algoritmo Perceptron - Fase de Treinamento
print("Pesos finais:", w)
print("Épocas:", epoca)

# Função para classificar uma amostra utilizando o vetor de pesos ajustado
def classificar_amostra(amostra, pesos):
    # Calcula u
    u = sum(x * y for x, y in zip(pesos, amostra))
    # Calcula y (sinal de u)
    y = 1 if u >= 0 else -1
    # Retorna a classe correspondente à saída y
    return "Classe A" if y == -1 else "Classe B"
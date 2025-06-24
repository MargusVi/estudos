import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from scipy.stats import skew, kurtosis

# --- Parâmetros Globais ---
# Define o tamanho padrão para as figuras geradas pelo Matplotlib
plt.rcParams['figure.figsize'] = (15, 8)
# Define o estilo dos gráficos do Seaborn
sns.set_theme(style="whitegrid")
ARQUIVO_NORMAL = 'Dataset_Power Quality Disturbance/Pure_Sinusoidal.csv'
ARQUIVO_ANORMAL = 'Dataset_Power Quality Disturbance/Harmonics.csv'

# --- 1. Organização dos Dados ---
def carregar_e_organizar_dados(arquivo_normal, arquivo_anormal):
    # Organização dos sinais em dataframes de modo que as N primeiras colunas/posições sejam ocupadas pela classe "Anormal" e as N seguintes pela classe "Normal"
    # Carrega os dados dos arquivos CSV, transpõe e concatena os dataframes
    try:
        # Carregar dados da classe anormal (Harmonics)
        df_anormal = pd.read_csv(arquivo_anormal, header=None)
        # Carregar dados da classe normal (Pure_Sinusoidal)
        df_normal = pd.read_csv(arquivo_normal, header=None)
    except FileNotFoundError as e:
        print(f"Erro: arquivo não encontrado: {e}")
        return None, 0, 0

    # Transpor os dataframes (sinais como colunas, amostras como linhas)
    df_anormal_T = df_anormal.T
    df_normal_T = df_normal.T

    num_sinais_anormais = df_anormal_T.shape[1]
    num_sinais_normais = df_normal_T.shape[1]

    print(f"Número de sinais 'anormais' ({arquivo_anormal}): {num_sinais_anormais}")
    print(f"Número de sinais 'normais' ({arquivo_normal}): {num_sinais_normais}")
    print(f"Número de amostras por sinal: {df_anormal_T.shape}")

    # Renomear colunas para facilitar identificação
    df_anormal_T.columns = [f'Anormal_{i+1}' for i in range(num_sinais_anormais)]
    df_normal_T.columns = [f'Normal_{i+1}' for i in range(num_sinais_normais)]

    # Concatenar: anormais primeiro, depois normais
    df_combinado = pd.concat([df_anormal_T, df_normal_T], axis=1)

    print(f"\nDimensões do dataframe anormal transposto: {df_anormal_T.shape}")
    print(f"Dimensões do dataframe normal transposto: {df_normal_T.shape}")
    print(f"Dimensões do dataframe combinado: {df_combinado.shape}")

    return df_combinado

# --- 2. Extração dos atributos ---
def extrair_atributos(sinais_df):
    # a). Calcular os atributos para cada coluna (sinal) usando axis=0.
    atributos_dict = {
        'Max': sinais_df.max(axis=0),
        'Min': sinais_df.min(axis=0),
        'RMS': np.sqrt(np.mean(np.square(sinais_df), axis=0)),
        'Energia': np.sum(np.square(sinais_df), axis=0),
        'Media': sinais_df.mean(axis=0),
        'Desvio_Padrao': sinais_df.std(axis=0),
        'Skewness': skew(sinais_df, axis=0), 
        'Kurtosis': kurtosis(sinais_df, axis=0)
    }
    
    # b). Criar o DataFrame de atributos a partir do dicionário.
    atributos_df = pd.DataFrame(atributos_dict)
    
    # c). Adicionar a coluna 'Classe' com base no nome do sinal (que está no índice).
    atributos_df['Classe'] = np.where(atributos_df.index.str.contains('Anormal'), 'Anormal', 'Normal')
    
    print("\nAtributos extraídos com sucesso.")
    return atributos_df

# --- 3. Plotagem dos atributos ---
def plotar_atributos(atributos_df):
    # Nomes dos atributos a serem plotados
    nomes_atributos = atributos_df.columns.drop('Classe')
    num_atributos = len(nomes_atributos)

    print("\n--- 3. Análise Visual dos Atributos ---")
    print("Gerando gráficos para visualizar a separação das classes por atributo...")

    # Cria uma figura com subplots para cada atributo
    fig, axes = plt.subplots(nrows=2, ncols=4, figsize=(20, 10))
    axes = axes.flatten() # Transforma a matriz de eixos em um vetor para facilitar a iteração

    for i, nome_attr in enumerate(nomes_atributos):
        sns.boxplot(x='Classe', y=nome_attr, data=atributos_df, ax=axes[i], hue='Classe', palette=['#ff6347', '#4682b4'], legend=False)
        axes[i].set_title(f'Distribuição de: {nome_attr}', fontsize=12)
        axes[i].set_xlabel('Classe', fontsize=10)
        axes[i].set_ylabel('Valor', fontsize=10)
    
    # Remove eixos não utilizados se o número de atributos for ímpar
    for j in range(i + 1, len(axes)):
        fig.delaxes(axes[j])

    plt.tight_layout(pad=3.0)
    plt.suptitle("Distribuição dos Atributos por Classe", fontsize=16, y=1.02)
    plt.show()

# --- 4. Ranqueamento com Fisher ---
def calcular_fisher_discriminant_ratio(atributos_df):
    print("\n--- 4. Ranqueamento de Atributos com a Razão Discriminante de Fisher ---")
    
    scores_fisher = {}
    classes = atributos_df['Classe'].unique()
    
    # Itera sobre cada atributo (coluna), exceto a coluna 'Classe'
    for attr in atributos_df.columns.drop('Classe'):
        # Separa os valores do atributo para cada classe
        valores_c1 = atributos_df[atributos_df['Classe'] == classes[0]][attr]
        valores_c2 = atributos_df[atributos_df['Classe'] == classes[1]][attr]
        
        # Calcula as médias e desvios padrão para cada classe
        media_c1, media_c2 = np.mean(valores_c1), np.mean(valores_c2)
        std_c1, std_c2 = np.std(valores_c1), np.std(valores_c2)
        
        # Fórmula da Razão Discriminante de Fisher
        # Garante que não haverá divisão por zero se um desvio padrão for nulo
        if (std_c1**2 + std_c2**2) > 0:
            score = (media_c1 - media_c2)**2 / (std_c1**2 + std_c2**2)
        else:
            score = 0
            
        scores_fisher[attr] = score
        
    # Converte o dicionário de scores em uma Série do pandas e ordena
    ranking_fisher = pd.Series(scores_fisher).sort_values(ascending=False)
    
    print("Ranking dos atributos (do melhor para o pior) com base em Fisher:")
    print(ranking_fisher)
    return ranking_fisher

#  --- 5. Análise de Correlação ---
def analisar_correlacao(atributos_df):
    print("\n--- 5. Seleção de Atributos por Correlação ---")

    # a) Correlação entre os próprios atributos para eliminar redundância
    print("\na) Análise de correlação entre atributos:")
    atributos_numeric = atributos_df.drop('Classe', axis=1)
    matriz_corr = atributos_numeric.corr()

    plt.figure(figsize=(10, 8))
    sns.heatmap(matriz_corr, annot=True, cmap='coolwarm', fmt=".2f", linewidths=.5)
    plt.title('Matriz de Correlação entre Atributos')
    plt.show()
    
    print("A matriz de correlação acima mostra a relação linear entre os atributos.")
    print("Valores próximos de 1 ou -1 indicam alta correlação e possível redundância.")

    # b) Correlação com um vetor de saídas
    print("\nb) Análise de correlação dos atributos com a classe de saída:")
    
    # Cria um vetor de saída: +1 para 'Anormal', -1 para 'Normal'
    vetor_saida = atributos_df['Classe'].apply(lambda x: 1 if x == 'Anormal' else -1)
    
    corr_com_saida = atributos_numeric.corrwith(vetor_saida)
    corr_com_saida = corr_com_saida.abs().sort_values(ascending=False) # Usa o valor absoluto

    print("Correlação (absoluta) de cada atributo com o vetor de saída (+1/-1):")
    print(corr_com_saida)

    plt.figure(figsize=(10, 6))
    sns.barplot(x=corr_com_saida.index, y=corr_com_saida.values, hue=corr_com_saida.index, palette='viridis', legend=False)
    plt.title('Correlação dos Atributos com a Classe de Saída')
    plt.xlabel('Atributos')
    plt.ylabel('Correlação Absoluta')
    plt.xticks(rotation=45)
    plt.show()

def main():
    # 1. Carrega os dados dos arquivos
    df_sinais = carregar_e_organizar_dados(ARQUIVO_NORMAL, ARQUIVO_ANORMAL)

    if df_sinais is not None:
        # 2. Extração dos atributos
        df_atributos = extrair_atributos(df_sinais)
        print("\nAmostra da tabela de atributos:")
        print(df_atributos.head())

        # 3. Plotagem dos atributos para análise visual
        plotar_atributos(df_atributos)
        
        # 4. Ranqueamento com Fisher
        ranking = calcular_fisher_discriminant_ratio(df_atributos)
        
        # Compara o ranking de Fisher com a análise visual
        print("\nVerificação da análise visual com o ranking de Fisher:")
        print(f"Os 3 melhores atributos segundo Fisher: {list(ranking.index[:3])}")
        print(f"Os 3 piores atributos segundo Fisher: {list(ranking.index[-3:])}")
        
        # 5. Análise de Correlação
        analisar_correlacao(df_atributos)

if __name__ == '__main__':
    main()
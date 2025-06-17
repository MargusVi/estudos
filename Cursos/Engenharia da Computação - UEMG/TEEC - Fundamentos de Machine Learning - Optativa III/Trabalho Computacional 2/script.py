import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from scipy.stats import skew, kurtosis

# --- Configurações Globais ---
# Define o tamanho padrão para as figuras geradas pelo Matplotlib
plt.rcParams['figure.figsize'] = (15, 8)
# Define o estilo dos gráficos do Seaborn
sns.set_theme(style="whitegrid")

# --- Nomes dos Arquivos ---
ARQUIVO_NORMAL = 'Dataset_Power Quality Disturbance/Pure_Sinusoidal.csv'
ARQUIVO_ANORMAL = 'Dataset_Power Quality Disturbance/Harmonics.csv'

# --- Funções Auxiliares ---

def carregar_dados(arquivo_normal, arquivo_anormal):
    """
    Carrega os dados dos arquivos CSV, atribui as classes e os combina em um único DataFrame.

    Args:
        arquivo_normal (str): Caminho para o arquivo CSV com os dados da classe 'Normal'.
        arquivo_anormal (str): Caminho para o arquivo CSV com os dados da classe 'Anormal'.

    Returns:
        pandas.DataFrame: DataFrame contendo todos os sinais com uma coluna 'Classe'.
    """
    try:
        df_normal = pd.read_csv(arquivo_normal, header=None)
        df_anormal = pd.read_csv(arquivo_anormal, header=None)

        # Adiciona a coluna 'Classe' para identificar a origem dos dados
        df_normal['Classe'] = 'Normal'
        df_anormal['Classe'] = 'Anormal'

        # Combina os dois DataFrames em um só
        df_combinado = pd.concat([df_anormal, df_normal], ignore_index=True)
        print("Dados carregados e organizados com sucesso.")
        print(f"Total de sinais da classe 'Anormal': {len(df_anormal)}")
        print(f"Total de sinais da classe 'Normal': {len(df_normal)}")
        return df_combinado
    except FileNotFoundError as e:
        print(f"Erro: Arquivo não encontrado - {e}. Verifique os caminhos dos arquivos.")
        return None

def extrair_atributos(sinais_df):
    """
    Extrai um conjunto de atributos estatísticos de cada sinal (linha) no DataFrame.

    Args:
        sinais_df (pandas.DataFrame): DataFrame onde cada linha é um sinal.

    Returns:
        pandas.DataFrame: DataFrame com os atributos extraídos para cada sinal.
    """
    # Isola apenas os dados do sinal, excluindo a coluna 'Classe'
    dados_sinais = sinais_df.drop('Classe', axis=1)
    
    atributos = pd.DataFrame(index=sinais_df.index)
    
    # 1. Valor Máximo
    atributos['Max'] = dados_sinais.max(axis=1)
    # 2. Valor Mínimo
    atributos['Min'] = dados_sinais.min(axis=1)
    # 3. Valor Eficaz (RMS)
    atributos['RMS'] = np.sqrt(np.mean(np.square(dados_sinais), axis=1))
    # 4. Energia
    atributos['Energia'] = np.sum(np.square(dados_sinais), axis=1)
    # 5. Média
    atributos['Media'] = dados_sinais.mean(axis=1)
    # 6. Desvio Padrão
    atributos['Desvio_Padrao'] = dados_sinais.std(axis=1)
    # 7. Skewness (Assimetria)
    atributos['Skewness'] = dados_sinais.apply(skew, axis=1)
    # 8. Kurtosis (Curtose)
    atributos['Kurtosis'] = dados_sinais.apply(kurtosis, axis=1)
    
    # Adiciona a coluna 'Classe' de volta para análises futuras
    atributos['Classe'] = sinais_df['Classe']
    
    print("\nAtributos extraídos com sucesso.")
    return atributos

def plotar_atributos(atributos_df):
    """
    Plota boxplots para cada atributo para visualizar a separação entre as classes.

    Args:
        atributos_df (pandas.DataFrame): DataFrame contendo os atributos e a coluna 'Classe'.
    """
    # Nomes dos atributos a serem plotados
    nomes_atributos = atributos_df.columns.drop('Classe')
    num_atributos = len(nomes_atributos)

    print("\n--- 1. Análise Visual dos Atributos ---")
    print("Gerando gráficos para visualizar a separação das classes por atributo...")

    # Cria uma figura com subplots para cada atributo
    fig, axes = plt.subplots(nrows=2, ncols=4, figsize=(20, 10))
    axes = axes.flatten() # Transforma a matriz de eixos em um vetor para facilitar a iteração

    for i, nome_attr in enumerate(nomes_atributos):
        sns.boxplot(x='Classe', y=nome_attr, data=atributos_df, ax=axes[i], palette=['#ff6347', '#4682b4'])
        axes[i].set_title(f'Distribuição de: {nome_attr}', fontsize=12)
        axes[i].set_xlabel('Classe', fontsize=10)
        axes[i].set_ylabel('Valor', fontsize=10)
    
    # Remove eixos não utilizados se o número de atributos for ímpar
    for j in range(i + 1, len(axes)):
        fig.delaxes(axes[j])

    plt.tight_layout(pad=3.0)
    plt.suptitle("Distribuição dos Atributos por Classe", fontsize=16, y=1.02)
    plt.show()

def calcular_fisher_discriminant_ratio(atributos_df):
    """
    Calcula e ranqueia os atributos com base na Razão Discriminante de Fisher.

    Args:
        atributos_df (pandas.DataFrame): DataFrame com os atributos e a coluna 'Classe'.

    Returns:
        pandas.Series: Série com os atributos ranqueados pelo score de Fisher.
    """
    print("\n--- 2. Ranqueamento de Atributos com a Razão Discriminante de Fisher ---")
    
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

def analisar_correlacao(atributos_df):
    """
    Realiza a análise de correlação entre os atributos e com a saída.

    Args:
        atributos_df (pandas.DataFrame): DataFrame com os atributos e a coluna 'Classe'.
    """
    print("\n--- 3. Seleção de Atributos por Correlação ---")

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
    sns.barplot(x=corr_com_saida.index, y=corr_com_saida.values, palette='viridis')
    plt.title('Correlação dos Atributos com a Classe de Saída')
    plt.xlabel('Atributos')
    plt.ylabel('Correlação Absoluta')
    plt.xticks(rotation=45)
    plt.show()

# --- Função Principal de Execução ---
def main():
    """
    Função principal que orquestra a execução do script.
    """
    # Carrega os dados dos arquivos
    df_sinais = carregar_dados(ARQUIVO_NORMAL, ARQUIVO_ANORMAL)

    if df_sinais is not None:
        # 1. Extração dos atributos
        df_atributos = extrair_atributos(df_sinais)
        print("\nAmostra da tabela de atributos:")
        print(df_atributos.head())

        # 2. Plotagem dos atributos para análise visual
        plotar_atributos(df_atributos)
        
        # 3. Ranqueamento com Fisher
        ranking = calcular_fisher_discriminant_ratio(df_atributos)
        
        # Compara o ranking de Fisher com a análise visual
        print("\nVerificação da análise visual com o ranking de Fisher:")
        print(f"Os 3 melhores atributos segundo Fisher: {list(ranking.index[:3])}")
        print(f"Os 3 piores atributos segundo Fisher: {list(ranking.index[-3:])}")
        print("Compare este resultado com os gráficos gerados para verificar se a separação visual corresponde ao ranking numérico.")

        # 4. Análise de Correlação
        analisar_correlacao(df_atributos)

if __name__ == '__main__':
    main()
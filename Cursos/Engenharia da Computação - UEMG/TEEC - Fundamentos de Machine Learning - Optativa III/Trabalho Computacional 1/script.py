import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.fft import fft, fftfreq
from scipy import signal as sig

# --- Parâmetros globais ---
ARQUIVO_NORMAL = 'Dataset_Power Quality Disturbance/Pure_Sinusoidal.csv'
ARQUIVO_ANORMAL = 'Dataset_Power Quality Disturbance/Harmonics.csv'
N_AMOSTRAS = 100            # Número de amostras por sinal
FREQ_AMOSTRAGEM = 5000      # Frequência de amostragem em Hz (assumindo fundamental de 50Hz e 100 amostras/ciclo)
FREQ = 50                   # Hz
N_SINAIS_PARA_PLOTAR = 3    # Número de sinais de cada classe para plotar

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

    return df_combinado, num_sinais_anormais, num_sinais_normais

# --- 2. Visualização no domínio do tempo ---
def visualizar_sinais_tempo(df, num_sinais_anormais, num_sinais_normais, n_plot=3):
    # Escolha aleatória de três sinais de cada classe e visualização dos mesmos no domínio do tempo (isto é, obtenção dos gráficos temporais dos sinais)
    if df is None:
        return pd.DataFrame(), pd.DataFrame() # Retornar dataFrames vazios caso haja algum problema

    # Verificar se há sinais suficientes para plotar
    n_plot_anormais = min(n_plot, num_sinais_anormais)
    n_plot_normais = min(n_plot, num_sinais_normais)

    if n_plot_anormais == 0 and n_plot_normais == 0:
        print("Não há sinais suficientes para plotar.")
        return pd.DataFrame(), pd.DataFrame()

    sinais_anormais_plot = pd.DataFrame()
    sinais_normais_plot = pd.DataFrame()

    if n_plot_anormais > 0:
        # Selecionar índices aleatórios para sinais anormais
        indices_anormais_plot = np.random.choice(num_sinais_anormais, n_plot_anormais, replace=False)
        sinais_anormais_plot = df.iloc[:, indices_anormais_plot]
    
    if n_plot_normais > 0:
        # Selecionar índices aleatórios para sinais normais
        indices_normais_plot = np.random.choice(num_sinais_normais, n_plot_normais, replace=False)
        sinais_normais_plot = df.iloc[:, num_sinais_anormais + indices_normais_plot]

    tempo = np.arange(N_AMOSTRAS) # Vetor de amostras (0 a N_AMOSTRAS-1)

    # Ajustar o número de colunas do subplot dinamicamente
    num_cols_subplot = max(n_plot_anormais, n_plot_normais)
    if num_cols_subplot == 0: # Caso não haja sinais para plotar
        return sinais_anormais_plot, sinais_normais_plot

    plt.figure(figsize=(4 * num_cols_subplot, 8)) # Ajustar tamanho da figura
    plt.suptitle('Sinais selecionados no domínio do tempo', fontsize=16)

    for i in range(n_plot_anormais):
        # Plotar sinais anormais
        plt.subplot(2, num_cols_subplot, i + 1)
        plt.plot(tempo, sinais_anormais_plot.iloc[:, i])
        plt.title(f'Sinal anormal: {sinais_anormais_plot.columns[i]}')
        plt.xlabel('Número da amostra')
        plt.ylabel('Amplitude')
        plt.grid(True)

    for i in range(n_plot_normais):
        # Plotar sinais normais
        plt.subplot(2, num_cols_subplot, i + 1 + num_cols_subplot)
        plt.plot(tempo, sinais_normais_plot.iloc[:, i])
        plt.title(f'Sinal normal: {sinais_normais_plot.columns[i]}')
        plt.xlabel('Número da amostra')
        plt.ylabel('Amplitude')
        plt.grid(True)

    plt.tight_layout(rect=[0, 0, 1, 0.96])
    plt.show()
    
    return sinais_anormais_plot, sinais_normais_plot

# --- 3. Emprego e visualização da Transformada de Fourier (FFT) ---
def analisar_sinais_frequencia(sinais_anormais, sinais_normais, fs, n_samples, n_plot=3):
    # Emprego da Transformada de Fourier (FFT) para os sinais escolhidos na etapa anterior e visualização do espectro de frequências do mesmo
    if sinais_anormais.empty and sinais_normais.empty:
        print("Nenhum sinal encontrado.")
        return

    n_plot_anormais = sinais_anormais.shape[1]
    n_plot_normais = sinais_normais.shape[1]
    num_cols_subplot = max(n_plot_anormais, n_plot_normais)

    if num_cols_subplot == 0:
        return

    plt.figure(figsize=(4 * num_cols_subplot, 8)) # Ajustar tamanho da figura
    plt.suptitle('Transformada de Fourier (FFT) dos sinais selecionados', fontsize=16)

    # Frequências para o eixo X da FFT (apenas positivas)
    freq_axis = fftfreq(n_samples, 1/fs)[:n_samples//2]

    for i in range(n_plot_anormais):
        # FFT para sinais anormais
        sinal_anormal_atual = sinais_anormais.iloc[:, i]
        fft_anormal = fft(sinal_anormal_atual.values)
        magnitude_anormal = np.abs(fft_anormal)[:n_samples//2] # Pegar apenas a metade positiva

        plt.subplot(2, num_cols_subplot, i + 1)
        plt.plot(freq_axis, magnitude_anormal)
        plt.title(f'FFT sinal anormal: {sinais_anormais.columns[i]}')
        plt.xlabel('Frequência (Hz)')
        plt.ylabel('Magnitude')
        plt.grid(True)
        plt.xlim(0, fs/10) # Limitar eixo X para melhor visualização (ex: até 500 Hz se FS=5000)

    for i in range(n_plot_normais):
        # FFT para sinais normais
        sinal_normal_atual = sinais_normais.iloc[:, i]
        fft_normal = fft(sinal_normal_atual.values)
        magnitude_normal = np.abs(fft_normal)[:n_samples//2] # Pegar apenas a metade positiva
        
        plt.subplot(2, num_cols_subplot, i + 1 + num_cols_subplot)
        plt.plot(freq_axis, magnitude_normal)
        plt.title(f'FFT sinal normal: {sinais_normais.columns[i]}')
        plt.xlabel('Frequência (Hz)')
        plt.ylabel('Magnitude')
        plt.grid(True)
        plt.xlim(0, fs/10) # Limitar eixo X

    plt.tight_layout(rect=[0, 0, 1, 0.96])
    plt.show()

# --- 4. Filtragem digital (filtro IIR Butterworth Passa-Baixas) ---
def aplicar_e_visualizar_filtro(nome_sinal, sinais_originais, freq, n_amostras):
    # Realização da filtragem digital dos sinais e visualização das respostas em frequência dos mesmos
    sinal_original = sinais_originais.values

    # Parâmetros do filtro
    ordem_filtro = 4
    freq_corte = 300            # Hz (atenuar harmônicas acima da 5a para 50Hz)
    nyquist_freq = 0.5 * freq
    freq_corte_normalizada = freq_corte / nyquist_freq

    # Projetar o filtro Butterworth passa-baixas
    b, a = sig.butter(ordem_filtro, freq_corte_normalizada, btype='low', analog=False)

    # Aplicar o filtro
    sinal_filtrado = sig.lfilter(b, a, sinal_original)

    # Visualizar resposta em frequência do filtro
    w, h = sig.freqz(b, a, worN=8000, fs=freq)
    plt.figure(figsize=(9.6, 8)) # Ajustar tamanho da figura
    plt.subplot(3, 1, 1)
    plt.plot(w, np.abs(h))
    plt.title(f'Resposta em frequência do filtro Butterworth (Corte: {freq_corte} Hz)')
    plt.xlabel('Frequência (Hz)')
    plt.ylabel('Ganho')
    plt.grid(True)
    plt.axvline(freq_corte, color='red', linestyle='--', label=f'Freq. Corte ({freq_corte} Hz)')
    plt.legend()

    # Visualizar sinal original vs. filtrado no domínio do tempo
    tempo = np.arange(n_amostras)
    plt.subplot(3, 1, 2)
    plt.plot(tempo, sinal_original, label='Sinal original')
    plt.plot(tempo, sinal_filtrado, label='Sinal filtrado', linestyle='--')
    plt.title(f'Sinal "{nome_sinal}" original vs. filtrado (Tempo)')
    plt.xlabel('Número da Amostra')
    plt.ylabel('Amplitude')
    plt.legend()
    plt.grid(True)

    # Visualizar FFT do sinal original vs. filtrado
    freq_axis = fftfreq(n_amostras, 1/freq)[:n_amostras//2]

    fft_original = fft(sinal_original)
    magnitude_original = np.abs(fft_original)[:n_amostras//2]

    fft_filtrado = fft(sinal_filtrado)
    magnitude_filtrado = np.abs(fft_filtrado)[:n_amostras//2]

    plt.subplot(3, 1, 3)
    plt.plot(freq_axis, magnitude_original, label='FFT original')
    plt.plot(freq_axis, magnitude_filtrado, label='FFT filtrado', linestyle='--')
    plt.title(f'FFT Sinal "{nome_sinal}" original vs. filtrado')
    plt.xlabel('Frequência (Hz)')
    plt.ylabel('Magnitude')
    plt.legend()
    plt.grid(True)
    plt.xlim(0, freq/5) # Limitar eixo X para melhor visualização

    plt.tight_layout()
    plt.show()

# --- Execução Principal ---
if __name__ == '__main__':
    print("--- Iniciando pré-processamento de Sinais ---")

    # 1. Organização dos Dados
    print("\n--- 1. Organização dos dados ---")
    df_combinado, num_anormais, num_normais = carregar_e_organizar_dados(ARQUIVO_NORMAL, ARQUIVO_ANORMAL)

    if df_combinado is not None:
        # 2. Visualização no domínio do tempo
        print(f"\n--- 2. Visualização de até {N_SINAIS_PARA_PLOTAR} Sinais Aleatórios no Domínio do Tempo ---")
        sinais_anormais_selecionados, sinais_normais_selecionados = visualizar_sinais_tempo(
            df_combinado, num_anormais, num_normais, n_plot=N_SINAIS_PARA_PLOTAR
        )

        # 3. Transformada de Fourier (FFT)
        if not sinais_anormais_selecionados.empty or not sinais_normais_selecionados.empty:
            print(f"\n--- 3. Emprego e visualização da Transformada de Fourier (FFT) ---")
            analisar_sinais_frequencia(
                sinais_anormais_selecionados, sinais_normais_selecionados, 
                FREQ_AMOSTRAGEM, N_AMOSTRAS, n_plot=N_SINAIS_PARA_PLOTAR
            )

            # 4. Filtragem digital (IIR Butterworth Passa-Baixas)
            if not sinais_anormais_selecionados.empty:
                print("\n--- 4. Filtragem digital (IIR Butterworth Passa-Baixas) ---")
                sinal_anormal_nome = sinais_anormais_selecionados.columns
                sinal_anormal_dados = sinais_anormais_selecionados.iloc[:, 0]
                aplicar_e_visualizar_filtro(sinal_anormal_nome, sinal_anormal_dados, FREQ_AMOSTRAGEM, N_AMOSTRAS)
            else:
                print("\nNenhum sinal anormal selecionado para demonstrar a filtragem.")
        else:
            print("\nNão foi possível selecionar sinais para análise de frequência e filtragem.")
    else:
        print("\nProcessamento interrompido devido a erro no carregamento dos dados.")
        
    print("\n--- Pré-processamento Concluído ---")
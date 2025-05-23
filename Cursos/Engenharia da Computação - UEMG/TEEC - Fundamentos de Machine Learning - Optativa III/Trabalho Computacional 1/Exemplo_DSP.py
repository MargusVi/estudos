# -*- coding: utf-8 -*-
"""

@author: Arismar Jr
"""

import numpy as np                        # Biblioteca para trabalho com vetores e matrizes
import matplotlib.pyplot as plt           # Biblioteca para plotar figuras
from scipy.fft import rfft, rfftfreq      # Biblioteca para obtenção da FFT
from scipy.signal import butter, lfilter, freqz, filtfilt # Biblioteca para implementação do filtro digital

# A FFT da biblioteca scipy contém mais recursos que aquela da biblioteca numpy

plt.close('all')  # Fechando todas as figuras
# ============================================================================

# Definindo parâmetros
fs = 10000;  # Frequência de amostragem
tf = 1;      # Tempo de duração dos sinais

# Função para geração de sinais senoidais
def generate_sin_wave(freq, sample_rate, duration):
    t = np.linspace(0, duration, sample_rate * duration, endpoint=False)  # Vetor tempo
    f = t*freq
    y = np.sin((2*np.pi)*f) # Sinal
    return t,y

t, x1 = generate_sin_wave(60, fs, tf)
t, x2 = generate_sin_wave(180, fs, tf)

y = 1*x1 + 0.5*x2 # Sinais somados
    
# Plotando sinais gerados no domínio do tempo
plt.figure()
plt.subplot(3,1,1)
plt.plot(t, x1)
plt.ylabel('x1')
#plt.title('Sinal senoidal com frequência de 60 Hz')
plt.subplot(3,1,2)
plt.plot(t,x2)
plt.ylabel('x2')
#plt.title('Sinal senoidal com frequência de 180 Hz')
plt.subplot(3,1,3)
plt.plot(t, y)
plt.xlabel('t (s)')
plt.ylabel('y = x1 + x2')
#plt.title('Sinais senoidais somados')
plt.show()

# ============================================================================
# Espectro de frequências obtido por meio da FFT (algoritmo que implementa a DFT)

N = len(y); # Comprimento do sinal

yf = rfft(y);                             # Cálculo da transformada de Fourier
ff = rfftfreq(N,1/fs);                    # Cálculo do eixo de frequências
yf_abs_norm = np.abs(yf)/max(np.abs(yf)); # Tomando a amplitude e normalizando

# O comando rfft() e rfftfreq() retorna apenas a parte positiva do espectro gerado 
# pelos comandos fft() e fftfreq()

plt.figure()
plt.plot(ff,yf_abs_norm)  
plt.xlabel('f (Hz)')
plt.show()

# ============================================================================
# Filtro Passa-baixas para remoção da componente de 180 Hz

# Função para implementação do filtro
def butter_lowpass(cutoff,sample_rate,order):
    return butter(order, cutoff, fs=sample_rate, btype='low', analog=False)

# Parâmetros para filtragem do sinal
fc = 100;   # Frequência de corte
nfilt = 7; # Ordem do filtro

# Obtenção dos coeficientes do filtro
b,a = butter_lowpass(fc,fs,nfilt);

# Resposta em frequência do filtro
w,h = freqz(b,a,fs=fs);

plt.figure()
plt.plot(w,np.abs(h),'b')
plt.axvline(fc, linestyle='--', color='r')
plt.title("Resposta em frequência do filtro desenvolvido")
plt.xlabel('f [Hz]')

# Filtragem do sinal
y_filt = lfilter(b,a,y);

plt.figure()
plt.plot(t,y,label='Sinal original')
plt.plot(t,y_filt,color='r', label='Sinal filtrado')
plt.legend()

# ============================================================================
# Espectro de frequências do sinal filtrado

N_filt = len(y_filt); # Comprimento do sinal

yf_filt = rfft(y_filt);                             # Cálculo da transformada de Fourier
ff_filt = rfftfreq(N_filt,1/fs);                    # Cálculo do eixo de frequências
yfilt_abs_norm = np.abs(yf_filt)/max(np.abs(yf_filt)); # Tomando a amplitude e normalizando

# O comando rfft() e rfftfreq() retorna apenas a parte positiva do espectro gerado 
# pelos comandos fft() e fftfreq()

plt.figure()
plt.plot(ff_filt,yfilt_abs_norm)  
plt.xlabel('f (Hz)')
plt.show()





